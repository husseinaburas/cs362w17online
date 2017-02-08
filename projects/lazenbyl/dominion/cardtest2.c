#include<stdio.h>
#include<stdlib.h>

#include "dominion.h"

void testPerformAdventureAction(){

  struct gameState state;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
  sea_hag, tribute, smithy};

  initializeGame(2, k, 1, &state);
  
  int currentPlayer = whoseTurn(&state);

  /***************Test 1 ********************/
  // No shuffle needed draws two treasures
  
  state.handCount[currentPlayer] = 1;
  state.hand[currentPlayer][0] = adventurer;

  state.deckCount[currentPlayer] = 5;
  state.deck[currentPlayer][4] = village;
  state.deck[currentPlayer][3] = gold;
  state.deck[currentPlayer][2] = gold;
  state.deck[currentPlayer][1] = copper;
  state.deck[currentPlayer][0] = smithy;

  state.discardCount[currentPlayer] = 5;
  state.discard[currentPlayer][0] = copper;
  state.discard[currentPlayer][1] = copper;
  state.discard[currentPlayer][2] = minion;
  state.discard[currentPlayer][3] = mine;
  state.discard[currentPlayer][4] = tribute;
  printf("Starting testPerformAdventureAction\n");
  performAdventureAction(&state, currentPlayer);

  // we should add two treasure cards to deck so hand count should = 3
  if(state.handCount[currentPlayer]==3){
        printf("Test 1 Function testPerformAdventureAction PASS. Hand count size == 3.\n");
  }
  else{

        printf("Test 1 Function testPerformAdventureAction FAIL. Hand count size != 3.\n");
  }

  // assert two of the cards in hand are treasure
  int numTreasure = 0;
  for (int i = 0; i < state.handCount[currentPlayer]; i++) {
    int currentCard = state.hand[currentPlayer][i];
    if (currentCard == copper || currentCard == silver || currentCard == gold) {
      numTreasure++;
    }
  }

  if (numTreasure == 2) {
    printf("Test 1 Function testPerformAdventureAction PASS. Hand had 2 treature cards.\n");
  } else {

    printf("Test 1 Function testPerformAdventureAction FAIL. Hand did not have 2 treature cards. %i\n", numTreasure);
  }

  // Three cards drawn from deck, two treasure and one non treasure
  if(state.deckCount[currentPlayer]==2){
        printf("Test 1 Function testPerformAdventureAction PASS. Deck count size == 2.\n");
  }
  else{

        printf("Test 1 Function testPerformAdventureAction FAIL. Deck count size != 2.\n");
  }

  // One extra card added to discard
  if(state.discardCount[currentPlayer]==6){
        printf("Test 1 Function testPerformAdventureAction PASS. Discard count size == 6.\n");
  }
  else{

        printf("Test 1 Function testPerformAdventureAction FAIL. Discard count size != 6.\n");
  }


  /***************Test 2 ********************/
  // Shuffle needed draws two treasures discard is full of treasure
  
  state.handCount[currentPlayer] = 1;
  state.hand[currentPlayer][0] = adventurer;

  state.deckCount[currentPlayer] = 2;
  state.deck[currentPlayer][1] = smithy;
  state.deck[currentPlayer][0] = copper;

  state.discardCount[currentPlayer] = 5;
  state.discard[currentPlayer][0] = copper;
  state.discard[currentPlayer][1] = copper;
  state.discard[currentPlayer][2] = gold;
  state.discard[currentPlayer][3] = gold;
  state.discard[currentPlayer][4] = gold;
  printf("Starting testPerformAdventureAction Test 2\n");
  performAdventureAction(&state, currentPlayer);

  // we should add two treasure cards to deck so hand count should = 3
  if(state.handCount[currentPlayer]==3){
        printf("Test 2 Function testPerformAdventureAction PASS. Hand count size == 3.\n");
  }
  else{
        printf("Test 2 Function testPerformAdventureAction FAIL. Hand count size != 3.\n");
  }

  // assert two of the cards in hand are treasure
  numTreasure = 0;
  for (int i = 0; i < state.handCount[currentPlayer]; i++) {
    int currentCard = state.hand[currentPlayer][i];
    if (currentCard == copper || currentCard == silver || currentCard == gold) {
      numTreasure++;
    }
  }

  if (numTreasure == 2) {
     printf("Test 2 Function testPerformAdventureAction PASS. Hand had 2 treature cards.\n");
  } else {
     printf("Test 2 Function testPerformAdventureAction FAIL. Hand did not have 2 treature cards. %i\n", numTreasure);
  }
  
  // Two cards drawn from deck, one treasure and one non treasure, then shuffle 5 back in and draw one...4 should be left in deck
  int deckCount = state.deckCount[currentPlayer];
  if(deckCount==4){
        printf("Test 2 Function testPerformAdventureAction PASS. Deck count size == 4.\n");
  }
  else{
        printf("Test 2 Function testPerformAdventureAction FAIL. Deck count size != 4. %i \n", deckCount);
  }

  int discardCount = state.discardCount[currentPlayer];
  // 1 discarded from hand then discard shuffled to deck, and 0 discarded afterwards, so size should be 1
  if(state.discardCount[currentPlayer]==1){
        printf("Test 2 Function testPerformAdventureAction PASS. Discard count size == 1.\n");
  }
  else{
        printf("Test 2 Function testPerformAdventureAction FAIL. Discard count size != 1. %i\n", discardCount);
  }

}

int main(int argc, char *argv[])
{
    testPerformAdventureAction();
    return 0;
}