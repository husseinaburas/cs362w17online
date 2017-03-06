#include <unistd.h>
#include "randomtest.h"

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

int test_playAdventurer(struct gameState *_state)
{
	int temphand[MAX_HAND];
	int cardDrawn;
	int drawnTreasure = 0;
	int z = 0;
	int result;

	struct gameState state;

	//a_test_generate((SomeTest*)&t);

	memcpy(&state, _state, sizeof(struct gameState));

	while (drawnTreasure < 2)
	{
		if (state.deckCount[whoseTurn(&state)] < 1)
			shuffle(whoseTurn(&state), &state);

		drawnTreasure++;
		drawCard(whoseTurn(&state), &state);

		cardDrawn = state.hand[whoseTurn(&state)][state.handCount[whoseTurn(&state)]-1];

		if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
			drawnTreasure++;
		else
		{
			temphand[z] = cardDrawn;
			state.handCount[whoseTurn(&state)]--;
			z++;
		}
	}

	while (z-1 >= 0)
	{
		state.discard[whoseTurn(&state)][state.discardCount[whoseTurn(&state)]++] = temphand[z-1];
		z = z-1;
	}

	//result = a_test_some_card((SomeTest*)&t, playAdventurer);

	result = playAdventurer(&state);

	return result;
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
	while(result != 0)
	{
		for (j = 0; j < sizeof(struct gameState); j++)
			((char*)&state)[j] = floor(Random() * 256);

		players = floor(Random() * 2);
		state.whoseTurn = floor(Random() * (players));
		state.deckCount[players] = floor(Random() * MAX_DECK);
		state.discardCount[players] = floor(Random() * MAX_DECK);
		state.handCount[players] = floor(Random() * MAX_HAND);
		result = test_playAdventurer(&state);
	}

	return 0;
}

/*
void some_class()
{
	ATest t;
	a_test_new(&t);
	a_test_init_state(&t, MAX_PLAYERS, globalArgs.seed_value);
}
*/
