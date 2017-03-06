/*********************************************************************
 * cardtest1.c
 *********************************************************************/


#include "dominion.h"
#include "dominion_helpers.h"
#include "newAssert.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>



int main(){
  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  int newCards = 0;
  int playedCards = 0;
  int newNumBuys = 0;
  int newNumActions = 0;
  int seed = 100;
  int numPlayers = 0;
  int numTreasure = 0;
  int thisPlayer = 0;
  int index, index2, index3, makeChoice;
struct gameState testG, staticG;
int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
    sea_hag, tribute, smithy, council_room};

printf("\n\n----------------------------------------------------\n");
printf("----------------RANDOM ADVENTURER TEST CARD----------------\n");
printf("----------------------------------------------------\n\n");

srand(time(NULL));

for(index = 0; index < 2000; index++){
  numTreasure = 0;
  choice1 = 0;
  choice2 = 0;
  choice3 = 0;
  newCards = 0;
  numPlayers = rand() % 3 + 2;
  initializeGame(numPlayers, k, seed, &testG);

  for(index2 = 0; index2 < numPlayers; index2++){
    testG.deckCount[index2] =  rand() % MAX_DECK;
    testG.handCount[index2] = rand() % MAX_DECK;
    testG.discardCount[index2] = rand () % MAX_DECK;

    for(index3 = 0; index3 < testG.deckCount[index2]; index3++){
      testG.deck[index2][index3] = rand() % 27;
      if(testG.deck[index2][index3] == 4 || testG.deck[index2][index3] == 5 || testG.deck[index2][index3] == 6){
        numTreasure++;
      }
    }
    for(index3 = 0; index3 < testG.handCount[index2]; index3++){
      testG.hand[index2][index3] = rand() % 27;
      if(testG.hand[index2][index3] == 4 || testG.hand[index2][index3] == 5 || testG.hand[index2][index3] == 6){
        numTreasure++;
      }
    }
    for(index3 = 0; index3 < testG.discardCount[index2]; index3++){
      testG.discard[index2][index3] = rand() % 27;
      if(testG.discard[index2][index3] == 4 || testG.discard[index2][index3] == 5 || testG.discard[index2][index3] == 6){
        numTreasure++;
      }
    }
  }

  if(numTreasure > 2){
    newCards = 2;
    playedCards = 1;
  }
  else if(numTreasure == 1){
    newCards = 1;
    playedCards = 1;
  }
  else{
    newCards = 0;
    playedCards = 1;
  }


  makeChoice = rand() % 4;
  switch (makeChoice) {
    case 0:
      choice1 = 1;
    case 1:
      choice2 = 1;
    case 2:
      choice3 = 1;
  }
  memcpy(&staticG, &testG, sizeof(struct gameState));
  cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

  //Test Cases

  if(testG.handCount[thisPlayer] != staticG.handCount[thisPlayer] + newCards - playedCards){
    printf("\t\tHand Count = %d, expected = %d -- ", testG.handCount[thisPlayer], staticG.handCount[thisPlayer] + newCards - playedCards);
    printf("\t\tD&D: %d, E D&D: %d", testG.deckCount[thisPlayer] + testG.discardCount[thisPlayer], staticG.deckCount[thisPlayer] + staticG.discardCount[thisPlayer]- newCards);

    printf("\n-------------------------------------------------------\n");
    for(index2 = 0; index2 < 1; index2++){
      printf("Deck Count: %d -- EXPECTED ", testG.deckCount[index2]);
      printf("Deck Count: %d\n", staticG.deckCount[index2]);

      printf("Hand Count: %d -- EXPECTED ", testG.handCount[index2]);
      printf("Deck Count: %d\n", staticG.handCount[index2]);

      printf("Discard Count: %d -- EXPECTED ", testG.discardCount[index2]);
      printf("Discard Count: %d\n", staticG.discardCount[index2]);

      /*
      for(index3 = 0; index3 < testG.deckCount[index2]; index3++){
        printf("Deck %d: %d\n", index3, testG.deck[index2][index3]);
      }
      for(index3 = 0; index3 < testG.handCount[index2]; index3++){
        printf("Hand %d: %d\n", index3, testG.hand[index2][index3]);
      }
      for(index3 = 0; index3 < testG.discardCount[index2]; index3++){
        printf("Discard %d: %d\n", index3, testG.discard[index2][index3]);
      }*/
    }
    }
  /*else{
    if((rand() % 100) == 0){
      printf("\t\tHand Count = %d, expected = %d -- ", testG.handCount[thisPlayer], staticG.handCount[thisPlayer] + newCards - playedCards);
      printf("\t\tD&D: %d, E D&D: %d", testG.deckCount[thisPlayer] + testG.discardCount[thisPlayer], staticG.deckCount[thisPlayer] + staticG.discardCount[thisPlayer]- newCards);

      printf("\n*************************************\n");
      for(index2 = 0; index2 < 1; index2++){
        printf("Deck Count: %d -- EXPECTED ", testG.deckCount[index2]);
        printf("Deck Count: %d\n", staticG.deckCount[index2]);

        printf("Hand Count: %d -- EXPECTED ", testG.handCount[index2]);
        printf("Deck Count: %d\n", staticG.handCount[index2]);

        printf("Discard Count: %d -- EXPECTED ", testG.discardCount[index2]);
        printf("Discard Count: %d\n", staticG.discardCount[index2]);

        
        for(index3 = 0; index3 < testG.deckCount[index2]; index3++){
          printf("Deck %d: %d\n", index3, testG.deck[index2][index3]);
        }
        for(index3 = 0; index3 < testG.handCount[index2]; index3++){
          printf("Hand %d: %d\n", index3, testG.hand[index2][index3]);
        }
        for(index3 = 0; index3 < testG.discardCount[index2]; index3++){
          printf("Discard %d: %d\n", index3, testG.discard[index2][index3]);
        }
      }
    }
  }*/
  assertTrue(testG.handCount[thisPlayer], "==",staticG.handCount[thisPlayer] + newCards - playedCards);
  assertTrue(testG.deckCount[thisPlayer] + testG.discardCount[thisPlayer], "==",staticG.deckCount[thisPlayer] + staticG.discardCount[thisPlayer]- newCards);
  assertTrue(testG.playedCardCount, "==", staticG.playedCardCount + playedCards);
  assertTrue(testG.numBuys, "==", staticG.numBuys + newNumBuys);
  assertTrue(testG.numActions, "==", staticG.numActions + newNumActions);
  assertTrue(testG.phase, "==", staticG.phase);
  assertTrue(testG.coins, "==", staticG.coins);

  assertTrue(testG.deckCount[thisPlayer+1], "==", staticG.deckCount[thisPlayer+1]);
  if(numPlayers == 3){
    assertTrue(testG.deckCount[thisPlayer+2], "==", staticG.deckCount[thisPlayer+2]);
  }
  if(numPlayers == 4){
    assertTrue(testG.deckCount[thisPlayer+3], "==", staticG.deckCount[thisPlayer+3]);
  }

  assertTrue(testG.handCount[thisPlayer+1], "==", staticG.handCount[thisPlayer+1]);
  if(numPlayers == 3){
    assertTrue(testG.handCount[thisPlayer+2], "==", staticG.handCount[thisPlayer+2]);
  }
  if(numPlayers == 4){
    assertTrue(testG.handCount[thisPlayer+3], "==", staticG.handCount[thisPlayer+3]);
  }
}
printf("TEST COMPLETE\n");
return 0;

}
