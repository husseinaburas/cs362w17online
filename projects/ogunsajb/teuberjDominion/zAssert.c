#include <stdio.h>
#include <stdlib.h>

void zAssert(int result, int testNumber){
	if(result){
		printf("Test Case %d: PASSED\n",testNumber);
	}else{
		printf("Test Case %d: FAILED\n",testNumber);
	}
}	 
