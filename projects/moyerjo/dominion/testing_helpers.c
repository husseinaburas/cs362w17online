#include "testing_helpers.h"

#define SUPPLYTOTAL 27

int compareGameState(int player, struct gameState *state1, struct gameState *state2) {

	int i = 0;
	if (state1->handCount[player] != state2->handCount[player]) {
		return 0;
	}
	for (i = state1->handCount[player]; i < state1->handCount[player]; i++) {
		if (state1->hand[player][i] != state2->hand[player][i]) {
			return 0;
		}
	}

	if (state1->deckCount[player] != state2->deckCount[player]) {
		return 0;
	}

	for (i = state1->deckCount[player]; i < state1->deckCount[player]; i++) {
		if (state1->deck[player][i] != state2->deck[player][i]) {
			return 0;
		}
	}

	if (state1->discardCount[player] != state2->discardCount[player]) {
		return 0;
	}
	for (i = state1->discardCount[player]; i < state1->discardCount[player]; i++) {
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
	int curPlayers;
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
		state->numPlayers = rand() % MAX_PLAYERS + 1; //randomly set number of players

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
		}
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

		//the switch is largely to add some granularity, some cards will go to the hand, while most will go to the deck/discard.
		//Rarely some will go to trash - e.g. they will go nowhere
		switch (sendLocation) {
		case 1:
		case 2:
		case 3:
			state->hand[playerPicked][state->handCount[playerPicked]] = card;
			state->handCount[playerPicked]++;
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
			state->discard[playerPicked][state->discardCount[playerPicked]] = card;
			state->discardCount[playerPicked]++;
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
			state->deck[playerPicked][state->deckCount[playerPicked]] = card;
			state->deckCount[playerPicked]++;
			break;
		case 22:
			state->playedCards[state->playedCardCount] = card;
			state->playedCardCount++;
			break;
		default:
			//trashed
			break;
		}
	}
}

void shuffleCards(int curPlayer, int deckSection, struct gameState * state){
	//0 = deck, 1 = discard, 2 = hand, 3 = played
	int cardPlace1, cardPlace2, temp;

	if (deckSection == 0) {
		cardPlace1 = rand() % state->deckCount[curPlayer];
		cardPlace2 = rand() % state->deckCount[curPlayer];
		temp = state->deck[curPlayer][cardPlace1];
		state->deck[curPlayer][cardPlace1] = state->deck[curPlayer][cardPlace2];
		state->deck[curPlayer][cardPlace2] = temp;
	}
	else if (deckSection == 1) {
		cardPlace1 = rand() % state->discardCount[curPlayer];
		cardPlace2 = rand() % state->discardCount[curPlayer];
		temp = state->discard[curPlayer][cardPlace1];
		state->discard[curPlayer][cardPlace1] = state->discard[curPlayer][cardPlace2];
		state->discard[curPlayer][cardPlace2] = temp;
	}
	else if (deckSection == 2) {
		cardPlace1 = rand() % state->handCount[curPlayer];
		cardPlace2 = rand() % state->handCount[curPlayer];
		temp = state->hand[curPlayer][cardPlace1];
		state->hand[curPlayer][cardPlace1] = state->hand[curPlayer][cardPlace2];
		state->hand[curPlayer][cardPlace2] = temp;
	}
	else {
		cardPlace1 = rand() % state->playedCardCount;
		cardPlace2 = rand() % state->playedCardCount;
		temp = state->playedCards[cardPlace1];
		state->playedCards[cardPlace1] = state->playedCards[cardPlace2];
		state->playedCards[cardPlace2] = temp;
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
int numActions; /* Starts at 1 each turn 
int coins; /* Use as you see fit! 
int numBuys; /* Starts at 1 each turn 
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