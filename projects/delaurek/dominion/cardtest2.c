/*********************************************************************
 * cardtes2.c
 *********************************************************************/


#include "dominion.h"
#include "dominion_helpers.h"
#include "newAssert.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "Smithy"

int main(){
  int newCards = 0;
  int playedCards = 0;
  int newNumBuys = 0;
  int newNumActions = 0;
  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  int seed = 100;
  int numPlayers = 4;
  int thisPlayer = 0;
struct gameState gameControlledG, testerControlledG;
int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
    sea_hag, tribute, smithy, council_room};

// initialize a game state and player cards
initializeGame(numPlayers, k, seed, &gameControlledG);


printf("\n\n------------------------------------------------\n");
printf("----------------SMITHY CARD TEST----------------\n");
printf("------------------------------------------------\n\n");

// ----------- TEST 1: Testing when 3 cards available to draw --------------
printf("----------------------------------------------------------------------------\n");
printf("-----TEST 1: Testing when 3 cards available to draw-----\n\n");

// copy the game state to a test case
memcpy(&testerControlledG, &gameControlledG, sizeof(struct gameState));
cardEffect(smithy, choice1, choice2, choice3, &gameControlledG, handpos, &bonus);

newCards = 3;
playedCards = 1;

printf("\tCheck current player game status:\n");
printf("\t\tHand Count = %d, expected = %d -- ", gameControlledG.handCount[thisPlayer], testerControlledG.handCount[thisPlayer] + newCards - playedCards);
assertTrue(gameControlledG.handCount[thisPlayer], "==",testerControlledG.handCount[thisPlayer] + newCards - playedCards);
printf("\t\tDeck & Discard Count = %d, expected = %d -- ", (gameControlledG.deckCount[thisPlayer] + gameControlledG.discardCount[thisPlayer]), (testerControlledG.deckCount[thisPlayer] + testerControlledG.discardCount[thisPlayer]- newCards));
assertTrue(gameControlledG.deckCount[thisPlayer] + gameControlledG.discardCount[thisPlayer], "==",testerControlledG.deckCount[thisPlayer] + testerControlledG.discardCount[thisPlayer]- newCards);
printf("\t\tPlayed Cards Count = %d, expected = %d -- ", gameControlledG.playedCardCount, testerControlledG.playedCardCount + playedCards);
assertTrue(gameControlledG.playedCardCount, "==", testerControlledG.playedCardCount + playedCards);
printf("\t\tNumber of Buys = %d, expected = %d -- ", gameControlledG.numBuys, testerControlledG.numBuys + newNumBuys);
assertTrue(gameControlledG.numBuys, "==", testerControlledG.numBuys + newNumBuys);
printf("\t\tNumber of Actions = %d, expected = %d -- ", gameControlledG.numActions, testerControlledG.numActions + newNumActions);
assertTrue(gameControlledG.numActions, "==", testerControlledG.numActions + newNumActions);
printf("\t\tPhase = %d, expected = %d -- ", gameControlledG.phase, testerControlledG.phase);
assertTrue(gameControlledG.phase, "==", testerControlledG.phase);
printf("\t\tCoins = %d, expected = %d -- ", gameControlledG.coins, testerControlledG.coins);
assertTrue(gameControlledG.coins, "==", testerControlledG.coins);

printf("\t3 other players deck counts unchanged:\n");
printf("\t\tPlayer 2 actual: %d, expected: %d -- ", gameControlledG.deckCount[thisPlayer+1], testerControlledG.deckCount[thisPlayer+1]);
assertTrue(gameControlledG.deckCount[thisPlayer+1], "==", testerControlledG.deckCount[thisPlayer+1]);
printf("\t\tPlayer 3 actual: %d, expected: %d -- ", gameControlledG.deckCount[thisPlayer+2], testerControlledG.deckCount[thisPlayer+2]);
assertTrue(gameControlledG.deckCount[thisPlayer+2], "==", testerControlledG.deckCount[thisPlayer+2]);
printf("\t\tPlayer 4 actual: %d, expected: %d -- ", gameControlledG.deckCount[thisPlayer+3], testerControlledG.deckCount[thisPlayer+3]);
assertTrue(gameControlledG.deckCount[thisPlayer+3], "==", testerControlledG.deckCount[thisPlayer+3]);

printf("\t3 other players hand counts unchanged:\n");
printf("\t\tPlayer 2 actual: %d, expected: %d -- ", gameControlledG.handCount[thisPlayer+1], testerControlledG.handCount[thisPlayer+1]);
assertTrue(gameControlledG.handCount[thisPlayer+1], "==", testerControlledG.handCount[thisPlayer+1]);
printf("\t\tPlayer 3 actual: %d, expected: %d -- ", gameControlledG.handCount[thisPlayer+2], testerControlledG.handCount[thisPlayer+2]);
assertTrue(gameControlledG.handCount[thisPlayer+2], "==", testerControlledG.handCount[thisPlayer+2]);
printf("\t\tPlayer 4 actual: %d, expected: %d -- ", gameControlledG.handCount[thisPlayer+3], testerControlledG.handCount[thisPlayer+3]);
assertTrue(gameControlledG.handCount[thisPlayer+3], "==", testerControlledG.handCount[thisPlayer+3]);


// ----------- TEST 2: Testing when 2 cards available to draw --------------
printf("----------------------------------------------------------------------------\n");
printf("\n-----TEST 2: Testing when 2 cards available to draw-----\n\n");

// copy the game state to a test case

newCards = 2;
playedCards = 1;

gameControlledG.deck[thisPlayer][0] = 4;
gameControlledG.deck[thisPlayer][1] = 1;
gameControlledG.deck[thisPlayer][2] = 1;
gameControlledG.deck[thisPlayer][3] = 1;
gameControlledG.deck[thisPlayer][4] = 1;
gameControlledG.deck[thisPlayer][5] = 1;

gameControlledG.discard[thisPlayer][0] = 1;
gameControlledG.discard[thisPlayer][1] = 1;
gameControlledG.discard[thisPlayer][2] = 1;
gameControlledG.discard[thisPlayer][3] = 1;
gameControlledG.discard[thisPlayer][4] = 1;
gameControlledG.discard[thisPlayer][5] = 1;

gameControlledG.deckCount[thisPlayer] = 1;
gameControlledG.discardCount[thisPlayer] = 1;

memcpy(&testerControlledG, &gameControlledG, sizeof(struct gameState));
cardEffect(smithy, choice1, choice2, choice3, &gameControlledG, handpos, &bonus);

printf("\tCheck current player game status:\n");
printf("\t\tHand Count = %d, expected = %d -- ", gameControlledG.handCount[thisPlayer], testerControlledG.handCount[thisPlayer] + newCards - playedCards);
assertTrue(gameControlledG.handCount[thisPlayer], "==",testerControlledG.handCount[thisPlayer] + newCards - playedCards);
printf("\t\tDeck & Discard Count = %d, expected = %d -- ", (gameControlledG.deckCount[thisPlayer] + gameControlledG.discardCount[thisPlayer]), (testerControlledG.deckCount[thisPlayer] + testerControlledG.discardCount[thisPlayer]- newCards));
assertTrue(gameControlledG.deckCount[thisPlayer] + gameControlledG.discardCount[thisPlayer], "==",testerControlledG.deckCount[thisPlayer] + testerControlledG.discardCount[thisPlayer]- newCards);
printf("\t\tPlayed Cards Count = %d, expected = %d -- ", gameControlledG.playedCardCount, testerControlledG.playedCardCount + playedCards);
assertTrue(gameControlledG.playedCardCount, "==", testerControlledG.playedCardCount + playedCards);
printf("\t\tNumber of Buys = %d, expected = %d -- ", gameControlledG.numBuys, testerControlledG.numBuys + newNumBuys);
assertTrue(gameControlledG.numBuys, "==", testerControlledG.numBuys + newNumBuys);
printf("\t\tNumber of Actions = %d, expected = %d -- ", gameControlledG.numActions, testerControlledG.numActions + newNumActions);
assertTrue(gameControlledG.numActions, "==", testerControlledG.numActions + newNumActions);
printf("\t\tPhase = %d, expected = %d -- ", gameControlledG.phase, testerControlledG.phase);
assertTrue(gameControlledG.phase, "==", testerControlledG.phase);
printf("\t\tCoins = %d, expected = %d -- ", gameControlledG.coins, testerControlledG.coins);
assertTrue(gameControlledG.coins, "==", testerControlledG.coins);

printf("\t3 other players deck counts unchanged:\n");
printf("\t\tPlayer 2 actual: %d, expected: %d -- ", gameControlledG.deckCount[thisPlayer+1], testerControlledG.deckCount[thisPlayer+1]);
assertTrue(gameControlledG.deckCount[thisPlayer+1], "==", testerControlledG.deckCount[thisPlayer+1]);
printf("\t\tPlayer 3 actual: %d, expected: %d -- ", gameControlledG.deckCount[thisPlayer+2], testerControlledG.deckCount[thisPlayer+2]);
assertTrue(gameControlledG.deckCount[thisPlayer+2], "==", testerControlledG.deckCount[thisPlayer+2]);
printf("\t\tPlayer 4 actual: %d, expected: %d -- ", gameControlledG.deckCount[thisPlayer+3], testerControlledG.deckCount[thisPlayer+3]);
assertTrue(gameControlledG.deckCount[thisPlayer+3], "==", testerControlledG.deckCount[thisPlayer+3]);

printf("\t3 other players hand counts unchanged:\n");
printf("\t\tPlayer 2 actual: %d, expected: %d -- ", gameControlledG.handCount[thisPlayer+1], testerControlledG.handCount[thisPlayer+1]);
assertTrue(gameControlledG.handCount[thisPlayer+1], "==", testerControlledG.handCount[thisPlayer+1]);
printf("\t\tPlayer 3 actual: %d, expected: %d -- ", gameControlledG.handCount[thisPlayer+2], testerControlledG.handCount[thisPlayer+2]);
assertTrue(gameControlledG.handCount[thisPlayer+2], "==", testerControlledG.handCount[thisPlayer+2]);
printf("\t\tPlayer 4 actual: %d, expected: %d -- ", gameControlledG.handCount[thisPlayer+3], testerControlledG.handCount[thisPlayer+3]);
assertTrue(gameControlledG.handCount[thisPlayer+3], "==", testerControlledG.handCount[thisPlayer+3]);

// ----------- Testing when 0 cards are available to draw --------------
printf("----------------------------------------------------------------------------\n");
printf("\n-----TEST 3: Testing when 0 cards are available to draw-----\n\n");

// copy the game state to a test case

newCards = 0;
playedCards = 1;

gameControlledG.deck[thisPlayer][0] = 1;
gameControlledG.deck[thisPlayer][1] = 1;
gameControlledG.deck[thisPlayer][2] = 1;
gameControlledG.deck[thisPlayer][3] = 1;
gameControlledG.deck[thisPlayer][4] = 1;
gameControlledG.deck[thisPlayer][5] = 1;

gameControlledG.discard[thisPlayer][0] = 1;
gameControlledG.discard[thisPlayer][1] = 1;
gameControlledG.discard[thisPlayer][2] = 1;
gameControlledG.discard[thisPlayer][3] = 1;
gameControlledG.discard[thisPlayer][4] = 1;
gameControlledG.discard[thisPlayer][5] = 1;

gameControlledG.deckCount[thisPlayer] = 0;
gameControlledG.discardCount[thisPlayer] = 0;

memcpy(&testerControlledG, &gameControlledG, sizeof(struct gameState));
cardEffect(smithy, choice1, choice2, choice3, &gameControlledG, handpos, &bonus);

printf("\tCheck current player game status:\n");
printf("\t\tHand Count = %d, expected = %d -- ", gameControlledG.handCount[thisPlayer], testerControlledG.handCount[thisPlayer] + newCards - playedCards);
assertTrue(gameControlledG.handCount[thisPlayer], "==",testerControlledG.handCount[thisPlayer] + newCards - playedCards);
printf("\t\tDeck & Discard Count = %d, expected = %d -- ", (gameControlledG.deckCount[thisPlayer] + gameControlledG.discardCount[thisPlayer]), (testerControlledG.deckCount[thisPlayer] + testerControlledG.discardCount[thisPlayer]- newCards));
assertTrue(gameControlledG.deckCount[thisPlayer] + gameControlledG.discardCount[thisPlayer], "==",testerControlledG.deckCount[thisPlayer] + testerControlledG.discardCount[thisPlayer]- newCards);
printf("\t\tPlayed Cards Count = %d, expected = %d -- ", gameControlledG.playedCardCount, testerControlledG.playedCardCount + playedCards);
assertTrue(gameControlledG.playedCardCount, "==", testerControlledG.playedCardCount + playedCards);
printf("\t\tNumber of Buys = %d, expected = %d -- ", gameControlledG.numBuys, testerControlledG.numBuys + newNumBuys);
assertTrue(gameControlledG.numBuys, "==", testerControlledG.numBuys + newNumBuys);
printf("\t\tNumber of Actions = %d, expected = %d -- ", gameControlledG.numActions, testerControlledG.numActions + newNumActions);
assertTrue(gameControlledG.numActions, "==", testerControlledG.numActions + newNumActions);
printf("\t\tPhase = %d, expected = %d -- ", gameControlledG.phase, testerControlledG.phase);
assertTrue(gameControlledG.phase, "==", testerControlledG.phase);
printf("\t\tCoins = %d, expected = %d -- ", gameControlledG.coins, testerControlledG.coins);
assertTrue(gameControlledG.coins, "==", testerControlledG.coins);

printf("\t3 other players deck counts Check:\n");
printf("\t\tPlayer 2 actual: %d, expected: %d -- ", gameControlledG.deckCount[thisPlayer+1], testerControlledG.deckCount[thisPlayer+1]);
assertTrue(gameControlledG.deckCount[thisPlayer+1], "==", testerControlledG.deckCount[thisPlayer+1]);
printf("\t\tPlayer 3 actual: %d, expected: %d -- ", gameControlledG.deckCount[thisPlayer+2], testerControlledG.deckCount[thisPlayer+2]);
assertTrue(gameControlledG.deckCount[thisPlayer+2], "==", testerControlledG.deckCount[thisPlayer+2]);
printf("\t\tPlayer 4 actual: %d, expected: %d -- ", gameControlledG.deckCount[thisPlayer+3], testerControlledG.deckCount[thisPlayer+3]);
assertTrue(gameControlledG.deckCount[thisPlayer+3], "==", testerControlledG.deckCount[thisPlayer+3]);

printf("\t3 other players hand counts unchanged:\n");
printf("\t\tPlayer 2 actual: %d, expected: %d -- ", gameControlledG.handCount[thisPlayer+1], testerControlledG.handCount[thisPlayer+1]);
assertTrue(gameControlledG.handCount[thisPlayer+1], "==", testerControlledG.handCount[thisPlayer+1]);
printf("\t\tPlayer 3 actual: %d, expected: %d -- ", gameControlledG.handCount[thisPlayer+2], testerControlledG.handCount[thisPlayer+2]);
assertTrue(gameControlledG.handCount[thisPlayer+2], "==", testerControlledG.handCount[thisPlayer+2]);
printf("\t\tPlayer 4 actual: %d, expected: %d -- ", gameControlledG.handCount[thisPlayer+3], testerControlledG.handCount[thisPlayer+3]);
assertTrue(gameControlledG.handCount[thisPlayer+3], "==", testerControlledG.handCount[thisPlayer+3]);

return 0;

}
