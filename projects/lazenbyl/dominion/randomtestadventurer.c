#include<stdio.h>
#include<stdlib.h>

#include "dominion.h"
#include "rngs.h"

#define MAX_PLAYER 4
#define	MAX_HAND 10
#define MAX_DECK 20
#define MAX_COINS 5
#define MAX_ACTIONS 5
#define MAX_DISCARD_COUNT 10
#define MIN_DECK_COUNT 1  //need at least two treasure in hand 
#define MIN_DISCARD_COUNT 1 //need at least two treasure in hand 


int treasureCount(int amountOfCards, int cardArray[]){

	int treasureCount = 0;
	int i;

	for(i=0;i<amountOfCards;i++){

		int currentCard = cardArray[i];
		if(currentCard==copper || currentCard==silver || currentCard== gold){

			treasureCount++;
		}
	}

	return treasureCount;


}

//adventurer test

int main(int argc, char **argv){

	if (argc < 2) {
		printf("You must supply a random seed!\n");
	}
	int randomNumber = atoi(argv[1]);

	struct gameState state;
  	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
  	sea_hag, tribute, smithy};

  	//
  	int i;
  	int x; 
  	int y;
  	int z;
  	
  	SelectStream(2);
  	PutSeed(randomNumber);

  	for(i=0;i<2000;i++){

  		//generate random player, hand, deck, actions, hand position for Great Hall 
  
  		//make sure numPlayers and handPos are not at 0 
 		int numPlayers = floor(Random()* (MAX_PLAYER-2) )+ 2;//numPlayers should be 2 or more 
  		int currentPlayer = floor(Random() * (numPlayers-1));
  		int handCount = floor(Random()* (MAX_HAND-1)) + 1;//must always be one in the hand to play 
  		int deckCount = floor(Random()* (MAX_DECK-MIN_DECK_COUNT)) + MIN_DECK_COUNT;
  		int coinCount = floor(Random()* MAX_COINS);
  		int numActions = floor(Random()* MAX_ACTIONS);
  		int handPos = floor(Random()*(handCount-1));
  		int discardCount = floor(Random()* (MAX_DISCARD_COUNT-MIN_DISCARD_COUNT)) + MIN_DISCARD_COUNT;
  		

  		state.numPlayers = numPlayers;
  		state.handCount[currentPlayer] = handCount;
  		state.deckCount[currentPlayer] = deckCount;
  		state.coins = coinCount;
  		state.numActions = numActions;
  		state.whoseTurn = currentPlayer;
  		state.phase = 0;
  		state.numBuys = 1;
  		state.discardCount[currentPlayer] = discardCount;
  		state.playedCardCount = 0;

  		//randomly setting the hand for the player 
  		for(x=0;x<handCount;x++){

  			state.hand[currentPlayer][x] = floor(Random()*27);
  		}

  		for(y=0;y<deckCount;y++){

  			state.deck[currentPlayer][y] = floor(Random()*27);
  		}

  		for(z=0;z<discardCount;z++){

  			state.discard[currentPlayer][z] = floor(Random()*27);
  		}

  		int numTreasure = treasureCount(state.deckCount[currentPlayer],state.deck[currentPlayer]);
  		numTreasure+= treasureCount(state.discardCount[currentPlayer],state.discard[currentPlayer]);

  		//need to make sure there are at least two treasure 
  		if(numTreasure<2){

  				int deckPos = floor(Random()* (state.deckCount[currentPlayer]-1));
  				int discardPos = floor(Random()* (state.discardCount[currentPlayer]-1));

  				state.deck[currentPlayer][deckPos] = copper;
  				state.discard[currentPlayer][discardPos] = silver;
  		}



  		printf("NumPlayers is: %i,Current Player is %i,Hand Count is %i,Deck count is %i,Coin count is %i,Num Actions is %i,Hand Pos is %i\n,Discard Count is %i\n",
  			numPlayers,currentPlayer,handCount,deckCount,coinCount,numActions,handPos);

  		struct gameState pre;
  		memcpy(&pre, &state, sizeof(struct gameState));

  		performAdventureAction(&state,currentPlayer);

  		int preHandNumTreasure = treasureCount(pre.handCount[currentPlayer],pre.hand[currentPlayer]);
  		int postHandNumTreasure = treasureCount(state.handCount[currentPlayer],state.hand[currentPlayer]);

  		if(postHandNumTreasure==preHandNumTreasure+2){

  			printf("Treasure count PASS.Treasure added for adventurer action.\n");
  		}
  		else{

  			printf("Treasure count FAIL.Expected treasure = %i. Actual treasure = %i\n",preHandNumTreasure+2,postHandNumTreasure);
  		}

  		if(pre.handCount[currentPlayer]+2==state.handCount[currentPlayer]){

  			printf("Hand count PASS for adventurer action.\n");
  		}
  		else{

  			printf("Hand count FAIL for adventurer action.Expected hand count = %i. Actual hand count = %i.\n",
  				pre.handCount[currentPlayer]+2,state.handCount[currentPlayer]);
  		}
  		if(pre.coins==state.coins){

  			printf("Coin count PASS for adventurer action.\n");
  		}
  		else{

  			printf("Coin count FAIL for adventurer action.Coin count changed.\n");
  		}
  		if(pre.phase==state.phase){

  			printf("Phase PASS for adventurer action.\n");
  		}
  		else{

  			printf("Phase FAIL for adventurer action.\n");
  		}
  		if(pre.numActions==state.numActions){

  			printf("NumActions PASS for adventurer action.\n");
  		}
  		else{

  			printf("NumActions FAIL for adventurer action.\n");
  		}

  	}





	return 0;
}