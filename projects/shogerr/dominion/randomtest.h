#include <assert.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int *intdup(int const *, size_t);

/**
 * Base class.
 */
typedef struct SomeTest
{
	int (*generate)(struct SomeTest *test);
} SomeTest;

int some_test_generate(SomeTest *);

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
} ATest;

int a_test_generate(SomeTest *);

void a_test_new(ATest *);

int a_test_init_state(ATest *, int, int);

int a_test_some_card(SomeTest *, int (*f)(struct gameState *));

int a_test_some_card__hand_pos( SomeTest *, int (*f)(struct gameState *, int));
