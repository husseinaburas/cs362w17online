#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"

//---------------------------------
//Unit Test For Draw Card Function
//---------------------------------
int main(int argc, char const *argv[])
{
	int i, j, k, l;
	int errorFlag[3]={0,0,0};
	int players=2;
	int seed=999;
	struct gameState twoPlayerG, threePlayerG, fourPlayerG, copyG;
	int c[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	initializeGame(players, c, seed, &twoPlayerG);
	initializeGame((players+1), c, seed, &threePlayerG);
	initializeGame((players+2), c, seed, &fourPlayerG);

	printf("-----------------------------------------------------------------------\n");
	printf("Running Unit Test 2: Draw Card Function\n\n");
	printf("Testing drawCard(), Two Player Game\n");
	memcpy(&copyG, &twoPlayerG, sizeof(struct gameState));
	
	//Test Draw Card Two Players
	for(i=0; i<players; i++){
		//set vars for player indexs
		if(i==0){
			j=1;
		}
		else{
			j=0;
		}
		drawCard(i, &twoPlayerG);
		//Check Deck Counts
		if(twoPlayerG.deckCount[i] != (copyG.deckCount[i]-1)){
			printf("Player %d Drew A Card, Deck Count Error For Player\n", (i+1));
			errorFlag[0]++;
		}
		if(twoPlayerG.deckCount[j] != copyG.deckCount[j]){
			printf("Player %d Drew A Card, Deck Count Error For Player %d\n", (i+1), (j+1));
			errorFlag[0]++;
		}
		//Check Hand Counts
		if(twoPlayerG.handCount[i] != (copyG.handCount[i]+1)){
			printf("Player %d Drew A Card, Hand Count Error For Player\n", (i+1));
			errorFlag[0]++;
		}
		if(twoPlayerG.handCount[j] != copyG.handCount[j]){
			printf("Player %d Drew A Card, Hand Count Error For Player %d\n", (i+1), (j+1));
			errorFlag[0]++;
		}
		memcpy(&copyG, &twoPlayerG, sizeof(struct gameState));
	}
	printf("Two Player Game Draw Card Test Complete, %d Errors\n\n", errorFlag[0]);

	printf("Testing drawCard(), Three Player Game\n");
	memcpy(&copyG, &threePlayerG, sizeof(struct gameState));
	
	//Test Draw Card Three Players
	for(i=0; i<(players+1); i++){
		//set vars for player indexs
		if(i==0){
			j=1;
			k=2;
		}
		else if(i==1){
			j=0;
			k=2;
		}
		else{
			j=0;
			k=1;
		}
		drawCard(i, &threePlayerG);
		//Check Deck Counts
		if(threePlayerG.deckCount[i] != (copyG.deckCount[i]-1)){
			printf("Player %d Drew A Card, Deck Count Error For Player\n", (i+1));
			errorFlag[1]++;
		}
		if(threePlayerG.deckCount[j] != copyG.deckCount[j]){
			printf("Player %d Drew A Card, Deck Count Error For Player %d\n", (i+1), (j+1));
			errorFlag[1]++;
		}
		if(threePlayerG.deckCount[k] != copyG.deckCount[k]){
			printf("Player %d Drew A Card, Deck Count Error For Player %d\n", (i+1), (k+1));
			errorFlag[1]++;
		}
		//Check Hand Counts
		if(threePlayerG.handCount[i] != (copyG.handCount[i]+1)){
			printf("Player %d Drew A Card, Hand Count Error For Player\n", (i+1));
			errorFlag[1]++;
		}
		if(threePlayerG.handCount[j] != copyG.handCount[j]){
			printf("Player %d Drew A Card, Hand Count Error For Player %d\n", (i+1), (j+1));
			errorFlag[1]++;
		}
		if(threePlayerG.handCount[k] != copyG.handCount[k]){
			printf("Player %d Drew A Card, Hand Count Error For Player %d\n", (i+1), (k+1));
			errorFlag[1]++;
		}
		memcpy(&copyG, &threePlayerG, sizeof(struct gameState));
	}
	printf("Three Player Game Draw Card Test Complete, %d Errors\n\n", errorFlag[1]);


	printf("Testing drawCard(), Four Player Game\n");
	memcpy(&copyG, &fourPlayerG, sizeof(struct gameState));

	//Test Draw Card Four Players
	for(i=0; i<(players+2); i++){
		//set vars for player indexs
		if(i==0){
			j=1;
			k=2;
			l=3;
		}
		else if(i==1){
			j=0;
			k=2;
			l=3;
		}
		else if(i==2){
			j=0;
			k=1;
			l=3;
		}
		else{
			j=0;
			k=1;
			l=2;
		}
		drawCard(i, &fourPlayerG);
		//Check Deck Counts
		if(fourPlayerG.deckCount[i] != (copyG.deckCount[i]-1)){
			printf("Player %d Drew A Card, Deck Count Error For Player\n", (i+1));
			errorFlag[2]++;
		}
		if(fourPlayerG.deckCount[j] != copyG.deckCount[j]){
			printf("Player %d Drew A Card, Deck Count Error For Player %d\n", (i+1), (j+1));
			errorFlag[2]++;
		}
		if(fourPlayerG.deckCount[k] != copyG.deckCount[k]){
			printf("Player %d Drew A Card, Deck Count Error For Player %d\n", (i+1), (k+1));
			errorFlag[2]++;
		}
		if(fourPlayerG.deckCount[l] != copyG.deckCount[l]){
			printf("Player %d Drew A Card, Deck Count Error For Player %d\n", (i+1), (l+1));
			errorFlag[2]++;
		}
		//Check Hand Counts
		if(fourPlayerG.handCount[i] != (copyG.handCount[i]+1)){
			printf("Player %d Drew A Card, Hand Count Error For Player\n", (i+1));
			errorFlag[2]++;
		}
		if(fourPlayerG.handCount[j] != copyG.handCount[j]){
			printf("Player %d Drew A Card, Hand Count Error For Player %d\n", (i+1), (j+1));
			errorFlag[2]++;
		}
		if(fourPlayerG.handCount[k] != copyG.handCount[k]){
			printf("Player %d Drew A Card, Hand Count Error For Player %d\n", (i+1), (j+1));
			errorFlag[2]++;
		}
		if(fourPlayerG.handCount[l] != copyG.handCount[l]){
			printf("Player %d Drew A Card, Hand Count Error For Player %d\n", (i+1), (l+1));
			errorFlag[2]++;
		}
		memcpy(&copyG, &fourPlayerG, sizeof(struct gameState));
	}
	printf("Four Player Game Draw Card Test Complete, %d Errors\n\n", errorFlag[2]);

	printf("Unit Test 2 Complete: %d Total Errors\n",(errorFlag[0]+errorFlag[1]+errorFlag[2]));
    printf("-----------------------------------------------------------------------\n");

	return 0;
}