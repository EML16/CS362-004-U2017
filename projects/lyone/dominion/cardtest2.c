/*
 *  cardtest2.c
  	Unit test for the Smithy card of Dominion

*/
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include "asserttrue.h"
#include "dominion.h"

int testSmithyEffect()
{
	printf("\nTEST BEGAN\n");

	int all_passed = 1;
	char *fmt; 
	
	srand(time(NULL)); 
	
	int numPlayers = rand() % 3 + 2;
	int randomSeed = rand();
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	struct gameState G;
	
	initializeGame(numPlayers, k, randomSeed, &G);
	
	G.hand[0][0] = smithy;

	//save the hand count and action count before smithy is played
	int preHandCount = numHandCards(&G);
	int preActionCount = G.numActions;

	fmt = "Playing smithy\n";	
	all_passed &= asserttrue(playCard(0, 0, 0, 0, &G), 0, '=', 1, fmt);
	
	//save the hand count and action count after smithy is played
	int postHandCount = numHandCards(&G);
	int postActionCount = G.numActions;
		
	fmt = "Hand count before and after playing smithy: %d %d\n";
	// +3 cards 
	all_passed &= asserttrue(postHandCount, (preHandCount + 3 - 1), '=', 1, fmt, preHandCount, postHandCount);
	
	fmt = "Action count before and after playing smithy: %d %d\n";
	// discard smithy
	all_passed &= asserttrue(postActionCount, (preActionCount - 1), '=', 1, fmt, preActionCount, postActionCount);
	
	if(all_passed)
		printf("TEST COMPLETED SUCCESSFULLY\n");
	else
		printf("TEST FAILED\n");

	return 0;
}

int main()
{
	printf("\n\nTesting smithyEffect() defined in dominion.c\n");
	testSmithyEffect();
	printf("\n\n");
	return 0;
}
