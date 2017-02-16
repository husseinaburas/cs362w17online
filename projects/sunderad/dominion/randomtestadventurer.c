#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "rngs.h"

#define TEST_LENGTH 1000

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

void printGameState(struct gameState G){
	printf("Using Random Inputs\n");
	printf("---------------------------\n");
	printf("numPlayers: %d\n", G.numPlayers);
	printf("whoseTurn: %d\n", G.whoseTurn);
	printf("deckCount: %d\n", G.deckCount[G.whoseTurn]);
	printf("handCount: %d\n", G.handCount[G.whoseTurn]);
	printf("---------------------------\n");
}

int main(int argc, char const *argv[]){

	SelectStream(2);
    PutSeed((int) *argv[argc-1]);
	int i, j;
	struct gameState G;
	//int testCards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	int treasure_pre, treasure_post;     //Treasure card counts
	int coins_pre, coins_post;           //Coin counts
	int deck_pre, deck_post;			 //Deck counts	
	int hand_pre, hand_post;             //Hand counts
	int played_pre, played_post;         //Played card counts
	int adventurer_position;             //Random spot in hand for adventurer card    
    

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

		playCard(adventurer_position, 0, 0, 0, &G);

		//Setup Validation Values
		coins_post = G.coins;
		treasure_post = treasureCardCount(G.whoseTurn, G);
		deck_post = G.deckCount[G.whoseTurn];
		hand_post = G.handCount[G.whoseTurn];
		played_post = G.playedCardCount;

		printf("---------------------------------------------------------------------------------------------------------------\n");
		printf("Starting Test %d\n", i+1);
		printGameState(G);
		//Check Pre and Post Values
		if(coins_post <= coins_pre){
			printf("Error Test %d Coin Count Not Increased. Before: %d After: %d\n", i+1, coins_pre, coins_post);
		}
		if(treasure_post != (treasure_pre + 2)){
			printf("Error Test %d Treasure Card Count Wrong. Expected: %d Recieved: %d\n", i+1, (treasure_pre + 2), treasure_post);
		}
		if((deck_pre - 2) != (deck_post + G.discardCount[G.whoseTurn])){
			printf("Error Test %d Deck and Discard Count Wrong. Expected: %d Recieved: %d\n", i+1, (deck_pre - 2), (deck_post + G.discardCount[G.whoseTurn]));
		}
		if((hand_pre + 1) != hand_post){
			printf("Error Test %d Hand Count Wrong. Expected: %d Recieved: %d\n", i+1, (hand_pre + 1), hand_post);
		}
		if((played_pre + 1) != played_post){
			printf("Error Test %d Played Card Count Wrong (Adventurer Not Removed). Expected: %d Recieved: %d\n", i+1, (played_pre + 1), played_post);
		}
		printf("End of Test %d\n", i+1);
		printf("---------------------------------------------------------------------------------------------------------------\n");
		
		//memset(&G, 0, sizeof(struct gameState));
		//printf("Players: %d, Player: %d, Hand Count: %d, Deck Count: %d, \n", G.numPlayers, G.whoseTurn, G.handCount[G.whoseTurn], G.deckCount[G.whoseTurn] );	
		//initializeGame(players, testCards, gameSeed, &G);
		//Give all players a hand
		/*
		for(j=1; j<(players-1); j++){
			for(k=0; k<5; k++){
				drawCard(j, &G);
			}	
		}
		*/
	}
	return 0;
}