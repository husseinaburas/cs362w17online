//Name:				unittest4.c
//Assignment:		Assignment 3
//Author:				Benjamin Ford
//Date:					2/5/2017
//Description:		Unit test for getCost function

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define TESTFUN "GET COST"

int testCardCost(int card,int cost){
	int returnCost = -1;
	
	returnCost = getCost(card);
	if(returnCost == cost){
		return 1;
	}
	return 0;
}

int testFakeCard(int card){
	int returnCost = -1;
	
	returnCost = getCost(card);
	
	if(returnCost == -1){
		return 1;
	}
	
	return 0;
}

//Test if kingdom cards have changed
int testSupply(struct gameState *old, struct gameState *new){
	int i;
	
	for (i = 0; i < 10; i++){
		if(old->supplyCount[i] != new->supplyCount[i]){
			return 0;
		}
	}
	return 1;
}

int main(){
	const int kCards[] =  {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	const int players = 2;
	const int gameSeed = 5;
	int testsPassed = 1;
	
	printf("----------------- Testing Fucntion: %s ----------------\n", TESTFUN);
	
	//Test copper cost (0)
	if(testCardCost(copper,0)==0){
		printf("TEST FAILED\n");
		testsPassed = 0;
	}
	
	//Test embargo (2)
	if(testCardCost(embargo,2)==0){
		printf("TEST FAILED\n");
		testsPassed = 0;
	}
	
	//Should fail
	//Test silver (3), inputting 10
	if(testCardCost(silver,10)){
		printf("TEST FAILED\n");
		testsPassed = 0;
	}
	

	//Test a card that doesnt exist
	//There is no card 30 in enum CARD
	if(testFakeCard(30)==0){
		printf("TEST FAILED\n");
		testsPassed = 0;
	}
		

	
	if(testsPassed){
		printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTFUN);
	}
	else{
		printf("A Test Failed\n");
	}
	
	return 0;
}