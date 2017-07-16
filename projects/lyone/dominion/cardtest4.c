#include <stdio.h>
#include <string.h>
#include "asserttrue.h"
#include "dominion.h"

int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus);

int testMinionEffect()
{
	printf("\nTEST BEGAN\n");
	
	int all_passed = 1, coins;
	char *fmt;
	struct gameState G;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

	initializeGame(2, k, 10, &G);
	coins = G.coins;	
	all_passed &= asserttrue(cardEffect(minion, 1, 0, 0, &G, 0, NULL), 0, '=', 1,  "Testing minion effect\n");
	all_passed &= asserttrue(G.numActions, 2, '=', 1, "Number of action is %d\n", G.numActions);
	all_passed &= asserttrue(G.handCount[whoseTurn(&G)], 4, '=', 1, "Hand count is %d\n", G.handCount[whoseTurn(&G)]);
	all_passed &= asserttrue(G.coins, coins + 2, '=', 1, "Number of coins is %d\n", G.coins);

	if(all_passed)
		printf("TEST COMPLETED SUCCESSFULLY\n");
	else
		printf("TEST FAILED\n");

	return 0;
}

int main()
{
	printf("\n\nTesting adventurerEffect() defined in dominion.c\n");
	testMinionEffect();
	printf("\n\n");
	return 0;
}
