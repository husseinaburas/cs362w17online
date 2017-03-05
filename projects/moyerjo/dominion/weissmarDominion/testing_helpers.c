#include "testing_helpers.h"
#include <stdlib.h>
#include <stdio.h>

#define SUPPLYTOTAL 27

int compareGameState(int player, struct gameState *state1, struct gameState *state2) {

	int i = 0;
	if (state1->handCount[player] != state2->handCount[player]) {
		return 0;
	}
	for (i = 0; i < state1->handCount[player]; i++) {
		if (state1->hand[player][i] != state2->hand[player][i]) {
			return 0;
		}
	}

	if (state1->deckCount[player] != state2->deckCount[player]) {
		return 0;
	}

	for (i = 0; i < state1->deckCount[player]; i++) {
		if (state1->deck[player][i] != state2->deck[player][i]) {
			return 0;
		}
	}

	if (state1->discardCount[player] != state2->discardCount[player]) {
		return 0;
	}
	for (i = 0; i < state1->discardCount[player]; i++) {
		if (state1->discard[player][i] != state2->discard[player][i]) {
			return 0;
		}
	}
	return 1; //all compared values are equal
}

int cardNumbersConstant(int player, struct gameState *state1, struct gameState *state2) {
	int state1Cards = 0, state2Cards = 0;

	state1Cards = state1->handCount[player] + state1->deckCount[player] + state1->playedCardCount + state1->discardCount[player];
	
	state2Cards = state2->handCount[player] + state2->deckCount[player] + state2->playedCardCount + state2->discardCount[player];

	if (state1Cards == state2Cards) {
		return 1;
	}
	else {
		return 0;
	}

	return 0;
}

int supplyUnchanged(struct gameState *state1, struct gameState *state2) {
	int i;
	for (i = 0; i < SUPPLYTOTAL; i++) {
		if (state1->supplyCount[i] != state2->supplyCount[i]) {
			return 0;
		}
	}
	return 1;
}

int treasureMapSupplyUnchanged(struct gameState *state1, struct gameState *state2) {
	int i;
	for (i = 0; i < SUPPLYTOTAL; i++) {
		if (state1->supplyCount[i] != state2->supplyCount[i] && i != 6) {
			return 0;
		}
	}
	return 1;
}

int scoreForRefactor(int player, struct gameState *state) {

	int i;
	int score = 0;
	//score from hand

	for (i = 0; i < state->handCount[player]; i++)
	{
		if (state->hand[player][i] == curse) {
			score = score - 1;
		}
		else if (state->hand[player][i] == estate) {
			score = score + 1;
		}
		else if (state->hand[player][i] == duchy) {
			score = score + 3;
		}
		else if (state->hand[player][i] == province) {
			score = score + 6;
		}
		else if (state->hand[player][i] == great_hall) {
			score = score + 1;
		}
		else if (state->hand[player][i] == gardens) {
			score = score + ((state->handCount[player] + state->deckCount[player] + state->discardCount[player]) / 10);
		}
	}

	//score from discard
	for (i = 0; i < state->discardCount[player]; i++)
	{
		if (state->discard[player][i] == curse) {
			score = score - 1;
		}
		else if (state->discard[player][i] == estate) {
			score = score + 1;
		}
		else if (state->discard[player][i] == duchy) {
			score = score + 3;
		}
		else if (state->discard[player][i] == province) {
			score = score + 6;
		}
		else if (state->discard[player][i] == great_hall) {
			score = score + 1;
		}
		else if (state->discard[player][i] == gardens) {
			score = score + ((state->handCount[player] + state->deckCount[player] + state->discardCount[player]) / 10);
		}
	}

	//score from deck
	for (i = 0; i < state->deckCount[player]; i++)
	{
		if (state->deck[player][i] == curse) {
			score = score - 1;
		}
		else if (state->deck[player][i] == estate) {
			score = score + 1;
		}
		else if (state->deck[player][i] == duchy) {
			score = score + 3;
		}
		else if (state->deck[player][i] == province) {
			score = score + 6;
		}
		else if (state->deck[player][i] == great_hall) {
			score = score + 1;
		}
		else if (state->deck[player][i] == gardens) {
			score = score + ((state->handCount[player] + state->deckCount[player] + state->discardCount[player]) / 10);
		}
	}

	return score;
}

void randomSetup(struct gameState *state) {
	int maxRemainingCopper;
	int kingdomCount = 0, kingdomCardStackSize;
	int i;
	int kingdomCard;
	int emptySupplies = 0;
	int outpostRandom = 0;

	//set supplies to -1
	for (i = 0; i <= treasure_map; i++) {
		state->supplyCount[i] = -1;
	}

	do {
		state->numPlayers = rand() % 3 + 2; //randomly set number of players

		for (i = 0; i < state->numPlayers; i++) {
			state->discardCount[i] = 0;
			state->handCount[i] = 0;
			state->deckCount[i] = 0;
		}
		state->playedCardCount = 0;

		if (state->numPlayers == 2) {
			state->supplyCount[curse] = rand() % 11;
			state->supplyCount[estate] = rand() % 9;
			state->supplyCount[duchy] = rand() % 9;
			state->supplyCount[province] = rand() % 9;
		}
		else if (state->numPlayers == 3) {
			state->supplyCount[curse] = rand() % 21;
			state->supplyCount[estate] = rand() % 13;
			state->supplyCount[duchy] = rand() % 13;
			state->supplyCount[province] = rand() % 13;
		}
		else {
			state->supplyCount[curse] = rand() % 31;
			state->supplyCount[estate] = rand() % 13;
			state->supplyCount[duchy] = rand() % 13;
			state->supplyCount[province] = rand() % 13;
		}
		
		maxRemainingCopper = 60 - (state->numPlayers * 7);
		state->supplyCount[copper] = rand() % (maxRemainingCopper + 1);
		state->supplyCount[silver] = rand() % 40;
		state->supplyCount[gold] = rand() % 30;
		
		for (i = 0; i < 7; i++) {
			if (state->supplyCount[i] == 0) {
				emptySupplies++;
			}
		}
	} while (emptySupplies < 3);


	if (state->numPlayers == 2) {
		kingdomCardStackSize = 8;
	}
	else {
		kingdomCardStackSize = 12;
	}


	while (kingdomCount <= 10) {
		kingdomCard = rand() % (treasure_map - 7) + 7; //random card - min is adventurer, max is treasure_map

		//fills up to 10 supply piles with cards - will create a game state with up to three empty piles (three empty would be last turn being completed)
		if (state->supplyCount[kingdomCard] <= 0) {
			state->supplyCount[kingdomCard] = rand() % (kingdomCardStackSize + 1);
			if (state->supplyCount[kingdomCard] <= 0 && emptySupplies < 3) {
				emptySupplies++;
				kingdomCount++;
			}
			else if (state->supplyCount[kingdomCard] > 0) {
				kingdomCount++;
			}
		}
	}


	if (state->numPlayers == 2) {
		addCards(curse, 10 - state->supplyCount[curse], state);
	}
	else if (state->numPlayers == 3) {
		addCards(curse, 20 - state->supplyCount[curse], state);
	}
	else {
		addCards(curse, 30 - state->supplyCount[curse], state);
	}

	//send the various cards to the deck, discard, hands, etc. of the various players
	addCards(copper, 60 - state->supplyCount[copper], state);
	addCards(silver, 40 - state->supplyCount[silver], state);
	addCards(gold, 30 - state->supplyCount[gold], state);

	if (state->numPlayers == 2) {
		for (i = 1; i < 4; i++) {
			if (state->supplyCount[i] >= 0) {
				addCards(i, 8 - state->supplyCount[i], state);
			}
		}

		for (i = 7; i < treasure_map + 1; i++) {
			if (state->supplyCount[i] >= 0) {
				addCards(i, 8 - state->supplyCount[i], state);
			}
		}
	}
	else {
		for (i = 1; i < 4; i++) {
			if (state->supplyCount[i] >= 0) {
				addCards(i, 12 - state->supplyCount[i], state);
			}
		}
		for (i = 7; i < treasure_map + 1; i++) {
			if (state->supplyCount[i] >= 0) {
				addCards(i, 12 - state->supplyCount[i], state);
			}
		}
	}

	//Set up the remaining gamestate
	state->whoseTurn = random() % state->numPlayers;

	state->coins = rand() % 1000; //the max gold can go quite high, but this is likely a safe bet for potential coins using the limited set we are allowed
	state->numActions = rand() % 50;
	state->numBuys = rand() % 50;
	state->phase = 0; //unclear, but it should likely be 0 for playing cards
	//sets outpost flags - appears to not be functioning yet

	//only mess with flags if outposts are in play
	if (state->supplyCount[outpost] >= 0) {
		outpostRandom = rand() % 10 + 1;
		switch (outpostRandom) {
		case 1:
			state->outpostPlayed = 1;
			break;
		case 2:
			state->outpostTurn = 1;
			break;
		default:
			break;
		}
	}
	else {
		state->outpostTurn = 0;
		state->outpostPlayed = 0;
	}

	//SHUFFLE THE DECKS, DISCARDS, HANDS, ETC. 50 times for each player
	for (i = 0; i < state->numPlayers; i++) {
		int j;

		for (j = 0; j < 50; j++) {
			shuffleCards(i, 0, state);
			shuffleCards(i, 1, state);
			shuffleCards(i, 2, state);
			shuffleCards(i, 3, state);
		}
	}


}

void addCards(int card, int numToAdd, struct gameState *state) {
	int i;
	int sendLocation; //represents the location to send the card to
	int playerPicked; //represents the player to send the card to

	for (i = 0; i < numToAdd; i++) {
		playerPicked = rand() % state->numPlayers;
		sendLocation = rand() % 23 + 1;
		//printf("TEST - ADDCARD ITERATION %d\n", i);
		//the switch is largely to add some granularity, some cards will go to the hand, while most will go to the deck/discard.
		//Rarely some will go to trash - e.g. they will go nowhere
		switch (sendLocation) {
		case 1:
		case 2:
		case 3:
			//printf("TEST - ADDCARD 1-3\n");
			//printf("PLAYER PICKED: %d Card: %d COUNT: %d\n", playerPicked, card, state->handCount[playerPicked]);
			//printf("TEST - ADDCARD 1-3\n");
			state->hand[playerPicked][state->handCount[playerPicked]] = card;
			state->handCount[playerPicked]++;
			//printf("TEST - ADDCARD 1-3 END\n");
			break;
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
			//printf("TEST - ADDCARD 13-21\n");
			//printf("PLAYER PICKED: %d Card: %d COUNT: %d\n", playerPicked, card, state->discardCount[playerPicked]);
			state->discard[playerPicked][state->discardCount[playerPicked]] = card;
			//printf("TEST - ADDCARD 13-21\n");
			state->discardCount[playerPicked]++;
			//printf("TEST - ADDCARD 4-12 END\n");
			break;
		case 13:
		case 14:
		case 15:
		case 16:
		case 17:
		case 18:
		case 19:
		case 20:
		case 21:
			//printf("TEST - ADDCARD 13-21\n");
			//printf("PLAYER PICKED: %d Card: %d COUNT: %d\n", playerPicked, card, state->deckCount[playerPicked]);
			state->deck[playerPicked][state->deckCount[playerPicked]] = card;
			//printf("TEST - ADDCARD 13-21\n");
			state->deckCount[playerPicked]++;
			//printf("TEST - ADDCARD 13-21 END\n");
			break;
		case 22:
			//printf("TEST - ADDCARD 22\n");
			//printf("PLAYER PICKED: %d Card: %d COUNT: %d\n", playerPicked, card, state->playedCardCount);
			state->playedCards[state->playedCardCount] = card;
			//printf("TEST - ADDCARD 22\n");
			state->playedCardCount++;
			//printf("TEST - ADDCARD 22 END\n");
			break;
		default:
			//printf("TEST - ADDCARD DEFAULT\n");
			//printf("PLAYER PICKED: %d\n", playerPicked);
			break;
		}
	}

}

void shuffleCards(int curPlayer, int deckSection, struct gameState * state){
	//0 = deck, 1 = discard, 2 = hand, 3 = played
	int cardPlace1, cardPlace2, temp;

	if (deckSection == 0 && state->deckCount[curPlayer] > 2) {

		cardPlace1 = rand() % state->deckCount[curPlayer];
		cardPlace2 = rand() % state->deckCount[curPlayer];
		temp = state->deck[curPlayer][cardPlace1];
		state->deck[curPlayer][cardPlace1] = state->deck[curPlayer][cardPlace2];
		state->deck[curPlayer][cardPlace2] = temp;
	}
	else if (deckSection == 1 && state->discardCount[curPlayer] > 2) {
		cardPlace1 = rand() % state->discardCount[curPlayer];
		cardPlace2 = rand() % state->discardCount[curPlayer];
		temp = state->discard[curPlayer][cardPlace1];
		state->discard[curPlayer][cardPlace1] = state->discard[curPlayer][cardPlace2];
		state->discard[curPlayer][cardPlace2] = temp;
	}
	else if (deckSection == 2 && state->handCount[curPlayer] > 2) {
		cardPlace1 = rand() % state->handCount[curPlayer];
		cardPlace2 = rand() % state->handCount[curPlayer];
		temp = state->hand[curPlayer][cardPlace1];
		state->hand[curPlayer][cardPlace1] = state->hand[curPlayer][cardPlace2];
		state->hand[curPlayer][cardPlace2] = temp;
	}
	else if (deckSection == 3 && state->playedCardCount > 2) {
		cardPlace1 = rand() % state->playedCardCount;
		cardPlace2 = rand() % state->playedCardCount;
		temp = state->playedCards[cardPlace1];
		state->playedCards[cardPlace1] = state->playedCards[cardPlace2];
		state->playedCards[cardPlace2] = temp;
	}
}

int validateAdventurerDraw(int curPlayer, struct gameState *state1, struct gameState *state2) {
	int i;
	int failed = 0;
	int coinCount = 0;
	int cardsToDiscard = 0;
	int totalTreasure = 0;
	//checks cards in deck
	for (i = state1->deckCount[curPlayer] - 1; i >= 0 && coinCount < 2; i--) {
		if (state1->deck[curPlayer][i] == copper || state1->deck[curPlayer][i] == silver || state1->deck[curPlayer][i] == gold) {
			if (state2->hand[curPlayer][state2->handCount[curPlayer] - (2 - coinCount)] != state1->deck[curPlayer][i]) {
				//incorrect position of the drawn card
				printf("Test Failed - Incorrect position of treasure cards drawn\n");
				failed = 1;
			}
			coinCount++;
		}
		else {
			//not a coin card
			cardsToDiscard++;
		}
	}
	if (coinCount >= 2) {
		if (state1->discardCount[curPlayer] + cardsToDiscard != state2->discardCount[curPlayer]) {
			printf("Test Failed - Discard did not increase by number of non-treasure cards drawn\n");
			failed = 1;
		}
	}
	else {
		//check discard for potential treasure cards
		for (i = 0; i < state1->discardCount[curPlayer]; i++) {
			if (state1->discard[curPlayer][i] == copper || state1->discard[curPlayer][i] == silver || state1->discard[curPlayer][i] == gold) {
				//found a coin
				if (state2->hand[curPlayer][state2->handCount[curPlayer] - (2 - coinCount)] != copper || state2->hand[curPlayer][state2->handCount[curPlayer] - (2 - coinCount)] != silver || state2->hand[curPlayer][state2->handCount[curPlayer] - (2 - coinCount)] != gold) {
					printf("Test Failed - expected drawn item was not treasure\n");
					failed = 1;
				}
				coinCount++;
			}
		}
		if (state1->handCount[curPlayer] + (coinCount - 1) != state2->handCount[curPlayer]) {
			printf("Test Failed - Hand size not as expected based up on treasure drawn\n");
			failed = 1;
		}
	}

	for (i = 0; i < state1->deckCount[curPlayer]; i++) {
		if (state1->deck[curPlayer][i] == copper || state1->deck[curPlayer][i] == silver || state1->deck[curPlayer][i] == gold) {
			totalTreasure++;
		}
	}

	for (i = 0; i < state1->discardCount[curPlayer]; i++) {
		if (state1->discard[curPlayer][i] == copper || state1->discard[curPlayer][i] == silver || state1->discard[curPlayer][i] == gold) {
			totalTreasure++;
		}
	}

	if (totalTreasure > 2) {
		totalTreasure = 2;
	}

	if (state1->handCount[curPlayer] + (totalTreasure - 1) != state2->handCount[curPlayer]) {
		printf("Test Failed - Hand size not as expected base on possible treasure cards to draw\n");
		failed = 1;
	}

	if (failed == 1) {
		return 0;
	}
	else {
		return 1;
	}
}

int testFlags(struct gameState *state1, struct gameState *state2) {
	int failed = 0, i;
	if (state1->numPlayers != state2->numPlayers) {
		printf("Test Failed - num players was changed\n");
		failed = 1;
	}
	if (state1->outpostPlayed != state2->outpostPlayed) {
		printf("Test Failed - outpostPlayed was changed\n");
		failed = 1;
	}
	if (state1->outpostTurn != state2->outpostTurn) {
		printf("Test Failed - outpostTurn was changed\n");
		failed = 1;
	}
	if (state1->whoseTurn != state2->whoseTurn) {
		printf("Test Failed - whose turn was changed\n");
		failed = 1;
	}
	if (state1->phase != state2->phase) {
		printf("Test Failed - phase was changed\n");
		failed = 1;
	}
	//not testing coins - implementation is a little too ambiguous at the moment
	for (i = 0; i < treasure_map + 1; i++) {
		if (state1->embargoTokens[i] != state2->embargoTokens[i]) {
			failed = 1;
		}
	}
	if (failed == 1) {
		return 0;
	}
	else {
		return 1; //tests ok
	}
}


/*
struct gameState {
int numPlayers; //number of players
int supplyCount[treasure_map+1];  //this is the amount of a specific type of card given a specific number.
int embargoTokens[treasure_map+1];
int outpostPlayed;
int outpostTurn;
int whoseTurn;
int phase;
int numActions; // Starts at 1 each turn 
int coins; // Use as you see fit! 
int numBuys; // Starts at 1 each turn 
int hand[MAX_PLAYERS][MAX_HAND];
int handCount[MAX_PLAYERS];
int deck[MAX_PLAYERS][MAX_DECK];
int deckCount[MAX_PLAYERS];
int discard[MAX_PLAYERS][MAX_DECK];
int discardCount[MAX_PLAYERS];
int playedCards[MAX_DECK];
int playedCardCount;
};
*/