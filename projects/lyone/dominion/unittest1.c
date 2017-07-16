#include <stdio.h>
#include "asserttrue.h"

int compare(const void* a, const void* b);	//Defined in dominion.c

int testCompare()
{
	printf("\nTEST BEGAN\n");

	int all_passed = 1;
	int n1, n2;
	char *fmt = "compare(%d, %d)\n";

	n1 = 10;
	n2 = 11;
	//Should return -1 
	all_passed &= asserttrue(compare(&n1, &n2), -1, '=', 1, fmt, n1, n2);

	n1 = 11;
	n2 = 11;
	//Should return 0 
	all_passed &= asserttrue(compare(&n1, &n2), 0, '=', 1, fmt, n1, n2);

	n1 = 12;
	n2 = 11;
	//Should return 1 
	all_passed &= asserttrue(compare(&n1, &n2), 1, '=', 1, fmt, n1, n2);

	if(all_passed)
		printf("TEST COMPLETED SUCCESSFULLY\n");
	else
		printf("TEST FAILED\n");

	return 0;
}

int main()
{
	printf("\n\nTesting compare() defined in dominion.c\n");
	testCompare();
	printf("\n\n");
	return 0;
}
