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
    int i, j;
    int seed = 1000;
    int numPlayers = 2;
    int kingdom[10] = {ambassador, minion, tribute, gardens, mine, remodel, smithy, village, baron, great_hall};
			   
    struct gameState state, control;
	
	initializeGame(numPlayers, kingdom, seed, &state);
	state.hand[0][0] = minion;	// initialize players first card to minion
	for(i = 0; i < 5; i++) // draw a hand for player 2
	{
		drawCard(1, &state);
	}
	memcpy(&control, &state, sizeof(struct gameState)); // copy initial game state to control state
	
	// begin testing
	printf("testing minion card play...\n");
	playMinion(&state, 1);	// play minion card and choose option 1: gain 2 coin
	
	printf("Test if number of actions increased by 1:\n");
	if(state.numActions == control.numActions + 1)
	{	
		printf("\tPassed: numActions increased by 1.\n");
	}
	else
	{
		printf("\tFailed: numActions changed from %d to %d.\n", control.numActions, state.numActions);
	}
	
	printf("Test if coin increased by 2 for option 1:\n");
	if(state.coins == control.coins + 2)
	{	
		printf("\tPassed: coin increased by 2.\n");
	}
	else
	{
		printf("\tFailed: coin changed from %d to %d.\n", control.coins, state.coins);
	}
	
	printf("Test that number of player cards remained the same:\n"); 
	if(_fullCardCount(&state, 0) == _fullCardCount(&control, 0))
	{
		printf("\tPassed: number of cards remained the same.\n");
	}
	else
	{
		printf("\tFailed: number of cards changed from %d to %d.\n", _fullCardCount(&control, 0), _fullCardCount(&state, 0));
	}
	
	printf("Test that only 1 card was discarded for option 1 (minion card):\n");
	if(state.discardCount[0] == control.discardCount[0] + 1)
	{
		printf("\tPassed: Only one card discarded.\n");
	}
	else
	{
		printf("\tFailed: number of discarded cards: %d.\n", state.discardCount[0] - control.discardCount[0]);
	}
	
	// change control situation, all other cards in hand now silver and all cards in decks are copper
	for(i = 1; i < control.handCount[0]; i++)
	{
		control.hand[0][i] = silver;
	}
	// Set all cards in player 2 hand to be silver
	for(i = 0; i < control.handCount[1]; i++)
	{
		control.hand[1][i] = silver;
	}
	// set all player 1 deck cards to copper
	for(i = 0; i < control.deckCount[0]; i++)
	{
		control.deck[0][i] = copper;
	}
	// set all player 2 deck cards to copper
	for(i = 0; i < control.deckCount[1]; i++)
	{
		control.deck[1][i] = copper;
	}
	memcpy(&state, &control, sizeof(struct gameState)); // make state into control
	playMinion(&state, 2);	// play minion card, option 2: discard all cards and draw 4 more, all other players also discard and draw
	
	printf("Test if coin remained the same:\n");
	if(state.coins == control.coins)
	{	
		printf("\tPassed: coins did not change.\n");
	}
	else
	{
		printf("\tFailed: coin changed from %d to %d.\n", control.coins, state.coins);
	}
	
	printf("Test that player 1 discarded 5 cards:\n");
	if(state.discardCount[0] == 5)
	{	
		printf("\tPassed: player 1 discarded total of 5 cards.\n");
	}
	else
	{
		printf("\tFailed: player 1 discarded %d cards.\n", state.discardCount[0]);
	}
	
	printf("Test that the player 1 has 4 cards in hand and are all copper:\n");
	j = 0;
	for(i = 0; i < state.handCount[0]; i++)
	{
		if(state.hand[0][i] == copper)
		{
			j++;
		}
	}
	if(i == 4 && j == 4)
	{
		printf("\tPassed: player 1 has 4 copper cards in hand.\n");
	}
	else
	{
		printf("\tFailed: player 1 has %d cards in hand and %d non-copper cards.\n", i, i - j);
	}
	
	printf("Test that player 2 discarded 5 cards:\n");
	if(state.discardCount[1] == 5)
	{	
		printf("\tPassed: player 2 discarded total of 5 cards.\n");
	}
	else
	{
		printf("\tFailed: player 2 discarded %d cards.\n", state.discardCount[1]);
	}
	
	printf("Test that the player 2 has 4 cards in hand and are all copper:\n");
	j = 0;
	for(i = 0; i < state.handCount[1]; i++)
	{
		if(state.hand[1][i] == copper)
		{
			j++;
		}
	}
	if(i == 4 && j == 4)
	{
		printf("\tPassed: player 2 has 4 copper cards in hand.\n");
	}
	else
	{
		printf("\tFailed: player 2 has %d cards in hand and %d non-copper cards.\n", i, i - j);
	}


    return 0;
}