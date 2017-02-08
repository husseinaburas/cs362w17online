//Name:				unittest1.c
//Assignment:		Assignment 3
//Author:				Benjamin Ford
//Date:					2/5/2017
//Description:		Unit test for kingdomCards function

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define TESTFUN "KINGDOMCARDS"

int assertInKindomCards(int kCard, int* ptrKCards){
	int i;
	for(i = 0; i < 10; i++){
		if(kCard == ptrKCards[i]){
			return 1;
		}
	}
	return 0;
}

int assertSameOrder (int kCard, int* ptrKCards){
	if(kCard == ptrKCards){
		return 1;
	}
	else{
		return 0;
	}
}

int main(){
	const int kCards[] = {adventurer, smithy, village, baron, great_hall, minion, steward, council_room, mine, sea_hag};
	int i;
	int failedFlg = 0;
	int testsPassed = 1;
	int* kCardsIntPtr, kCardsIntPtrBad;
	
	kCardsIntPtr = kingdomCards(adventurer, smithy, village, baron, great_hall, minion, steward, council_room, mine, sea_hag);
	kCardsIntPtrBad = kingdomCards(tribute, smithy, village, baron, great_hall, minion, steward, council_room, mine, sea_hag);
	
	printf("----------------- Testing Fucntion: %s ----------------\n", TESTFUN);
	
	//Verify Card is in kingdomCards set
	for(i = 0; i < 10; i++){
		if(assertInKindomCards(kCards[i],kCardsIntPtr)==0){
			printf("TEST FAILED\n");
			testsPassed = 1;
		}
	}
	
	//Verify that adventurer wasnt in the bad set
	for(i = 0; i < 10; i++){
		if(assertInKindomCards(kCards[i],kCardsIntPtrBad)==0){
				failedFlg = 1;
		}
	}
	
	if(!failedFlg){
		printf("TEST FAILED\n");
		testsPassed = 1;
	}
	
	//Verify They are in the same order
	for(i = 0; i < 10; i++){
		if(assertSameOrder(kCards[i],kCardsIntPtr[i])==0){
			printf("TEST FAILED\n");
			testsPassed = 1;
		}
	}
	
	if(testsPassed){
		printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTFUN);
	}
	else{
		printf("A Test Failed\n");
	}
	
	return 0;
}