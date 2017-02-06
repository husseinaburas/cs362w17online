#include "dominion.c"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "rngs.c"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define UNIT_ASSERT(conditional, message) \
	if(!conditional) {printf("%s FAILED!\n", message);} \
	else {printf("%s PASSED!\n", message);}
