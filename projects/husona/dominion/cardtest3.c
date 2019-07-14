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
	// set player 1's hand to known state (all mines)
	for(i = 0; i < state.handCount[0]; i++)
	{
		state.hand[0][i] = mine;
	}
	// set players 1's deck to a known state (all mines)
	for(i = 0; i < state.deckCount[0]; i++)
	{
		state.deck[0][i] = mine;
	}
	// set player 2's hand to known state (all barons)
	for(i = 0; i < state.handCount[1]; i++)
	{
		state.hand[1][i] = baron;
	}
	// set players 2's deck to a known state (all barons)
	for(i = 0; i < state.deckCount[1]; i++)
	{
		state.deck[1][i] = baron;
	}
	memcpy(&control, &state, sizeof(struct gameState)); // copy initial game state to control state
	
	// begin testing
	printf("testing endTurn function...\n");
	
	if(endTurn(&state) == 0)
	{
		printf("\tPassed: function returned success.\n");
	}
	else
	{
		printf("\tFailed: function returned failure.\n");
	}
	
	printf("Verify previous player has no cards in hand:\n");
	if(state.handCount[control.whoseTurn] == 0)
	{	
		printf("\tPassed: control has moved to the next player.\n");
	}
	else
	{
		printf("\tFailed: previous player still has %d cards in hand.\n", state.handCount[control.whoseTurn]);
	}
	
	printf("Verify control has passed to the next player:\n");
	if(state.whoseTurn == whoseNext(&control))
	{	
		printf("\tPassed: control has moved to the next player.\n");
	}
	else
	{
		printf("\tFailed: control moved from player %d to %d instead of player %d.\n", control.whoseTurn, state.whoseTurn, whoseNext(&control));
	}
	
	printf("Verify current player has 5 cards in hand:\n");
	if(state.handCount[state.whoseTurn] == 5)
	{	
		printf("\tPassed: current player has 5 cards in hand.\n");
	}
	else
	{
		printf("\tFailed: current player has %d cards in hand.\n", state.handCount[state.whoseTurn]);
	}
	
	printf("Verify player 1 did not lose any cards:\n");
	if(_fullCardCount(&state, 0) == _fullCardCount(&control, 0))
	{	
		printf("\tPassed: player 1 has the same number of cards.\n");
	}
	else
	{
		printf("\tFailed: player 1 card count changed from %d to %d.\n", _fullCardCount(&control, 0), _fullCardCount(&state, 0));
	}
	
	printf("Verify player 2 did not lose any cards:\n");
	if(_fullCardCount(&state, 1) == _fullCardCount(&control, 1))
	{	
		printf("\tPassed: player 2 has the same number of cards.\n");
	}
	else
	{
		printf("\tFailed: player 2 card count changed from %d to %d.\n", _fullCardCount(&control, 1), _fullCardCount(&state, 1));
	}
	
	printf("Verify player 1\'s cards did not change:\n");
	if(fullDeckCount(0, mine, &state) == fullDeckCount(0, mine, &control))
	{	
		printf("\tPassed: player 1\'s cards have not changed.\n");
	}
	else
	{
		printf("\tFailed: 1 or more of of player 1\'s cards have changed.\n");
	}
	
	printf("Verify player 2\'s cards did not change:\n");
	if(fullDeckCount(1, mine, &state) == fullDeckCount(1, mine, &control))
	{	
		printf("\tPassed: player 2\'s cards have not changed.\n");
	}
	else
	{
		printf("\tFailed: 2 or more of of player 1\'s cards have changed.\n");
	}


    return 0;
}