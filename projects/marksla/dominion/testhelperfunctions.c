/*************************************************************************
 * Author: Lance Marks marksla
 * Date: 20170205
 * Class: CS362 Software Development II
 * Description: This is a set of helper functions for test suite
 * **********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "testhelperfunctions.h"

int fillPlayerHandDeckDiscardRandom(int player, struct gameState *state) {
   int i, randDeckCount, randHandCount, randDiscardCount;

   randDeckCount = (rand() % 100);
   state->deckCount[player] = randDeckCount;
   randHandCount = (rand() % 100);
   state->handCount[player] = randHandCount;
   randDiscardCount = (rand() % 100);
   state->discardCount[player] = randDiscardCount;

   for (i=0; i<randDeckCount; i++) {
     state->hand[player][i] = (rand() % 26);
   }

   for (i=0; i<randHandCount; i++) {
     state->deck[player][i] = (rand() % 26);
   }

   for (i=0; i<randHandCount; i++) {
     state->discard[player][i] = (rand() % 26);
   }

   return 1;

}

int fillPlayerHand(int player, int card, int count, struct gameState *state) {
  int i;

  for (i = 0; i < count; i++) {
    state->hand[player][i] = card;
  }

  state->handCount[player] = count;

  return 1;
}

int placePlayerHand(int player, int card, int position, struct gameState *state) {
  state->hand[player][position] = card;
  return 1;
}

int fillPlayerDeck(int player, int card, int count, struct gameState *state) {
  int i;

  for (i = 0; i < count; i++) {
    state->deck[player][i] = card;
  }

  state->deckCount[player] = count;

  return 1;
}

int placePlayerDeck(int player, int card, int position, struct gameState *state) {
  state->deck[player][position] = card;
  return 1;
}

int fillPlayerDiscard(int player, int card, int count, struct gameState *state) {
  int i;

  for (i = 0; i < count; i++) {
    state->discard[player][i] = card;
  }

  state->discardCount[player] = count;

  return 1;
}

int placePlayerDiscard(int player, int card, int position, struct gameState *state) {
  state->discard[player][position] = card;
  return 1;
}

int assertTest(int result, int expected, int testNumber) {
  if (result == expected) {
    printf("TEST %d SUCCESSFULLY COMPLETED\n",testNumber);
    return 1;
  } else {
    printf("TEST %d FAILED\n",testNumber);
    printf("EXPECTED %d ---- ACTUAL %d\n",expected,result);
    return 0;
  }
}

int controlPlayAdventurer(struct gameState *state, int handPos) {
      int drawntreasure = 0;
      int currentPlayer = whoseTurn(state);
      int temphand[MAX_HAND];
      int cardDrawn;
      int z = 0; //counter for tempHand
      state->numActions--;

      //put played card in played card pile
      state->playedCards[state->playedCardCount] = state->hand[currentPlayer][handPos];
      state->playedCardCount = state->playedCardCount + 1;
      //replace played card with last card in hand
      state->hand[currentPlayer][handPos] = state->hand[currentPlayer][ (state->handCount[currentPlayer] - 1)];
      //set last card to -1
      state->hand[currentPlayer][state->handCount[currentPlayer] - 1] = -1;
      //reduce number of cards in hand
      state->handCount[currentPlayer] = state->handCount[currentPlayer] - 1;

      while(drawntreasure<2){
	if (state->deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
	  shuffle(currentPlayer, state);
	}
	drawCard(currentPlayer, state);
	cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
	if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
	  drawntreasure++;
	else{
          //Place card in temphand and remove from players hand
	  temphand[z]=cardDrawn;
          state->hand[currentPlayer][state->handCount[currentPlayer] - 1] = -1;
	  state->handCount[currentPlayer]--; 
	  z++;
	}
      }
      while(z!=0){
        state->discardCount[currentPlayer] = state->discardCount[currentPlayer] + 1;  
	state->discard[currentPlayer][state->discardCount[currentPlayer]]=temphand[z]; // discard all cards in play that have been drawn
	z=z-1;
      }

      return 0;
}

int controlPlaySmithy(struct gameState *state, int handPos) {
    int i;
    int currentPlayer = whoseTurn(state);
    state->numActions--;
    //put played card in played card pile
    state->playedCards[state->playedCardCount] = state->hand[currentPlayer][handPos];
    state->playedCardCount = state->playedCardCount + 1;
    //replace played card with last card in hand
    state->hand[currentPlayer][handPos] = state->hand[currentPlayer][ (state->handCount[currentPlayer] - 1)];
    //set last card to -1
    state->hand[currentPlayer][state->handCount[currentPlayer] - 1] = -1;
    //reduce number of cards in hand
    state->handCount[currentPlayer] = state->handCount[currentPlayer] - 1;

    //+3 Cards
    for (i = 0; i < 3; i++)
      {
        drawCard(currentPlayer, state);
      }
			
    return 0;
}

int controlPlayVillage(struct gameState *state, int handPos) {
    int currentPlayer = whoseTurn(state);
    state->numActions--;

    //put played card in played card pile
    state->playedCards[state->playedCardCount] = state->hand[currentPlayer][handPos];
    state->playedCardCount = state->playedCardCount + 1;
    //replace played card with last card in hand
    state->hand[currentPlayer][handPos] = state->hand[currentPlayer][ (state->handCount[currentPlayer] - 1)];
    //set last card to -1
    state->hand[currentPlayer][state->handCount[currentPlayer] - 1] = -1;
    //reduce number of cards in hand
    state->handCount[currentPlayer] = state->handCount[currentPlayer] - 1;

    //+1 Card
    drawCard(currentPlayer, state);
                      
    //+2 Actions
    state->numActions = state->numActions + 2;
                      
    //discard played card from hand
    discardCard(handPos, currentPlayer, state, 0);

    return 0;
}

