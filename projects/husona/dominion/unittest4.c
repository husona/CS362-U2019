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

int i;

void runTests(struct gameState* state, struct gameState* control, int addActions, int addCoins, int newCards)
{
	i++;
	printf("Test[%d]:\n", i);
	
	printf("Test that player 1 discarded 1 card:\n");
	if(state->discardCount[0] == control->discardCount[0] + 1)
	{
		printf("\tPassed: One cards discarded.\n");
	}
	else
	{
		printf("\tFailed: number of discarded cards: %d.\n", state->discardCount[0] - control->discardCount[0]);
	}
	
	printf("Test that player 2 discarded 2 cards:\n");
	if(state->discardCount[1] == control->discardCount[1] + 2)
	{
		printf("\tPassed: Two cards discarded.\n");
	}
	else
	{
		printf("\tFailed: number of discarded cards: %d.\n", state->discardCount[1] - control->discardCount[1]);
	}
	
	printf("Test if number of actions increased by %d:\n", addActions);
	if(state->numActions == control->numActions + addActions)
	{	
		printf("\tPassed: numActions increased by %d.\n", addActions);
	}
	else
	{
		printf("\tFailed: numActions changed from %d to %d.\n", control->numActions, state->numActions);
	}
	
	printf("Test if number of coins increased by %d:\n", addCoins);
	if(state->coins == control->coins + addCoins)
	{	
		printf("\tPassed: coins increased by %d.\n", addCoins);
	}
	else
	{
		printf("\tFailed: coins changed from %d to %d.\n", control->coins, state->coins);
	}
	
	printf("Test that number of cards in player 1's hand changed by %d:\n", newCards - 1);	// number of expected new cards minus the discard
	if(state->handCount[0] == control->handCount[0] + newCards - 1)
	{	
		printf("\tPassed: Player 1s hand changed by %d cards.\n", newCards - 1);
	}
	else
	{
		printf("\tFailed: player 1 handCount changed from %d to %d.\n", control->handCount[0], state->handCount[0]);
	}
	
	printf("\n");
}

int main() 
{
	i = 0;
    int seed = 1000;
    int numPlayers = 2;
    int kingdom[10] = {ambassador, minion, tribute, curse, mine, remodel, smithy, village, baron, great_hall};
			   
    struct gameState state, control;
	
	initializeGame(numPlayers, kingdom, seed, &state);
	state.hand[0][0] = tribute;	// initialize players first card to tribute
	// set player 2 top two deck cards to known state
	state.deck[1][state.deckCount[1]-1] = tribute;	// action card
	state.deck[1][state.deckCount[1]-2] = copper;	// treasure card
	memcpy(&control, &state, sizeof(struct gameState)); // copy new game state to control state
	// begin testing
	printf("testing tribute card play...\n");
	ce_Tribute(&state);
	runTests(&state, &control, 2, 2, 0);
	
	memcpy(&state, &control, sizeof(struct gameState)); // reset game state
	// set player 2 top two deck cards to a new known state
	state.deck[1][state.deckCount[1]-1] = tribute;	// action card
	state.deck[1][state.deckCount[1]-2] = tribute;	// same action card
	memcpy(&control, &state, sizeof(struct gameState)); // copy new game state to control state
	ce_Tribute(&state);
	runTests(&state, &control, 2, 0, 0);
	memcpy(&state, &control, sizeof(struct gameState)); // reset game state
	
	// set player 2 top two deck cards to a new known state
	state.deck[1][state.deckCount[1]-1] = silver;	// treasure card
	state.deck[1][state.deckCount[1]-2] = gold;	// different treasure card
	memcpy(&control, &state, sizeof(struct gameState)); // copy new game state to control state
	ce_Tribute(&state);
	runTests(&state, &control, 0, 4, 0);
	memcpy(&state, &control, sizeof(struct gameState)); // reset game state
	
	// set player 2 top two deck cards to a new known state
	state.deck[1][state.deckCount[1]-1] = curse;	// curse card
	state.deck[1][state.deckCount[1]-2] = curse;	// curse card
	memcpy(&control, &state, sizeof(struct gameState)); // copy new game state to control state
	ce_Tribute(&state);
	runTests(&state, &control, 0, 0, 0);
	memcpy(&state, &control, sizeof(struct gameState)); // reset game state
	
	// set player 2 top two deck cards to a new known state
	state.deck[1][state.deckCount[1]-1] = province;	// victory card
	state.deck[1][state.deckCount[1]-2] = estate;	// victory card
	memcpy(&control, &state, sizeof(struct gameState)); // copy new game state to control state
	ce_Tribute(&state);
	runTests(&state, &control, 0, 0, 4);
	memcpy(&state, &control, sizeof(struct gameState)); // reset game state
	
	// set player 2 top two deck cards to a new known state
	state.deck[1][state.deckCount[1]-1] = tribute;	// action card
	state.deck[1][state.deckCount[1]-2] = great_hall;	// victory card
	memcpy(&control, &state, sizeof(struct gameState)); // copy new game state to control state
	ce_Tribute(&state);
	runTests(&state, &control, 2, 0, 2);	

    return 0;
}