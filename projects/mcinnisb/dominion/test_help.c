#ifndef TEST_HELP_H
#define TEST_HELP_H

#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "test_help.h"

void assertIsEqual(char *msg, int a, int b) //change to use void pointers
{
    if (a == b)
	printf("TEST CASE %s PASSED.\n", msg);
    else
	printf("TEST CASE %s FAILED.\n", msg);
}

int assertIsValid(char *msg, int player, struct gameState *state)
{
    if (player >= state->numPlayers)
    {
	printf("TEST CASE %s FAILED: Invalid Index.\n", msg);
	return 0;
    }
    else
    {
	printf("TEST CASE %s PASSED.\n", msg);
	return 1;
    }
}

#endif
