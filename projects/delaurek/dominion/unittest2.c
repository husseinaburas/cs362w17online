/*********************************************************************
 * unittest2.c
 *********************************************************************/


#include "dominion.h"
#include "dominion_helpers.h"
#include "newAssert.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main(){
  int seed = 100;
  int numPlayers = 4;
  int thisPlayer = 0;
  int returnVal = 0;
  int cardNum = 0;
struct gameState gameControlledG, testerControlledG;
int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
    sea_hag, tribute, smithy, council_room};

// initialize a game state and player cards
initializeGame(numPlayers, k, seed, &gameControlledG);


printf("\n\n----------------------------------------------------\n");
printf("----------------GETCOST() TEST----------------\n");
printf("----------------------------------------------------\n\n");



// ----------- TEST 1: Random Card Generation to get cost --------------
printf("----------------------------------------------------------------------------\n");
printf("TEST 1: Random Card Generation to get cost\n\n");
for(int i = 0; i < 40; i++){
  printf("\nITERATION %d:\n\n", i + 1);

  cardNum = rand() % 29;
  // copy the game state to a test case
  returnVal = getCost(cardNum);

  printf("\tCheck return status: ");
  printf("Card Number: %d, Return Value: %d -- ", cardNum, returnVal);
  if(cardNum <= 26){
    assertTrue(returnVal, ">=", 0);
  }
  else{
    assertTrue(returnVal, "<<", 0);
  }
}

printf("----------------------------------------------------------------------------\n");
printf("TEST 2: Status check when return valid input\n\n");

cardNum = 1;
returnVal = getCost(cardNum);

printf("\tCheck return status:\n");
printf("Return Value: %d -- ", returnVal);
assertTrue(returnVal, ">=", 0);
memcpy(&testerControlledG, &gameControlledG, sizeof(struct gameState));
printf("\n\n\tCheck players game status:\n");
printf("\t\tHand Count = %d, expected = %d -- ", gameControlledG.handCount[thisPlayer], testerControlledG.handCount[thisPlayer]);
assertTrue(gameControlledG.handCount[thisPlayer], "==",testerControlledG.handCount[thisPlayer]);
printf("\t\tDeck & Discard Count = %d, expected = %d -- ", (gameControlledG.deckCount[thisPlayer] + gameControlledG.discardCount[thisPlayer]), (testerControlledG.deckCount[thisPlayer] + testerControlledG.discardCount[thisPlayer]));
assertTrue(gameControlledG.deckCount[thisPlayer] + gameControlledG.discardCount[thisPlayer], "==",testerControlledG.deckCount[thisPlayer] + testerControlledG.discardCount[thisPlayer]);
printf("\t\tPlayed Cards Count = %d, expected = %d -- ", gameControlledG.playedCardCount, testerControlledG.playedCardCount);
assertTrue(gameControlledG.playedCardCount, "==", testerControlledG.playedCardCount);
printf("\t\tNumber of Buys = %d, expected = %d -- ", gameControlledG.numBuys, testerControlledG.numBuys);
assertTrue(gameControlledG.numBuys, "==", testerControlledG.numBuys);
printf("\t\tNumber of Actions = %d, expected = %d -- ", gameControlledG.numActions, testerControlledG.numActions);
assertTrue(gameControlledG.numActions, "==", testerControlledG.numActions);
printf("\t\tPhase = %d, expected = %d -- ", gameControlledG.phase, testerControlledG.phase);
assertTrue(gameControlledG.phase, "==", testerControlledG.phase);
printf("\t\tCoins = %d, expected = %d -- ", gameControlledG.coins, testerControlledG.coins);
assertTrue(gameControlledG.coins, "==", testerControlledG.coins);


printf("\n\t3 other players deck counts unchanged:\n");
printf("\t\tPlayer 2 actual: %d, expected: %d -- ", gameControlledG.deckCount[thisPlayer+1], testerControlledG.deckCount[thisPlayer+1]);
assertTrue(gameControlledG.deckCount[thisPlayer+1], "==", testerControlledG.deckCount[thisPlayer+1]);
printf("\t\tPlayer 3 actual: %d, expected: %d -- ", gameControlledG.deckCount[thisPlayer+2], testerControlledG.deckCount[thisPlayer+2]);
assertTrue(gameControlledG.deckCount[thisPlayer+2], "==", testerControlledG.deckCount[thisPlayer+2]);
printf("\t\tPlayer 4 actual: %d, expected: %d -- ", gameControlledG.deckCount[thisPlayer+3], testerControlledG.deckCount[thisPlayer+3]);
assertTrue(gameControlledG.deckCount[thisPlayer+3], "==", testerControlledG.deckCount[thisPlayer+3]);

printf("\n\t3 other players hand counts unchanged:\n");
printf("\t\tPlayer 2 actual: %d, expected: %d -- ", gameControlledG.handCount[thisPlayer+1], testerControlledG.handCount[thisPlayer+1]);
assertTrue(gameControlledG.handCount[thisPlayer+1], "==", testerControlledG.handCount[thisPlayer+1]);
printf("\t\tPlayer 3 actual: %d, expected: %d -- ", gameControlledG.handCount[thisPlayer+2], testerControlledG.handCount[thisPlayer+2]);
assertTrue(gameControlledG.handCount[thisPlayer+2], "==", testerControlledG.handCount[thisPlayer+2]);
printf("\t\tPlayer 4 actual: %d, expected: %d -- ", gameControlledG.handCount[thisPlayer+3], testerControlledG.handCount[thisPlayer+3]);
assertTrue(gameControlledG.handCount[thisPlayer+3], "==", testerControlledG.handCount[thisPlayer+3]);

printf("----------------------------------------------------------------------------\n");
printf("TEST 3: Status check when return invalid input\n\n");

cardNum = 40;
returnVal = getCost(cardNum);

printf("\tCheck return status:\n");
printf("Return Value: %d -- ", returnVal);
assertTrue(returnVal, "<<", 0);
memcpy(&testerControlledG, &gameControlledG, sizeof(struct gameState));
printf("\n\n\tCheck players game status:\n");
printf("\t\tHand Count = %d, expected = %d -- ", gameControlledG.handCount[thisPlayer], testerControlledG.handCount[thisPlayer]);
assertTrue(gameControlledG.handCount[thisPlayer], "==",testerControlledG.handCount[thisPlayer]);
printf("\t\tDeck & Discard Count = %d, expected = %d -- ", (gameControlledG.deckCount[thisPlayer] + gameControlledG.discardCount[thisPlayer]), (testerControlledG.deckCount[thisPlayer] + testerControlledG.discardCount[thisPlayer]));
assertTrue(gameControlledG.deckCount[thisPlayer] + gameControlledG.discardCount[thisPlayer], "==",testerControlledG.deckCount[thisPlayer] + testerControlledG.discardCount[thisPlayer]);
printf("\t\tPlayed Cards Count = %d, expected = %d -- ", gameControlledG.playedCardCount, testerControlledG.playedCardCount);
assertTrue(gameControlledG.playedCardCount, "==", testerControlledG.playedCardCount);
printf("\t\tNumber of Buys = %d, expected = %d -- ", gameControlledG.numBuys, testerControlledG.numBuys);
assertTrue(gameControlledG.numBuys, "==", testerControlledG.numBuys);
printf("\t\tNumber of Actions = %d, expected = %d -- ", gameControlledG.numActions, testerControlledG.numActions);
assertTrue(gameControlledG.numActions, "==", testerControlledG.numActions);
printf("\t\tPhase = %d, expected = %d -- ", gameControlledG.phase, testerControlledG.phase);
assertTrue(gameControlledG.phase, "==", testerControlledG.phase);
printf("\t\tCoins = %d, expected = %d -- ", gameControlledG.coins, testerControlledG.coins);
assertTrue(gameControlledG.coins, "==", testerControlledG.coins);


printf("\n\t3 other players deck counts unchanged:\n");
printf("\t\tPlayer 2 actual: %d, expected: %d -- ", gameControlledG.deckCount[thisPlayer+1], testerControlledG.deckCount[thisPlayer+1]);
assertTrue(gameControlledG.deckCount[thisPlayer+1], "==", testerControlledG.deckCount[thisPlayer+1]);
printf("\t\tPlayer 3 actual: %d, expected: %d -- ", gameControlledG.deckCount[thisPlayer+2], testerControlledG.deckCount[thisPlayer+2]);
assertTrue(gameControlledG.deckCount[thisPlayer+2], "==", testerControlledG.deckCount[thisPlayer+2]);
printf("\t\tPlayer 4 actual: %d, expected: %d -- ", gameControlledG.deckCount[thisPlayer+3], testerControlledG.deckCount[thisPlayer+3]);
assertTrue(gameControlledG.deckCount[thisPlayer+3], "==", testerControlledG.deckCount[thisPlayer+3]);

printf("\n\t3 other players hand counts unchanged:\n");
printf("\t\tPlayer 2 actual: %d, expected: %d -- ", gameControlledG.handCount[thisPlayer+1], testerControlledG.handCount[thisPlayer+1]);
assertTrue(gameControlledG.handCount[thisPlayer+1], "==", testerControlledG.handCount[thisPlayer+1]);
printf("\t\tPlayer 3 actual: %d, expected: %d -- ", gameControlledG.handCount[thisPlayer+2], testerControlledG.handCount[thisPlayer+2]);
assertTrue(gameControlledG.handCount[thisPlayer+2], "==", testerControlledG.handCount[thisPlayer+2]);
printf("\t\tPlayer 4 actual: %d, expected: %d -- ", gameControlledG.handCount[thisPlayer+3], testerControlledG.handCount[thisPlayer+3]);
assertTrue(gameControlledG.handCount[thisPlayer+3], "==", testerControlledG.handCount[thisPlayer+3]);

return 0;

}
