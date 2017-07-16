#include <stdio.h>
#include <string.h>
#include "asserttrue.h"
#include "dominion.h"

int testIsGameOver()
{
	printf("\nTEST BEGAN\n");
	
	int all_passed = 1;
	
	struct gameState G;	

	memset(G.supplyCount, 1, sizeof(G.supplyCount));

	//Each supply is initialized to 1; hence, the game is not over
	all_passed &= asserttrue(isGameOver(&G), 0, '=', 1, "The game is not over when no supply is exhausted\n");

	//When only province pile is exhausted, the game is over
	G.supplyCount[province] = 0;
	all_passed &= asserttrue(isGameOver(&G), 1, '=', 1, "The game is over when province pile is exhausted\n");

	//When only two piles other than province are exhausted, the game is not over	
	G.supplyCount[province] = 1;
	G.supplyCount[smithy] = 0;
	G.supplyCount[adventurer] = 0;

	all_passed &= asserttrue(isGameOver(&G), 0, '=', 1, "The game is not over when two piles other than province are exhausted\n");

	//The game is over when three piles are exhausted
	G.supplyCount[mine] = 0;
	all_passed &= asserttrue(isGameOver(&G), 1, '=', 1, "The game is over when three piles are exhausted\n");
	
	//The game is over when more than three piles are exhausted
	G.supplyCount[minion] = 0;
	all_passed &= asserttrue(isGameOver(&G), 1, '=', 1, "The game is over when more than three piles are exhausted\n");

	if(all_passed)
		printf("TEST COMPLETED SUCCESSFULLY\n");
	else
		printf("TEST FAILED\n");

	return 0;
}

int main()
{
	printf("\n\nTesting isGameOver() defined in dominion.c\n");
	testIsGameOver();
	printf("\n\n");
	return 0;
}
