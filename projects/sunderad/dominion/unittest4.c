#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"

int main(int argc, char const *argv[])
{
	int i;
	int errorFlag=0;
	int players=2;
	int seed=999;
	struct gameState twoPlayerG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("Running Unit Test 4: Discard Card Function\n");
	printf("-------------------------------------------------------------------------------------------------------------------------------------\n");	
	printf("\n");

	initializeGame(players, k, seed, &twoPlayerG);

	//Add all playable kingdom cards to hand and set new hand count
	for(i=0; i<10; i++){
		twoPlayerG.hand[0][i] = k[i]; 
	}
	twoPlayerG.handCount[0] = 10;

	printf("Discarding council_room...\n");
	//Discard council_room
	discardCard(9, 0, &twoPlayerG, 0);
	if(twoPlayerG.handCount[0] != 9){
		printf("council_room not discarded properly, handCount unchanged\n");
		errorFlag++;
	}
	if(twoPlayerG.hand[0][9] != -1){
		printf("council_room not discarded properly, hand position not set to -1\n");
		errorFlag++;
	}
	if(twoPlayerG.playedCards[twoPlayerG.playedCardCount-1] != council_room){
		printf("council_room not discarded properly, playedCards not set to council_room\n");
		errorFlag++;
	}

	printf("Discarding smithy...\n");
	//Discard smithy
	discardCard(8, 0, &twoPlayerG, 0);
	if(twoPlayerG.handCount[0] != 8){
		printf("smithy not discarded properly, handCount unchanged\n");
		errorFlag++;
	}
	if(twoPlayerG.hand[0][8] != -1){
		printf("smithy not discarded properly, hand position not set to -1\n");
		errorFlag++;
	}
	if(twoPlayerG.playedCards[twoPlayerG.playedCardCount-1] != smithy){
		printf("smithy not discarded properly, playedCards not set to smithy\n");
		errorFlag++;
	}

	printf("Discarding tribute...\n");
	//Discard tribute
	discardCard(7, 0, &twoPlayerG, 0);
	if(twoPlayerG.handCount[0] != 7){
		printf("tribute not discarded properly, handCount unchanged\n");
		errorFlag++;
	}
	if(twoPlayerG.hand[0][7] != -1){
		printf("tribute not discarded properly, hand position not set to -1\n");
		errorFlag++;
	}
	if(twoPlayerG.playedCards[twoPlayerG.playedCardCount-1] != tribute){
		printf("tribute not discarded properly, playedCards not set to tribute\n");
		errorFlag++;
	}

	printf("Discarding sea_hag...\n");
	//Discard sea_hag
	discardCard(6, 0, &twoPlayerG, 0);
	if(twoPlayerG.handCount[0] != 6){
		printf("sea_hag not discarded properly, handCount unchanged\n");
		errorFlag++;
	}
	if(twoPlayerG.hand[0][6] != -1){
		printf("sea_hag not discarded properly, hand position not set to -1\n");
		errorFlag++;
	}
	if(twoPlayerG.playedCards[twoPlayerG.playedCardCount-1] != sea_hag){
		printf("sea_hag not discarded properly, playedCards not set to sea_hag\n");
		errorFlag++;
	}

	printf("Discarding cutpurse...\n");
	//Discard cutpurse
	discardCard(5, 0, &twoPlayerG, 0);
	if(twoPlayerG.handCount[0] != 5){
		printf("cutpurse not discarded properly, handCount unchanged\n");
		errorFlag++;
	}
	if(twoPlayerG.hand[0][5] != -1){
		printf("cutpurse not discarded properly, hand position not set to -1\n");
		errorFlag++;
	}
	if(twoPlayerG.playedCards[twoPlayerG.playedCardCount-1] != cutpurse){
		printf("cutpurse not discarded properly, playedCards not set to cutpurse\n");
		errorFlag++;
	}

	printf("Discarding mine...\n");
	//Discard mine
	discardCard(4, 0, &twoPlayerG, 0);
	if(twoPlayerG.handCount[0] != 4){
		printf("mine not discarded properly, handCount unchanged\n");
		errorFlag++;
	}
	if(twoPlayerG.hand[0][4] != -1){
		printf("mine not discarded properly, hand position not set to -1\n");
		errorFlag++;
	}
	if(twoPlayerG.playedCards[twoPlayerG.playedCardCount-1] != mine){
		printf("mine not discarded properly, playedCards not set to mine\n");
		errorFlag++;
	}

	printf("Discarding minion...\n");
	//Discard minion
	discardCard(3, 0, &twoPlayerG, 0);
	if(twoPlayerG.handCount[0] != 3){
		printf("minion not discarded properly, handCount unchanged\n");
		errorFlag++;
	}
	if(twoPlayerG.hand[0][3] != -1){
		printf("minion not discarded properly, hand position not set to -1\n");
		errorFlag++;
	}
	if(twoPlayerG.playedCards[twoPlayerG.playedCardCount-1] != minion){
		printf("minion not discarded properly, playedCards not set to minion\n");
		errorFlag++;
	}

	printf("Discarding village...\n");
	//Discard village
	discardCard(2, 0, &twoPlayerG, 0);
	if(twoPlayerG.handCount[0] != 2){
		printf("village not discarded properly, handCount unchanged\n");
		errorFlag++;
	}
	if(twoPlayerG.hand[0][2] != -1){
		printf("village not discarded properly, hand position not set to -1\n");
		errorFlag++;
	}
	if(twoPlayerG.playedCards[twoPlayerG.playedCardCount-1] != village){
		printf("village not discarded properly, playedCards not set to village\n");
		errorFlag++;
	}

	printf("Discarding embargo...\n");
	//Discard embargo
	discardCard(1, 0, &twoPlayerG, 1);
	if(twoPlayerG.handCount[0] != 1){
		printf("embargo not discarded properly, handCount unchanged\n");
		errorFlag++;
	}
	if(twoPlayerG.hand[0][1] != -1){
		printf("embargo not discarded properly, hand position not set to -1\n");
		errorFlag++;
	}
	if(twoPlayerG.playedCards[twoPlayerG.playedCardCount-1] != village){
		printf("embargo not trashed properly, playedCards not set to previous card (village)\n");
		errorFlag++;
	}

	printf("Discarding adventurer (Last Card)...\n");
	//Discard adventurer
	discardCard(0, 0, &twoPlayerG, 0);
	if(twoPlayerG.handCount[0] != 0){
		printf("adventurer not discarded properly, handCount unchanged\n");
		errorFlag++;
	}
	if(twoPlayerG.hand[0][0] != -1){
		printf("adventurer not discarded properly, hand position not set to -1\n");
		errorFlag++;
	}
	if(twoPlayerG.playedCards[twoPlayerG.playedCardCount-1] != adventurer){
		printf("adventurer not discarded properly, playedCards not set to adventurer\n");
		errorFlag++;
	}


	printf("\n");
    printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("Unit Test 4 Complete: %d Total Errors\n",errorFlag);
    printf("-------------------------------------------------------------------------------------------------------------------------------------\n");

	
	return 0;
}