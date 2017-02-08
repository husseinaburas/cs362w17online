//Name:				unittest2.c
//Assignment:		Assignment 3
//Author:				Benjamin Ford
//Date:					2/5/2017
//Description:		Unit test for updateCoins function

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define TESTFUN "UPDATE COINS"

int addCopper(struct gameState *state, int player){
	//set coins to 0
	state->coins = 0;
	//Sent hand count to 0
	state->handCount[player] = 0;
	
	
	//Hand of player 1 should be empty
	if(state->handCount[player] == 0 && state->coins == 0){
		//Place copper in the players hand
		state->hand[player][0] = copper;
		//Set hand to 1
		state->handCount[player] = 1;
		
		//Update the players coins
		updateCoins(player,state,0);
	}
	
	if(state->coins == 1){
		return 1;
	}
		
	return 0;
}

int addSilver(struct gameState *state, int player){
	//set coins to 0
	state->coins = 0;
	//Sent hand count to 0
	state->handCount[player] = 0;
	
	//Hand of player 1 should be empty
	if(state->handCount[player] == 0 && state->coins == 0){
		//Place copper in the players hand
		state->hand[player][0] = silver;
		//Set hand to 1
		state->handCount[player] = 1;
		
		//Update the players coins
		updateCoins(player,state,0);
	}
	
	if(state->coins == 2){
		return 1;
	}
		
	return 0;
}

int addGold(struct gameState *state, int player){
	//set coins to 0
	state->coins = 0;
	//Sent hand count to 0
	state->handCount[player] = 0;
	
	//Hand of player 1 should be empty
	if(state->handCount[player] == 0 && state->coins == 0){
		//Place copper in the players hand
		state->hand[player][0] = gold;
		//Set hand to 1
		state->handCount[player] = 1;
		
		//Update the players coins
		updateCoins(player,state,0);
	}
	
	if(state->coins == 3){
		return 1;
	}
		
	return 0;
}

int addBonus(struct gameState *state, int player){
	//set coins to 0
	state->coins = 0;
	//Sent hand count to 0
	state->handCount[player] = 0;
	
	//Hand of player 1 should be empty
	if(state->handCount[player] == 0 && state->coins == 0){
		//Update the players coins
		updateCoins(player,state,1);
	}
	
	if(state->coins == 1){
		return 1;
	}
		
	return 0;
}

int addThreeCopper(struct gameState *state, int player){
	//set coins to 0
	state->coins = 0;
	//Sent hand count to 0
	state->handCount[player] = 0;
	
	//Hand of player 1 should be empty
	if(state->handCount[player] == 0 && state->coins == 0){
		//Place coppers in the players hand
		state->hand[player][0] = copper;
		state->hand[player][1] = copper;
		state->hand[player][2] = copper;
		//Set hand to 3
		state->handCount[player] = 3;
		
		//Update the players coins
		updateCoins(player,state,0);
	}
	
	if(state->coins == 3){
		return 1;
	}
		
	return 0;
}


int addCopperToCurr(struct gameState *state, int player){
	int startCoins = state->coins;
	int handCnt = state->handCount[player];
	
	state->hand[player][handCnt] = copper;
	state->handCount[player] += 1;
	
	updateCoins(player,state,0);
	
	if(state->coins == (startCoins+1) ){
		return 1;
	}
		
	return 0;
}

int main(){
	struct gameState game;
	const int kCards[] = {adventurer, smithy, village, baron, great_hall, minion, steward, council_room, mine, sea_hag};
	const int players = 2;
	const int gameSeed = 5;
	int testsPassed = 1;
	
	initializeGame(players,kCards,gameSeed,&game);
	
	printf("----------------- Testing Fucntion: %s ----------------\n", TESTFUN);
	
	//Update empty hand with copper
	if(addCopper(&game,1)==0){
		printf("TEST FAILED\n");
		testsPassed = 0;
	}
	
	//Update empty hand with silver
	if(addSilver(&game,1)==0){
		printf("TEST FAILED\n");
		testsPassed = 0;
	}
	
	//Update empty hand with gold
	if(addGold(&game,1)==0){
		printf("TEST FAILED\n");
		testsPassed = 0;
	}
	
	//Add bouns coin 
	if(addBonus(&game,1)==0){
		printf("TEST FAILED\n");
		testsPassed = 0;
	}
	
	//Add Three Copper to empty hand
	if(addThreeCopper(&game,1)==0){
		printf("TEST FAILED\n");
		testsPassed = 0;
	}
	
	
	//Adds a copper to the current hand (has cards)
	if(addCopperToCurr(&game,1)==0){
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