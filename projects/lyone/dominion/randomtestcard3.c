#include "dominion.h"
#include "asserttrue.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Test effect of playing minion

#define MAX_TESTS 3 

int testMinion() {

	printf("\nTEST BEGAN\n");
	
	srand(time(NULL));

	int all_passed = 1; 
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

	int i, j, choice1, choice2, numPlayers, player, seed, preCoins;

	int preHandCount[MAX_PLAYERS], postHandCount[MAX_PLAYERS];
	int preDiscardCount[MAX_PLAYERS], postDiscardCount[MAX_PLAYERS];

	struct gameState G;


	char *msg_fmt;
	printf("Performing %d random tests\n", MAX_TESTS);
	
	for (i = 0; i < MAX_TESTS; i++) {
		numPlayers = 2 + (rand() % (MAX_PLAYERS - 1));
		printf("\nTest %d. a %d-player game\n", i + 1, numPlayers);

		seed = rand();		//pick random seed
		
		initializeGame(numPlayers, k, seed, &G);

		for(j = 0; j < numPlayers; ++j){
			G.deckCount[j] = rand() % MAX_DECK; //Pick random deck size out of MAX DECK size
			G.discardCount[j] = rand() % MAX_DECK;
			G.handCount[j] = rand() % MAX_HAND;
		}

		//Save the hand count and discard count of each player BEFORE the game
		for(j = 0; j < numPlayers; ++j){
			preDiscardCount[j] = G.discardCount[j];
			preHandCount[j] = G.handCount[j]; 
		}	
		preCoins = G.coins;

		//choices to play minion
		choice1 = rand() % 2;
		choice2 = choice1 ^ 1;	//	

		player = rand() % numPlayers;
		printf("Player %d's turn\n", player + 1);
		
		G.hand[player][0] = minion;
		G.whoseTurn = player;

		msg_fmt = "Playing minion with choice1 and choice2 set to %d and %d, respectively\n"; 
		all_passed &= asserttrue(playCard(0, choice1, choice2, 0, &G), 0, '=', 1, msg_fmt, choice1, choice2);
		
		//Save the hand count and discard count of each player AFTER the game
		for(j = 0; j < numPlayers; ++j){
			postDiscardCount[j] = G.discardCount[j];
			postHandCount[j] = G.handCount[j]; 
		}	

		if(choice1){
			//Check the count of coins 
			msg_fmt = "Number of coins before and after minion is played: %d %d\n";
			all_passed &= asserttrue(preCoins + 2, G.coins, '=', 1, msg_fmt, preCoins, G.coins);	//The count count must increase by +2

			//Check each player's discard count and hand count after the game
			msg_fmt = "Player %d's %s count before and after minion is played: %d %d\n";
			for(j = 0; j < numPlayers; ++j){
				if(j == player){
					all_passed &= asserttrue(preHandCount[j] - postHandCount[j], 1, '=', 1, msg_fmt, j + 1, "hand", preHandCount[j], postHandCount[j]);
					all_passed &= asserttrue(preDiscardCount[j], postDiscardCount[j], '=', 1, msg_fmt, j +1, "discard", preDiscardCount[j], postDiscardCount[j]);
				}
				else{
					all_passed &= asserttrue(preHandCount[j], postHandCount[j], '=', 1, msg_fmt, j + 1, "hand", preHandCount[j], postHandCount[j]);
					all_passed &= asserttrue(preDiscardCount[j], postDiscardCount[j], '=', 1, msg_fmt, j +1, "discard", preDiscardCount[j], postDiscardCount[j]);
				}
			}
			
		}
		else if(choice2){
			//Check the count of coins 
			msg_fmt = "Number of coins before and after minion is played: %d %d\n";
			all_passed &= asserttrue(preCoins, G.coins, '=', 1, msg_fmt, preCoins, G.coins);	//The coin count must remain unchanged

			//Check each player's discard count and hand count after the game
			msg_fmt = "Player %d's %s count before and after minion is played: %d %d\n";
			for(j = 0; j < numPlayers; ++j){
				if(j == player){
					all_passed &= asserttrue(postHandCount[j], 4, '=', 1, msg_fmt, j + 1, "hand", preHandCount[j], postHandCount[j]);
					all_passed &= asserttrue(preDiscardCount[j], postDiscardCount[j], '=', 1, msg_fmt, j +1, "discard", preDiscardCount[j], postDiscardCount[j]);
				}
				else{
					all_passed &= asserttrue2(postHandCount[j], 4, "<=", 1, msg_fmt, j + 1, "hand", preHandCount[j], postHandCount[j]);
					all_passed &= asserttrue(preDiscardCount[j], postDiscardCount[j], '=', 1, msg_fmt, j +1, "discard", preDiscardCount[j], postDiscardCount[j]);
				}
			}
		}
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
	testMinion();
	printf("\n\n");
}
