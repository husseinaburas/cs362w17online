#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "rngs.h"

#define TEST_LENGTH 1000

void printGameState(struct gameState G, char* card){
	printf("---------------------------\n");
	printf("%s Using These Random Inputs\n", card);
	printf("numPlayers: %d\n", G.numPlayers);
	printf("whoseTurn: %d\n", G.whoseTurn);
	printf("deckCount: %d\n", G.deckCount[G.whoseTurn]);
	printf("handCount: %d\n", G.handCount[G.whoseTurn]);
	printf("---------------------------\n");
}

//Makes sure only the current players hand was affected
void checkOtherHands(struct gameState G, struct gameState Gc){
	int x;
	for(x=0; x<G.numPlayers; x++){
		if(x != G.whoseTurn){
			if(G.handCount[x] != Gc.handCount[x]){
				printf("Error Other Player Number %d Hand Count Changed\n", (x + 1));
			}
			if(G.deckCount[x] != Gc.deckCount[x]){
				printf("Error Other Player Number %d Deck Count Changed\n", (x + 1));
			}
			if(G.discardCount[x] != Gc.discardCount[x]){
				printf("Error Other Player Number %d Discard Count Changed\n", (x + 1));
			}
		}	
	}
}

//Custom Assert With Error Reporting
void myAssert(char* msg, int testNum, int expected, int actual){
	if(expected != actual){
		printf("Error Test %d, %s Count Wrong. Expected: %d Actual: %d\n", (testNum + 1), msg, expected, actual);
	}
}

int main(int argc, char const *argv[]){

	SelectStream(2);
    PutSeed((int) *argv[argc-1]);
	int i, j;
	struct gameState G, Gcopy;
	//int testCards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	int actions_pre, actions_post;       //Action counts
	int deck_pre, deck_post;			 //Deck counts	
	int hand_pre, hand_post;             //Hand counts
	int played_pre, played_post;         //Played card counts
	int village_position;                //Random spot in hand for village card 
	char* msg1 = "Deck";     //Messages for myAssert
    char* msg2 = "Hand";
    char* msg3 = "Played Card";
    char* msg4 = "Actions";
    char* card = "Village";

	for(i=0; i<TEST_LENGTH; i++){

		//Setup Game State
		G.numActions = 1;
		G.phase = 0;

		//Random Game Players 2 - 4
		G.numPlayers = (MAX_PLAYERS - ((int) floor((Random() * 3))));

		//Random Player for Test
		G.whoseTurn = (((int) floor(Random() * G.numPlayers)));

		//Random Hand
		G.handCount[G.whoseTurn]=(((int) floor(Random() * MAX_HAND)));
		/*if(G.handCount[G.whoseTurn] == 0){
			G.handCount[G.whoseTurn] = 20; // Make sure hand not empty
		}*/
		for(j=0; j<G.handCount[G.whoseTurn]; j++){
			G.hand[G.whoseTurn][j] = ((int) floor(Random() * treasure_map));
		}

		//Random Deck
		G.deckCount[G.whoseTurn] = (((int) floor(Random() * MAX_HAND)));
		if(G.deckCount[G.whoseTurn] == 0){
			G.deckCount[G.whoseTurn] = 20; // Make sure deck not empty
		}
		for(j=0; j<G.deckCount[G.whoseTurn]; j++){
			G.deck[G.whoseTurn][j] = ((int) floor(Random() * treasure_map));
		}

		//Put village in random spot in hand
		village_position = ((int) floor(Random() * (G.handCount[G.whoseTurn]-1)));
		G.hand[G.whoseTurn][village_position] = village;

		//More Game State setup
		G.playedCardCount = 0;
		G.discardCount[G.whoseTurn] = 0;
		assert(updateCoins(G.whoseTurn, &G, 0) == 0);

		//Setup Initial Check Values
		actions_pre = G.numActions;
		deck_pre = G.deckCount[G.whoseTurn];
		hand_pre = G.handCount[G.whoseTurn];
		played_pre = G.playedCardCount;

		memcpy(&Gcopy, &G, sizeof(struct gameState));
		playCard(village_position, 0, 0, 0, &G);

		//Setup Validation Values
		actions_post = G.numActions;
		deck_post = G.deckCount[G.whoseTurn];
		hand_post = G.handCount[G.whoseTurn];
		played_post = G.playedCardCount;

		printf("---------------------------------------------------------------------------------------------------------------\n");
		printf("Starting Test %d\n", i+1);
		printGameState(G, card);

		myAssert(msg1, i, (deck_pre - 1), deck_post);
		myAssert(msg2, i, hand_pre, hand_post);
		myAssert(msg3, i, (played_pre + 1), played_post);
		myAssert(msg4, i, (actions_pre + 1), actions_post);
		checkOtherHands(G, Gcopy);

		printf("End of Test %d\n", i+1);
		printf("---------------------------------------------------------------------------------------------------------------\n");
		
	}
	return 0;
}