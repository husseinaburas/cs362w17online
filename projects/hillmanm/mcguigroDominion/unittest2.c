/* matthew hillman
 * unittest2.c getCost()
 * 
 */

  
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTUNIT "getCost"

void my_assert(int test, char* msg)
{
	if (!test) {
		printf ("ASSERT HAS FAILED: %s\n", msg);
	}
	return;
}

int main() {
	int i, r;
 
 
	printf("----------------- Testing Unit: %s ----------------\n", TESTUNIT);

 
//check boundaries and normal expected values 
	for (i = -2; i < 30; i++){
		r = getCost(i);

		if (i == -2) {
			my_assert(r == -1, "msg1");
		}
		if (i == -1) {
			my_assert(r == -1, "msg1");
		}
		if (i == 0) {
			my_assert(r == 0, "msg1");
		}
		if (i == 27) {
			my_assert(r == -1, "msg1");
		}
		if (i > 27) {
			my_assert(r == -1, "msg1");
		}
		if ((i > 0) && (i < 27)) {
			my_assert(r != -1, "msg1");
			my_assert((r > -1 && r < 9), "msg1");
		}
	}

//check large positive and negative	
	
		r = getCost(1000000);
		my_assert(r == -1, "msg2");
		
		r = getCost(-1000000);
		my_assert(r == -1, "msg2");
		
		
//check some specific values	
	
		r = getCost(5);
		my_assert(r == 3, "msg3");
		
		r = getCost(10);
		my_assert(r == 4, "msg3");
			
		r = getCost(26);
		my_assert(r == 4, "msg3");
		
		r = getCost(20);
		my_assert(r == 3, "msg3");
					
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTUNIT);


	return 0;
}


