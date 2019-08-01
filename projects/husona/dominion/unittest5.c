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
	state.hand[0][0] = mine;	// initialize players first card to mine
	state.hand[0][1] = copper;	// add all versions of treasures to hand
	state.hand[0][2] = silver;
	state.hand[0][3] = gold;
	
	memcpy(&control, &state, sizeof(struct gameState)); // copy initial game state to control state
	// begin testing
	printf("testing mine card play...\n");
	
	
	i = ce_Mine(2, gold, &state, 0);	// attempt to buy gold with silver
	printf("Test: attempt to buy gold using silver.\n");
	if(i == 0)
	{	
		printf("\tPassed: function returned success.\n");
	}
	else
	{
		printf("\tFailed: function returned failure.\n");
	}
	
	printf("Test that player 1 has same number of cards (one trashed, one received).\n");
	if(_fullCardCount(&state, 0) == _fullCardCount(&control, 0))
	{	
		printf("\tPassed: No change in number of cards for Player 1.\n");
	}
	else
	{
		printf("\tFailed: number of cards changed from %d to %d.\n", _fullCardCount(&state, 0), _fullCardCount(&control, 0));
	}

	printf("Test that player 1 has one fewer silver cards.\n");
	if(fullDeckCount(0, silver, &state) == fullDeckCount(0, silver, &control) - 1)
	{	
		printf("\tPassed: Player 1 has one fewer silver cards.\n");
	}
	else
	{
		printf("\tFailed: number of silver cards changed from %d to %d.\n", fullDeckCount(0, silver, &control), fullDeckCount(0, silver, &state));
	}
	
	printf("Test that player 1 has one more gold cards.\n");
	if(fullDeckCount(0, gold, &state) == fullDeckCount(0, gold, &control) + 1)
	{	
		printf("\tPassed: Player 1 has one more gold card.\n");
	}
	else
	{
		printf("\tFailed: number of gold cards changed from %d to %d.\n", fullDeckCount(0, gold, &control), fullDeckCount(0, gold, &state));
	}
	
	memcpy(&state, &control, sizeof(struct gameState)); // reset game state to initial state
	i = ce_Mine(1, gold, &state, 0);	// attempt to buy gold with copper
	printf("Test: attempt to buy gold using copper.\n");
	if(i == -1)
	{	
		printf("\tPassed: function returned failure.\n");
	}
	else
	{
		printf("\tFailed: function returned success.\n");
	}
	
	printf("Test that player 1 has same number of cards (nothing discarded).\n");
	if(_fullCardCount(&state, 0) == _fullCardCount(&control, 0))
	{	
		printf("\tPassed: No change in number of cards for Player 1.\n");
	}
	else
	{
		printf("\tFailed: number of cards changed from %d to %d.\n", _fullCardCount(&control, 0), _fullCardCount(&state, 0));
	}

	printf("Test that player has same number of copper cards.\n");
	if(fullDeckCount(0, copper, &state) == fullDeckCount(0, copper, &control))
	{	
		printf("\tPassed: Player 1 has the same number of copper cards.\n");
	}
	else
	{
		printf("\tFailed: number of copper cards changed from %d to %d.\n", fullDeckCount(0, copper, &control), fullDeckCount(0, copper, &state));
	}
	
	printf("Test that player 1 has same number of gold cards.\n");
	if(fullDeckCount(0, gold, &state) == fullDeckCount(0, gold, &control))
	{	
		printf("\tPassed: Player 1 has the same number of gold cards.\n");
	}
	else
	{
		printf("\tFailed: number of gold cards changed from %d to %d.\n", fullDeckCount(0, gold, &control), fullDeckCount(0, gold, &state));
	}
	
	memcpy(&state, &control, sizeof(struct gameState)); // reset game state to initial state
	i = ce_Mine(3, mine, &state, 0);	// attempt to buy a non treasure card with gold
	printf("Test: attempt to buy non treasure card using gold.\n");
	if(i == -1)
	{	
		printf("\tPassed: function returned failure.\n");
	}
	else
	{
		printf("\tFailed: function returned success.\n");
	}
	printf("Test that player 1 has same number of cards (nothing discarded).\n");
	if(_fullCardCount(&state, 0) == _fullCardCount(&control, 0))
	{	
		printf("\tPassed: No change in number of cards for Player 1.\n");
	}
	else
	{
		printf("\tFailed: number of cards changed from %d to %d.\n", _fullCardCount(&control, 0), _fullCardCount(&state, 0));
	}

	printf("Test that player has same number of gold cards.\n");
	if(fullDeckCount(0, gold, &state) == fullDeckCount(0, gold, &control))
	{	
		printf("\tPassed: Player 1 has the same number of gold cards.\n");
	}
	else
	{
		printf("\tFailed: number of gold cards changed from %d to %d.\n", fullDeckCount(0, gold, &control), fullDeckCount(0, gold, &state));
	}
	
	printf("Test that player 1 has same number of mine cards.\n");
	if(fullDeckCount(0, mine, &state) == fullDeckCount(0, mine, &control))
	{	
		printf("\tPassed: Player 1 has the same number of mine cards.\n");
	}
	else
	{
		printf("\tFailed: number of mine cards changed from %d to %d.\n", fullDeckCount(0, silver, &control), fullDeckCount(0, silver, &state));
	}

    return 0;
}