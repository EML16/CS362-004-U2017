#include "dominion/dominion.h"
#include "asserttrue.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TESTS 10 

int testAdventurer() {

	printf("\nTEST BEGAN\n");
	
	srand(time(NULL));

	int all_passed = 1; 
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

	int i, j, numPlayers, player, handCount, deckCount, discardCount, seed;
	
	struct gameState G;

	int treasureCount = 0;

	char *fmt;
	printf("Performing %d random tests\n", MAX_TESTS);
	
	for (i = 0; i < MAX_TESTS; i++) {
		numPlayers = 2 + (rand() % (MAX_PLAYERS - 1));
		printf("\nTest %d. a %d-player game\n", i + 1, numPlayers);

		player = rand() % numPlayers;
		printf("Player %d's turn\n", player + 1);

		seed = rand();		//pick random seed
		
		initializeGame(numPlayers, k, seed, &G);

		G.deckCount[player] = rand() % MAX_DECK; //Pick random deck size out of MAX DECK size
		G.discardCount[player] = rand() % MAX_DECK;
		G.handCount[player] = rand() % MAX_HAND;

		handCount = G.handCount[player];
		deckCount = G.deckCount[player];
		discardCount = G.discardCount[player];

		G.hand[player][0] = adventurer;
		G.whoseTurn = player;

		int treasureCount_before=0;
		for (j = 0; j < G.handCount[player]; j++)
		{
			if (G.hand[player][j] == copper || G.hand[player][j] == silver || G.hand[player][j] == gold)
				treasureCount_before++;
		}
		
		playCard(0, 0, 0, 0, &G); 
		
		for (j = 0; j < G.handCount[player]; j++)
		{
			if (G.hand[player][j] == copper || G.hand[player][j] == silver || G.hand[player][j] == gold)
				treasureCount++;
		}
		fmt = "Treausre count before and after playing adventure: %d, %d\n";
		all_passed &= asserttrue2(treasureCount_before - treasureCount, 2, "<=", 1, fmt, treasureCount_before, treasureCount);
		fmt = "Hand count before and after playing adventure: %d, %d\n";
		all_passed &= asserttrue2(G.handCount[player] - handCount, 2, "<=", 1, fmt, G.handCount[player], handCount);
		
		fmt = "Deck count before and after playing adventure: %d, %d\n";
		all_passed &= asserttrue2(deckCount, G.deckCount[player], ">=", 1, fmt,  deckCount, G.deckCount[player]);

		fmt = "Discard count before and after playing adventure: %d, %d\n";
		all_passed &= asserttrue2(discardCount, G.discardCount[player], "<=", 1, fmt, discardCount, G.discardCount[player]);
	}


	if(all_passed)
		printf("\nTEST COMPLETED SUCCESSFULLY\n");
	else
		printf("\nTEST FAILED\n");
	return 0;
}
int main()
{

	printf("\nTesting effect of playing adventurer\n");
	testAdventurer();
	printf("\n\n");
}
