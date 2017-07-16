/*
 *  cardtest2.c
	 Unit test Feast
 */

#include <stdio.h> 
#include "asserttrue.h"
#include "dominion.h"

int testFeastEffect()
{
	printf("\nTEST BEGAN\n");

	int all_passed = 1;
	char *fmt; 

	int numPlayers = 2;
	int i;
	struct gameState G;

	int k[10] ={feast, council_room, smithy, tribute, ambassador, great_hall, remodel, mine, village, salvager};

	initializeGame(numPlayers, k, 10, &G);

	G.hand[0][0] = feast;

	G.whoseTurn = 1;
	
	int handCount = G.handCount[1];
	int deckCount = G.deckCount[1];
	int discardCount = G.discardCount[1];

	//Save hand before playing
	int temphand[MAX_HAND];
	for(i = 0; i < handCount; ++i)
	{
		temphand[i] = G.hand[1][i];
	}

	fmt = "Playing feast with village\n";	
	all_passed &= asserttrue(playCard(0, village, 0, 0, &G), 0, '=', 1, fmt);

	fmt = "Number of cards in hand: %d\n";
	all_passed &= asserttrue(G.handCount[1], handCount, '=', 1, fmt, handCount);

	for(i = 0; i < handCount; ++i)
	{
		all_passed &= asserttrue(temphand[i],  G.hand[1][i], '=', 1, "Player hand content after play\n");
	}

	fmt = "Number of cards in deck: %d\n";
	all_passed &= asserttrue(G.deckCount[1], deckCount, '=', 1, fmt, deckCount);

	fmt = "Number of cards in discard: %d\n";
	all_passed &= asserttrue(G.discardCount[1], discardCount + 1, '=', 1, fmt, discardCount);

	fmt = "Village card must be in discard\n";
	all_passed &= asserttrue(G.discard[1][0], village, '=', 1, fmt, village);


	if(all_passed)
		printf("TEST COMPLETED SUCCESSFULLY\n");
	else
		printf("TEST FAILED\n");

	return 0;
}

int main()
{
	printf("\n\nTesting feastEffect() defined in dominion.c\n");
	testFeastEffect();
	printf("\n\n");
	return 0;
}
