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
	int i, j, k, l;
    int seed = 1000;
    int kingdom[10] = {ambassador, minion, tribute, gardens, mine, remodel, smithy, village, baron, great_hall};
	int badKingdom[10] = {mine, mine, mine, mine, mine, mine, mine, mine, mine, mine};
			   
    struct gameState state;
	printf("testing initializeGame function...\n");
	printf("Test: attempt to start game with 0 players:\n");
	if(initializeGame(0, kingdom, seed, &state) == -1)
	{
		printf("\tPassed: function returned failure.\n");
	}
	else
	{
		printf("\tFailed: function returned success.\n");
	}
	
	printf("Test: attempt to start game with 2 players:\n");
	if(initializeGame(2, kingdom, seed, &state) == 0)
	{
		printf("\tPassed: function returned success.\n");
	}
	else
	{
		printf("\tFailed: function returned failure.\n");
	}
	
	printf("Test: check handCount of player 1 (should be 5):\n");
	if(state.handCount[0] == 5)
	{
		printf("\tPassed: player 1 has 5 cards in hand.\n");
	}
	else
	{
		printf("\tFailed: player 1 has %d cards in their hand.\n", state.handCount[0]);
	}
	
	printf("Test: check handCount of player 2 (should be 0):\n");
	if(state.handCount[0] == 5)
	{
		printf("\tPassed: player 2 has 0 cards in hand.\n");
	}
	else
	{
		printf("\tFailed: player 2 has %d cards in their hand.\n", state.handCount[1]);
	}
	
	printf("Test: attempt to start game with bad kingdom (all mines):\n");
	if(initializeGame(2, badKingdom, seed, &state) == -1)
	{
		printf("\tPassed: function returned failure.\n");
	}
	else
	{
		printf("\tFailed: function returned success.\n");
	}
	
	printf("Test: attempt to start game with MAX_PLAYERS (%d) players:\n", MAX_PLAYERS);
	if(initializeGame(MAX_PLAYERS, kingdom, seed, &state) == 0)
	{
		printf("\tPassed: function returned success.\n");
	}
	else
	{
		printf("\tFailed: function returned failure.\n");
	}

	printf("Test: verify all cards in hands/decks are either estates or copper:\n");
	k = 0;
	l = 0;
	for(i = 0; i < MAX_PLAYERS; i++)
	{
			for(j = 0; j < state.handCount[i]; j++)
			{
				if(state.hand[i][j] != copper && state.hand[i][j] != estate)
				{
					k++;
				}
				l++;
			}
			for(j = 0; j < state.deckCount[i]; j++)
			{
				if(state.deck[i][j] != copper && state.deck[i][j] != estate)
				{
					k++;
				}
				l++;
			}
	}
	if(k == 0)
	{
		printf("\tPassed: all cards in hands and decks are copper or estate cards.\n");
	}
	else
	{
		printf("\tFailed: %d of %d cards were not copper or estate cards.\n", k, l);
	}
	

    return 0;
}