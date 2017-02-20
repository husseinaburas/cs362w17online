#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

//color output based on:
//http://stackoverflow.com/questions/3219393/stdlib-and-colored-output-in-c
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

//whether assert should crash program
#define ASSERT_SHOULD_EXIT 0
//whether assert should print tests that succeed
#define ASSERT_PRINT_SUCCESS 0
//number of times random tests should run
#define NUM_RANDOM_ITERATIONS 1000

//global variable for number of test failed
int numTestsFailed = 0;

//prints error message if test fails
//otherwise prints that test passed
//if shouldExit is not 0, will exit program after test fails
void custom_assert(int test, char *testName){
	if(!test){
		printf(ANSI_COLOR_RED "%s FAILED!\n" ANSI_COLOR_RESET, testName);
		numTestsFailed++;
		if(ASSERT_SHOULD_EXIT){
			exit(1);
		}
	}
	#if ASSERT_PRINT_SUCCESS
	else{
		printf(ANSI_COLOR_GREEN "%s PASSED!\n" ANSI_COLOR_RESET, testName);
	}
	#endif
}

//returns a random integer between min and max (inclusive)
//based on: http://stackoverflow.com/questions/822323/how-to-generate-a-random-number-in-c
int randIntInclusive(int min, int max){
	int difference = (max - min);
	// % 0 causes floating point exception
	if(difference == 0){
		return 0;
	}
	return rand() % difference + min + 1;
}

//copies gamestate from source to destination
//based on lecture slides
void copyGameState(struct gameState *source, struct gameState *destination){
	memcpy(destination, source, sizeof(struct gameState));
}

//returns 1 if gamestates have equal memory layouts
//0 if not
//based on lecture slides
int areGameStatesEqual(struct gameState *g1, struct gameState *g2){
	return memcmp(g1, g2, sizeof(struct gameState)) == 0;
}

//prints differences in integer values if they are different
void printIntDiff(int d1, int d2, char *fieldName){
	if(d1 != d2){
		printf("%s are different. Mock %d, Real %d\n", fieldName, d1, d2);
	}
}


//compares every field in two gameStates and prints the differences
void printGameStateDifferences(struct gameState *mock, struct gameState *real){
	puts("Differences found between gameStates: ");
  //compare the integer values
	printIntDiff(mock->numPlayers, real->numPlayers, "numPlayers");
  	printIntDiff(mock->outpostPlayed, real->outpostPlayed, "outpostPlayed");
	printIntDiff(mock->outpostTurn, real->outpostTurn, "outpostTurn");
	printIntDiff(mock->whoseTurn, real->whoseTurn, "whoseTurn");
	printIntDiff(mock->phase, real->phase, "phase");
	printIntDiff(mock->numActions , real->numActions , "numActions ");
	printIntDiff(mock->coins , real->coins , "coins");
	printIntDiff(mock->numBuys , real->numBuys , "numBuys ");
	printIntDiff(mock->playedCardCount, real->playedCardCount, "playedCardCount");

	int i;
	int j;
	char *printBuffer = malloc(sizeof(char) * 200);
	//sanity check - need hard assert because if no memory we have to exit
	assert(printBuffer != NULL);
	for(i = 0; i < mock->numPlayers; ++i){
		sprintf(printBuffer, "Number of cards in player %d's hand", i);
		printIntDiff(mock->handCount[i], real->handCount[i], printBuffer);

		sprintf(printBuffer, "Number of cards in player %d's deck", i);
		printIntDiff(mock->deckCount[i], real->deckCount[i], printBuffer);

		sprintf(printBuffer, "Number of cards in player %d's discard", i);
		printIntDiff(mock->discardCount[i], real->discardCount[i], printBuffer);


		for(j = 0; j < mock->handCount[i]; ++j){
			sprintf(printBuffer, "Card at index %d in player %d's hand", j, i);
			printIntDiff(mock->hand[i][j], real->hand[i][j], printBuffer);
		}

		for(j = 0; j < MAX_DECK; ++j){
			sprintf(printBuffer, "Card at index %d in player %d's discard", j, i);
			printIntDiff(mock->discard[i][j], real->discard[i][j], printBuffer);

			sprintf(printBuffer, "Card at index %d in player %d's deck", j, i);
			printIntDiff(mock->deck[i][j], real->deck[i][j], printBuffer);
		}
	}

	for(i = 0; i < MAX_DECK; ++i){
		sprintf(printBuffer, "Card at index %d in playedCards", i);
		printIntDiff(mock->playedCards[i], real->playedCards[i], printBuffer);
	}


	//compare the memory for the arrays
	//for commented out fields, no longer needed, because values are compared directly above
	custom_assert(memcmp(mock->supplyCount, real->supplyCount, sizeof(int) * (treasure_map+1)) == 0, "supplyCount is equal");
	custom_assert(memcmp(mock->embargoTokens, real->embargoTokens, sizeof(int) * (treasure_map+1)) == 0, "embargoTokens is equal");
	// custom_assert(memcmp(mock->hand, real->hand, sizeof(int) * (MAX_PLAYERS * MAX_HAND)) == 0, "hand is equal");
	// custom_assert(memcmp(mock->handCount, real->handCount, sizeof(int) * (MAX_PLAYERS)) == 0, "handCount is equal");
	// custom_assert(memcmp(mock->deck, real->deck, sizeof(int) * (MAX_PLAYERS * MAX_DECK)) == 0, "deck is equal");
	// custom_assert(memcmp(mock->deckCount, real->deckCount, sizeof(int) * (MAX_PLAYERS)) == 0, "deckCount is equal");
	// custom_assert(memcmp(mock->discard, real->discard, sizeof(int) * (MAX_PLAYERS * MAX_DECK)) == 0, "discard is equal");
	// custom_assert(memcmp(mock->discardCount, real->discardCount, sizeof(int) * (MAX_PLAYERS)) == 0, "discardCount is equal");
	// custom_assert(memcmp(mock->playedCards, real->playedCards, sizeof(int) * (MAX_DECK)) == 0, "playedCards is equal");

	//free memory from print buffer
	free(printBuffer);
}

//fill kingdom cards holder with random kingdom cards
void pickRandomKindomCards(int kingdomCardsHolder[10]){
	int kingdomCards[20] = {
		   adventurer,
		   /* If no/only 1 treasure found, stop when full deck seen */
		   council_room,
		   feast, /* choice1 is supply # of card gained) */
		   gardens,
		   mine, /* choice1 is hand# of money to trash, choice2 is supply# of
			    money to put in hand */
		   remodel, /* choice1 is hand# of card to remodel, choice2 is supply# */
		   smithy,
		   village,

		   baron, /* choice1: boolean for discard of estate */
		   /* Discard is always of first (lowest index) estate */
		   great_hall,
		   minion, /* choice1:  1 = +2 coin, 2 = redraw */
		   steward, /* choice1: 1 = +2 card, 2 = +2 coin, 3 = trash 2 (choice2,3) */
		   tribute,
		   ambassador, /* choice1 = hand#, choice2 = number to return to supply */
		   cutpurse,
		   embargo, /* choice1 = supply# */
		   outpost,
		   salvager, /* choice1 = hand# to trash */
		   sea_hag,
		   treasure_map
		  };
	int i;
	for(i = 0; i < 10; ++i){
		kingdomCardsHolder[i] = kingdomCards[randIntInclusive(0, 20 - 1)];
	}
}

//initialize gamestate to (valid) random values
void initializeRandomGameState(struct gameState *testGameState, int kingdomCardsHolder[10]){
	pickRandomKindomCards(kingdomCardsHolder);
	int randomPlayerNumber = randIntInclusive(2, MAX_PLAYERS);
	initializeGame(randomPlayerNumber, kingdomCardsHolder, rand(),
		   testGameState);
}

//print program usage
void printUsage(const char* programName){
	printf("usage: %s random_seed\n", programName);
}

//converts string to integer greater than or equal to 1
//returns -1 if string is negative or not numeric
int stringToInt(const char* s){
	int ret = 0;
	int i = 0;
	char c;
	int currentValue;
	int asciiZero = 48;
	while((c = s[i]) != '\0'){
		if(!isdigit(c)){
			return -1;
		}
		//convert ascii code to number
		currentValue = c - asciiZero;
		//we are moving 1 digit to left, so multiply by 10
		ret *= 10;
		ret += currentValue;
		i++;
	}
	return ret;
}

//converts int to uint for srand
//based on: https://www.quora.com/How-do-I-convert-an-integer-into-an-unsigned-integer-in-C
uint intToUint(int d){
	return UINT_MAX + 1 + d;
}

//returns 0 based index of random player in gameState
int pickRandomPlayer(struct gameState *g){
	return randIntInclusive(0, g->numPlayers);
}

//takes 0 based index of player and gameState
//makes sure that player has card to be tested, and returns index of that card
int getHandPos(int numPlayer, struct gameState *g){
	int i;
	for(i = 0; i < g->handCount[numPlayer]; ++i){
		if(g->hand[numPlayer][i] == CARD_ENUM){
			return i;
		}
	}
	//card is not in hand, so we have to insert it
	int randomCardIndex = randIntInclusive(0, g->handCount[numPlayer] - 1);
	g->hand[numPlayer][randomCardIndex] = CARD_ENUM;
	//if player had 0 cards, they now have 1
	if(g->handCount[numPlayer] == 0){
		g->handCount[numPlayer] = 1;
	}
	return randomCardIndex;
}

void runRandomTests(){
	//used to store initial gamestate for debugging purposes if test fails
	struct gameState originalState;
	//used for gamestate run through mock function
	struct gameState mockState;
	//used for gamestate run through actual game function
	struct gameState postState;

	//used to hold memory for kingdom cards
	int kingdomCardsHolder[10];

	int i;
	for(i = 0; i < NUM_RANDOM_ITERATIONS; ++i){
		initializeRandomGameState(&originalState, kingdomCardsHolder);
		//pick random player to play the card, and make sure the player
		//has the card to be played, and get the index of it
		int numPlayer = pickRandomPlayer(&originalState);
		int handPos = getHandPos(numPlayer, &originalState);
		//copy random game state to other 2 states
		copyGameState(&originalState, &mockState);
		copyGameState(&originalState, &postState);

		//conditional based on whether card function uses handPos as argument
		#if USE_HAND_POS
			int (*cardFunction)(int, struct gameState*, int) = CARD_FUNC;
			int postRet = cardFunction(numPlayer, &postState, handPos);
			int mockRet = mockCardAction(numPlayer, &mockState, handPos);
		#else 
			int (*cardFunction)(int, struct gameState*) = CARD_FUNC;
			int postRet = cardFunction(numPlayer, &postState);
			int mockRet = mockCardAction(numPlayer, &mockState);
		#endif
		//compare two states and see if they are the same
		int equal = areGameStatesEqual(&postState, &mockState);
		custom_assert(equal, "Testing to see if mock gameState and post gameState have the same memory layout");
		custom_assert(postRet == mockRet, "Test to see if mock card function and real card function have same return values");
		if(!equal){
			printGameStateDifferences(&mockState, &postState);
		}
	}
}



int main(int argc, char const *argv[]){
	if(argc != 2){
		printUsage(argv[0]);
		return 1;
	}
	//convert random seed argument to integer
	int seed = stringToInt(argv[1]);
	//check that seed was numeric
	if(seed == -1){
		printUsage(argv[0]);
		return 1;
	}
	//seed random number
	srand(intToUint(seed));

	puts("Randomly Testing " CARD_NAME "\n");

	runRandomTests();

	printf("\nNumber of random tests %d, number of failures %d\n", NUM_RANDOM_ITERATIONS, numTestsFailed);

	return 0;
}