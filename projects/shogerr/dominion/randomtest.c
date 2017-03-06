#include <assert.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int *intdup(int const *src, size_t len)
{
	int *p = malloc(len * sizeof(int));
	assert(p!=NULL);
	memcpy(p, src, len * sizeof(int));
	return p;
}

/**
 * Base class.
 */
typedef struct SomeTest
{
	int (*generate)(const struct SomeTest *test);
}
SomeTest;

int some_test_generate(const SomeTest *test)
{
	return test->generate(test);
}

/**
 * Inherited test class.
 */
typedef struct ATest
{
	SomeTest test;
	struct gameState state;
	int *kingdoms;
	int max_players;
	int length;
}
ATest;

static int a_test_generate(const SomeTest *t)
{
	int i;
	int n;
	const ATest *test = (const ATest *) t;

	SelectStream(0);
	PutSeed(-1);
	PlantSeeds(1);

	// Provide us with a random game state
	for (i = 0; i < sizeof((struct gameState)test->state); i++)
	{
		n = (char)floor(Random()*256);
		((char*)&test->state)[i] = abs(n);
	}

	return test->length;
}

int a_test_init_state(const ATest *t, int players, int seed)
{
	return (initializeGame(players, (int*)t->kingdoms, seed, (struct gameState *)&t->state));
}

int a_test_some_card(const SomeTest *t, int (*f)(struct gameState*))
{
	const ATest *test = (const ATest *) t;

	//printf("%i", whoseTurn((struct gameState *)&test->state));
	(*f)((struct gameState *)&test->state);

	return 0;
}

int a_test_some_card__hand_pos(const SomeTest *t, int (*f)(struct gameState*, int))
{
	const ATest *test = (const ATest *) t;

	(*f)((struct gameState *)&test->state, whoseTurn((struct gameState *)&test->state));

	return 0;
}

void a_test_new(ATest *t)
{
	t->length = 1; // set test runs

	int kingdoms[10] = { adventurer, council_room, feast, gardens, mine,
				remodel, smithy, village, baron, great_hall };

	t->kingdoms = intdup(kingdoms, sizeof(kingdoms)); // set kingdoms

	t->max_players = MAX_PLAYERS; // set players

	t->test.generate = a_test_generate; // overload a function

	// Run the function
	//t->test.generate((SomeTest*)t);
}

void print_state(ATest *t)
{
	int i;
	for (i = 0; i < sizeof((struct gameState)t->state); i++)
		printf("%i\n", ((char*)&t->state)[i]);
}

/**
 * Program entrance.
 */

int main(int argc, char** argv)
{
	ATest t1;

	a_test_new(&t1);

	// Init the game
	a_test_init_state(&t1, MAX_PLAYERS, floor(Random()*256)+1);

	// Call a card
	a_test_some_card__hand_pos((SomeTest*)&t1, playSmithy);

	//print_state(&t1);

	return 0;
}
