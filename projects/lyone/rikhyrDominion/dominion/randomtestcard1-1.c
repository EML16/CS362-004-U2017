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


#include "tester_dominion.h"
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
			(state->deckCount[currentPlayer] <1) ? shuffle(currentPlayer, state): state->deckCount[currentPlayer];
			
			//if the deck is empty we need to shuffle discard and add to deck
			//RR loose a card in a deck
			  
			
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
{
    SelectStream(1);
	PutSeed(-1);
    int i, r, j, locVal1, locVal2, zeros, seed; // auxilliary  vars
    int numPlayer = 4; // setting maximal count of players
    int k[10] = {adventurer, gardens, smithy, village, council_room, treasure_map, outpost, cutpurse, tribute, salvager};
    struct gameState G, copyG;
    //int seed = floor(Random() * 1000);

    srand(time(NULL));
    printf ("\nTESTING my_adventurer\n");
    
	

    
	for (i=0; i<1000; i++)
	{
	seed = floor(Random() * 1000);
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
	
	G.deckCount[0]=floor(Random() * 5); //generate random amound of cards in a deck
	G.discardCount[0]=15-G.deckCount[0];
	for (j=0; j<G.deckCount[0]; j++) //generate randomly cards in a deck
	{
		r=floor(Random()*27);
		for(zeros=curse;zeros<=r;zeros++)
			G.deck[0][j]=zeros;
	};
	for (j=0; j<G.discardCount[0]; j++) //generate randomly cards in dicard
	{
		r=floor(Random()*27);
		for(zeros=curse;zeros<=r;zeros++)
			G.discard[0][j]=zeros;
	};
	
	
	memcpy(&copyG, &G, sizeof(struct gameState)); // save the game state before we start checking isGameOver
	r=0;
	j=0;
	zeros=0;
	locVal1=my_adventurer(r,j,zeros,&G);
	locVal2=correct_adventurer(r,j,zeros,&copyG);
	
	
    (locVal1!=locVal2) ? printf("Error with random testing, either of the functions failed.\n"):printf("Control sets identical.\n");
	
	
    printf("Test %d: Testing general game state variables if they've been changed ...\n",i);
    printf("This will test to see if our copied game state before we performed adventurer testing is equal to the modified game state.\n");	
    
    for (j = 0; j < numPlayer; j++)
    {
	printf("Player %d\n",j);
    (cmpDeckCount(&G, &copyG, j)) ? printf("-Deck Count has changed between copied and modified game state! %d and %d \n", G.deckCount[0],copyG.deckCount[0]):printf("Deck Count untouched\n");
        
	(cmpDiscard(&G, &copyG, j)) ? printf("-Discard deck has changed between copied and modified game state!\n"):printf("Discard deck untouched\n");
		
    (cmpDiscardCount(&G, &copyG, j)) ? printf("-Discard count has been changed between copied and modified game state! %d and %d \n", G.discardCount[0], copyG.discardCount[0]):printf("Discard count untouched\n");
        
	(cmpDeck(&G, &copyG, j)) ? printf("-Deck has changed between copied and modified game state! \n"): printf("Deck untouched\n");
	
    }

    
    (cmpPlayedCards(&G, &copyG)) ? printf("-PlayedCards has changed between copied and modified game state!\n"): printf("PlayedCards untouched!\n");
    (cmpPlayedCardCount(&G, &copyG)) ? printf("-playedCardCount has changed between copied and modified game state!\n"): printf("PlayedCardsCount untouched\n");
    (cmpPhase(&G, &copyG)) ? printf("-phase has changed between copied and modified game state!\n"):printf("phase untouched\n");
    (cmpWhoseTurn(&G, &copyG)) ? printf("-WhoseTurn has changed between copied and modified game state!\n"):printf("WhooseTurn untouched\n"); 
    (cmpNumActions(&G, &copyG)) ? printf("-numActions has changed between copied and modified game state!\n"):printf("numActions untouched\n");
    (cmpOutpostPlayed(&G, &copyG)) ? printf("-OutpostPlayed has changed between copied and modified game state!\n"):printf("OutpostPlayed untouched\n");
    (cmpNumPlayers(&G, &copyG)) ? printf("-NumPlayers has changed between copied and modified game state!\n"):printf("NumPlayers untouched\n");
    (cmpNumBuys(&G, &copyG)) ? printf("-NumBuys has changed between copied and modified game state!\n"):printf("NumBuys untouched\n");
    (cmpOutpostTurn(&G, &copyG)) ? printf("-OutpostTurn has changed between copied and modified game state!\n"):printf("OutpostTurn untouched\n");
	};
	
    printf("Done checking game states.\n");
    printf("\nAll tests done for adventurer!\n \n");
    return 0;
}