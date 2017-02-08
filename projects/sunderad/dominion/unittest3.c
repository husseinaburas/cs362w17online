#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"

//---------------------------------
//Unit Test For Supply Count Function
//---------------------------------
int main(int argc, char const *argv[])
{
	int i, j;
	int errorFlag=0;
	int players=2;
	int seed=999;
	struct gameState twoPlayerG, copyG;
	int c[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	initializeGame(players, c, seed, &twoPlayerG);

	printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("Running Unit Test 3: Supply Count Function\n");
	printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("\n");

	printf("Testing supplyCount(), Two Player Game\n");
	memcpy(&copyG, &twoPlayerG, sizeof(struct gameState));
	
	for(i=0; i<(treasure_map+1); i++){
		for(j=0; j<10; j++){
			if(i==c[j] && supplyCount(i, &twoPlayerG) != twoPlayerG.supplyCount[i]){
				printf("Error with starting Supply Count of Kingdom Card %d, Position in array: %d\n, Should be 10 is %d", c[j], j, supplyCount(i, &twoPlayerG));
				errorFlag++;
			}
		}
		if(i == copper && supplyCount(i, &twoPlayerG) != twoPlayerG.supplyCount[i]){
			printf("Error with starting Supply Count of Copper Card, Should be 46 is %d\n", supplyCount(i, &twoPlayerG));
			errorFlag++;
		}
		if(i == silver && supplyCount(i, &twoPlayerG) != twoPlayerG.supplyCount[i]){
			printf("Error with starting Supply Count of Silver Card, Should be 40 is %d\n", supplyCount(i, &twoPlayerG));
			errorFlag++;
		}
		if(i == gold && supplyCount(i, &twoPlayerG) != twoPlayerG.supplyCount[i]){
			printf("Error with starting Supply Count of Gold Card, Should be 30 is %d\n", supplyCount(i, &twoPlayerG));
			errorFlag++;
		}
		if(i == estate && supplyCount(i, &twoPlayerG) != twoPlayerG.supplyCount[i]){
			printf("Error with starting Supply Count of Estate Card, Should be 8 is %d\n", supplyCount(i, &twoPlayerG));
			errorFlag++;
		}
		if(i == duchy && supplyCount(i, &twoPlayerG) != twoPlayerG.supplyCount[i]){
			printf("Error with starting Supply Count of Duchy Card, Should be 8 is %d\n", supplyCount(i, &twoPlayerG));
			errorFlag++;
		}
		if(i == province && supplyCount(i, &twoPlayerG) != twoPlayerG.supplyCount[i]){
			printf("Error with starting Supply Count of Province Card, Should be 8 is %d\n", supplyCount(i, &twoPlayerG));
			errorFlag++;
		}
		if(i == curse && supplyCount(i, &twoPlayerG) != twoPlayerG.supplyCount[i]){
			printf("Error with starting Supply Count of Curse Card, Should be 10 is %d\n", supplyCount(i, &twoPlayerG));
			errorFlag++;
		}
		if(i == feast || i == gardens || i == remodel || i == baron || i == great_hall || i == steward || i == ambassador || i == outpost || i == salvager || i == treasure_map){
			if(supplyCount(i, &twoPlayerG) != twoPlayerG.supplyCount[i]){
				printf("Error with starting Supply Count of Unused Card, Should be -1 is %d\n", supplyCount(i, &twoPlayerG));
				errorFlag++;
			}
		}
		
	}

	printf("\n");
	
    printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
   	printf("Unit Test 3 Complete: %d Total Errors\n",errorFlag);
    printf("-------------------------------------------------------------------------------------------------------------------------------------\n");

	return 0;
}