#include <stdlib.h>
#include <stdio.h>

void test1 (void);   // Function in file2.c
void test2 (char a); // Function in file3.c

void main (void)
{
	test1();
	test2(3);
}
