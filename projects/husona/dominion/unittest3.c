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
	state.hand[0][0] = ambassador;	// initialize players first card to ambassador
	state.hand[0][1] = curse;	// initialize the next two cards to curse
	state.hand[0][2] = curse;
	state.hand[0][3] = curse;
	memcpy(&control, &state, sizeof(struct gameState)); // copy initial game state to control state
	
	// begin testing
	printf("testing ambassador card play...\n");
	for(j = 1; j < 3; j++)
	{
		i = playAmbassador(&state, 0, 1, j);	// play Ambassador card with curse card selected and 2 copies to return
		
		printf("Test that function returned normally:\n");
		if(i == 0)
		{	
			printf("\tPassed: function returned normally.\n");

		}
		else
		{
			printf("\tFailed: function returned %d.\n", i);
		}
		
		printf("Test that players card count decreased by %d:\n", j);
		if(_fullCardCount(&state, 0) == _fullCardCount(&control, 0) - j)
		{
			printf("\tPassed: players cardcount decreased by %d.\n", j);
		}
		else
		{
			printf("\tFailed: number of cards changed from %d to %d.\n", _fullCardCount(&control, 0), _fullCardCount(&state, 0));
		}
		
		printf("Test that the supply of curses increased by %d:\n", j - 1);	// j returned to pile and one given to player 2
		if(supplyCount(curse, &state) == supplyCount(curse, &control) + j - 1)
		{	
			printf("\tPassed: curse supply increased by %d.\n", j - 1);
		}
		else
		{
			printf("\tFailed: curse supply changed from %d to %d.\n", supplyCount(curse, &control), supplyCount(curse, &state));
		}
		
		printf("Test that the number of curses held by player 1 decreased by %d:\n", j);
		if(fullDeckCount(0, curse, &state) == fullDeckCount(0, curse, &control) - j)
		{
			printf("\tPassed: player 1 has %d fewer curse(s).\n", j);
		}
		else
		{
			printf("\tFailed: player 1 curses changed from %d to %d.\n", fullDeckCount(0, curse, &control), fullDeckCount(0, curse, &state));
		}
		
		printf("Test that the number of curses held by player 2 increased by 1:\n");
		if(fullDeckCount(1, curse, &state) == fullDeckCount(1, curse, &control) + 1)
		{
			printf("\tPassed: player 2 has 1 additional curse.\n");
		}
		else
		{
			printf("\tFailed: player 2 curses changed from %d to %d.\n", fullDeckCount(1, curse, &control), fullDeckCount(1, curse, &state));
		}
		
		printf("Test that only 1 card was discarded:\n");
		if(state.discardCount[0] == control.discardCount[0] + 1)
		{
			printf("\tPassed: Only one card discarded.\n");
		}
		else
		{
			printf("\tFailed: number of discarded cards: %d.\n", state.discardCount[0] - control.discardCount[0]);
		}
		
		memcpy(&state, &control, sizeof(struct gameState)); // reset the state to the control state
	}

    return 0;
}