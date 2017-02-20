#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "rngs.h"

#define TEST_LENGTH 1000

//Counts treasure cards in a players hand
int treasureCardCount(int player, struct gameState G){
	int x;
	int t=0;
	for(x=0; x<(G.handCount[player]); x++){
		if(G.hand[player][x] == copper || G.hand[player][x] == silver || G.hand[player][x] == gold){
			t++;
		}
	}
	return t;
}

//Prints info about the game state and its random inputs
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
	int treasure_pre, treasure_post;     //Treasure card counts
	int coins_pre, coins_post;           //Coin counts
	int deck_pre, deck_post;			 //Deck counts	
	int hand_pre, hand_post;             //Hand counts
	int played_pre, played_post;         //Played card counts
	int adventurer_position;             //Random spot in hand for adventurer card 
	char* msg1 = "Treasure Card";    	 //Messages for myAssert
    char* msg2 = "Deck and Discard";
    char* msg3 = "Hand";
    char* msg4 = "Played Card";
    char* card = "Adventurer";

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
		if(G.handCount[G.whoseTurn] == 0){
			G.handCount[G.whoseTurn] = 20; // Make sure hand not empty
		}
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

		//Put adventurer in random spot in hand
		adventurer_position = ((int) floor(Random() * (G.handCount[G.whoseTurn]-1)));
		G.hand[G.whoseTurn][adventurer_position] = adventurer;

		//More Game State setup
		G.playedCardCount = 0;
		G.discardCount[G.whoseTurn] = 0;
		assert(updateCoins(G.whoseTurn, &G, 0) == 0);

		//Setup Initial Check Values
		coins_pre = G.coins;
		treasure_pre = treasureCardCount(G.whoseTurn, G);
		deck_pre = G.deckCount[G.whoseTurn];
		hand_pre = G.handCount[G.whoseTurn];
		played_pre = G.playedCardCount;

		memcpy(&Gcopy, &G, sizeof(struct gameState));
		playCard(adventurer_position, 0, 0, 0, &G);

		//Setup Validation Values
		coins_post = G.coins;
		treasure_post = treasureCardCount(G.whoseTurn, G);
		deck_post = G.deckCount[G.whoseTurn];
		hand_post = G.handCount[G.whoseTurn];
		played_post = G.playedCardCount;

		printf("---------------------------------------------------------------------------------------------------------------\n");
		printf("Starting Test %d\n", i+1);
		printGameState(G, card);

		//Check Pre and Post Values and other players hands 
		//Didn't use myAssert since we won't know which type of treasure card was drawn
		if(coins_post <= coins_pre){
			printf("Error Test %d Coin Count Not Increased. Before: %d After: %d\n", i+1, coins_pre, coins_post);
		}
		myAssert(msg1, i, (treasure_pre + 2), treasure_post);
		myAssert(msg2, i, (deck_pre - 2), (deck_post + G.discardCount[G.whoseTurn]));
		myAssert(msg3, i, (hand_pre + 1), hand_post);
		myAssert(msg4, i, (played_pre + 1), played_post);
		checkOtherHands(G, Gcopy);
		
		printf("End of Test %d\n", i+1);
		printf("---------------------------------------------------------------------------------------------------------------\n");
		
	}
	return 0;
}