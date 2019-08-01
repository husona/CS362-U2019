/****************************************************
**
** Andrew Huson 
** husona@oregonstate.edu 
** OSU CS362 Summer 2019
** Assignment 3
**
****************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() 
{
    int i;
    int seed = 1000;
    int numPlayers = 2;
    int kingdom[10] = {ambassador, minion, tribute, gardens, mine, remodel, smithy, village, baron, great_hall};
			   
    struct gameState state, control;
	
	initializeGame(numPlayers, kingdom, seed, &state);
	state.hand[0][0] = baron;	// initialize players first card to baron
	state.hand[0][1] = estate;	// ensure player has at least one estate card for option 1
	
	memcpy(&control, &state, sizeof(struct gameState)); // copy initial game state to control state
	// begin testing
	printf("testing baron card play...\n");
	ce_Baron(1, &state);	// play baron card, and choose option 1, discard estate
	
	printf("Test if number of buys increased by 1:\n");
	if(state.numBuys == control.numBuys + 1)
	{	
		printf("\tPassed: numBuys increased by 1.\n");
	}
	else
	{
		printf("\tFailed: numBuys changed from %d to %d.\n", control.numBuys, state.numBuys);
	}
	
	printf("Test if coin increased by 4 when discarding an estate:\n");
	if(state.coins == control.coins + 4)
	{	
		printf("\tPassed: coin increased by 4.\n");
	}
	else
	{
		printf("\tFailed: coin changed from %d to %d.\n", control.coins, state.coins);
	}
	
	printf("Test that number of player cards remained the same when discarding an estate:\n"); 
	if(_fullCardCount(&state, 0) == _fullCardCount(&control, 0))
	{
		printf("\tPassed: number of cards remained the same.\n");
	}
	else
	{
		printf("\tFailed: number of cards changed from %d to %d.\n", _fullCardCount(&control, 0), _fullCardCount(&state, 0));
	}
	
	printf("Test that 2 cards where discarded when discarding an estate (baron and estate):\n");
	if(state.discardCount[0] == control.discardCount[0] + 2)
	{
		printf("\tPassed: two cards discarded.\n");
	}
	else
	{
		printf("\tFailed: number of discarded cards: %d.\n", state.discardCount[0] - control.discardCount[0]);
	}
	
	// change control situation, all other cards in hand now copper (no estate)
	for(i = 1; i < control.handCount[0]; i++)
	{
		control.hand[0][i] = copper;
	}
	memcpy(&state, &control, sizeof(struct gameState)); // make state into control
	
	ce_Baron(1, &state);	// play baron card, and choose option 1, discard estate (should only gain an estate as doesn't have one to discard)
	
	printf("Test if coin remained the same:\n");
	if(state.coins == control.coins)
	{	
		printf("\tPassed: coins did not change.\n");
	}
	else
	{
		printf("\tFailed: coin changed from %d to %d.\n", control.coins, state.coins);
	}
	
	printf("Test that player gained an estate:\n");
	if(fullDeckCount(0, estate, &state) == fullDeckCount(0, estate, &control) + 1)
	{	
		printf("\tPassed: player gained an estate.\n");
	}
	else
	{
		printf("\tFailed: player estates changed from %d to %d.\n", fullDeckCount(0, estate, &control), fullDeckCount(0, estate, &state));
	}
	
	printf("Test that the supply of estates decreased by 1:\n");
	if(supplyCount(estate, &state) == supplyCount(estate, &control) - 1)
	{	
		printf("\tPassed: estate supply decreased by 1.\n");
	}
	else
	{
		printf("\tFailed: estate supply changed from %d to %d.\n", supplyCount(estate, &control), supplyCount(estate, &state));
	}

    return 0;
}