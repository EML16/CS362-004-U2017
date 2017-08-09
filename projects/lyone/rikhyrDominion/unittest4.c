#include <stdio.h>
#include <string.h>
#include "asserttrue.h"
#include "dominion/dominion.h"

int updateCoins(int player, struct gameState *state, int bonus);	//Define in dominion.c

int testUpdateCoins()
{
	printf("\nTEST BEGAN\n");
	
	int all_passed = 1;
	int coinCount = 0;	
	struct gameState G;	
	memset(G.supplyCount, 1, sizeof(G.supplyCount));

	//When a player has none of copper, silver or gold cards; the coin is equal to the bonus
	int player = 1;
	char *fmt;

	int bonus = 0;
	G.hand[player][0] = adventurer;
	G.hand[player][1] = smithy;
	G.hand[player][2] = mine;
	G.handCount[player] = 3;
	updateCoins(player, &G, bonus);
	
	coinCount = bonus + 0 * 1 + 0 * 2 + 0 * 3;
	fmt = "The player has no copper, silver or gold. Coins with %d bonus: %d\n";
	all_passed &= asserttrue(G.coins, coinCount, '=', 1, fmt, bonus, G.coins); 

	bonus = -2;
	G.hand[player][0] = copper;
	G.hand[player][1] = smithy;
	G.hand[player][2] = mine;
	G.handCount[player] = 3;
	updateCoins(player, &G, bonus);

	coinCount = bonus + 1 * 1 + 0 * 2 + 0 * 3;
	fmt = "The player has one  copper, no silver or gold. Coins with %d bonus: %d\n";
	all_passed &= asserttrue(G.coins, coinCount, '=', 1, fmt, bonus, G.coins); 
		
	bonus = 1;
	G.hand[player][0] = copper;
	G.hand[player][1] = silver;
	G.hand[player][2] = silver;
	G.hand[player][3] = mine;
	G.handCount[player] = 4;
	updateCoins(player, &G, bonus);

	coinCount = bonus + 1 * 1 + 2 * 2 + 0 * 3;
	fmt = "The player has one  copper, two silvers and no gold. Coins with %d bonus: %d\n";
	all_passed &= asserttrue(G.coins, coinCount, '=', 1, fmt, bonus, G.coins); 

	bonus = 77;
	G.hand[player][0] = copper;
	G.hand[player][1] = silver;
	G.hand[player][2] = silver;
	G.hand[player][3] = gold;
	G.hand[player][4] = gold;
	G.hand[player][5] = gold;
	G.handCount[player] = 6;
	updateCoins(player, &G, bonus);
	
	coinCount = bonus + 1 * 1 + 2 * 2 + 3 * 3;
	fmt = "The player has one  copper, two silvers and three golds. Coins with %d bonus: %d\n";
	all_passed &= asserttrue(G.coins, coinCount, '=', 1, fmt, bonus, G.coins); 
	
	if(all_passed)
		printf("TEST COMPLETED SUCCESSFULLY\n");
	else
		printf("TEST FAILED\n");

	return 0;
}

int main()
{
	printf("\n\nTesting updateCoins() defined in dominion.c\n");
	testUpdateCoins();
	printf("\n\n");
	return 0;
}
