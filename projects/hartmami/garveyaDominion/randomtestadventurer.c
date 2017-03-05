//random tests for adventurer card (playAdventurer function)

#include "dominion.h"

#define CARD_NAME "Adventurer"
#define CARD_ENUM adventurer
#define CARD_FUNC &playAdventurer
//playAdventurer does not require handPos as an argument
#define USE_HAND_POS 0


//returns 1 if card is treasure card
//0 if not
int isTreasureCard(enum CARD card){
	return card == copper || card == silver || card == gold;
}


//function to mock what playAdventurer should do
//takes cards from deck until 2 treasure cards are revealed
//those 2 treasure cards should be added to the player's hand
int mockCardAction(int currentPlayer, struct gameState *state){
	int treasuresFound = 0;
	int i = 0;
	//need to save initial discard, since we don't want to check discarded
	//cards from deck, since we already know they are not treasures
	int initialDiscardCount = state->discardCount[currentPlayer];
	//first look through all the cards in a player's deck for treasures
	while(treasuresFound < 2 && i < state->deckCount[currentPlayer]){
		//draw a card, and then check for treasure
		drawCard(currentPlayer, state);
		//examine to see if treasure
		//if not discard the card
		int cardPos = state->handCount[currentPlayer] - 1;
		if(isTreasureCard(state->hand[currentPlayer][cardPos])){
			treasuresFound++;
		}
		else{
			//discard card since not a treasure
			discardCard(cardPos, currentPlayer, state, 0);
		}
		i++;
	}
	i = 0;
	//if still not enough treasures found, look through discard
	//until found 2 treasures, or discard is exhausted
	//discard should be sorted first before doing this, but there is no built in function to do this
	//so we are not going to write our own, since because of randomness in the shuffling the tests
	//would always fail
	while(treasuresFound < 2 && i < initialDiscardCount){
		if(isTreasureCard(state->discard[currentPlayer][i])){
			//add card to hand
			state->hand[currentPlayer][state->handCount[currentPlayer]] = state->discard[currentPlayer][i];
			//swap last card in discard with the card we found
			state->discard[currentPlayer][i] = state->discard[currentPlayer][state->discardCount[currentPlayer] - 1];
			//add to handcount and subtract from discard
			state->handCount[currentPlayer] = state->handCount[currentPlayer] + 1;
			state->discardCount[currentPlayer] = state->discardCount[currentPlayer] - 1;
			treasuresFound++;
		}
		i++;
	}


	//last thing to do is discard adventurer from player's hand
	//since handPos is not given as an argument, we will have to search for it
	//so we will discard 1st adventurer card found
	for(i = 0; i < state->handCount[currentPlayer]; ++i){
		if(state->hand[currentPlayer][i] == CARD_ENUM){
			discardCard(i, currentPlayer, state, 0);
			return 0;
		}
	}

	//return error, since adventurer was not found in player's hand to discard
	return -1;
}


#include "random_test_runner.c"