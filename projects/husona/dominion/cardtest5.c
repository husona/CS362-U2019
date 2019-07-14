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
	// set player 1's hand to a known state (all mines)
	for(i = 0; i < state.handCount[0]; i++)
	{
		state.hand[0][i] = mine;
	}
	// set players 1's deck to a known state (all barons)
	for(i = 0; i < state.deckCount[0]; i++)
	{
		state.deck[0][i] = baron;
	}
	memcpy(&control, &state, sizeof(struct gameState)); // copy initial game state to control state
	
	printf("testing drawCard function...\n");
	
	i = state.deckCount[0];
	for(j = 0; j < i; j++)
	{
		drawCard(0, &state);
	}
	
	printf("Test: %d draw attempts, verify player 1 handCount increases.\n", i);
	if(state.handCount[0] == control.handCount[0] + i)
	{
		printf("\tPassed: players handCount increased by %d.\n", i);
	}
	else
	{
		printf("\tFailed: players handCount changed from %d to %d.\n", control.handCount[0], state.handCount[0]);
	}
	
	printf("Test: %d draw attempts, verify player 1 deckCount decreases.\n", i);
	if(state.deckCount[0] == control.deckCount[0] - i)
	{
		printf("\tPassed: players deckCount decreased by %d.\n", i);
	}
	else
	{
		printf("\tFailed: players deckCount changed from %d to %d.\n", control.deckCount[0], state.deckCount[0]);
	}
	
	printf("Test: %d draw attempts for player 1, verify player 2 handCount is unchanged.\n", i);
	if(state.handCount[1] == control.handCount[1])
	{
		printf("\tPassed: player 2\'s handCount is unchanged.\n");
	}
	else
	{
		printf("\tFailed: player 2\'s handCount changed from %d to %d.\n", control.handCount[1], state.handCount[1]);
	}
	
	printf("Test: %d draw attempts for player 1, verify player 2 deckCount unchanged.\n", i);
	if(state.deckCount[1] == control.deckCount[1])
	{
		printf("\tPassed: players deckCount unchanged.\n");
	}
	else
	{
		printf("\tFailed: player 2\'s deckCount changed from %d to %d.\n", control.deckCount[1], state.deckCount[1]);
	}
	
	printf("Test: verify player 1\'s cards are unchanged.\n");
	if(fullDeckCount(0, mine, &state) == fullDeckCount(0, mine, &control) && fullDeckCount(0, baron, &state) == fullDeckCount(0, baron, &control))
	{
		printf("\tPassed: players cards are unchanged.\n");
	}
	else
	{
		printf("\tFailed: one or more of the players cards have changed.\n");
	}	
	
	state.deckCount[0] = 0;
	state.discardCount[0] = 0;
	printf("Test: attempt draw from empty deck, no discards.\n");
	if(drawCard(0, &state) == -1)
	{
		printf("\tPassed: function returned failure.\n");
	}
	else
	{
		printf("\tFailed: function returned success.\n");
	}


    return 0;
}