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
	// set player 1's hand to known state
	for(i = 0; i < state.handCount[0]; i++)
	{
		state.hand[0][i] = kingdom[(i % 10)];
	}
	// set players deck to a known state
	for(i = 0; i < state.deckCount[0]; i++)
	{
		state.deck[0][i] = kingdom[(i % 10)];
	}
	memcpy(&control, &state, sizeof(struct gameState)); // copy initial game state to control state
	printf("testing shuffle function...\n");
	printf("Test: shuffling player 1 deck\n");
	if(shuffle(0, &state) == 0)
	{
		printf("\tPassed: function returned success.\n");
	}
	else
	{
		printf("\tFailed: function returned failure.\n");
	}

	printf("Test: Make sure player 1 handCount is unchanged\n");
	if(state.handCount[0] == control.handCount[0])
	{
		printf("\tPassed: player 1 handCount did not change.\n");
		
		printf("Test: Make sure player 1 hand is unchanged\n");
		j = 0;
		for(i = 0; i < state.handCount[0]; i++)
		{
			if(state.hand[0][i] != control.hand[0][i])
			{
				j++;
			}
		}
		if(j == 0)
		{
			printf("\tPassed: player 1\'s hand did not change.\n");
		}
		else
		{
			printf("\tFailed: %d cards in player 1\'s hand changed.\n", j);
		}
	}
	else
	{
		printf("\tFailed: player 1 handCount changed from %d to %d.\n",control.handCount[0], state.handCount[0]);
	}
	
	printf("Test: Make sure player 1\'s deckCount is unchanged\n");
	if(state.deckCount[0] == control.deckCount[0])
	{
		printf("\tPassed: player 1 deckCount did not change.\n");
		
		printf("Test: Make sure player 1 deck has changed\n");
		j = 0;
		for(i = 0; i < state.deckCount[0]; i++)
		{
			if(state.deck[0][i] != control.deck[0][i])
			{
				j++;
			}
		}
		if(j != 0)
		{
			printf("\tPassed: player 1\'s deck is shuffled, %d of %d cards have changed locations in the deck.\n", j, state.deckCount[0]);
		}
		else
		{
			printf("\tFailed: in player 1\'s deck of %d cards, no card positions have changed.\n", state.deckCount[0]);
		}
	}
	else
	{
		printf("\tFailed: player 1 deckCount changed from %d to %d.\n",control.deckCount[0], state.deckCount[0]);
	}
	
	printf("Test: Make sure player 2 handCount is unchanged\n");
	if(state.handCount[1] == control.handCount[1])
	{
		printf("\tPassed: player 2 handCount did not change.\n");
		
		printf("Test: Make sure player 2 hand is unchanged\n");
		j = 0;
		for(i = 0; i < state.handCount[1]; i++)
		{
			if(state.hand[1][i] != control.hand[1][i])
			{
				j++;
			}
		}
		if(j == 0)
		{
			printf("\tPassed: player 2\'s hand did not change.\n");
		}
		else
		{
			printf("\tFailed: %d cards in player 2\'s hand changed.\n", j);
		}
	}
	else
	{
		printf("\tFailed: player 2 handCount changed from %d to %d.\n",control.handCount[1], state.handCount[1]);
	}
	
	printf("Test: Make sure player 2\'s deckCount is unchanged\n");
	if(state.deckCount[1] == control.deckCount[1])
	{
		printf("\tPassed: player 2 deckCount did not change.\n");
		
		printf("Test: Make sure player 2 deck has not changed\n");
		j = 0;
		for(i = 0; i < state.deckCount[1]; i++)
		{
			if(state.deck[1][i] != control.deck[1][i])
			{
				j++;
			}
		}
		if(j == 0)
		{
			printf("\tPassed: player 2\'s deck has not changed.\n");
		}
		else
		{
			printf("\tFailed: in player 2\'s deck of %d cards, %d cards have changed positions.\n", state.deckCount[1], j);
		}
	}
	else
	{
		printf("\tFailed: player 2 deckCount changed from %d to %d.\n",control.deckCount[1], state.deckCount[1]);
	}
	
	memcpy(&state, &control, sizeof(struct gameState)); // reset state to control


    return 0;
}