/*
   Real-Time Transients Program RTTP
   Copyright (c) Jesús Calviño-Fraga 2006

gs.h:
   Solves an sparse system of linear equations using the Gauss-Seidel method
*/

#ifdef C51_mcs51
#define double float
#else
#define reentrant
#endif
/*Data Structures*/

typedef struct
{
   double b;     // Constant value in Gx=b
   double g;     // Diagonal element
   double x;     // Estimate and Solution
   double * gij; // Off diagonal elements
   int * eqn;    // An index to the position of x that multiplies gij
   int n;        // Number of off-diagonal non-zero elements
} _eq;

typedef struct
{
   int order;    // The order of the system
   int maxiter;  // The maximum number of iteration before giving up
   int numiter;  // The number of iterations it took to solve the system
   double tol;   // The tolerance to stop iterating
   double alpha; // Acceleration factor for Gauss-Seidel method
   int debug;	 // Display debug information while running
   _eq * eq;     // The array of equations that compose the system
} _syseq;

/*Prototypes*/

void add_syseq (_syseq * syseq, int row, int col, double value) reentrant;
_syseq * create_syseq (int order, int maxiter, double tol, double alpha) reentrant;
void free_syseq (_syseq * syseq) reentrant;
int eval_syseq(_syseq * syseq) reentrant;
void print_syseq_x(_syseq * syseq) reentrant;
int solve_syseq(_syseq * syseq) reentrant;
void zero_start_syseq(_syseq * syseq) reentrant;


