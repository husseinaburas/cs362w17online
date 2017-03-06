//getCost unit test

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rngs.h"
#define TRUE 0
#define FALSE 1

int expectedvalue[] = {0, 2, 5, 8, 0, 3, 6, 6, 5, 4, 4, 5, 4, 4, 3, 4, 3, 5, 3, 5, 3, 4, 2, 5, 4, 4, 4, -1};

int testGetCost(int cardNumber){
	int returnedCost = getCost(cardNumber);
	
	if (returnedCost == expectedvalue[cardNumber]){
		printf("Expected value: %d\n Returned value: %d\n", expectedvalue[cardNumber], returnedCost);
		return TRUE; 
	}
	
	else if (returnedCost != expectedvalue[cardNumber]){
		printf("Expected value: %d\n Returned value: %d\n", expectedvalue[cardNumber], returnedCost);
		return FALSE; 
	}


}


int main(){
	int i, x;
	int passed = 0;
	for (i = curse; i <= treasure_map; i++){
		x = testGetCost(i);
		if (x == FALSE){
			passed = 1;
		}
	}
	
	if (passed == 1){
		printf("TEST FAILED\n");
	}
	
	else{
		printf("TEST PASSED\n");
	}
	
	return 0;
}