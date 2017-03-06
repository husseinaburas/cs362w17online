#include "dominion.h"
#include "dominion_helpers.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "rngs.h"

void display_usage(void)
{
	printf("Provide a seed value\n");
}

struct globalArgs_t
{
	int seed_value;
} globalArgs;

static const char *opt_string = ":hs:";

int get_options(int argc, char** argv)
{
	extern char *optarg;
	extern int optind, optopt, opterr;

	int c;

	while ((c = getopt(argc, argv, opt_string)) != -1)
	{
		switch (c)
		{
		case 's':
			globalArgs.seed_value = (int) strtol(optarg,NULL,10);
			break;
		case 'h':
			display_usage();
			break;
		case  '?':
			display_usage();
			break;
		default:
			break;
		}
	}

	return 0;
}

int test_playVillage(struct gameState *_state)
{
	int result;
	int handPos;

	struct gameState state;

	memcpy(&state, _state, sizeof(struct gameState));

	handPos = 1;

	//+1 Card
	if (drawCard(whoseTurn(&state), &state))
		return -1;

	//+2 Actions
	state.numActions += 2;
	// Discard played card from hand
	if (discardCard(handPos, whoseTurn(&state), &state, 0))
		return -1;

	result = playVillage(&state, handPos);

	if (memcmp(&state, _state, sizeof(struct gameState)))
		result = -1;

	return result;
	return 0;
}

int main(int argc, char** argv)
{
	struct gameState state;

	int i, j, players;
	int result = 1;

	if (argc == 1)
		globalArgs.seed_value = (int)floor(Random() * 256);
	else if (argc == 2)
		globalArgs.seed_value = (int)strtol(argv[1], NULL, 10);
	else
		get_options(argc, argv);

	PutSeed(-1);

	//for (i = 0; i < 2000; i++)
	for (i = 0; i < 2000; i++)
	{
		for (j = 0; j < sizeof(struct gameState); j++)
			((char*)&state)[j] = floor(Random() * 256);

		players = floor(Random() * 2);
		state.whoseTurn = players;
		state.handCount[players] = 10;
		state.deckCount[players] = floor(Random() * MAX_DECK);
		state.discardCount[players] = floor(Random() * MAX_DECK);
		state.handCount[players] = floor(Random() * MAX_HAND);
		result = test_playVillage(&state);
	}

	return 0;
}
