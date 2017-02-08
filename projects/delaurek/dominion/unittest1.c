/*********************************************************************
 * unittest1.c
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
  int expectedCoins = 0;
  int bonusCoins = 0;
  int seed = 100;
  int numPlayers = 4;
  int thisPlayer = 0;
struct gameState gameControlledG, testerControlledG;
int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
    sea_hag, tribute, smithy, council_room};

// initialize a game state and player cards
initializeGame(numPlayers, k, seed, &gameControlledG);


printf("\n\n----------------------------------------------------\n");
printf("----------------UPDATECOINS() TEST----------------\n");
printf("----------------------------------------------------\n\n");



// ----------- TEST 1: Update Coins when hand filled with only copper with no bonus coins --------------
printf("----------------------------------------------------------------------------\n");
printf("TEST 1: Update Coins when hand filled with only copper with no bonus coins\n\n");

gameControlledG.hand[thisPlayer][0] = 4;
gameControlledG.hand[thisPlayer][1] = 4;
gameControlledG.hand[thisPlayer][2] = 4;
gameControlledG.hand[thisPlayer][3] = 4;
gameControlledG.hand[thisPlayer][4] = 4;
gameControlledG.hand[thisPlayer][5] = 4;
gameControlledG.handCount[thisPlayer] = 6;


expectedCoins = 6;
bonusCoins = 0;

// copy the game state to a test case
memcpy(&testerControlledG, &gameControlledG, sizeof(struct gameState));
updateCoins(thisPlayer, &gameControlledG, bonusCoins);


printf("\tCheck Coins:\n");
printf("\t\tCoins = %d, expected = %d -- ", gameControlledG.coins, expectedCoins + bonusCoins);
assertTrue(gameControlledG.coins, "==", expectedCoins + bonusCoins);

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

// ----------- TEST 2: Update Coins when hand filled with only copper with bonus coins --------------
printf("----------------------------------------------------------------------------\n");
printf("TEST 2: Update Coins when hand filled with only copper with bonus coins\n\n");

gameControlledG.hand[thisPlayer][0] = 4;
gameControlledG.hand[thisPlayer][1] = 4;
gameControlledG.hand[thisPlayer][2] = 4;
gameControlledG.hand[thisPlayer][3] = 4;
gameControlledG.hand[thisPlayer][4] = 4;
gameControlledG.hand[thisPlayer][5] = 4;
gameControlledG.handCount[thisPlayer] = 4;


expectedCoins = 4;
bonusCoins = 3;

// copy the game state to a test case
memcpy(&testerControlledG, &gameControlledG, sizeof(struct gameState));
updateCoins(thisPlayer, &gameControlledG, bonusCoins);


printf("\tCheck Coins:\n");
printf("\t\tCoins = %d, expected = %d -- ", gameControlledG.coins, expectedCoins + bonusCoins);
assertTrue(gameControlledG.coins, "==", expectedCoins + bonusCoins);

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

// ----------- TEST 3: Update Coins when hand filled with only silver with no bonus coins --------------
printf("----------------------------------------------------------------------------\n");
printf("TEST 3: Update Coins when hand filled with only silver with no bonus coins\n\n");

gameControlledG.hand[thisPlayer][0] = 5;
gameControlledG.hand[thisPlayer][1] = 5;
gameControlledG.hand[thisPlayer][2] = 5;
gameControlledG.hand[thisPlayer][3] = 5;
gameControlledG.hand[thisPlayer][4] = 5;
gameControlledG.hand[thisPlayer][5] = 5;
gameControlledG.handCount[thisPlayer] = 5;


expectedCoins = 10;
bonusCoins = 0;

// copy the game state to a test case
memcpy(&testerControlledG, &gameControlledG, sizeof(struct gameState));
updateCoins(thisPlayer, &gameControlledG, bonusCoins);


printf("\tCheck Coins:\n");
printf("\t\tCoins = %d, expected = %d -- ", gameControlledG.coins, expectedCoins + bonusCoins);
assertTrue(gameControlledG.coins, "==", expectedCoins + bonusCoins);

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

// ----------- TEST 4: Update Coins when hand filled with only silver with bonus coins --------------
printf("----------------------------------------------------------------------------\n");
printf("TEST 4: Update Coins when hand filled with only silver with bonus coins\n\n");

gameControlledG.hand[thisPlayer][0] = 5;
gameControlledG.hand[thisPlayer][1] = 5;
gameControlledG.hand[thisPlayer][2] = 5;
gameControlledG.hand[thisPlayer][3] = 5;
gameControlledG.hand[thisPlayer][4] = 5;
gameControlledG.hand[thisPlayer][5] = 5;
gameControlledG.handCount[thisPlayer] = 2;


expectedCoins = 4;
bonusCoins = 1;

// copy the game state to a test case
memcpy(&testerControlledG, &gameControlledG, sizeof(struct gameState));
updateCoins(thisPlayer, &gameControlledG, bonusCoins);


printf("\tCheck Coins:\n");
printf("\t\tCoins = %d, expected = %d -- ", gameControlledG.coins, expectedCoins + bonusCoins);
assertTrue(gameControlledG.coins, "==", expectedCoins + bonusCoins);

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

// ----------- TEST 5: Update Coins when hand filled with only gold with no bonus coins --------------
printf("----------------------------------------------------------------------------\n");
printf("TEST 5: Update Coins when hand filled with only gold with no bonus coins\n\n");

gameControlledG.hand[thisPlayer][0] = 6;
gameControlledG.hand[thisPlayer][1] = 6;
gameControlledG.hand[thisPlayer][2] = 6;
gameControlledG.hand[thisPlayer][3] = 6;
gameControlledG.hand[thisPlayer][4] = 6;
gameControlledG.hand[thisPlayer][5] = 6;
gameControlledG.handCount[thisPlayer] = 6;


expectedCoins = 18;
bonusCoins = 0;

// copy the game state to a test case
memcpy(&testerControlledG, &gameControlledG, sizeof(struct gameState));
updateCoins(thisPlayer, &gameControlledG, bonusCoins);


printf("\tCheck Coins:\n");
printf("\t\tCoins = %d, expected = %d -- ", gameControlledG.coins, expectedCoins + bonusCoins);
assertTrue(gameControlledG.coins, "==", expectedCoins + bonusCoins);

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

// ----------- TEST 6: Update Coins when hand filled with only gold with bonus coins --------------
printf("----------------------------------------------------------------------------\n");
printf("TEST 6: Update Coins when hand filled with only gold with bonus coins\n\n");

gameControlledG.hand[thisPlayer][0] = 6;
gameControlledG.hand[thisPlayer][1] = 6;
gameControlledG.hand[thisPlayer][2] = 6;
gameControlledG.hand[thisPlayer][3] = 6;
gameControlledG.hand[thisPlayer][4] = 6;
gameControlledG.hand[thisPlayer][5] = 6;
gameControlledG.handCount[thisPlayer] = 4;


expectedCoins = 12;
bonusCoins = 2;

// copy the game state to a test case
memcpy(&testerControlledG, &gameControlledG, sizeof(struct gameState));
updateCoins(thisPlayer, &gameControlledG, bonusCoins);


printf("\tCheck Coins:\n");
printf("\t\tCoins = %d, expected = %d -- ", gameControlledG.coins, expectedCoins + bonusCoins);
assertTrue(gameControlledG.coins, "==", expectedCoins + bonusCoins);

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

// ----------- TEST 7: Update Coins when hand filled with gold, silver, and copper with no bonus coins --------------
printf("----------------------------------------------------------------------------\n");
printf("TEST 7: Update Coins when hand filled with gold, silver, and copper with no bonus coins\n\n");

gameControlledG.hand[thisPlayer][0] = 6;
gameControlledG.hand[thisPlayer][1] = 6;
gameControlledG.hand[thisPlayer][2] = 5;
gameControlledG.hand[thisPlayer][3] = 5;
gameControlledG.hand[thisPlayer][4] = 5;
gameControlledG.hand[thisPlayer][5] = 4;
gameControlledG.handCount[thisPlayer] = 6;


expectedCoins = 13;
bonusCoins = 0;

// copy the game state to a test case
memcpy(&testerControlledG, &gameControlledG, sizeof(struct gameState));
updateCoins(thisPlayer, &gameControlledG, bonusCoins);


printf("\tCheck Coins:\n");
printf("\t\tCoins = %d, expected = %d -- ", gameControlledG.coins, expectedCoins + bonusCoins);
assertTrue(gameControlledG.coins, "==", expectedCoins + bonusCoins);

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

// ----------- TEST 8: Update Coins when hand filled with gold, silver, and copper with bonus coins --------------
printf("----------------------------------------------------------------------------\n");
printf("TEST 8: Update Coins when hand filled with gold, silver, and copper with bonus coins\n\n");

gameControlledG.hand[thisPlayer][0] = 6;
gameControlledG.hand[thisPlayer][1] = 5;
gameControlledG.hand[thisPlayer][2] = 4;
gameControlledG.hand[thisPlayer][3] = 4;
gameControlledG.hand[thisPlayer][4] = 4;
gameControlledG.hand[thisPlayer][5] = 4;
gameControlledG.handCount[thisPlayer] = 6;


expectedCoins = 9;
bonusCoins = 3;

// copy the game state to a test case
memcpy(&testerControlledG, &gameControlledG, sizeof(struct gameState));
updateCoins(thisPlayer, &gameControlledG, bonusCoins);


printf("\tCheck Coins:\n");
printf("\t\tCoins = %d, expected = %d -- ", gameControlledG.coins, expectedCoins + bonusCoins);
assertTrue(gameControlledG.coins, "==", expectedCoins + bonusCoins);

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

// ----------- TEST 9: Update Coins when hand filled with no treasure cards and with no bonus coins --------------
printf("----------------------------------------------------------------------------\n");
printf("TEST 9: Update Coins when hand filled with no treasure cards and with no bonus coins\n\n");

gameControlledG.hand[thisPlayer][0] = 1;
gameControlledG.hand[thisPlayer][1] = 2;
gameControlledG.hand[thisPlayer][2] = 3;
gameControlledG.hand[thisPlayer][3] = 7;
gameControlledG.hand[thisPlayer][4] = 8;
gameControlledG.hand[thisPlayer][5] = 9;
gameControlledG.handCount[thisPlayer] = 6;


expectedCoins = 0;
bonusCoins = 0;

// copy the game state to a test case
memcpy(&testerControlledG, &gameControlledG, sizeof(struct gameState));
updateCoins(thisPlayer, &gameControlledG, bonusCoins);


printf("\tCheck Coins:\n");
printf("\t\tCoins = %d, expected = %d -- ", gameControlledG.coins, expectedCoins + bonusCoins);
assertTrue(gameControlledG.coins, "==", expectedCoins + bonusCoins);

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

// ----------- TEST 10: Update Coins when hand filled with no treasure cards and with bonus coins --------------
printf("----------------------------------------------------------------------------\n");
printf("TEST 10: Update Coins when hand filled with no treasure cards and with bonus coins\n\n");

gameControlledG.hand[thisPlayer][0] = 10;
gameControlledG.hand[thisPlayer][1] = 12;
gameControlledG.hand[thisPlayer][2] = 13;
gameControlledG.hand[thisPlayer][3] = 1;
gameControlledG.hand[thisPlayer][4] = 0;
gameControlledG.hand[thisPlayer][5] = 2;
gameControlledG.handCount[thisPlayer] = 6;


expectedCoins = 0;
bonusCoins = 3;

// copy the game state to a test case
memcpy(&testerControlledG, &gameControlledG, sizeof(struct gameState));
updateCoins(thisPlayer, &gameControlledG, bonusCoins);


printf("\tCheck Coins:\n");
printf("\t\tCoins = %d, expected = %d -- ", gameControlledG.coins, expectedCoins + bonusCoins);
assertTrue(gameControlledG.coins, "==", expectedCoins + bonusCoins);

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
