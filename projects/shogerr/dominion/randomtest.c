#include "randomtest.h"
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
/*
int *fdup(int (**f), size_t len)
{
	//int **p = malloc(len * size
	return p;
}
*/

int some_test_generate(SomeTest *test)
{
	return test->generate(test);
}


/**
 * Generate a completely random state
 */
int a_test_generate(SomeTest *t)
{
	int i;
	int n, p;
	ATest *test = (ATest *) t;

	struct gameState state;

	// Provide us with a random game state
	for (i = 0; i < sizeof(struct gameState); i++)
	{
		n = (char)floor(Random() * 256);
		((char*)&test->state)[i] = n;
	}
	p = (int)floor(Random() * MAX_PLAYERS);
	test->state.deckCount[p] = (int)floor(Random() * MAX_DECK);
	test->state.discardCount[p] = (int)floor(Random() * MAX_DECK);
	test->state.handCount[p] = (int)floor(Random() * MAX_HAND);

	/*
	printf("%i, %i, %i, %i\n ", p, test->state.deckCount[p],
			test->state.deckCount[p],
			test->state.discardCount[p]);
	*/

	return 0;
}

int a_test_init_state(ATest *t, int players, int seed)
{
	return (initializeGame(players, (int*)t->kingdoms, seed, (struct gameState *)&t->state));
}

int a_test_some_card(SomeTest *t, int (*f)(struct gameState *))
{
	ATest *test = (ATest *) t;

	//printf("Calling some function...\n");
	return (*f)((struct gameState *)&test->state);
}

int a_test_some_card__hand_pos(SomeTest *t, int (*f)(struct gameState*, int))
{
	ATest *test = (ATest *) t;

	//printf("Calling some function...\n");
	return (*f)((struct gameState *)&test->state, whoseTurn((struct gameState *)&test->state));
}

int a_test_some_combo(SomeTest *t)
{
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

struct testable {
	int (**f);
	int (**g);
};

/*
int main(int argc, char** argv)
{
	int (*f[1])(struct gameState*, int) = { playSmithy };

	ATest t1;

	a_test_new(&t1);

	// Init the game
	a_test_init_state(&t1, MAX_PLAYERS, floor(Random()*256)+1);

	// Call a card
	a_test_some_card__hand_pos((SomeTest*)&t1, *f[0]);

	//print_state(&t1);

	return 0;
}
*/
