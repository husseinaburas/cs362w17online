//Joseph Rebolledo
//CS362-400
//Random test adventurer

#include "newassert.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char** argv){

	if(argc != 2){
		printf("Usage: randomtestadventurer [integer value]\n");
		return 1;
	}

	printf("---Now beginning random testing on adventurer card--- \n");

	//Initialize game 
	struct gameState Game;
	int kingdomCards[10]={adventurer,council_room,feast,gardens,mine,remodel,smithy,village,baron,great_hall};
	
	//Seed random from command line
	srand(atoi(argv[1]));
	int seed = rand() % 20;
	int numberPlayers = 2;

	int i = 0;
	int errors = 0;
	int numberTests = 50;

	printf("\n---Now beginning %d tests --- \n", numberTests);

	for(i = 0; i < numberTests; i++){

		printf("\n***Beginning test round: %d *** \n", i+1);

		initializeGame(numberPlayers,kingdomCards,seed,&Game);

		Game.whoseTurn = 0;

		//Instantiating randomized amounts for deckCount,handCount, and discardCount
		int player1DeckCount;

		//Deciding whether or not to run callAdventurer with deck < 1
		int smallDeck = rand() % 2;
		if(smallDeck == 1){
			printf("Testing with player 1 deck count = 0: \n");
			player1DeckCount = 0;
		}
		else{
			printf("Testing with normal randomized player 1 deck count: \n");
			 player1DeckCount = rand() % 100 + 20; //20-119
		}

		int player1HandCount = rand() % 100 + 20; //20-119
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

		//Deciding how many treasures in deck to test adventurer with
		int howManyTreasures = rand() % 3;

		//Only one treasure in deck
		if(howManyTreasures == 1){
			printf("Testing with one treasure in deck: \n");
			for(m = 0;m < player1HandCount; m++){
				if(Game.hand[0][m] == copper || Game.hand[0][m] == silver || Game.hand[0][m] == gold){
					Game.hand[0][m] = minion;
				}	
			}
			Game.hand[0][10] = copper;
		}

		//No treasures in deck
		else if(howManyTreasures == 0){
			printf("Testing with no treasures in deck: \n");
			for(m = 0;m < player1HandCount; m++){
				if(Game.hand[0][m] == copper || Game.hand[0][m] == silver || Game.hand[0][m] == gold){
					Game.hand[0][m] = minion;
				}	
			}
		}

		//Normal randomized amount of treasures in deck
		else if(howManyTreasures == 2){
			printf("Testing with normal randomized amount of treasures in deck: \n");
		}
	

		//Draw random hand for player 2
		for(m = 0;m < player2HandCount; m++){
			drawCard(2,&Game);	
		}

		//Place adventurer in the beginning
		Game.hand[0][0] = adventurer;

		//Create discard pile for player 1
		for(m = 0; m < player1DiscardCount ; m++){
			Game.discard[0][m] = rand() % treasure_map + 1;
			Game.discardCount[0]++;
		}

		//Create player 1 deck
		for(m = 0; m < player1DeckCount; m++){
			Game.deck[0][m] = rand() % treasure_map + 1;	
		}

		//Calculating how many cards should be discarded to find treasure
		int foundTreasure = 0;
		int cardsLeft = 0;
		for(m = player1DeckCount; m > 0; m--){
			if(Game.deck[0][m]== copper || Game.deck[0][m] == silver || Game.deck[0][m] == gold){
				foundTreasure++;
			}
			if(foundTreasure == 2){
				break;
			}
		} 
		cardsLeft = m;
		int cardsDiscarded = player1DeckCount - cardsLeft - 2;

		//Play adventurer
		adventurerCard(&Game);

	 	//Testing player 1 status
		printf("Testing player1 hand count: \n");
		if(numHandCards(&Game) == player1HandCount + 2){
			printf("Test successfully passed. \n");
		}
		else{
			printf("Test failed: expected: %d, actual: %d \n", player1HandCount + 2, numHandCards(&Game));
			errors++;
		}

		printf("Testing player1 discard count: \n");
		if(Game.discardCount[0] == player1DiscardCount + cardsDiscarded){
			printf("Test successfully passed. \n");
		}
		else{
			printf("Test failed: expected: %d, actual: %d \n", player1DiscardCount + cardsDiscarded, Game.discardCount[0]);
			errors++;
		}

		printf("Testing player1 deckCount count: \n");
		if(Game.deckCount[0] == cardsLeft){
			printf("Test successfully passed. \n");
		}
		else{
			printf("Test failed: expected: %d, actual: %d \n", cardsLeft,Game.deckCount[0]);
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
	printf("End adventurer random testing\n\n");

	return 0;
}