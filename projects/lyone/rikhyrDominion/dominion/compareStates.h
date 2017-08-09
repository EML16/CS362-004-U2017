#include "dominion.h"

#ifndef _COMPARE_STATES_H
#define _COMPARE_STATES_H

int cmpDeckCount(struct gameState * g1, struct gameState * g2, int player);

int cmpDiscard(struct gameState * g1, struct gameState * g2, int player);

int cmpDiscardCount(struct gameState * g1, struct gameState * g2, int player);

int cmpDeck(struct gameState * g1, struct gameState * g2, int player);

int cmpPlayedCards(struct gameState * g1, struct gameState * g2);

int cmpPlayedCardCount(struct gameState * g1, struct gameState * g2);

int cmpPhase(struct gameState * g1, struct gameState * g2);

int cmpWhoseTurn(struct gameState * g1, struct gameState * g2);

int cmpNumActions(struct gameState * g1, struct gameState * g2);

int cmpOutpostTurn(struct gameState * g1, struct gameState * g2);

int cmpNumPlayers(struct gameState * g1, struct gameState * g2);

int cmpNumBuys(struct gameState * g1, struct gameState * g2);

int cmpOutpostPlayed(struct gameState * g1, struct gameState * g2);

int cmpSupplyCount(struct gameState * g1, struct gameState * g2);

#endif