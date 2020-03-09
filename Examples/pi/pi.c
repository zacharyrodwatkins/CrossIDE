/*
**  PI.C - Computes Pi to an arbitrary number of digits
*/

//  ~C51~  --code-size 0x8000 --xram-size 0x2000

#include<stdio.h>
#include<stdlib.h>
#include <DE2_8052.h>

#define HEAP_SIZE 0x1F80
__xdata char _c51_heap[HEAP_SIZE];
const unsigned int _c51_heap_size = HEAP_SIZE;

#define CLK 33333333L
#define BAUD 115200L
#define TIMER_2_RELOAD (0x10000L-(CLK/(32L*BAUD)))
#define LOW(X)  (X%0x100)
#define HIGH(X) (X/0x100)

xdata long kf, ks;
xdata long *mf, *ms;
xdata long cnt, n, temp, nd;
xdata long i;
xdata long col, col1;
xdata long loc, stor[21];

void shift(long *l1, long *l2, long lp, long lmod)
{
	long k;
	
	k = ((*l2) > 0 ? (*l2) / lmod: -(-(*l2) / lmod) - 1);
	*l2 -= k * lmod;
	*l1 += k * lp;
}

void yprint(long m)
{
	if (cnt<n)
	{
		if (++col == 11)
		{
			col = 1;
			if (++col1 == 6)
			{
				col1 = 0;
				printf("\n");
				printf("%4ld",m%10);
			}
			else  printf("%3ld",m%10);
		}
		else  printf("%ld",m);
		cnt++;
	}
}

void xprint(long m)
{
	long ii, wk, wk1;
	
	if (m < 8)
	{
		for (ii = 1; ii <= loc; )
		yprint(stor[(int)(ii++)]);
		loc = 0;
	}
	else
	{
		if (m > 9)
		{
			wk = m / 10;
			m %= 10;
			for (wk1 = loc; wk1 >= 1; wk1--)
			{
				wk += stor[(int)wk1];
				stor[(int)wk1] = wk % 10;
				wk /= 10;
			}
		}
	}
	stor[(int)(++loc)] = m;
}

void memerr(int errno)
{
    printf("\a\nOut of memory error #%d\n", errno);
    if (2 == errno) free(mf);
    while(1);
}

void main(void)
{
	int i=0;

	LEDRA=0;
	LEDRB=0;
	LEDRC=0;
	LEDG=0;
	
	stor[i++] = 0;

	RCAP2H=HIGH(TIMER_2_RELOAD);
	RCAP2L=LOW(TIMER_2_RELOAD);
	T2CON=0x34; // #00110100B
	SCON=0x52; // Serial port in mode 1, ren, txrdy, rxempty
	
	printf("Number of digits (max %d): ", (HEAP_SIZE/(2*sizeof(long)))-6);
	scanf("%ld", &n);
	
	if (NULL == (mf = calloc((size_t)(n + 3L), (size_t)sizeof(long))))
	    memerr(1);
	if (NULL == (ms = calloc((size_t)(n + 3L), (size_t)sizeof(long))))
	    memerr(2);
      
	printf("\nApproximation of PI to %ld digits\n", (long)n);
	cnt = 0;
	kf = 25;
	ks = 57121L;
	mf[1] = 1L;
	for (i = 2; i <= (int)n; i += 2)
	{
		mf[i] = -16L;
		mf[i+1] = 16L;
	}
	for (i = 1; i <= (int)n; i += 2)
	{
		ms[i] = -4L;
		ms[i+1] = 4L;
	}
	printf("\n 3.");
	while (cnt < n)
	{
		for (i = 0; ++i <= (int)n - (int)cnt; )
		{
			mf[i] *= 10L;
			ms[i] *= 10L;
		}
		for (i =(int)(n - cnt + 1); --i >= 2; )
		{
			temp = 2 * i - 1;
			shift(&mf[i - 1], &mf[i], temp - 2, temp * kf);
			shift(&ms[i - 1], &ms[i], temp - 2, temp * ks);
		}
		nd = 0;
		shift((long *)&nd, &mf[1], 1L, 5L);
		shift((long *)&nd, &ms[1], 1L, 239L);
		xprint(nd);
	}
	printf("\n\nCalculations Completed!\n");
	free(ms);
	free(mf);
}
