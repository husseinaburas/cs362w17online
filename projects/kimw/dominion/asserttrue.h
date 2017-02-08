#include <stdlib.h>

void asserttrue(int exp){
    if(exp){
    	printf("TEST SUCCESSFULLY COMPLETED.\n");
    }else{
    	printf("TEST FAILED.\n");
    }
    return;
}