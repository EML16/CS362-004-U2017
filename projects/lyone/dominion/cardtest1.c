#include <stdio.h>
#include <string.h>
#include "asserttrue.h"
#include "dominion.h"

int testAdventurerEffect()
{
	printf("\nTEST BEGAN\n");
	
	int all_passed = 1;
	struct gameState G;	
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

	initializeGame(2, k, 17, &G);

	int whoseTurn = G.whoseTurn;

	// make sure phase = 0, numActions > 0, handCount > 0
	G.phase = 0;
	G.numActions = G.numActions > 0 ? G.numActions : 1;
	G.handCount[whoseTurn] = G.handCount[whoseTurn] > 0 ? G.handCount[whoseTurn] : 1;

	// Save state before card effect
	G.hand[whoseTurn][0] = adventurer;
	G.discard[whoseTurn][0] = copper;
	G.discard[whoseTurn][1] = curse;
	G.discard[whoseTurn][2] = estate;
	G.discard[whoseTurn][3] = copper;
	G.deck[whoseTurn][0] = estate;
	G.deck[whoseTurn][1] = duchy;
	G.discardCount[whoseTurn] = 4;
	G.deckCount[whoseTurn] = 2;

	int coins = G.coins;

	// should shuffle deck and discard if < 2 treasure cards are revealed before
	// deck is empty
	// don't check return value of playCard because not unit test for playCard
	playCard(0, 0, 0, 0, &G);

	// test G after card effect
	all_passed &= asserttrue(G.whoseTurn, whoseTurn, '=', 1, "Whose turn?\n");
	all_passed &= asserttrue(G.coins, coins + 2, '=', 1, "Coins gained: %d\n", G.coins);

	if(all_passed)
		printf("TEST COMPLETED SUCCESSFULLY\n");
	else
		printf("TEST FAILED\n");

	return 0;
}

int main()
{
	printf("\n\nTesting adventurerEffect() defined in dominion.c\n");
	testAdventurerEffect();
	printf("\n\n");
	return 0;
}
