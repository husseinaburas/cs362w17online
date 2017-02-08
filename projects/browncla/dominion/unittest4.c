/*unittest4.c*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#define FUNCTION_NAME "isGameOver"


//Own assert function
int asserttrue(int input, int number){
	if (input){
		printf("\tTEST %d SUCCESSFUL\n", number);
	}
	else
		printf("\tTEST %d FAILED\n", number);
	return 0;
}

int main(){

	int i, result, success, tester;
    int seed = 1000;
    int numPlayers = 2;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	int preSupply[treasure_map + 1]; 
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	// Getting prior info for testing
	for (i = 0; i <= treasure_map; i++){
		preSupply[i] = G.supplyCount[i];
	}

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	printf("----------------- Function: %s ----------------\n", FUNCTION_NAME);
	// DURING THE GAME
	printf("IMMEDIATELY AFTER INITIALIZATION\n");
	result = isGameOver(&testG);
	// ----------- TEST 1: Test result from isGameOver should be 0 -----------
	printf("%s TEST 1: Result from function call should be 0\n", FUNCTION_NAME);
	if (result == 0){
		asserttrue(1, 1);
	}
	else{
		asserttrue(0, 1);
	}
	// ----------- TEST 2: Test supplyCount[province] doesn't change -----------
	printf("%s TEST 2: supplyCount[province] does not change\n", FUNCTION_NAME);
	if (testG.supplyCount[province] == preSupply[province]){
		asserttrue(1, 2);
	}
	else{
		asserttrue(0, 2);
	}
	// ----------- TEST 3: Test supplyCount[province] is not equal to 0 -----------
	printf("%s TEST 3: supplyCount[province] is not equal to 0\n", FUNCTION_NAME);
	if (testG.supplyCount[province] == 0){
		asserttrue(0, 3);
	}
	else{
		asserttrue(1, 3);
	}
	// ----------- TEST 4: Test supplyCounts do not change -----------
	printf("%s TEST 4: Supply counts do not change for any card\n", FUNCTION_NAME);
	for (i = 0; i < treasure_map; i++){
		if (preSupply[i] != testG.supplyCount[i]){
			asserttrue(0, 4);
			success = 0;
			break;
		}
		else{
			success = 1;
		}
	}
	if (success == 1){
		asserttrue(1, 4);
	}
	// ----------- TEST 5: Test no three supply counts are 0 -----------
	tester = 0;
	printf("%s TEST 5: No three supply counts are 0\n", FUNCTION_NAME);
	for (i = 0; i < treasure_map; i++){
		if (testG.supplyCount[i] == 0){
			tester ++;
		}
	}
	if (tester >= 3){
		asserttrue(0, 5);
	}
	else{
		asserttrue(1, 5);
	}


	// NO PROVINCE CARDS

	printf("\nENDING GAME BASED ON 0 PROVINCE CARDS\n");
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	// Setting up to test that game should be over
	G.supplyCount[province] = 0;
	for (i = 0; i <= treasure_map; i++){
		preSupply[i] = G.supplyCount[i];
	}


	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	result = isGameOver(&testG);
	// ----------- TEST 6: Test result from is GameOver should be 1 -----------
	printf("%s TEST 6: Result from function call should be 1\n", FUNCTION_NAME);
	if (result == 1){
		asserttrue(1, 6);
	}
	else{
		asserttrue(0, 6);
	}
	// ----------- TEST 7: Test supplyCount doesn't change for any cards -----------
	printf("%s TEST 7: Supply counts do not change for any card\n", FUNCTION_NAME);
	for (i = 0; i < treasure_map; i++){
		if (preSupply[i] != testG.supplyCount[i]){
			asserttrue(0, 7);
			success = 0;
			break;
		}
		else{
			success = 1;
		}
	}
	if (success == 1){
		asserttrue(1, 7);
	}
	// ----------- TEST 8: Test supplyCount[province] = 0 -----------
	printf("%s TEST 8: supplyCount[province] == 0\n", FUNCTION_NAME);
	if (testG.supplyCount[province] == 0){
		asserttrue(1, 8);
	}
	else{
		asserttrue(0, 8);
	}
	// 3 SUPPLY PILES AT 0
	printf("\nENDING GAME BASED ON SUPPLY COUNT FOR 3 PILES\n");

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	G.supplyCount[remodel] = 0;
	G.supplyCount[mine] = 0;
	G.supplyCount[council_room] = 0;
	for (i = 0; i <= treasure_map; i++){
		preSupply[i] = G.supplyCount[i];
	}

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	result = isGameOver(&testG);
	// ----------- TEST 9: Test result from is GameOver should be 1 -----------
	printf("%s TEST 9: Result from function call should be 1\n", FUNCTION_NAME);
	if (result == 1){
		asserttrue(1, 9);
	}
	else{
		asserttrue(0, 9);
	}
	// ----------- TEST 10: Test supplyCount doesn't change for any cards -----------
	printf("%s TEST 10: Supply counts do not change for any card\n", FUNCTION_NAME);
	for (i = 0; i < treasure_map; i++){
		if (preSupply[i] != testG.supplyCount[i]){
			asserttrue(0, 10);
			success = 0;
			break;
		}
		else{
			success = 1;
		}
	}
	if (success == 1){
		asserttrue(1, 10);
	}
	// ----------- TEST 11: Test 3 piles have a count of 0 -----------
	printf("%s TEST 11: 3 piles of supply cards have a count of 0\n", FUNCTION_NAME);
	for (i = 0; i < treasure_map; i++){
		if (testG.supplyCount[i] == 0){
			result ++;
		}
	}
	if (result >= 3){
		asserttrue(1, 11);
	}
	else{
		asserttrue(0, 11);
	}
	return 0;
}