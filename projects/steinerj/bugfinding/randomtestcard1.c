#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "rngs.h" 
#include <unistd.h>
#include <time.h>
int compareStates(struct gameState *originGame, struct gameState *modGame, int currentPlayer); //prototype
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
int compareVictory(int k[10], struct gameState *originGame, struct gameState *modGame);
int compareKingdom(int k[10], struct gameState *originGame, struct gameState *modGame);

int main(int argc, char *argv[])
{ 
  //int clArgument = atoi(argv[1]);
  int randomPlayer, randomHandPos, randomInitSeed, preHandCount, postHandCount;
  int randomNumPlayers = 0;	
  int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
  struct gameState game;
  struct gameState game2;
  SelectStream(1);
  PutSeed(time(NULL));
  int n;
  int i;

  for (n = 0; n < 2000; n++) 
  {
    for (i = 0; i < sizeof(struct gameState); i++)
    {
      ((char*)&game)[i] = floor(Random() * 256);
    }
	while(randomNumPlayers < 2)
	{
	randomNumPlayers = floor(Random() * MAX_PLAYERS);
	}
	randomInitSeed = floor(Random() * 2147483646);
    initializeGame(randomNumPlayers, k, randomInitSeed, &game);
	memcpy(&game2, &game, sizeof(struct gameState));
	randomPlayer = floor(Random() * randomNumPlayers);
	randomHandPos = floor(Random() * game.handCount[randomPlayer]); 
	preHandCount = game.handCount[randomPlayer];
	smithyFunc(randomPlayer, &game, randomHandPos);	
	postHandCount = game.handCount[randomPlayer];

	if(postHandCount - preHandCount != 2)
	{
		printf("postHandCount is %i preHandCount is %i\n", postHandCount, preHandCount);
		printf("test %i failed. Player's hand wasn't increased by 2\n", n);
		return 0;
	}
	compareStates(&game2, &game, randomPlayer);
  }

  printf ("ALL TESTS OK\n");

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


int compareStates(struct gameState *originGame, struct gameState *modGame, int currentPlayer)
{
	if(compareNumPlayers(originGame, modGame)!= 0)
	{
		printf("change to number of players\n");
		return -1;

	}
	if(compareSupply(originGame, modGame) != 0)
	{
		printf("change to supply\n");
		return -1;
	}
	if(compareEmbargo(originGame, modGame) != 0)
	{
		printf("change to embargo\n");
		return -1;
	}
	if(compareOutpostPlayed(originGame, modGame) != 0)
	{
		printf("change to outpostplayed\n");
		return -1;
	}
	if(compareOutpostTurn(originGame, modGame) != 0)
	{
		printf("change to outpost turn\n");
		return -1;
	}
	if(compareWhoseTurn(originGame, modGame) != 0)
	{
		printf("change to whose turn\n");
		return -1;
	}
	if(comparePhase(originGame, modGame) != 0)
	{
		printf("change to phase\n");
		return -1;
	}
	if(compareNumActions(originGame, modGame) != 0)
	{
		printf("change to number of actions\n");
		return -1;
	}
	if(compareCoins(originGame, modGame) != 0)
	{
		printf("change to number of coins\n");
		return -1;
	}
	if(compareNumBuys(originGame, modGame) != 0)
	{
		printf("change to number of buys\n");
		return -1;
	}

 
	//if(compareHandCount(originGame, modGame) != 0)
	//{
	//	printf("change to hand count\n");
	//	return -1;
    //}
	//if(compareDeckCount(originGame, modGame) != 0)
	//{
	//	printf("change to deck count\n");
	//	return -1;
    //}
	if(compareDiscardedCount(originGame, modGame) != 0)
	{
		printf("change to discard count\n");
		return -1;
	}
	
	if(comparePlayed(originGame, modGame) != 0)
	{
		printf("change to played\n");
		return -1;
	}
//	if(comparePlayedCount(originGame, modGame) != 0)
//	{
//		printf("change to played count\n");
//		return -1;
//	}
	if(inactiveChange(currentPlayer, originGame, modGame) != 0)
	{
		printf("change to inactive players\n");
		return -1;
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
	if(originGame->numPlayers != modGame->numPlayers)
	{
		printf("players changed from %i to %i \n", originGame->numPlayers, modGame->numPlayers);
		return 1;
	}
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


