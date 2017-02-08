/*
File: unittest3.c
Author: Brent Nolan
Description:  This is a unit test for the getCost function in dominion.c


*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rngs.h"

int expectedValue[] = {0, 2, 5, 8, 0, 3, 6, 6, 5, 4, 4, 5, 4, 4, 3, 4, 3, 5, 3, 5, 3, 4, 2, 5, 4, 4, 4, -1};


int testGetCost(int cardNumber){
	int returnedCost = getCost(cardNumber);
	
	if (returnedCost == expectedValue[cardNumber]){
		printf("Expected value: %d\n Returned value: %d\n", expectedvalue[cardNumber], returnedCost);
		return 1; 
	}
	
	else if (returnedCost != expectedValue[cardNumber]){
		printf("Expected value: %d\n Returned value: %d\n", expectedvalue[cardNumber], returnedCost);
		return 0; 
	}


}


int main(){
	int i, x;
	int passed = 1;
	for (i = curse; i <= treasure_map; i++){
		x = testGetCost(i);
		if (x == 0){
			passed = 0;
		}
	}
	
	if (passed == 0){
		printf("TEST FAILED\n");
	}
	
	else{
		printf("TEST PASSED\n");
	}
	
	return 0;
}