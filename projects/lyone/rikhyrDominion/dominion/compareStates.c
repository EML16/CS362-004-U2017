/* -----------------------------------------------------------------------
 * CS 362
 * compareStates
 *
 * Convenience functions to quickly compare one game state with another
 * and see if it's the same. If it's different, will return 1. If it's the
 * same, will return 0. There's a compare function for every attribute of
 * game state.
 * -----------------------------------------------------------------------
 */

#include "compareStates.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int cmpDeckCount(struct gameState * g1, struct gameState * g2, int player) {
    if (g1->deckCount[player] != g2->deckCount[player])
        return 1;
    return 0;   
}

int cmpDiscard(struct gameState * g1, struct gameState * g2, int player) {
    int j;
    for (j = 0; j < MAX_DECK; j++)
    {
        if (g1->discard[player][j] != g2->discard[player][j])
            return 1;
    }
    return 0;    
}

int cmpDiscardCount(struct gameState * g1, struct gameState * g2, int player) {
    if (g1->discardCount[player] != g2->discardCount[player])
        return 1;  
    return 0;
}

int cmpDeck(struct gameState * g1, struct gameState * g2, int player) {
    int j;
    for (j = 0; j < MAX_DECK; j++)
    {
        if (g1->deck[player][j] != g2->deck[player][j])
            return 1;
    }
    return 0;
}

int cmpPlayedCards(struct gameState * g1, struct gameState * g2) {
    int j;
    for (j = 0; j < MAX_DECK; j++)
    {
        if (g1->playedCards[j] != g2->playedCards[j])
        {
            return 1;
        }
    }
    return 0;
}

int cmpPlayedCardCount(struct gameState * g1, struct gameState * g2) {
    if (g1->playedCardCount != g2->playedCardCount)
    {
        return 1;
    }
    return 0;
}

int cmpPhase(struct gameState * g1, struct gameState * g2) {
    if (g1->phase != g2->phase)
        return 1;
    return 0;
}

int cmpWhoseTurn(struct gameState * g1, struct gameState * g2) {
    if (g1->whoseTurn != g2->whoseTurn)
        return 1;
    return 0;
}

int cmpNumActions(struct gameState * g1, struct gameState * g2) {
    if (g1->numActions != g2->numActions)
        return 1;
    return 0;
}

int cmpOutpostTurn(struct gameState * g1, struct gameState * g2) {
    if (g1->outpostTurn != g2->outpostTurn)
        return 1;
    return 0;
}

int cmpNumPlayers(struct gameState * g1, struct gameState * g2) {
    if (g1->numPlayers != g2->numPlayers)
        return 1;
    return 0;
}   

int cmpNumBuys(struct gameState * g1, struct gameState * g2) {
    if (g1->numBuys != g2->numBuys)
        return 1;
    return 0;
}   

int cmpOutpostPlayed(struct gameState * g1, struct gameState * g2) {
    if (g1->outpostPlayed != g2->outpostPlayed)
        return 1;
    return 0;
}

int cmpSupplyCount(struct gameState * g1, struct gameState * g2) {
    int j;
    for (j = 0; j < treasure_map + 1; j++)
    {
        if (g1->supplyCount[j] != g2->supplyCount[j])
        {
            return 1;
        }
    }
    return 0;    
}