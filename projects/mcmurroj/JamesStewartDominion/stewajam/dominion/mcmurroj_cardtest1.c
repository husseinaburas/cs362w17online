#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"


// Unit test for adventurerAction found in dominion.c
// Funciton call: int adventurerAction(int currentPlayer, struct gameState *state, int *temphand)
// Note: adventurerAction function currently starts line 1282 from dominion.c

void testadventurerAction() {
  printf("----TEST adventurerAction Function-----\n");

  int k[10] = {adventurer, gardens, feast, village, minion, mine, steward,
        sea_hag, tribute, smithy};
  int seed = 44;
  int playerZero = 0;
  int temphand[MAX_HAND];



//---GS1 TEST---- Check to verify that the two tresure cards in the deck (copper/silver)
  //are drawn
  struct gameState *GS1 = newGame();
  initializeGame(2,k,seed,GS1);
  GS1->handCount[playerZero] = 5;
  GS1->hand[playerZero][0] = feast;  
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
  GS1->discardCount[playerZero] = 0;

//---GS2 TEST---- verify no cards added to hand when no treasure cards exist in deck.
  struct gameState *GS2 = newGame();
  initializeGame(2,k,seed,GS2);
  GS2->handCount[playerZero] = 5;
  GS2->hand[playerZero][0] = feast;  
  GS2->hand[playerZero][1] = adventurer;  
  GS2->hand[playerZero][2] = smithy;  
  GS2->hand[playerZero][3] = tribute;  
  GS2->hand[playerZero][4] = gardens; 
  GS2->deckCount[playerZero] = 5;
  GS2->deck[playerZero][0] = sea_hag;  
  GS2->deck[playerZero][1] = sea_hag;  
  GS2->deck[playerZero][2] = sea_hag;  
  GS2->deck[playerZero][3] = sea_hag;  
  GS2->deck[playerZero][4] = sea_hag;  
  GS2->discardCount[playerZero] = 0;

//---GS3 TEST---- Tests for functionality when treasure cards are in discard pile (should shuffle into deck and find)
  struct gameState *GS3 = newGame();
  initializeGame(2,k,seed,GS3);
  GS3->handCount[playerZero] = 5;
  GS3->hand[playerZero][0] = feast;  
  GS3->hand[playerZero][1] = adventurer;  
  GS3->hand[playerZero][2] = smithy;  
  GS3->hand[playerZero][3] = tribute;  
  GS3->hand[playerZero][4] = gardens; 
  GS3->deckCount[playerZero] = 0;
  GS3->discardCount[playerZero] = 5;
  GS3->discard[playerZero][0] = copper;  
  GS3->discard[playerZero][1] = silver;  
  GS3->discard[playerZero][2] = great_hall;  
  GS3->discard[playerZero][3] = duchy;  
  GS3->discard[playerZero][4] = copper;  

//---GS4 TEST---- Tests for functionality when deck/discard are 0
  struct gameState *GS4 = newGame();
  initializeGame(2,k,seed,GS4);
  GS4->handCount[playerZero] = 5;
  GS4->hand[playerZero][0] = feast;  
  GS4->hand[playerZero][1] = adventurer;  
  GS4->hand[playerZero][2] = smithy;  
  GS4->hand[playerZero][3] = tribute;  
  GS4->hand[playerZero][4] = gardens; 
  GS4->deckCount[playerZero] = 0;
  GS4->discardCount[playerZero] = 0;



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

  adventurerAction(playerZero,GS1,temphand);
  int expectedCardsInHandGS1 = 7;
  if(expectedCardsInHandGS1 == GS1->handCount[playerZero]){
        printf("PASS for success on drawing 2 cards.  Cards Expected:%i  Cards Returned:%i \n", expectedCardsInHandGS1, GS1->handCount[playerZero]);
    }
    else
    {
        printf("FAIL for success on drawing 2 cards.  Cards Expected:%i  Cards Returned:%i \n", expectedCardsInHandGS1, GS1->handCount[playerZero]);
    }

  adventurerAction(playerZero,GS2,temphand);  //Note: Passes but could pass even with treasure cards present due to bug
  int expectedCardsInHandGS2 = 5;
  if(expectedCardsInHandGS2 == GS2->handCount[playerZero]){
        printf("PASS for success draws no cards when no treasure cards in deck.  Cards Expected:%i  Cards Returned:%i \n", expectedCardsInHandGS2, GS2->handCount[playerZero]);
    }
    else
    {
        printf("FAIL for success draws no cards when no treasure cards in deck.  Cards Expected:%i  Cards Returned:%i \n", expectedCardsInHandGS2, GS2->handCount[playerZero]);
    }

  adventurerAction(playerZero,GS3,temphand);  
  int expectedCardsInHandGS3 = 7;
  if(expectedCardsInHandGS3 == GS3->handCount[playerZero]){
        printf("PASS for success draws 2 cards from discard.  Cards Expected:%i  Cards Returned:%i \n", expectedCardsInHandGS3, GS3->handCount[playerZero]);
    }
    else
    {
        printf("FAIL for success draws 2 cards from discard.  Cards Expected:%i  Cards Returned:%i \n", expectedCardsInHandGS3, GS3->handCount[playerZero]);
    }

  adventurerAction(playerZero,GS4,temphand);  //Note: Passes but could pass even with treasure cards present due to bug
  int expectedCardsInHandGS4 = 5;
  if(expectedCardsInHandGS4 == GS4->handCount[playerZero]){
        printf("PASS for success draws no cards as there is no deck or discard cards.  Cards Expected:%i  Cards Returned:%i \n", expectedCardsInHandGS4, GS4->handCount[playerZero]);
    }
    else
    {
        printf("FAIL for success draws no cards as there is no deck or discard cards.  Cards Expected:%i  Cards Returned:%i \n", expectedCardsInHandGS4, GS4->handCount[playerZero]);
    }


    return;
}



int main(int argc, char *argv[])
{
    testadventurerAction();
    return 0;
}
