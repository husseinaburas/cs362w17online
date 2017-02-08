/*********************************************************************
 * cardtest1.c
 * Include the following lines in your makefile:
 *
 * cardtest1: cardtest1.c dominion.o rngs.o newAssert.0
 *      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o newAssert.o $(CFLAGS)
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
  int players[MAX_PLAYERS];
struct gameState gameControlledG, testerControlledG;
int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
    sea_hag, tribute, smithy, council_room};




printf("\n\n----------------------------------------------------\n");
printf("----------------GETWINNERS() TEST----------------\n");
printf("----------------------------------------------------\n\n");



// ----------- TEST 1: 2 players with same decks --------------
printf("----------------------------------------------------------------------------\n");
printf("TEST 1: 2 players with same decks\n\n");
// initialize a game state and player cards
numPlayers = 2;
players[0] = 0;
players[1] = 0;
players[2] = 0;
players[3] = 0;

initializeGame(numPlayers, k, seed, &gameControlledG);

// copy the game state to a test case
memcpy(&testerControlledG, &gameControlledG, sizeof(struct gameState));
for(thisPlayer = 0; thisPlayer < 2; thisPlayer++){
  gameControlledG.hand[thisPlayer][0] = 0;
  gameControlledG.hand[thisPlayer][1] = 1;
  gameControlledG.hand[thisPlayer][2] = 2;
  gameControlledG.hand[thisPlayer][3] = 3;
  gameControlledG.hand[thisPlayer][4] = 4;
  gameControlledG.hand[thisPlayer][5] = 5;
  gameControlledG.handCount[thisPlayer] = 6;

  gameControlledG.deck[thisPlayer][0] = 0;
  gameControlledG.deck[thisPlayer][1] = 1;
  gameControlledG.deck[thisPlayer][2] = 2;
  gameControlledG.deck[thisPlayer][3] = 3;
  gameControlledG.deck[thisPlayer][4] = 4;
  gameControlledG.deck[thisPlayer][5] = 5;
  gameControlledG.deckCount[thisPlayer] = 6;


  gameControlledG.discard[thisPlayer][0] = 0;
  gameControlledG.discard[thisPlayer][1] = 1;
  gameControlledG.discard[thisPlayer][2] = 2;
  gameControlledG.discard[thisPlayer][3] = 3;
  gameControlledG.discard[thisPlayer][4] = 4;
  gameControlledG.discard[thisPlayer][5] = 5;
  gameControlledG.discardCount[thisPlayer] = 6;
}


getWinners(players, &gameControlledG);

printf("\n\tCheck players status:\n");
printf("\t\tPlayer 1: %d Expected: %d -- ", players[0], 0);
assertTrue(players[0],"==", 0);
printf("\t\tPlayer 2: %d Expected: %d -- ", players[1], 1);
assertTrue(players[1],"==", 1);
printf("\t\tPlayer 3: %d Expected: %d -- ", players[2], 0);
assertTrue(players[2], "==", 0);
printf("\t\tPlayer 4: %d Expected: %d -- ", players[3], 0);
assertTrue(players[3], "==", 0);

// ----------- TEST 2: 4 players with same decks --------------
printf("----------------------------------------------------------------------------\n");
printf("TEST 2: 4 players with same decks\n\n");
// initialize a game state and player cards
numPlayers = 4;
players[0] = 0;
players[1] = 0;
players[2] = 0;
players[3] = 0;

initializeGame(numPlayers, k, seed, &gameControlledG);

// copy the game state to a test case
memcpy(&testerControlledG, &gameControlledG, sizeof(struct gameState));
for(thisPlayer = 0; thisPlayer < 4; thisPlayer++){
  gameControlledG.hand[thisPlayer][0] = 1;
  gameControlledG.hand[thisPlayer][1] = 1;
  gameControlledG.hand[thisPlayer][2] = 1;
  gameControlledG.hand[thisPlayer][3] = 1;
  gameControlledG.hand[thisPlayer][4] = 1;
  gameControlledG.hand[thisPlayer][5] = 1;
  gameControlledG.handCount[thisPlayer] = 3;

  gameControlledG.deck[thisPlayer][0] = 1;
  gameControlledG.deck[thisPlayer][1] = 1;
  gameControlledG.deck[thisPlayer][2] = 1;
  gameControlledG.deck[thisPlayer][3] = 1;
  gameControlledG.deck[thisPlayer][4] = 1;
  gameControlledG.deck[thisPlayer][5] = 1;
  gameControlledG.deckCount[thisPlayer] = 3;


  gameControlledG.discard[thisPlayer][0] = 1;
  gameControlledG.discard[thisPlayer][1] = 1;
  gameControlledG.discard[thisPlayer][2] = 1;
  gameControlledG.discard[thisPlayer][3] = 1;
  gameControlledG.discard[thisPlayer][4] = 1;
  gameControlledG.discard[thisPlayer][5] = 1;
  gameControlledG.discardCount[thisPlayer] = 3;
}


getWinners(players, &gameControlledG);

printf("\n\tCheck players status:\n");
printf("\t\tPlayer 1: %d Expected: %d -- ", players[0], 0);
assertTrue(players[0],"==", 0);
printf("\t\tPlayer 2: %d Expected: %d -- ", players[1], 1);
assertTrue(players[1],"==", 1);
printf("\t\tPlayer 3: %d Expected: %d -- ", players[2], 1);
assertTrue(players[2], "==", 1);
printf("\t\tPlayer 4: %d Expected: %d -- ", players[3], 1);
assertTrue(players[3], "==", 1);


// ----------- TEST 1: 2 players with different decks --------------
printf("----------------------------------------------------------------------------\n");
printf("TEST 1: 2 players with different decks\n\n");
// initialize a game state and player cards
numPlayers = 2;
players[0] = 0;
players[1] = 0;
players[2] = 0;
players[3] = 0;

initializeGame(numPlayers, k, seed, &gameControlledG);

// copy the game state to a test case
memcpy(&testerControlledG, &gameControlledG, sizeof(struct gameState));
  gameControlledG.hand[0][0] = 0;
  gameControlledG.hand[0][1] = 0;
  gameControlledG.hand[0][2] = 2;
  gameControlledG.hand[0][3] = 3;
  gameControlledG.hand[0][4] = 4;
  gameControlledG.hand[0][5] = 2;
  gameControlledG.handCount[0] = 6;

  gameControlledG.deck[0][0] = 0;
  gameControlledG.deck[0][1] = 2;
  gameControlledG.deck[0][2] = 12;
  gameControlledG.deck[0][3] = 13;
  gameControlledG.deck[0][4] = 4;
  gameControlledG.deck[0][5] = 8;
  gameControlledG.deckCount[0] = 6;


  gameControlledG.discard[0][0] = 9;
  gameControlledG.discard[0][1] = 10;
  gameControlledG.discardCount[0] = 2;


  gameControlledG.hand[1][0] = 1;
  gameControlledG.hand[1][1] = 1;
  gameControlledG.hand[1][2] = 1;
  gameControlledG.hand[1][3] = 1;
  gameControlledG.hand[1][4] = 1;
  gameControlledG.hand[1][5] = 1;
  gameControlledG.handCount[1] = 3;

  gameControlledG.deck[1][0] = 1;
  gameControlledG.deck[1][1] = 1;
  gameControlledG.deck[1][2] = 1;
  gameControlledG.deck[1][3] = 1;
  gameControlledG.deck[1][4] = 1;
  gameControlledG.deck[1][5] = 1;
  gameControlledG.deckCount[1] = 3;


  gameControlledG.discard[1][0] = 1;
  gameControlledG.discard[1][1] = 1;
  gameControlledG.discard[1][2] = 1;
  gameControlledG.discard[1][3] = 1;
  gameControlledG.discard[1][4] = 1;
  gameControlledG.discard[1][5] = 1;
  gameControlledG.discardCount[1] = 3;

getWinners(players, &gameControlledG);

printf("\n\tCheck players status:\n");
printf("\t\tPlayer 1: %d Expected: %d -- ", players[0], 1);
assertTrue(players[0],"==", 1);
printf("\t\tPlayer 2: %d Expected: %d -- ", players[1], 0);
assertTrue(players[1],"==", 0);
printf("\t\tPlayer 3: %d Expected: %d -- ", players[2], 0);
assertTrue(players[2], "==", 0);
printf("\t\tPlayer 4: %d Expected: %d -- ", players[3], 0);
assertTrue(players[3], "==", 0);

// ----------- TEST 2: 4 players with different decks --------------
printf("----------------------------------------------------------------------------\n");
printf("TEST 2: 4 players with different decks\n\n");
// initialize a game state and player cards
numPlayers = 4;
players[0] = 0;
players[1] = 0;
players[2] = 0;
players[3] = 0;

initializeGame(numPlayers, k, seed, &gameControlledG);

// copy the game state to a test case
memcpy(&testerControlledG, &gameControlledG, sizeof(struct gameState));
gameControlledG.hand[0][0] = 0;
gameControlledG.hand[0][1] = 0;
gameControlledG.hand[0][2] = 2;
gameControlledG.hand[0][3] = 3;
gameControlledG.hand[0][4] = 4;
gameControlledG.hand[0][5] = 2;
gameControlledG.handCount[0] = 6;

gameControlledG.deck[0][0] = 0;
gameControlledG.deck[0][1] = 2;
gameControlledG.deck[0][2] = 12;
gameControlledG.deck[0][3] = 13;
gameControlledG.deck[0][4] = 4;
gameControlledG.deck[0][5] = 8;
gameControlledG.deckCount[0] = 6;


gameControlledG.discard[0][0] = 9;
gameControlledG.discard[0][1] = 10;
gameControlledG.discardCount[0] = 2;


gameControlledG.hand[1][0] = 1;
gameControlledG.hand[1][1] = 1;
gameControlledG.hand[1][2] = 1;
gameControlledG.hand[1][3] = 1;
gameControlledG.hand[1][4] = 1;
gameControlledG.hand[1][5] = 1;
gameControlledG.handCount[1] = 3;

gameControlledG.deck[1][0] = 1;
gameControlledG.deck[1][1] = 1;
gameControlledG.deck[1][2] = 1;
gameControlledG.deck[1][3] = 1;
gameControlledG.deck[1][4] = 1;
gameControlledG.deck[1][5] = 1;
gameControlledG.deckCount[1] = 3;


gameControlledG.discard[1][0] = 1;
gameControlledG.discard[1][1] = 1;
gameControlledG.discard[1][2] = 1;
gameControlledG.discard[1][3] = 1;
gameControlledG.discard[1][4] = 1;
gameControlledG.discard[1][5] = 1;
gameControlledG.discardCount[1] = 3;

gameControlledG.hand[3][0] = 1;
gameControlledG.hand[3][1] = 2;
gameControlledG.hand[3][2] = 3;
gameControlledG.hand[3][3] = 3;
gameControlledG.hand[3][4] = 4;
gameControlledG.hand[3][5] = 2;
gameControlledG.handCount[3] = 6;

gameControlledG.deck[3][0] = 0;
gameControlledG.deck[3][1] = 2;
gameControlledG.deck[3][2] = 12;
gameControlledG.deck[3][3] = 13;
gameControlledG.deck[3][4] = 4;
gameControlledG.deck[3][5] = 8;
gameControlledG.deckCount[3] = 6;


gameControlledG.discard[3][0] = 9;
gameControlledG.discard[3][1] = 13;
gameControlledG.discardCount[3] = 2;


gameControlledG.hand[2][0] = 3;
gameControlledG.hand[2][1] = 3;
gameControlledG.hand[2][2] = 3;
gameControlledG.hand[2][3] = 3;
gameControlledG.hand[2][4] = 3;
gameControlledG.hand[2][5] = 3;
gameControlledG.handCount[2] = 6;

gameControlledG.deck[2][0] = 3;
gameControlledG.deck[2][1] = 3;
gameControlledG.deck[2][2] = 3;
gameControlledG.deck[2][3] = 3;
gameControlledG.deck[2][4] = 3;
gameControlledG.deck[2][5] = 3;
gameControlledG.deckCount[2] = 6;


gameControlledG.discard[2][0] = 3;
gameControlledG.discard[2][1] = 3;
gameControlledG.discard[2][2] = 3;
gameControlledG.discard[2][3] = 3;
gameControlledG.discard[2][4] = 3;
gameControlledG.discard[2][5] = 3;
gameControlledG.discardCount[2] = 6;


getWinners(players, &gameControlledG);

printf("\n\tCheck players status:\n");
printf("\t\tPlayer 1: %d Expected: %d -- ", players[0], 0);
assertTrue(players[0],"==", 0);
printf("\t\tPlayer 2: %d Expected: %d -- ", players[1], 0);
assertTrue(players[1],"==", 0);
printf("\t\tPlayer 3: %d Expected: %d -- ", players[2], 1);
assertTrue(players[2], "==", 1);
printf("\t\tPlayer 4: %d Expected: %d -- ", players[3], 0);
assertTrue(players[3], "==", 0);

return 0;

}
