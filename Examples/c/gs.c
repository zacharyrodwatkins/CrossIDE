/* gs.c:
Solves an sparse system of linear equations using the Gauss-Seidel method
Written by Jesús Calviño-Fraga October, 2006-2011*/

// ~C51~

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <DE2_8052.h>
#include "gs.h"

#define HEAP_SIZE 0x180

//The DE2-8052 softcore clock is 33.33MHz
#define CLK 33333333L
#define BAUD 115200L
#define TIMER_2_RELOAD (0x10000L-(CLK/(32L*BAUD)))
#define LOW(X)  (X%0x100)
#define HIGH(X) (X/0x100)

#define xyz printf("%f")

__xdata char _c51_heap[HEAP_SIZE];
const unsigned int _c51_heap_size = HEAP_SIZE;

void inituart (void)
{
	RCAP2H=HIGH(TIMER_2_RELOAD);
	RCAP2L=LOW(TIMER_2_RELOAD);
	T2CON=0x34; // #00110100B
	SCON=0x52; // Serial port in mode 1, ren, txrdy, rxempty
}

void putchar (char c)
{
	if (c=='\n')
	{
		while (!TI);
		TI=0;
		SBUF='\r';
	}
	while (!TI);
	TI=0;
	SBUF=c;
}

char getchar (void)
{
	char c;
	
	while (!RI);
	RI=0;
	c=SBUF;
	return c;
}

void exit (int j)
{
	while(1);
	j;
}

#define log10(x) log10f(x)
#define fabs(x) fabsf(x)

// Adds an element to the sparse matrix of a linear system of equations.
// Notice that if the element has a value already, the new value will be
// added to it.  Also notice that simetry is not assumed, therefore both
// g(i,j) and g(j,i) will be stored, even if they are equal.  This works
// out fine with the MNA formulation of electric circuits.
void add_syseq(_syseq * syseq, int row, int col, double value) reentrant
{
    int i;

    if(value==0.0) return; //Preserve sparsity

	//The diagonal element
    if(row==col)
    {
        syseq->eq[row].g+=value;
        return;
    }
    
    //Check the off diagonal elements to see if this element has been added already
    for(i=0; i < syseq->eq[row].n; i++)
    {
        if (col==syseq->eq[row].eqn[i])
        {
            syseq->eq[row].gij[i]+=value;
            return;
        }
    }
    
    //Increase the size of the 'gif' and 'eqn' arrays by one
    syseq->eq[row].gij=realloc(syseq->eq[row].gij, (syseq->eq[row].n+1)*sizeof(double));
    if((void *)syseq->eq[row].gij==NULL)
    {
    	printf("ERROR: not enough memory for 'gij' array.\n");
    }
    
    syseq->eq[row].eqn=realloc(syseq->eq[row].eqn, (syseq->eq[row].n+1)*sizeof(int));
    if((void *)syseq->eq[row].eqn==NULL)
    {
    	printf("ERROR: not enough memory for 'eq' array.\n");
    }
    
    //Add the new off-diagonal element
    syseq->eq[row].gij[syseq->eq[row].n]=value;
    syseq->eq[row].eqn[syseq->eq[row].n]=col;
    syseq->eq[row].n++;
}

//Allocate and initialize a system of equations.
_syseq * create_syseq(int order, int maxiter, double tol, double alpha) reentrant
{
    int j;
    _syseq * syseq=NULL;

    syseq=malloc(sizeof(_syseq));
    if(syseq==NULL)
    {
    	printf("ERROR: not enough memory for system of equations.\n");
    	exit(1);
    }
    
    syseq->eq=malloc(order*sizeof(_eq));
    if(syseq->eq==NULL)
    {
    	printf("ERROR: not enough memory for equation.\n");
    	exit(1);
    }
    
    syseq->order=order;
    syseq->alpha=alpha;
    syseq->maxiter=maxiter;
    syseq->tol=tol;
    syseq->debug=0;
    
    for(j=0; j<order; j++)
    {
        syseq->eq[j].gij=NULL;
        syseq->eq[j].eqn=NULL;
        syseq->eq[j].n=0;
        syseq->eq[j].x=0;
        syseq->eq[j].b=0;
        syseq->eq[j].g=0;
    }
    return syseq;
}

//Free the vectors of off-diagonal elements and indeces.
void free_syseq(_syseq * syseq) reentrant
{
    int j;
    for(j=0; j<syseq->order; j++)
    {
        free(syseq->eq[j].gij);
        free(syseq->eq[j].eqn);
    }
}

//Evaluate the system of equations.  Uses the initial values of x, and
//produces a new set of values, also in x.
int eval_syseq(_syseq * syseq) reentrant
{
    int i, j, intol=1;
    double x;
    
    for(j=0; j<syseq->order; j++)
    {
        x=0.0;
        for(i=0; i<syseq->eq[j].n; i++)
        {
            x-=syseq->eq[j].gij[i]*syseq->eq[syseq->eq[j].eqn[i]].x;
        }
        x+=syseq->eq[j].b;
        x*=(syseq->alpha/syseq->eq[j].g);
        x+=((1.0-syseq->alpha)*syseq->eq[j].x);
        
        //See page 386 of "Numerical Analysis" 2nd edition by Burden, Faires, Reynolds
        if((fabs(x-syseq->eq[j].x)/fabs(x))>syseq->tol) intol=0;
        
        syseq->eq[j].x=x;
    }
    return intol;
}

//Display the the x's of a system of equations.
void print_syseq_x(_syseq * syseq) reentrant
{
	int j;
	int digits;
	char outfmt[20];
	
	digits=(int)log10(1.0/syseq->tol);
	sprintf(outfmt, "%%%d.%df", digits+3, digits-1);
	
	for(j=0; j<syseq->order; j++)
	{
		printf(outfmt, syseq->eq[j].x);
		if(j<(syseq->order-1))
			printf(", ");
		else
			printf("\n");
	}
}

//Solve a system of linear equations using the accelerated Gauss-Seidel
//iterative method.
int solve_syseq(_syseq * syseq) reentrant
{
	if(syseq->debug)
	{
		printf("x(%d)= ", 0);
		print_syseq_x(syseq);
	}

    for(syseq->numiter=1; syseq->numiter!=syseq->maxiter; syseq->numiter++)
    {
    	int intol;
    	intol=eval_syseq(syseq);

		if(syseq->debug)
		{
			printf("x(%d)= ", syseq->numiter);
			print_syseq_x(syseq);
		}
    	
    	if(intol)
    	{
			if(syseq->debug)
    			printf("%d-digit accuracy reached in %d iterations\n", (int) log10(1.0/syseq->tol), syseq->numiter);
    		return 1;
    	}
    }
    
	if(syseq->debug)
	    printf("ERROR: %d-digit accuracy not reached in %d iterations\n", (int) log10(1.0/syseq->tol), syseq->numiter);
    return 0;

}

/*This saves one iteration when the initial guess is zero*/
void zero_start_syseq(_syseq * syseq) reentrant
{
	int j;
	for(j=0; j<syseq->order; j++)
		syseq->eq[j].x=syseq->eq[j].b/syseq->eq[j].g;
}

void main(void)
{
     _syseq * syseq;
	
	inituart();
	LEDRA=0;
	LEDRB=0;
	LEDRC=0;
	LEDG=0;
	
	printf("\n\nGauss-Seidel Solution of linear systems\nBy Jesus Calvino-Fraga (c) 2006-2011\n\n");	
	// Test system.  The solution is 1.0, 2.0, -1.0, 1.0

    syseq=create_syseq(4, 25, 1.0e-7, 1.0);
    
    add_syseq(syseq, 0, 0, 10.0);
    add_syseq(syseq, 0, 1, -1.0);
    add_syseq(syseq, 0, 2, 2.0);
    syseq->eq[0].b=6.0;

    add_syseq(syseq, 1, 0, -1.0);
    add_syseq(syseq, 1, 1, 11.0);
    add_syseq(syseq, 1, 2, -1.0);
    add_syseq(syseq, 1, 3, 3.0);
    syseq->eq[1].b=25.0;
    
    add_syseq(syseq, 2, 0, 2.0);
    add_syseq(syseq, 2, 1, -1.0);
    add_syseq(syseq, 2, 2, 10.0);
    add_syseq(syseq, 2, 3, -1.0);
    syseq->eq[2].b=-11.0;

    add_syseq(syseq, 3, 1, 3.0);
    add_syseq(syseq, 3, 2, -1.0);
    add_syseq(syseq, 3, 3, 8.0);
    syseq->eq[3].b=15.0;
    
    // zero_start_syseq(syseq);
	syseq->debug=1;
	solve_syseq(syseq);
    free_syseq(syseq);
    free(syseq);
    
	// The system below converges better when alpha=1.25. The solution
	// is: 3.0, 4.0, -5.0
    
    syseq=create_syseq(3, 25, 1.0e-7, 1.25);

    add_syseq(syseq, 0, 0, 4.0);
    add_syseq(syseq, 0, 1, 3.0);
    syseq->eq[0].b=24.0;

    add_syseq(syseq, 1, 0, 3.0);
    add_syseq(syseq, 1, 1, 4.0);
    add_syseq(syseq, 1, 2, -1.0);
    syseq->eq[1].b=30.0;
    
    add_syseq(syseq, 2, 1, -1.0);
    add_syseq(syseq, 2, 2, 4.0);
    syseq->eq[2].b=-24.0;

    syseq->eq[0].x=1;
    syseq->eq[1].x=1;
    syseq->eq[2].x=1;
    
	solve_syseq(syseq);
	printf("\nThe second system was solved in %d iterations with %d-digit accuracy:\n",
		syseq->numiter, (int) log10(1.0/syseq->tol));
	print_syseq_x(syseq);
    free_syseq(syseq);
    free(syseq);
    
}

