//Joseph Rebolledo
//CS362-400
//Random test smithy

#include "newassert.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv){

	if(argc != 2){
		printf("Usage: randomtestcard1 [integer value]\n");
		return 1;
	}
	
	printf("---Now beginning random testing on smithy --- \n");

	//Initialize game 
	struct gameState Game;
	int kingdomCards[10]={adventurer,council_room,feast,gardens,mine,remodel,smithy,village,baron,great_hall};
	
	//Seed random from command line
	srand(atoi(argv[1]));
	int seed = rand() % 5;
	int numberPlayers = 2;

	int i = 0;
	int errors = 0;
	int numberTests = 50;

	printf("\n---Now beginning %d tests --- \n", numberTests);

	for(i = 0; i < numberTests; i++){

		printf("\n***Beginning test round: %d *** \n", i+1);

		initializeGame(numberPlayers,kingdomCards,seed,&Game);

		Game.whoseTurn = 0;

		int player1HandCount = rand() % 100 + 20; //20-119

		int player1DeckCount;

		//Deciding whether or not to play smithy with an empty deck
		int emptyDeck = rand() % 2;
		if(emptyDeck == 1){
			printf("Playing smithy with an empty deck: \n");
			player1DeckCount = 0;
		}
		else{
			printf("Playing smithy with a normal deck: \n");
			player1DeckCount = rand() % 100 + 20; //20-119
		}

		int player1DiscardCount = rand() % 100 + 20; //20-119

		int player2HandCount = rand() % 100 + 20; //20-119

		Game.handCount[0] = player1HandCount;
		Game.deckCount[0] = player1DeckCount;

		Game.handCount[1] = player2HandCount;

		//Draw random hand for player 1
		int m = 0;
		for(m = 0;m < player1HandCount; m++){
			Game.hand[0][m] = rand() % treasure_map + 1;
		}

		//Draw random hand for player 2
		for(m = 0;m < player2HandCount; m++){
			drawCard(2,&Game);		
		}

		//Place smithy in the beginning
		Game.hand[0][0] = smithy;

		//Create discard pile for player 1
		for(m = 0; m < player1DiscardCount ; m++){
			Game.discard[0][m] = rand() % treasure_map + 1;
			Game.discardCount[0]++;
		}

		//Create player 1 deck
		for(m = 0; m < player1DeckCount; m++){
			Game.deck[0][m] = rand() % treasure_map + 1;	
		}
	
		//Play smithy
		callSmithy(0, &Game,0);

	 	//Testing player 1

		printf("Testing player1 hand count: \n");
		if(numHandCards(&Game) == player1HandCount + 2){
			printf("Test successfully passed. \n");
		}
		else{
			printf("Test failed: expected: %d, actual: %d \n", player1HandCount + 2, numHandCards(&Game));
			errors++;
		}

		printf("Testing player1 discard count: \n");
		if(Game.discardCount[0] == player1DiscardCount){
			printf("Test successfully passed. \n");
		}
		else{
			printf("Test failed: expected: %d, actual: %d \n", player1DiscardCount, Game.discardCount[0]);
			errors++;
		}

		printf("Testing player1 deckCount count: \n");
		if(Game.deckCount[0] == player1DeckCount - 3){
			printf("Test successfully passed. \n");
		}
		else{
			printf("Test failed: expected: %d, actual: %d \n", player1DeckCount - 3,Game.deckCount[0]);
			errors++;
		}


		printf("Testing whose turn it is: \n");
		if(whoseTurn(&Game) == 0){
			printf("Test successfully passed \n");
		}
		else{
			printf("Test failed: expected to be 0, actual: %d \n", whoseTurn(&Game));
			errors++;
		}

		//Testing player 2 status
		printf("Testing player 2's handCount: \n");

		if(Game.handCount[1] == player2HandCount){
			printf("Test successfully passed \n");
		}
		else{
			printf("Test failed: expected: %d, actual: %d \n", player2HandCount, Game.handCount[1]);
			errors++;
		}

		//Testing supply count of victory and curse cards
		printf("Testing curse cards supply count: \n");
		if(Game.supplyCount[curse] == 10){
			printf("Test successfully passed \n");
		}
		else{
			printf("Test failed: expected: 8, actual: %d \n", Game.supplyCount[curse]);
			errors++;
		}
		printf("Testing province cards supply count:: \n");
		if(Game.supplyCount[province] == 8){
			printf("Test successfully passed \n");
		}
		else{
			printf("Test failed: expected: 8, actual: %d \n", Game.supplyCount[province] );
			errors++;
		}
		printf("Testing estate cards supply count: \n");
		if(Game.supplyCount[estate] == 8){
			printf("Test successfully passed \n");
		}
		else{
			printf("Test failed: expected: 8, actual: %d \n", Game.supplyCount[estate]);
			errors++;
		}
		printf("Testing duchy cards supply count: \n");
		if(Game.supplyCount[duchy] == 8){
			printf("Test successfully passed \n");
		}
		else{
			printf("Test failed: expected: 8, actual: %d \n", Game.supplyCount[duchy]);
			errors++;
		}

		
	}
	printf("\nTotal number of errors for %d tests: %d \n", numberTests, errors);
	printf("End smithy random testing\n\n");
	return 0;
}