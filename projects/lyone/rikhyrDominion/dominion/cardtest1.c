/*
* RR
* CS 362
* WhoseTurn() Unit Test
*
* 1. Test my_adventurer();
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

int correct_adventurer (int drawntreasure, int z, int currentPlayer, struct gameState *state)
{
int cardDrawn;
int temphand[MAX_HAND];// moved above the if statement

while(drawntreasure<2)
		{
			if (state->deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
			//RR loose a card in a deck
			  shuffle(currentPlayer, state);
			}
			drawCard(currentPlayer, state);
			cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
			if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
			  drawntreasure++;
			else
			{
			  temphand[z]=cardDrawn;
			  state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
			  z++;
			}
		}
      while(z-1>=0)
	  {
		state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
		z=z-1;
      }

	  return 0;

};

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
    printf ("\nTESTING my_adventurer\n");
    
	

    
	for (i=0; i<1000; i++)
	{
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
	memcpy(&copyG, &G, sizeof(struct gameState)); // save the game state before we start checking isGameOver
	r=0;
	j=0;
	zeros=0;
	locVal1=my_adventurer(r,j,zeros,&G);
	locVal2=correct_adventurer(r,j,zeros,&copyG);
	
	
    if ((locVal1-locVal2)!=0)
	{
		printf("Error with random testing, either of the functions failed.\n");
	};
	
    printf("Test %d: Testing general game state variables if they've been changed ...\n",i);
    printf("This will test to see if our copied game state before we performed adventurer testing is equal to the modified game state.\n");	
    
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
    printf("\nAll tests done for adventurer!\n \n");
    return 0;
}