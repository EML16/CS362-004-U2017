/*
* RR
* CS 362
* shuffle() Unit Test
*
* 1. Check against nonpositive amount of deck cards amount;
* 2. Check shuffle actually happens.
*
* Check for occasional changes of game state inbetween testing runs.
* Should return a message of deck change for the player 0.
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
    int i, j; // auxilliary  vars
    int numPlayer = 2; // setting minimal count of players
    int k[10] = {adventurer, gardens, smithy, village, sea_hag, treasure_map, outpost, cutpurse, tribute, salvager};
    struct gameState G, copyG;
    int seed = floor(Random() * 1000);

    srand(time(NULL));
    printf ("\nTESTING shuffle():\n");
    
	
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    i = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    memcpy(&copyG, &G, sizeof(struct gameState)); // save the game state before we start checking isGameOver
	// test if shuffle returns -1 if we set count of cards to 0
	//locVal=G.deckCount[0]; //should be 10 after game initialization
	G.deckCount[0]=0;
	printf("Force first player deck count to be 0 to see if shuffle() returns -1.\n");
    if (shuffle(0, &G) != -1)
    {
        printf("Deck card amount is 0, but shuffle() was not -1.\n");
    }
    printf("Running 1000 random tests for first player deck count to verify shuffle is -1 when deck amount is 0.\n");
    for (i = 0; i < 1000; i++)
    {
        int localDeck = rand() % numPlayer;
        G.deckCount[0] = localDeck;
        if (localDeck == 0)
        {
            if (shuffle(0,&G) != -1)
            {
                printf("Test %d: Deck card amount is 0, but shuffle() was not -1.\n",i);
            }
        }
    }
    printf("Done with deck card amount random testing.\n");
	
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
	
    printf("Running 10000 random tests for deck to see if we can detect when the shuffle is not performing correctly.\n");
   
   
   
    for (i = 0; i < 10000; i++)
    {
        if (shuffle(0,&G)==-1)
		{
			printf("Test %d failed: returned negative value on normal deck\n",i);
		}
		else
		{
			if ((G.deck[0][0]==curse)&&(G.deck[0][1]==estate)&&(G.deck[0][2]==duchy)&&(G.deck[0][3]==province)&&(G.deck[0][4]==copper)&&
			(G.deck[0][5]==silver)&&(G.deck[0][6]==gold)&&(G.deck[0][7]==adventurer)&&(G.deck[0][8]==smithy)&&(G.deck[0][9]==gardens))
			{
				printf("Test %d returned unshuffled deck\n",i);
			};
		
		};
    }
    for (j = 0; j < numPlayer; j++)
    {
        (cmpDeckCount(&G, &copyG, j)) ? printf("Deck Count has changed between copied and modified game state!\n"):printf("Deck Count untouched\n");
        
	(cmpDiscard(&G, &copyG, j)) ? printf("Discard deck has changed between copied and modified game state!\n"):printf("Discard deck untouched\n");
		
    (cmpDiscardCount(&G, &copyG, j)) ? printf("Discard count has been changed between copied and modified game state!\n"):printf("Discard count untouched\n");
        
	(cmpDeck(&G, &copyG, j)) ? printf("Deck has changed between copied and modified game state!\n"): printf("Deck untouched\n");
		//This message should appear because we changed decks
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
    printf("\nAll tests done for shuffle()!\n \n");
    return 0;
}