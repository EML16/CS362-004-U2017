/*
* RR
* CS 362
* WhoseTurn() Unit Test
*
* 1. Test council_room();
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

int correct_council_room(int currentPlayer, struct gameState *state, int handPos)
{
int i;

      //+4 Cards
      for (i = 0; i < 4; i++) 
	{
	  drawCard(currentPlayer, state);
	}

      //+1 Buy
      state->numBuys++;

      //Each other player draws a card
      for (i = 0; i < state->numPlayers; i++)
	{
	  if ( i != currentPlayer )
	    {
	      drawCard(i, state);
	    }
	}

      //put played card in played card pile
      discardCard(handPos, currentPlayer, state, 0);

      return 0;
}

int main() 
{int randomSeed;
    SelectStream(1);
	PutSeed(-1);
    int i, r, j, locVal1, locVal2, zeros; // auxilliary  vars
    int numPlayer = 4; // setting maximal count of players
    int k[10] = {adventurer, gardens, smithy, village, council_room, treasure_map, outpost, cutpurse, tribute, salvager};
    struct gameState G, copyG;
    int seed = floor(Random() * 1000);

    srand(time(NULL));
    printf ("\nTESTING council_room\n");
    
	

    
	for (i=0; i<1000; i++)
	{
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
	memcpy(&copyG, &G, sizeof(struct gameState)); // save the game state before we start checking isGameOver
	r=0;
	j=0;
	zeros=0;
	locVal1=my_council_room(zeros,&G,r);
	locVal2=correct_council_room(zeros,&copyG,r);
	
	
    if ((locVal1-locVal2)!=0)
	{
		printf("Error with random testing, either of the functions failed.\n");
	};
	
	printf("Test %d: Testing general game state variables if they've been changed ...\n",i);
    printf("This will test to see if our copied game state before we performed council_room testing is equal to the modified game state.\n");
    
    for (j = 0; j < numPlayer; j++)
    {
        if (cmpDeckCount(&G, &copyG, j))
            printf("Deck Count has changed between copied and modified game state!\n");
        
		if (cmpDiscard(&G, &copyG, j))
            printf("Discard deck has changed between copied and modified game state!\n");
		
        if (cmpDiscardCount(&G, &copyG, j))
            printf("Discard count has been changed between copied and modified game state!\n");
        
		if (cmpDeck(&G, &copyG, j))
            printf("Deck has changed between copied and modified game state!\n");
	
    }

    
    if (cmpPlayedCards(&G, &copyG))
        printf("playedCards has changed between copied and modified game state!\n");
    if (cmpPlayedCardCount(&G, &copyG))
        printf("playedCardCount has changed between copied and modified game state!\n");
    if (cmpPhase(&G, &copyG))
        printf("phase has changed between copied and modified game state!\n");
    if (cmpWhoseTurn(&G, &copyG))
        printf("WhoseTurn has changed between copied and modified game state!\n"); 
    if (cmpNumActions(&G, &copyG))
        printf("numActions has changed between copied and modified game state!\n");
    if (cmpOutpostPlayed(&G, &copyG))
        printf("OutpostPlayed has changed between copied and modified game state!\n");
    if (cmpNumPlayers(&G, &copyG))
        printf("NumPlayers has changed between copied and modified game state!\n");
    if (cmpNumBuys(&G, &copyG))
        printf("NumBuys has changed between copied and modified game state!\n");
    if (cmpOutpostTurn(&G, &copyG))
        printf("OutpostTurn has changed between copied and modified game state!\n");
	};
	
    printf("Done checking game states.\n");
    printf("\nAll tests done for council_room!\n \n");
    return 0;
}