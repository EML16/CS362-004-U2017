/*
 *  randomtestcard2.c
  	Random test for smithy 
*/

#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include "asserttrue.h"
#include "dominion.h"

#define MAX_TESTS 4 

int testSmithyEffect()
{
	printf("\nTEST BEGAN\n");

	int all_passed = 1;
	char *fmt; 
	
	srand(time(NULL)); 
	
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	struct gameState G;
	
	int i, player, numPlayers, preHandCount, preActionCount, postHandCount, postActionCount, seed;

	for (i = 0; i < MAX_TESTS; i++) {
		numPlayers = 2 + (rand() % (MAX_PLAYERS - 1));
		printf("\nTest %d. a %d-player game\n", i + 1, numPlayers);

		player = rand() % numPlayers;
		printf("Player %d's turn\n", player + 1);

		seed = rand();		//pick random seed
		initializeGame(numPlayers, k, seed, &G);

		G.hand[player][0] = smithy;
		G.handCount[player] = rand() % MAX_HAND;
		G.numActions = 1 + rand() % 10;
		G.whoseTurn = player;

		//save the hand count and action count before smithy is played
		preHandCount = numHandCards(&G);
		preActionCount = G.numActions;

		fmt = "Playing smithy\n";	
		all_passed &= asserttrue(playCard(0, 0, 0, 0, &G), 0, '=', 1, fmt);
		
		//save the hand count and action count after smithy is played
		postHandCount = numHandCards(&G);
		postActionCount = G.numActions;

		fmt = "Hand count before and after playing smithy: %d %d\n";
		
		// +3 cards 
		all_passed &= asserttrue(postHandCount, (preHandCount + 3 - 1), '=', 1, fmt, preHandCount, postHandCount);
		
		fmt = "Action count before and after playing smithy: %d %d\n";
		// discard smithy
		all_passed &= asserttrue(postActionCount, (preActionCount - 1), '=', 1, fmt, preActionCount, postActionCount);
	
	}

	if(all_passed)
		printf("\nTEST COMPLETED SUCCESSFULLY\n");
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
