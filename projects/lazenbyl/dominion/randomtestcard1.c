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


//Great Hall test

int main(int argc, char **argv){


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
  		int deckCount = floor(Random()* MAX_DECK);
  		int coinCount = floor(Random()* MAX_COINS);
  		int numActions = floor(Random()* MAX_ACTIONS);
  		int handPos = floor(Random()*(handCount-1));
  		int discardCount = floor(Random()* MAX_DISCARD_COUNT);

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

  		printf("NumPlayers is: %i,Current Player is %i,Hand Count is %i,Deck count is %i,Coin count is %i,Num Actions is %i,Hand Pos is %i\n,Discard Count is %i\n",
  			numPlayers,currentPlayer,handCount,deckCount,coinCount,numActions,handPos);


  		performGreatHallAction(currentPlayer,&state,handPos);

  		//assertions for performGreatHallAction function with random inputs 
  		//1 card added to hand and 1 card discarded
  		if(state.handCount[currentPlayer]==handCount){
  			
  			printf("Hand count PASS for great hall.\n");
  		}
  		else{

  			printf("Hand count FAIL for great hall.Expected hand count = %i Actual hand count = %i\n",handCount,state.handCount[currentPlayer]);
  		}
  		//deck count decreases by 1 because you draw a card 
  		if(state.deckCount[currentPlayer]==deckCount-1 && deckCount>0){

  			printf("Deck count PASS for great hall.\n");	
  		}
  		else if(state.deckCount[currentPlayer]==discardCount-1 && deckCount==0){
  			printf("Deck count PASS for great hall.\n");
  		}
  		else{

  			printf("Deck count FAIL for great hall.Expected deck count = %i Actual deck count = %i\n",deckCount-1,state.deckCount[currentPlayer]);
  		}
  		//1 action gained 
  		if(state.numActions==numActions+1){

  			printf("Number of actions PASS for great hall.");

  		}
  		else{

  			printf("Number of actions FAIL for great hall.Expected number of actions = %i Actual number of actions = %i\n",numActions+1,state.numActions);
  		}
  		//coin count stays the same 
  		if(state.coins==coinCount){

  			printf("Coin count PASS for great hall.\n");
  		}
  		else{

  			printf("Coin count FAIL for great hall.\n");
  		}
  		//discard count should stay the same according to discard function 
  		if(state.discardCount[currentPlayer]==discardCount && deckCount>0){
  			printf("Discard count PASS for great hall.");
  		}
  		else if(state.discardCount[currentPlayer]==0 && deckCount==0){
  			printf("Discard count PASS for great hall when deck is 0.");
  		}
  		else{
  			printf("Discard count FAIL for great hall.Expected number of cards in discard pile = %i Actual number of cards in discard pile = %i\n",discardCount,state.discardCount[currentPlayer]);
  		}


  	}





	return 0;
}