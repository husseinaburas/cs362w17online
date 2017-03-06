#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

void asserttrue(char* test_name, int actual, int expected);

int cards_in_hand(struct gameState* state, int player, int card);

int treasure_in_hand(struct gameState* state, int player);