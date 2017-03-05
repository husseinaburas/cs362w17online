#include "dominion.h"
#include "dominion_helpers.h"
#include "refactor.h"

void playAdventurer(struct gameState *state, int currentPlayer, int drawntreasure)
{
int temphand[MAX_HAND];
int z = 0;// this is the counter for the temp hand	
int cardDrawn;   

	while(drawntreasure<2){
		if (state->deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
			shuffle(currentPlayer, state);
		  }
		  
		drawCard(currentPlayer, state);
		cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]];//?? //top card of hand is most recently drawn card.
		if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
			drawntreasure++;
		else{
			temphand[z]=cardDrawn;
			state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
			z++;
		 }
     }
      
	while(z-1>=0){
		state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
		z=z-1;
      }	
	
	
}



void playSmithy(struct gameState *state, int currentPlayer, int handPos)
{
	int i;
	
   for (i = 0; i < 5; i++){	//??
	  drawCard(currentPlayer, state);
	}
			
    //discard card from hand
    discardCard(handPos, currentPlayer, state, 0);	
		
}


void playCouncil_room(struct gameState *state, int currentPlayer, int handPos)
{
	int i;
	
	for (i = 0; i < 4; i++){
	  drawCard(currentPlayer, state);
	}
			
      //+1 Buy
      //state->numBuys++;  //??
			
      //Each other player draws a card
     for (i = 0; i < state->numPlayers; i++){
	  if ( i != currentPlayer ){
	      drawCard(i, state);
	    }
	 }
			
      //put played card in played card pile
      discardCard(handPos, currentPlayer, state, 0);	
	
}


void playVillage(struct gameState *state, int currentPlayer, int handPos)
{
     drawCard(currentPlayer, state);
			
      //+2 Actions
     state->numActions = state->numActions + 2;
			
      //discard played card from hand
     discardCard(handPos, currentPlayer, state, 0);	

}


void playGreat_hall(struct gameState *state, int currentPlayer, int handPos)
{
      drawCard(currentPlayer, state);
	   //+1 Actions
      //state->numActions++; //??
			
      //discard card from hand
      discardCard(handPos, currentPlayer, state, 0);	
	
}