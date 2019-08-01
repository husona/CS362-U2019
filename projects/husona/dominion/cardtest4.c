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
    int numPlayers = 3;
	int players[MAX_PLAYERS] = {0};
    int kingdom[10] = {ambassador, minion, tribute, gardens, mine, remodel, smithy, village, baron, great_hall};
			   
    struct gameState state, control;
	
	initializeGame(numPlayers, kingdom, seed, &state);
	memcpy(&control, &state, sizeof(struct gameState)); // copy initial game state to control state
	
	printf("testing getWinners function...\n");
	getWinners(players, &state);
	
	for(i = 0; i < numPlayers; i++)
	{
		printf("Verify player %d did not lose any cards:\n", i + 1);
		if(_fullCardCount(&state, i) == _fullCardCount(&control, i))
		{	
			printf("\tPassed: player %d has the same number of cards.\n", i+1);
		}
		else
		{
			printf("\tFailed: player %d card count changed from %d to %d.\n", i+1, _fullCardCount(&control, i), _fullCardCount(&state, i));
		}
	}
	// from initialized game should be a tie for everyone except player 1
	printf("Verify player 1 lost the game:\n");
	if(players[0] == 0)
	{	
		printf("\tPassed: player 1 correctly determined to be loser.\n");
	}
	else
	{
		printf("\tFailed: player 1 determined to be a winner.\n");
	}
	
	printf("Verify players 2 and 3 are winner:\n");
	if(players[1] == 1 && players[2] == 1)
	{
		printf("\tPassed: players 2 and 3 determined to be winners.\n");
	}
	else if (players[1] == 1)
	{
		printf("\tFailed: player 3 not determined to be a winner.\n");
	}
	else if (players[2] == 1)
	{
		printf("\tFailed: player 2 not determined to be a winner.\n");
	}
	else
	{
		printf("\tFailed: neither player 2 or player 3 were determined to be a winner.\n");
	}
	
	memcpy(&state, &control, sizeof(struct gameState)); // convert state back to control state
	// set player 1's hand to known state (all province)
	for(i = 0; i < state.handCount[0]; i++)
	{
		state.hand[0][i] = province;
	}
	// set players 1's deck to a known state (all province)
	for(i = 0; i < state.deckCount[0]; i++)
	{
		state.deck[0][i] = province;
	}
	// set decks for other players (all curses)
	for(i = 0; i < state.deckCount[1]; i++)
	{
		state.deck[1][i] = curse;
		state.deck[2][i] = curse;
	}
	
	getWinners(players, &state);
	printf("Verify player 1 won the game:\n");
	if(players[0] == 1)
	{	
		printf("\tPassed: player 1 correctly determined to be winner.\n");
	}
	else
	{
		printf("\tFailed: player 1 not determined to be a winner.\n");
	}
	
	printf("Verify no other players indicated as winner:\n");
	j = 0;
	for(i = 1; i < MAX_PLAYERS; i++)
	{	
		if(players[i] == 1)
		{
			j++;
		}
	}
	if(j == 0)
	{
		printf("\tPassed: no other players determined to be a winner.\n");
	}
	else
	{
		printf("\tFailed: %d other players determined to be winners.\n", j);
	}

    return 0;
}