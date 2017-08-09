/*
* RR
* CS 362
* getCost() Unit Test
*
* 1. Check correct cards cost processing.
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
	int costs[27]={0,2,5,8,0,3,6,6,5,4,4,5,4,4,3,4,3,5,3,5,3,4,2,5,4,4,4};
    srand(time(NULL));
    printf ("\nTESTING getCost():\n");
    
	
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    zeros = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    memcpy(&copyG, &G, sizeof(struct gameState)); // save the game state before we start checking isGameOver
	
    printf("Running 1000 random tests for checking cards values to verify getCost() is showing correct amount.\n");
    for (i = 0; i < 1000; i++)
    {
        int localDeck = rand() % 26;
        
		zeros=getCost(localDeck);
        if ((zeros<0)||(zeros>26))
        {
			printf("Test %d. Value should be %d, but getCost() returned value out of allowed range: %d.\n",i,localDeck,zeros);
		}
		
        if (zeros != costs[localDeck])
        {
            printf("Test %d - getCost() failed to get correct amount: %d instead of %d.\n",i,zeros,localDeck);
        }
        
    }
    printf("Done with  random testing.\n");
	
	   
    for (j = 0; j < numPlayer; j++)
    {
    (cmpDeckCount(&G, &copyG, j)) ? printf("Deck Count has changed between copied and modified game state!\n"):printf("Deck Count untouched\n");
        
	(cmpDiscard(&G, &copyG, j)) ? printf("Discard deck has changed between copied and modified game state!\n"):printf("Discard deck untouched\n");
		
    (cmpDiscardCount(&G, &copyG, j)) ? printf("Discard count has been changed between copied and modified game state!\n"):printf("Discard count untouched\n");
        
	(cmpDeck(&G, &copyG, j)) ? printf("Deck has changed between copied and modified game state!\n"): printf("Deck untouched\n");
	
    }
    printf("Testing general game state variables if they've been changed ...\n");
    printf("This will test to see if our copied game state before we performed shuffle testing is equal to the modified game state.\n");
    
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
    printf("\nAll tests done for getCost()!\n\n");
    return 0;
}