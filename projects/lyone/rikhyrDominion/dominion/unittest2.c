/*
* RR
* CS 362
* WhoseTurn() Unit Test
*
* 1. Check correct player move turn handling
*
* Check for occasional changes of game state inbetween testing runs.
* 
* 
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "compareStates.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main() 
{
    SelectStream(1);
	PutSeed(-1);
    int i, j, zeros; // auxilliary  vars
    int numPlayer = 4; // setting maximal count of players
    int k[10] = {adventurer, gardens, smithy, village, sea_hag, treasure_map, outpost, cutpurse, tribute, salvager};
    struct gameState G, copyG;
    int seed = floor(Random() * 1000);

    srand(time(NULL));
    printf ("\nTESTING whoseTurn():\n");
    
	
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    zeros = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    memcpy(&copyG, &G, sizeof(struct gameState)); // save the game state before we start checking isGameOver
	
	printf("Current player numbershould be 0 initially to see if whoseTurn() returns 0.\n");
    if (whoseTurn(&G) != 0)
    {
        printf("Current turn should be with player 0, but whoseTurn() was not 0.\n");
    }
    printf("Running 1000 random tests for first player deck count to verify shuffle is -1 when deck amount is 0.\n");
    for (i = 0; i < 1000; i++)
    {
        int localDeck = rand() % (numPlayer-1);
        G.whoseTurn = localDeck;
		zeros=whoseTurn(&G);
        if ((zeros<0)||(zeros>3))
        {
			printf("Test %d. Turn should be at player %d, but whoseTurn returned value out of allowed range: %d.\n",i,localDeck,zeros);
		}
		
        if (zeros != localDeck)
        {
            printf("Test %d: whoseTurn() failed to get correct turn.\n",i);
        }
        
    }
    printf("Done with  random testing.\n");
	
	G.deckCount[0]=10;
	G.deck[0][0]=curse;
	G.deck[0][1]=estate;
	G.deck[0][2]=duchy;
	G.deck[0][3]=province;
	G.deck[0][4]=copper;
	G.deck[0][5]=silver;
	G.deck[0][6]=gold;
	G.deck[0][7]=adventurer;
	G.deck[0][8]=smithy;
	G.deck[0][9]=gardens;
	
    
    for (j = 0; j < numPlayer; j++)
    {
    (cmpDeckCount(&G, &copyG, j)) ? printf("Deck Count has changed between copied and modified game state!\n"):printf("Deck Count untouched\n");
        
	(cmpDiscard(&G, &copyG, j)) ? printf("Discard deck has changed between copied and modified game state!\n"):printf("Discard deck untouched\n");
		
    (cmpDiscardCount(&G, &copyG, j)) ? printf("Discard count has been changed between copied and modified game state!\n"):printf("Discard count untouched\n");
        
	(cmpDeck(&G, &copyG, j)) ? printf("Deck has changed between copied and modified game state!\n"): printf("Deck untouched\n");
	
    }
    printf("Testing general game state variables if they've been changed ...\n");
    printf("This will test to see if our copied game state before we performed whoseTurn() testing is equal to the modified game state.\n");
    
    (cmpPlayedCards(&G, &copyG)) ? printf("PlayedCards has changed between copied and modified game state!\n"): printf("PlayedCards untouched!\n");
    (cmpPlayedCardCount(&G, &copyG)) ? printf("playedCardCount has changed between copied and modified game state!\n"): printf("PlayedCardsCount untouched\n");
    (cmpPhase(&G, &copyG)) ? printf("phase has changed between copied and modified game state!\n"):printf("phase untouched\n");
    (cmpWhoseTurn(&G, &copyG)) ? printf("WhoseTurn has changed between copied and modified game state!\n"):printf("WhooseTurn untouched\n"); 
    (cmpNumActions(&G, &copyG)) ? printf("numActions has changed between copied and modified game state!\n"):printf("numActions untouched\n");
    (cmpOutpostPlayed(&G, &copyG)) ? printf("OutpostPlayed has changed between copied and modified game state!\n"):printf("OutpostPlayed untouched\n");
    (cmpNumPlayers(&G, &copyG)) ? printf("NumPlayers has changed between copied and modified game state!\n"):printf("NumPlayers untouched\n");
    (cmpNumBuys(&G, &copyG)) ? printf("NumBuys has changed between copied and modified game state!\n"):printf("NumBuys untouched\n");
    (cmpOutpostTurn(&G, &copyG)) ? printf("OutpostTurn has changed between copied and modified game state!\n"):printf("OutpostTurn untouched\n");
    printf("Done checking game states.\n");
    printf("\nAll tests done for whoseTurn()!\n \n");
    return 0;
}