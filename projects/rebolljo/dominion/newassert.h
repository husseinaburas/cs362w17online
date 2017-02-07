#include <stdlib.h> 
#include <stdio.h>

void newassert(int result){
	if(result == 1){
		printf("TEST SUCCESSFUL\n");
	}
	else{
		printf("TEST FAILURE\n");
	}
	return;
}