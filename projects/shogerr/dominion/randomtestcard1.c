#include "dominion.h"
#include "dominion_helpers.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
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

int test_playSmithy(struct gameState *_state)
{
	int i, result;

	struct gameState state;


	memcpy(&state, _state, sizeof(struct gameState));

	for (i = 0; i < 3; i++)
	{
		if (drawCard(state.numPlayers-1, &state))
			return -1;
	}

	// Discard card from hand
	if(discardCard(state.handCount[state.numPlayers-1], state.numPlayers-1, &state, 0))
		return -1;

	result = playSmithy(&state, state.handCount[state.numPlayers-1]);

	if (memcmp(&state, _state, sizeof(struct gameState)))
		result = -1;

	return result;
}

int main(int argc, char** argv)
{
	struct gameState state;

	int i, j, players;
	int result = 1;

	if (argc == 1)
		globalArgs.seed_value = (int)floor(Random() * 9) + 1;
	else if (argc == 2)
		globalArgs.seed_value = ((int)strtol(argv[1], NULL, 10) % 9)+1;
	else
		get_options(argc, argv);

	PutSeed(globalArgs.seed_value);

	//for (i = 0; i < 2000; i++)
	while(result != 0)
	{
		for (j = 0; j < sizeof(struct gameState); j++)
			((char*)&state)[j] = floor(Random() * 256);

		players = floor(Random() * 2);
		state.whoseTurn = floor(Random() * (players));
		state.deckCount[players] = floor(Random() * MAX_DECK);
		state.discardCount[players] = floor(Random() * MAX_DECK);
		state.handCount[players] = floor(Random() * MAX_HAND);
		result = test_playSmithy(&state);
	}

	return 0;
}
