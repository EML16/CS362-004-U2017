#include "dominion.h"
#include "asserttrue.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TESTS 3 

//int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus);

int testAdventurer() {

	printf("\nTEST BEGAN\n");
	
	srand(time(NULL));

	int all_passed = 1; 
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

	int i, j, numPlayers, player, handCount, deckCount, discardCount, seed;
	
	struct gameState G;

	int treasureCount = 0;

	char *msg_fmt;
	printf("Performing %d random tests\n", MAX_TESTS);
	
	for (i = 0; i < MAX_TESTS; i++) {
		numPlayers = 2 + (rand() % (MAX_PLAYERS - 1));
		printf("\nTest %d. a %d-player game\n", i + 1, numPlayers);

		player = rand() % numPlayers;
		printf("Player %d's turn\n", player + 1);

		seed = rand();		//pick random seed
		msg_fmt = "Game Initialization\n";
		all_passed &= asserttrue2(initializeGame(numPlayers, k, seed, &G),  0, "=", 1, msg_fmt);
		
		G.deckCount[player] = rand() % MAX_DECK; //Pick random deck size out of MAX DECK size
		G.discardCount[player] = rand() % MAX_DECK;
		G.handCount[player] = rand() % MAX_HAND;

		handCount = G.handCount[player];
		deckCount = G.deckCount[player];
		discardCount = G.discardCount[player];

		//To test coverage, make the player's deck empty
		if (seed % 3 == 0) {
			G.deckCount[player] = 0;
		}

		G.hand[player][0] = adventurer;
		G.whoseTurn = player;

		msg_fmt = "Playing adventurer\n";
		all_passed &= asserttrue(playCard(0, 0, 0, 0, &G), 0, '=', 1, msg_fmt);
		
		for (j = 0; j < G.handCount[player]; j++)
		{
			if (G.hand[player][j] == copper || G.hand[player][j] == silver || G.hand[player][j] == gold)
				treasureCount++;
		}
		
		all_passed &= asserttrue2(treasureCount, 2, "<=", 1, "Treasure count after playing adventure: %d\n", treasureCount);
		all_passed &= asserttrue2(G.handCount[player] - handCount, 2, "<=", 1, "Hand count before and after playing adventure: %d, %d\n", G.handCount[player], handCount);
		all_passed &= asserttrue2(deckCount, G.deckCount[player], ">=", 1, "Deck count before and after playing adventure: %d, %d\n", deckCount, G.deckCount[player]);
		all_passed &= asserttrue2(discardCount, G.discardCount[player], "<=", 1, "Discard count before and after playing adventure: %d, %d\n", discardCount, G.discardCount[player]);
	}


	if(all_passed)
		printf("TEST COMPLETED SUCCESSFULLY\n");
	else
		printf("TEST FAILED\n");
	return 0;
}
int main()
{

	printf("\n\nTesting playing adventurer defined in dominion.c\n");
	testAdventurer();
	printf("\n\n");
}
