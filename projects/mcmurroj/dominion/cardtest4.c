#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"


// Unit test for sea_hagAction found in dominion.c
// Funciton call: int sea_hagAction(int currentPlayer, struct gameState *state)
// Note: sea_hagAction function currently starts line 1334 from dominion.c

void testsea_hagAction() {
  printf("----TEST sea_hagAction Function-----\n");

  int k[10] = {adventurer, gardens, feast, village, minion, mine, steward,
        sea_hag, tribute, smithy};
  int seed = 44;
  int playerZero = 0;
  int playerOne = 1; 

//---GS1 TEST---- 
  struct gameState *GS1 = newGame();
  initializeGame(2,k,seed,GS1);
  GS1->numPlayers = 2;
  GS1->handCount[playerZero] = 5;
  GS1->hand[playerZero][0] = village;  
  GS1->hand[playerZero][1] = adventurer;  
  GS1->hand[playerZero][2] = smithy;  
  GS1->hand[playerZero][3] = sea_hag;  
  GS1->hand[playerZero][4] = gardens; 
  GS1->deckCount[playerZero] = 5;
  GS1->deck[playerZero][0] = estate;  
  GS1->deck[playerZero][1] = silver;  
  GS1->deck[playerZero][2] = great_hall;  
  GS1->deck[playerZero][3] = copper;  
  GS1->deck[playerZero][4] = duchy;  
  GS1->discardCount[playerZero] = 1;
  GS1->discard[playerZero][0] = minion;

  GS1->deckCount[playerOne] = 10;
  GS1->deck[playerOne][0] = estate;  
  GS1->deck[playerOne][1] = silver;  
  GS1->deck[playerOne][2] = great_hall;  
  GS1->deck[playerOne][3] = copper;  
  GS1->deck[playerOne][4] = duchy;
  GS1->deck[playerOne][0] = estate;  
  GS1->deck[playerOne][1] = silver;  
  GS1->deck[playerOne][2] = great_hall;  
  GS1->deck[playerOne][3] = copper;  
  GS1->deck[playerOne][4] = duchy;  
  GS1->discardCount[playerOne] = 1;
  GS1->discard[playerOne][0] = great_hall;



  int j;

  sea_hagAction(playerZero,GS1);
  int isCurseInOpponentDeck = 0;
  for(j=0; j < GS1->deckCount[playerOne]; j++)
  {
    if(GS1->deck[playerOne][j] == curse)
    {
      isCurseInOpponentDeck =1;
    }
  }

  if(isCurseInOpponentDeck == 1){
        printf("PASS for success on adding Curse to Opponent Deck.  Success Flag:%i  isCurseInOpponentDeck:%i \n", 1, isCurseInOpponentDeck);
    }
  else
    {
        printf("FAIL for success on adding Curse to Opponent Deck.  Success Flag:%i  isCurseInOpponentDeck:%i \n", 1, isCurseInOpponentDeck);
    }

  int isCurseInCurrentPlayerDeck = 1;
  for(j=0; j < GS1->deckCount[playerZero]; j++)
  {
    if(GS1->deck[playerZero][j] == curse)
    {
      isCurseInCurrentPlayerDeck =0;
    }
  }

  if(isCurseInCurrentPlayerDeck == 1){
        printf("PASS for success on no Curse added to current player's deck.  Success Flag:%i  isCurseInCurrentPlayerDeck:%i \n", 1, isCurseInCurrentPlayerDeck);
    }
  else
    {
        printf("FAIL for success on no Curse added to current player's deck.  Success Flag:%i  isCurseInCurrentPlayerDeck:%i \n", 1, isCurseInCurrentPlayerDeck);
    }

  int expecteddeckCountplayerZeroGS1 = 5;  //Expected to replace top card with curse card, deck count remain 5
  if(expecteddeckCountplayerZeroGS1 == GS1->deckCount[playerZero]){
        printf("PASS for success on current players deck count.  Expected Count:%i  Returned Count:%i \n", expecteddeckCountplayerZeroGS1, GS1->deckCount[playerZero]);
    }
  else
    {
        printf("FAIL for success on current players deck count.  Expected Count:%i  Returned Count:%i \n", expecteddeckCountplayerZeroGS1, GS1->deckCount[playerZero]);
    }

  int expecteddeckCountplayerOneGS1 = 10;  //Expected to replace top card with curse card, deck count remain 10
  if(expecteddeckCountplayerOneGS1 == GS1->deckCount[playerOne]){
        printf("PASS for success on opponents deck count.  Expected Count:%i  Returned Count:%i \n", expecteddeckCountplayerOneGS1, GS1->deckCount[playerOne]);
    }
  else
    {
        printf("FAIL for success on opponents deck count.  Expected Count:%i  Returned Count:%i \n", expecteddeckCountplayerOneGS1, GS1->deckCount[playerOne]);
    }

  int expecteddiscardCountplayerZeroGS1 = 2;  //Expected to incrase by one after playing sea_hag (1+1=2)
  if(expecteddiscardCountplayerZeroGS1 == GS1->discardCount[playerZero]){
        printf("PASS for success on current players discard count.  Expected Count:%i  Returned Count:%i \n", expecteddiscardCountplayerZeroGS1, GS1->discardCount[playerZero]);
    }
  else
    {
        printf("FAIL for success on current players discard count.  Expected Count:%i  Returned Count:%i \n", expecteddiscardCountplayerZeroGS1, GS1->discardCount[playerZero]);
    }

  int expecteddiscardCountplayerOneGS1 = 1;  //Expected to incrase by one after playing sea_hag and curse card added (1+1=2)
  if(expecteddiscardCountplayerOneGS1 == GS1->discardCount[playerOne]){
        printf("PASS for success on opponents discard count.  Expected Count:%i  Returned Count:%i \n", expecteddiscardCountplayerOneGS1, GS1->discardCount[playerOne]);
    }
  else
    {
        printf("FAIL for success on opponents discard count.  Expected Count:%i  Returned Count:%i \n", expecteddiscardCountplayerOneGS1, GS1->discardCount[playerOne]);
    }

  int isSea_hagInHand = 1;
  for(j=0; j < GS1->handCount[playerZero]; j++)
  {
    if(GS1->hand[playerZero][j] == sea_hag)
    {
      isSea_hagInHand =0;
    }
  }

  if(isSea_hagInHand == 1){
        printf("PASS for success on removing sea_hag from Hand.  Success Flag:%i  isSea_hagInHand:%i \n", 1, isSea_hagInHand);
    }
    else
    {
        printf("FAIL for success on removing sea_hag from Hand.  Success Flag:%i  isSea_hagInHand:%i \n", 1, isSea_hagInHand);
    }


    return;
}

  



int main(int argc, char *argv[])
{
    testsea_hagAction();
    return 0;
}
