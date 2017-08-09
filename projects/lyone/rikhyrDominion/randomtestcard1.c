#include "dominion/dominion.h"
#include "asserttrue.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Test effect of playing minion

#define MAX_TESTS 10 

int testMinion() {

	printf("\nTEST BEGAN\n");
	
	srand(time(NULL));

	int all_passed = 1; 
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

	int i, j, choice1, choice2, numPlayers, player, seed;

	int preHC[MAX_PLAYERS], postHC[MAX_PLAYERS];	//each player's hand count before and after playing minion
	int preDC[MAX_PLAYERS], postDC[MAX_PLAYERS];	//each player's discard count before and after playing minion

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
			preDC[j] = G.discardCount[j];
			preHC[j] = G.handCount[j]; 
		}	

		//choices to play minion
		choice1 = rand() % 2;
		choice2 = choice1 ^ 1;	//The opposite of choice1

		player = rand() % numPlayers;
		printf("Player %d's turn\n", player + 1);
		
		G.hand[player][0] = minion;
		G.whoseTurn = player;

		msg_fmt = "Playing minion with choice1 and choice2 set to %d and %d, respectively\n"; 
		all_passed &= asserttrue(playCard(0, choice1, choice2, 0, &G), 0, '=', 1, msg_fmt, choice1, choice2);
		
		//Save the hand count and discard count of each player AFTER the game
		for(j = 0; j < numPlayers; ++j){
			postDC[j] = G.discardCount[j];
			postHC[j] = G.handCount[j]; 
		}	

		if(choice1){
			//Check each player's discard count and hand count after the game
			msg_fmt = "Player %d's %s count before and after minion is played: %d %d\n";
			for(j = 0; j < numPlayers; ++j){
				if(j == player){
					all_passed &= asserttrue(preHC[j] - postHC[j], 1, '=', 1, msg_fmt, j + 1, "hand", preHC[j], postHC[j]);
					all_passed &= asserttrue(preDC[j], postDC[j], '=', 1, msg_fmt, j +1, "discard", preDC[j], postDC[j]);
				}
				else{
					all_passed &= asserttrue(preHC[j], postHC[j], '=', 1, msg_fmt, j + 1, "hand", preHC[j], postHC[j]);
					all_passed &= asserttrue(preDC[j], postDC[j], '=', 1, msg_fmt, j +1, "discard", preDC[j], postDC[j]);
				}
			}
			
		}
		else if(choice2){
			//Check each player's discard count and hand count after the game
			msg_fmt = "Player %d's %s count before and after minion is played: %d %d\n";
			for(j = 0; j < numPlayers; ++j){
				if(j == player){
					all_passed &= asserttrue(postHC[j], 4, '=', 1, msg_fmt, j + 1, "hand", preHC[j], postHC[j]);
					all_passed &= asserttrue(preDC[j], postDC[j], '=', 1, msg_fmt, j +1, "discard", preDC[j], postDC[j]);
				}
				else{
					all_passed &= asserttrue2(postHC[j], 4, "<=", 1, msg_fmt, j + 1, "hand", preHC[j], postHC[j]);
					all_passed &= asserttrue(preDC[j], postDC[j], '=', 1, msg_fmt, j +1, "discard", preDC[j], postDC[j]);
				}
			}
		}
	}
	if(all_passed)
		printf("\nTEST COMPLETED SUCCESSFULLY\n");
	else
		printf("\nTEST FAILED\n");
	return 0;
}
int main()
{
	printf("\nTesting effect of playing minion\n");
	testMinion();
	printf("\n\n");
}
