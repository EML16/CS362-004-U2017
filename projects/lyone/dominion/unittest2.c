#include <stdio.h>
#include "dominion.h"
#include "asserttrue.h"

static char *card_names[] = {
	"curse", "estate", "duchy", "province", "copper", "silver", "gold",
   "adventurer", "council_room", "feast", "gardens", "mine", "remodel", "smithy", "village",
   "baron", "great_hall", "minion", "steward", "tribute", "ambassador", "cutpurse", "embargo", "outpost",
   "salvager", "sea_hag", "treasure_map"
  };

int testInitializeGame()
{
	printf("\nTEST BEGAN\n");

	char *func_name = "initializeGame";
	int all_passed = 1;
	int numPlayers;
	int r = 0;

	int kingdom_cards[][10] = {	
		{adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy},
		{village, baron, great_hall, minion, steward, tribute, ambassador, cutpurse, embargo, outpost},
		{salvager, sea_hag, treasure_map, adventurer, embargo, village, gardens, smithy, minion,  council_room}, 
	 	{adventurer, adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy}
	};

	struct gameState G;	

	//Boundary Test. Should NOT initialize the game with less than 2 players or more than MAX_PLAYERS players
	numPlayers = MAX_PLAYERS + 12;
	r = initializeGame(numPlayers, kingdom_cards[0], 1, &G);
	all_passed &= asserttrue(r, -1, '=', 1, "Did not initialize game with %d players\n", numPlayers);

	numPlayers = 0;
	r = initializeGame(numPlayers, kingdom_cards[1], 1, &G);
	all_passed &= asserttrue(r, -1, '=', 1, "Did not initialize game with %d players\n", numPlayers);

	//The game shouldn't be initialized with duplicate kingdom cards
	numPlayers = 2;
	r = initializeGame(numPlayers, kingdom_cards[3], 1, &G);
	all_passed &= asserttrue(r, -1, '=', 1, "Did not initialize game with duplicate kingdom cards\n");
	
	int i, j, curseCount, *k;
	char *fmt;
	//Check initiale values based on the number of players.

	for(numPlayers = 2; numPlayers <= MAX_PLAYERS; ++numPlayers)
	{
		printf("\n\n%d-Player Game\n", numPlayers);
		k = kingdom_cards[numPlayers - 2];
		initializeGame(numPlayers, k, 1, &G);
		r = asserttrue(G.numPlayers, numPlayers, '=', 1, "Initialized game with %d players\n", numPlayers);
		all_passed &= r;

		if(r)
		{
			fmt = "Supply of %s is initialized to %d\n";
			
			curseCount = numPlayers * 10 - 10;	//Proper curse count

			//CHECK supply of curse 
			all_passed &= asserttrue(G.supplyCount[curse], curseCount, '=', 1, fmt, card_names[curse], curseCount);

			//CHECK supply of estate, duchy and province
			if(numPlayers == 2)
			{
				all_passed &= asserttrue(G.supplyCount[estate], 8, '=', 1, fmt, card_names[estate], 8);
				all_passed &= asserttrue(G.supplyCount[duchy], 8, '=', 1, fmt, card_names[duchy], 8);
				all_passed &= asserttrue(G.supplyCount[province], 8, '=', 1, fmt, card_names[province], 8);
			}
			else
			{
				all_passed &= asserttrue(G.supplyCount[estate], 12, '=', 1, fmt, card_names[estate], 12);
				all_passed &= asserttrue(G.supplyCount[duchy], 12, '=', 1, fmt, card_names[duchy], 12);
				all_passed &= asserttrue(G.supplyCount[province], 12, '=', 1, fmt, card_names[province], 12);
			}

			//CHECK supply of Treasure cards
			all_passed &= asserttrue(G.supplyCount[copper], 60-(7*numPlayers), '=', 1, fmt, \
					card_names[copper], 60-(7*numPlayers));
			all_passed &= asserttrue(G.supplyCount[silver], 40, '=', 1, fmt, card_names[silver], 40);
			all_passed &= asserttrue(G.supplyCount[gold], 30, '=', 1, fmt, card_names[gold], 30);

			//CHECK supply of Kingdom cards
			for(j = 0; j < 10; ++j)	//Iterate through the cards with which the game is initialized
			{
				if(k[j] == great_hall || k[j] == gardens)
				{
					if(numPlayers == 2)
						all_passed &= asserttrue(G.supplyCount[k[j]], 8, '=', 1, fmt, card_names[k[j]], 8);
					else
						all_passed &= asserttrue(G.supplyCount[k[j]], 12, '=', 1, fmt, card_names[k[j]], 12);
				}
				else
					all_passed &= asserttrue(G.supplyCount[k[j]], 10, '=', 1, fmt, card_names[k[j]], 10);
			}

			int player, silverCount = 0, copperCount = 0, dCount;
			int discardCount, deckCount, handCount, initCoinCount;
			
			//CHECK player deck count
			for(player = 0; player < numPlayers; ++player)	//For each player, ...
			{
				printf("Player %d\n", player + 1);
				fmt = "%s contains %d cards\n";

				dCount = ((player == 0)? 5: 10);	//After the initialization, the first player has 
						//a deck of 5 cards while each of the other players has a deck of 10 cards.
				deckCount = G.deckCount[player];
				handCount = G.handCount[player];
				discardCount = G.discardCount[player];

				all_passed &= asserttrue(deckCount, dCount, '=', 1, fmt, "deck", deckCount);
				//CHECK Initiale contents of player's discard pile and hand
				if(player == 0)
				{
					all_passed &= asserttrue(handCount, 5, '=', 1, fmt, "hand", handCount);
					all_passed &= asserttrue(discardCount, 0, '=',1, fmt, "discard",discardCount);
				}			
				else
				{
					all_passed &= asserttrue(handCount, 0, '=', 1, fmt, "hand", handCount);
					all_passed &= asserttrue(discardCount, 0, '=',1, fmt, "discard",discardCount);
				}
		
				//CHECK initiale coin counts of player 1
				if(player == 0)
				{
					copperCount = 0;
					silverCount = 0;
					for(j = 0; j < handCount; ++j)
					{
						if(G.hand[player][j] == copper)
							copperCount++;
						else if(G.hand[player][j] == silver)
							silverCount++;
					}
				
					initCoinCount = copperCount + 2 * silverCount;
					fmt = "Initialized with %d coins\n";
					all_passed &= asserttrue(G.coins, initCoinCount, '=', 1, fmt, G.coins);
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
	printf("\n\nTesting initializeGame() defined in dominion.c\n");
	testInitializeGame();
	printf("\n\n");
	return 0;
}
