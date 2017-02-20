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
	game.deck[0][4] = copper;
	game.deck[0][3] = estate;
	game.deck[0][2] = feast;
	game.deck[0][1] = curse; 
	game.deck[0][0] = silver; 
	game.deckCount[0] = 5;
	game.playedCardCount = 0;
	game.discardCount[0] = 0;
	
	int t1 = playAdventurer(&game);
	
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
	
	if (game.deckCount[0] != 0){ //in this case the entire deck should be drawn through 
		printf("Adventurer did not draw the expected number of cards from the deck\n");
		tests_passed = 1;
	}
	
	if (game.discardCount[0] != 4){ //in this case adventurer + estate + feast + curse should be discarded
		printf("Adventurer not properly moving non-treasures and itself to discard pile\n");
		tests_passed = 1;
	}
	
	if (tests_passed != 0){
		printf("playVAdventurer() function contains bugs. Test failed.\n");
	}
	else{
		printf("playAdventurer() passed all tests.\n");
	}
	
	return 0;
}