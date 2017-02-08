#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"


// Unit test for villageAction found in dominion.c
// Funciton call: int villageAction(int currentPlayer, int handPos, struct gameState *state)
// Note: villageAction function currently starts line 1323 from dominion.c

void testvillageAction() {
  printf("----TEST villageAction Function-----\n");

  int k[10] = {adventurer, gardens, feast, village, minion, mine, steward,
        sea_hag, tribute, smithy};
  int seed = 44;
  int playerZero = 0;

//---GS1 TEST---- Test that we Draw 1 cards from draw, and discard 1, so hand will have 5 cards.
  struct gameState *GS1 = newGame();
  initializeGame(2,k,seed,GS1);
  GS1->handCount[playerZero] = 5;
  GS1->hand[playerZero][0] = village;  
  GS1->hand[playerZero][1] = adventurer;  
  GS1->hand[playerZero][2] = smithy;  
  GS1->hand[playerZero][3] = tribute;  
  GS1->hand[playerZero][4] = gardens; 
  GS1->deckCount[playerZero] = 5;
  GS1->deck[playerZero][0] = estate;  
  GS1->deck[playerZero][1] = silver;  
  GS1->deck[playerZero][2] = great_hall;  
  GS1->deck[playerZero][3] = copper;  
  GS1->deck[playerZero][4] = duchy;  
  GS1->discardCount[playerZero] = 1;
  GS1->discard[playerZero][0] = feast;

//---GS2 TEST---- Verify the number of actions increases by 2.
  struct gameState *GS2 = newGame();
  initializeGame(2,k,seed,GS2);
  GS2->numActions = 2;   //Number of current actions set to 2
  GS2->handCount[playerZero] = 5;
  GS2->hand[playerZero][0] = village;  
  GS2->hand[playerZero][1] = adventurer;  
  GS2->hand[playerZero][2] = smithy;  
  GS2->hand[playerZero][3] = tribute;  
  GS2->hand[playerZero][4] = gardens; 
  GS2->deckCount[playerZero] = 5;
  GS2->deck[playerZero][0] = estate;  
  GS2->deck[playerZero][1] = silver;  
  GS2->deck[playerZero][2] = great_hall;  
  GS2->deck[playerZero][3] = copper;  
  GS2->deck[playerZero][4] = duchy;  
  GS2->discardCount[playerZero] = 1;
  GS2->discard[playerZero][0] = feast;

//---GS3 TEST---- Verify village card is in the discard pile
  struct gameState *GS3 = newGame();
  initializeGame(2,k,seed,GS3);
  GS3->numActions = 2;   //Number of current actions set to 2
  GS3->handCount[playerZero] = 5;
  GS3->hand[playerZero][0] = village;  
  GS3->hand[playerZero][1] = adventurer;  
  GS3->hand[playerZero][2] = smithy;  
  GS3->hand[playerZero][3] = tribute;  
  GS3->hand[playerZero][4] = gardens; 
  GS3->deckCount[playerZero] = 5;
  GS3->deck[playerZero][0] = estate;  
  GS3->deck[playerZero][1] = silver;  
  GS3->deck[playerZero][2] = great_hall;  
  GS3->deck[playerZero][3] = copper;  
  GS3->deck[playerZero][4] = duchy;  
  GS3->discardCount[playerZero] = 1;
  GS3->discard[playerZero][0] = feast;

//---GS4 TEST---- Verify village card is in the discard pile
  struct gameState *GS4 = newGame();
  initializeGame(2,k,seed,GS4);
  GS4->handCount[playerZero] = 5;
  GS4->hand[playerZero][0] = village;  
  GS4->hand[playerZero][1] = adventurer;  
  GS4->hand[playerZero][2] = smithy;  
  GS4->hand[playerZero][3] = tribute;  
  GS4->hand[playerZero][4] = gardens; 
  GS4->deckCount[playerZero] = 5;
  GS4->deck[playerZero][0] = estate;  
  GS4->deck[playerZero][1] = silver;  
  GS4->deck[playerZero][2] = great_hall;  
  GS4->deck[playerZero][3] = copper;  
  GS4->deck[playerZero][4] = duchy;  
  GS4->discardCount[playerZero] = 1;
  GS4->discard[playerZero][0] = feast;

//---GS5 TEST---- Verify playCards increments by one (trash flag not set)
  struct gameState *GS5 = newGame();
  initializeGame(2,k,seed,GS5);
  GS5->playedCardCount = 0;   //Number of played card count set to 0
  GS5->handCount[playerZero] = 5;
  GS5->hand[playerZero][0] = village;  
  GS5->hand[playerZero][1] = adventurer;  
  GS5->hand[playerZero][2] = smithy;  
  GS5->hand[playerZero][3] = tribute;  
  GS5->hand[playerZero][4] = gardens; 
  GS5->deckCount[playerZero] = 5;
  GS5->deck[playerZero][0] = estate;  
  GS5->deck[playerZero][1] = silver;  
  GS5->deck[playerZero][2] = great_hall;  
  GS5->deck[playerZero][3] = copper;  
  GS5->deck[playerZero][4] = duchy;  
  GS5->discardCount[playerZero] = 1;
  GS5->discard[playerZero][0] = feast;


  int j;
  villageAction(playerZero,0,GS1);
  int expectedCardsInHandGS1 = 5;  //Gain 1 and discard 1 (5+1-1=1)
  if(expectedCardsInHandGS1 == GS1->handCount[playerZero]){
        printf("PASS for success on drawing 1 cards.  Cards Expected:%i  Cards Returned:%i \n", expectedCardsInHandGS1, GS1->handCount[playerZero]);
    }
  else
    {
        printf("FAIL for success on drawing 1 cards.  Cards Expected:%i  Cards Returned:%i \n", expectedCardsInHandGS1, GS1->handCount[playerZero]);
    }

  villageAction(playerZero,0,GS2);
  int expectedNumOfActionsGS2 = 4;  //Start with 2 and add 2 (2+2=4)
  if(expectedNumOfActionsGS2 == GS2->numActions){
        printf("PASS for success on incrementing number of actions by 2.  Actions Expected:%i  Actions Returned:%i \n", expectedNumOfActionsGS2, GS2->numActions);
    }
  else
    {
        printf("FAIL for success on incrementing number of actions by 2.  Actions Expected:%i  Actions Returned:%i \n", expectedNumOfActionsGS2, GS2->numActions);
    }

  villageAction(playerZero,0,GS3);
  int isVillageInDiscard = 0;
  for(j=0; j < GS3->discardCount[playerZero]; j++)
  {
    if(GS3->discard[playerZero][j] == village)
    {
      isVillageInDiscard =1;
    }
  }

  if(isVillageInDiscard == 1){
        printf("PASS for success on discarding Village Card.  Success Flag:%i  isVillageInDiscard:%i \n", 1, isVillageInDiscard);
    }
    else
    {
        printf("FAIL for success on discarding Village Card.  Success Flag:%i  isVillageInDiscard:%i \n", 1, isVillageInDiscard);
    }



/*      //Used to show cards in hand/deck/discard b4 and after adventure action call
  int i;
   
 for(i=0; i < GS4->handCount[playerZero]; i++)
  {
    printf("B4 Card %i in hand is: %i: \n", i, GS4->hand[playerZero][i]);
  }
  for(i=0; i < GS4->deckCount[playerZero]; i++)
  {
    printf("B4 Card %i in deck is: %i: \n", i, GS4->deck[playerZero][i]);
  }
  for(i=0; i < GS4->discardCount[playerZero]; i++)
  {
    printf("B4 Card %i in discard is: %i: \n", i, GS4->discard[playerZero][i]);
  }

  adventurerAction(playerZero,GS4,temphand);

  for(i=0; i < GS4->handCount[playerZero]; i++)
  {
    printf("Card %i in hand is: %i: \n", i, GS4->hand[playerZero][i]);
  }
  for(i=0; i < GS4->deckCount[playerZero]; i++)
  {
    printf("Card %i in deck is: %i: \n", i, GS4->deck[playerZero][i]);
  }
  for(i=0; i < GS4->discardCount[playerZero]; i++)
  {
    printf("Card %i in discard is: %i: \n", i, GS4->discard[playerZero][i]);
  }
 */


  villageAction(playerZero,0,GS4);
  int isVillageInHand = 1;
  for(j=0; j < GS4->handCount[playerZero]; j++)
  {
    if(GS4->hand[playerZero][j] == village)
    {
      isVillageInHand =0;
    }
  }

  if(isVillageInHand == 1){
        printf("PASS for success on removing Village from Hand.  Success Flag:%i  isVillageInHand:%i \n", 1, isVillageInHand);
    }
    else
    {
        printf("FAIL for success on removing Village from Hand.  Success Flag:%i  isVillageInHand:%i \n", 1, isVillageInHand);
    }


  villageAction(playerZero,0,GS5);
  int expectedPlayedCardCountGS5 = 1;  //Gain 1 and discard 1 (5+1-1=1)
  if(expectedPlayedCardCountGS5 == GS5->playedCardCount){
        printf("PASS for incrementing played cards (trash flag not set).  PlayedCards Expected:%i  PlayedCards Returned:%i \n", expectedPlayedCardCountGS5, GS5->playedCardCount);
    }
  else
    {
        printf("FAIL for incrementing played cards (trash flag not set).  PlayedCards Expected:%i  PlayedCards Returned:%i \n", expectedPlayedCardCountGS5, GS5->playedCardCount);
    }



    return;
}

  



int main(int argc, char *argv[])
{
    testvillageAction();
    return 0;
}
