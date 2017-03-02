//Joseph Rebolledo
//CS362-400
//Random test steward

#include "newassert.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv){

	if(argc != 2){
		printf("Usage: randomtestcard2 [integer value]\n");
		return 1;
	}

	printf("---Now beginning random testing on steward card--- \n");

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

		Game.coins = 0;

		int player1HandCount = rand() % 100 + 20; //20-119
		int player1DeckCount = rand() % 100 + 20; //20-119
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

		//Place steward in the beginning
		Game.hand[0][0] = steward;

		updateCoins(0,&Game,0);
		int preCoins = Game.coins;

		//Create discard pile for player 1
		for(m = 0; m < player1DiscardCount ; m++){
			Game.discard[0][m] = rand() % treasure_map + 1;
			Game.discardCount[0]++;
		}

		//Create player 1 deck
		for(m = 0; m < player1DeckCount; m++){
			Game.deck[0][m] = rand() % treasure_map + 1;	
		}

		int choice = rand() % 3 + 1; //1-3

		//Playing steward with choice 1: +2 cards
		if(choice == 1){
			printf("Running steward with choice 1: +2 cards \n");
			
			//Deciding whether or not to play the card with an empty deck
			int emptyDeck = rand() % 2;
			if(emptyDeck == 1){
				printf("Running steward with an empty deck: \n");
				Game.deckCount[0] = 0;
				player1DeckCount = 0;
			}
			else{
				printf("Running steward with a normal deck: \n");
			}

			//Play steward
			stewardCard(&Game,1,0,0,0);

			//Testing player 1
			printf("Testing player1 hand count: \n");
			if(numHandCards(&Game) == player1HandCount + 1){
				printf("Test successfully passed. \n");
			}
			else{
				printf("Test failed: expected: %d, actual: %d \n", player1HandCount + 1, numHandCards(&Game));
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
			if(Game.deckCount[0] == player1DeckCount - 2){
				printf("Test successfully passed. \n");
			}
			else{
				printf("Test failed: expected: %d, actual: %d \n", player1DeckCount - 2,Game.deckCount[0]);
				errors++;
			}
		}

		//Playing steward with choice 2: +2 coins
		if(choice == 2){
			printf("Running steward with choice 2: +2 coins \n");

			//Play steward
			stewardCard(&Game,2,0,0,0);
			

			//Testing player 1
			printf("Testing player1 hand count: \n");
			if(numHandCards(&Game) == player1HandCount - 1){
				printf("Test successfully passed. \n");
			}
			else{
				printf("Test failed: expected: %d, actual: %d \n", player1HandCount - 1, numHandCards(&Game));
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
			if(Game.deckCount[0] == player1DeckCount){
				printf("Test successfully passed. \n");
			}
			else{
				printf("Test failed: expected: %d, actual: %d \n", player1DeckCount,Game.deckCount[0]);
				errors++;
			}

			printf("Testing player1 coin count: \n");
			if(Game.coins == preCoins + 2){
				printf("Test successfully passed. \n");
			}
			else{
				printf("Test failed: expected: %d, actual: %d \n", preCoins + 2,Game.coins);
				errors++;
			}
		}

		//Playing steward with choice 3: trash two cards
		if(choice == 3){
			printf("Running steward with choice 3: trash two cards \n");

			//Play steward
			stewardCard(&Game,3,3,1,0);

			//Testing player 1
			printf("Testing player1 hand count: \n");
			if(numHandCards(&Game) == player1HandCount - 3){
				printf("Test successfully passed. \n");
			}
			else{
				printf("Test failed: expected: %d, actual: %d \n", player1HandCount - 3, numHandCards(&Game));
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
			if(Game.deckCount[0] == player1DeckCount){
				printf("Test successfully passed. \n");
			}
			else{
				printf("Test failed: expected: %d, actual: %d \n", player1DeckCount,Game.deckCount[0]);
				errors++;
			}
		}

		//The following tests are ran for all choices
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

	printf("End steward random testing\n\n");

	return 0;
}