#include <stdlib.h>

void assertion(int eval) {
	if(eval) 
		printf("SUCCESS\n\n");
	else
		printf("FAILURE\n\n");
	return;
}


