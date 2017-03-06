#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#define TRUE 0
#define FALSE 1

int main(){
	struct gameState game;
	game.whoseTurn = 0;
	game.numActions = 1;
	game.handCount[0] = 1;
	game.hand[0][0] = adventurer;
	game.deck[0][6] = feast;
	game.deck[0][5] = smithy;
	game.deck[0][4] = silver;
	game.deck[0][3] = gold;
	game.deck[0][2] = copper;
	game.deck[0][1] = estate; 
	game.deck[0][0] = curse; 
	game.deckCount[0] = 7;
	game.playedCardCount = 0;
	game.discardCount[0] = 0;
	int temphand[10];
	
	int t1 = playAdventurer(&game, 0, 0, 0, temphand, 0);
	
	int tests_passed = 0;
	
	printf("Testing Adventurer\n");
	
	if (t1 != 0){
		printf("Function returned incorrect value\n");
		tests_passed = 1;
	}
	
	if (game.handCount[0] > 2){ //player starts with 1 card, draws 2 treasures, discards adventurer and non-treasures
		printf("Adventurer drew too many cards or did not discard properly\n");
		tests_passed = 1;
	}
	
	if (game.handCount[0] < 2){
		printf("Adventurer drew too few cards or did not discard properly\n");
		tests_passed = 1;
	}
	
	if (game.numActions != 1){ //so playAdventurer itself doesn't/shouldn't decrement the number of actions. playCard does. 
		printf("Number of actions improperly altered by function\n");
		tests_passed = 1;
	}
	
	if (game.deckCount[0] != 3){ //in this case there should be 3 cards left in the deck 
		printf("Adventurer did not draw the expected number of cards from the deck\n");
		tests_passed = 1;
	}
	
	if (game.discardCount[0] != 3){ //in this case 2 of the drawn cards should be discarded, plus adventurer
		printf("Adventurer not properly moving non-treasures and itself to discard pile\n");
		tests_passed = 1;
	}
	
	if (tests_passed != 0){
		printf("playAdventurer() function contains bugs. Test failed.\n");
	}
	else{
		printf("playAdventurer() passed all tests.\n");
	}
	
	return 0;
}