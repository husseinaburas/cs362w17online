#include <stdio.h>
#include <stdlib.h>

void zAssert(int result, int testNumber){
	if(result){
		printf("Test Case %d: Passed\n", testNumber);
	}else{
		printf("Test Case %d: Failed\n", testNumber);

	}

}


