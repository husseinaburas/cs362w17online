#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int compareHandTreasure (int currentPlayer, struct gameState *originGame, struct gameState * modGame);
int compareStates(struct gameState *originGame, struct gameState *modGame); //prototype
int handCountChange(int currentPlayer, struct gameState *originGame, struct gameState * modGame); 
int deckCountChange(int currentPlayer, struct gameState *originGame, struct gameState * modGame); 
int inactiveChange(int currentPlayer, struct gameState *originGame, struct gameState * modGame);
int compareHand(int currentPlayer, struct gameState *originGame, struct gameState * modGame); 
int compareDiscard(int currentPlayer, struct gameState *originGame, struct gameState * modGame);
int compareDeck(int currentPlayer, struct gameState *originGame, struct gameState * modGame);
int compareNumPlayers(struct gameState *originGame, struct gameState *modGame);
int compareSupply(struct gameState *originGame, struct gameState *modGame);
int compareEmbargo(struct gameState *originGame, struct gameState *modGame);
int compareOutpostPlayed(struct gameState *originGame, struct gameState *modGame);
int compareOutpostTurn(struct gameState *originGame, struct gameState *modGame);
int compareWhoseTurn(struct gameState *originGame, struct gameState *modGame);
int comparePhase(struct gameState *originGame, struct gameState *modGame);
int compareNumActions(struct gameState *originGame, struct gameState *modGame);
int compareCoins(struct gameState *originGame, struct gameState *modGame);
int compareNumBuys(struct gameState *originGame, struct gameState *modGame);
int compareHandCount(struct gameState *originGame, struct gameState *modGame);
int compareDeckCount(struct gameState *originGame, struct gameState *modGame);
int compareDiscardedCount(struct gameState *originGame, struct gameState *modGame);
int comparePlayed(struct gameState *originGame, struct gameState *modGame);
int comparePlayedCount(struct gameState *originGame, struct gameState *modGame);
int compareKingdom(int k[10], struct gameState *originGame, struct gameState *modGame);
int compareVictory(int k[10], struct gameState *originGame, struct gameState *modGame);
int allTests(int numP, int c1, int c2, int c3, int handP, int bonus, int seed);

int main()
{
	printf("-----cardtest2-----\n");
	allTests(3, 0, 0, 0, 0, 0, 0001);
	allTests(2, 0, 0, 1, 1, 1, 9999);
	allTests(1, 0, 1, 1, 2, 2, 8888);
	allTests(4, 1, 1, 1, 3, 3, 1111);
	allTests(5, 0, 0, 2, 4, 4, 6666);

	return 0;
}

int allTests(int numP, int c1, int c2, int c3, int handP, int bonus, int seed)
{
	struct gameState G;
	struct gameState G2;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,sea_hag, tribute, smithy, council_room};

	initializeGame(numP, k, seed, &G);
	memcpy(&G2, &G, sizeof(struct gameState)); 
	
	cardEffect(adventurer, c1, c2, c3, &G2, handP, &bonus);

	//printf("----------Testing if player has 2 additional treasure in hand----------\n");
	int pHandTreasure;
	int pHandCount;
	pHandTreasure =	compareHandTreasure(0, &G, &G2);
	pHandCount = handCountChange(0, &G, &G2);

	if(pHandTreasure == 2 && pHandCount == 2)
	{
	//	printf("----------Passed----------\n");
	}
	else
	{
		printf("----------Failed: player didn't receive 2 additional treasure----------\n");
	}


	//printf("----------Testing inactive players' states----------\n");
	if(inactiveChange(0, &G, &G2) == 0)
	{
	//	printf("----------Passed----------\n");
	}
	else
	{
		printf("----------Failed: inactive players' states were changed----------\n");
	}

	//printf("----------Testing Victory and Kingdom piles----------\n");
	if(	compareVictory(k, &G, &G2) == 0 && compareKingdom(k, &G, &G2) == 0)
	{
		//printf("----------Passed----------\n");
	}
	else
	{
		printf("----------Failed: Victory or Kingdom piles changed----------\n");
	}

	return 0;
}


int compareKingdom(int k[10], struct gameState *originGame, struct gameState *modGame)
{
	int i;
	int kingdomChange = 0;
	for (i=0; i < 10; i++) //
	{
		if (originGame->supplyCount[k[i]] != modGame->supplyCount[k[i]])
		{
			printf("supply of kingdom card %i has changed\n", k[i]);
			kingdomChange++;
		}
		
	}
	return kingdomChange;
}

int compareVictory(int k[10], struct gameState *originGame, struct gameState *modGame)
{
	int i;
	int victoryChange = 0;
	for (i=1; i < 4; i++) //
	{
		if (originGame->supplyCount[i] != modGame->supplyCount[i])
		{
			printf("supply of victory card %i has changed\n", i);
			victoryChange++;
		}
	
	}
	
	return victoryChange;
}


int compareHandTreasure (int currentPlayer, struct gameState *originGame, struct gameState * modGame)
{
	int i;
	int preTreasure = 0;
	int postTreasure = 0;
	for(i = 0; i < originGame->handCount[currentPlayer]; i++)
	{
		if (originGame->hand[currentPlayer][i] == copper || originGame->hand[currentPlayer][i] == silver

			 || originGame->hand[currentPlayer][i] == gold) 
		{
			preTreasure++;

		}
	}

	for(i = 0; i < modGame->handCount[currentPlayer]; i++)
	{
		if (modGame->hand[currentPlayer][i] == copper || modGame->hand[currentPlayer][i] == silver
			 || modGame->hand[currentPlayer][i] == gold) 
		{
			postTreasure++;
		}
	}
	
//	printf("Treasure cards in hand before card was played %i \n", preTreasure);
//	printf("Treasure cards in hand after card was played %i \n", postTreasure);
	return postTreasure - preTreasure;
}



int deckCountChange(int currentPlayer, struct gameState *originGame, struct gameState * modGame) //return pre-hand - post-hand
{
	return modGame->deckCount[currentPlayer] - originGame->deckCount[currentPlayer];
}


int handCountChange(int currentPlayer, struct gameState *originGame, struct gameState * modGame) //return pre-deck - post-deck
{
	return modGame->handCount[currentPlayer] - originGame->handCount[currentPlayer];
}


int inactiveChange(int currentPlayer, struct gameState *originGame, struct gameState * modGame) //1 if other players change
{
	int i; 
	for(i = 0; i < originGame->numPlayers; i++) //for each player
	{
		if (i != currentPlayer) //skip active player
		{
			if (compareHand(i, originGame, modGame) == 1)
			{
				printf("an inactive player's hand was changed\n");
				return 1; 
			}
			if (compareDiscard(i, originGame, modGame) == 1)
			{
				printf("an inactive player's discard pile was changed\n");
				return 1; 
			}
			if (compareDeck(i, originGame, modGame) == 1)
			{
				printf("an inactive player's deck was changed\n");
				return 1; 
			}

		}
			
	}
		return 0;
}


int compareStates(struct gameState *originGame, struct gameState *modGame)
{
	int i;
	compareNumPlayers(originGame, modGame);
	compareSupply(originGame, modGame);
	compareEmbargo(originGame, modGame);
	compareOutpostPlayed(originGame, modGame);
	compareOutpostTurn(originGame, modGame);
	compareWhoseTurn(originGame, modGame);
	comparePhase(originGame, modGame);
	compareNumActions(originGame, modGame);
	compareCoins(originGame, modGame);
	compareNumBuys(originGame, modGame);
	compareHandCount(originGame, modGame);
	compareDeckCount(originGame, modGame);
	compareDiscardedCount(originGame, modGame);
	comparePlayed(originGame, modGame);
	comparePlayedCount(originGame, modGame);
	 		
	for(i = 0; i < originGame->numPlayers; i++) //for all players
	{
		compareHand(i, originGame, modGame); //compare each player's hand
		compareDeck(i, originGame, modGame); //compare each player's deck
		handCountChange(i, originGame, modGame); 
		deckCountChange(i, originGame, modGame); 
		inactiveChange(i, originGame, modGame);
		compareDiscard(i, originGame, modGame);
	}

	return 0;
}


int compareHand(int currentPlayer, struct gameState *originGame, struct gameState * modGame)
{
	int i;
	for(i = 0; i < originGame->handCount[currentPlayer]; i++)
	{
		if (originGame->hand[currentPlayer][i] != modGame->hand[currentPlayer][i])
		{
			return 1;
		}
	}
	return 0;
}


int compareDiscard(int currentPlayer, struct gameState *originGame, struct gameState * modGame)
{
	int i;
	for(i = 0; i < originGame->discardCount[currentPlayer]; i++)
	{
		if (originGame->discard[currentPlayer][i] != modGame->discard[currentPlayer][i])
		{
			return 1;
		}
	}
	return 0;
}


int compareDeck(int currentPlayer, struct gameState *originGame, struct gameState * modGame)
{
	int i;
	for(i = 0; i < originGame->deckCount[currentPlayer]; i++)
	{
		if (originGame->deck[currentPlayer][i] != modGame->deck[currentPlayer][i])
		{
			return 1;
		}
	}
	return 0;
}


int compareNumPlayers(struct gameState *originGame, struct gameState *modGame)
{
	if(originGame->numPlayers != modGame->numPlayers){return 1;}
	return 0;
}


int compareSupply(struct gameState *originGame, struct gameState *modGame)
{
	if(originGame->supplyCount[treasure_map+1] != modGame->supplyCount[treasure_map+1]) {return 1;}
	return 0;
}


int compareEmbargo(struct gameState *originGame, struct gameState *modGame)
{
	if(originGame->embargoTokens[treasure_map+1] != modGame->embargoTokens[treasure_map+1]){return 1;}
	return 0;

}


int compareOutpostPlayed(struct gameState *originGame, struct gameState *modGame)
{
	if(originGame->outpostPlayed != modGame->outpostPlayed){return 1;}
	return 0;
}


int compareOutpostTurn(struct gameState *originGame, struct gameState *modGame)
{
	if(originGame->outpostTurn != modGame->outpostTurn){return 1;}
	return 0;
}


int compareWhoseTurn(struct gameState *originGame, struct gameState *modGame)
{
	if(originGame->whoseTurn != modGame->whoseTurn){return 1;}
	return 0;
}


int comparePhase(struct gameState *originGame, struct gameState *modGame)
{
	if(originGame->phase != modGame->phase){return 1;}
	return 0;
}


int compareNumActions(struct gameState *originGame, struct gameState *modGame)
{
	if(originGame->numActions != modGame->numActions){return modGame->numActions - originGame->numActions;}
	return 0;
}


int compareCoins(struct gameState *originGame, struct gameState *modGame)
{
	if(originGame->coins != modGame->coins) {return 1;}
	return 0;
}


int compareNumBuys(struct gameState *originGame, struct gameState *modGame)
{
	if(originGame->numBuys != modGame->numBuys) {return 1;}
	return 0;
}


int compareHandCount(struct gameState *originGame, struct gameState *modGame)
{
	int i;
	for(i = 0; i < originGame->numPlayers; i++) //for all players
		{
			if(originGame->handCount[i] != modGame->handCount[i]){return 1;} //compare hand count
		}
	return 0;
}


int compareDeckCount(struct gameState *originGame, struct gameState *modGame)
{
	int i;
	for(i = 0; i < originGame->numPlayers; i++) //for all players
		{
			if(originGame->deckCount[i] != modGame->deckCount[i]){return 1;} //compare deck count
		}
	return 0;
}


int compareDiscardedCount(struct gameState *originGame, struct gameState *modGame)
{
	int i;
	for(i = 0; i < originGame->numPlayers; i++) //for all players
		{
			if(originGame->discardCount[i] != modGame->discardCount[i]){return 1;} //compare dicard count
		}
	return 0;
}


int comparePlayed(struct gameState *originGame, struct gameState *modGame)
{
	int i;
	for(i = 0; i < originGame->playedCardCount; i++) //for all played cards
		{	
			if(originGame->playedCards[i] != modGame->playedCards[i]){return 1;} //compare played cards
		}
	return 0;
}


int comparePlayedCount(struct gameState *originGame, struct gameState *modGame)
{
	if(originGame->playedCardCount != modGame->playedCardCount){return 1;} //compare played card count (only 1)
	return 0;
}


