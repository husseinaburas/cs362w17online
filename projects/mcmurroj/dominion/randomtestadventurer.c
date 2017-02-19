#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"


// Random testing for adventurerAction function from dominion.c
// Funciton call: int adventurerAction(int currentPlayer, struct gameState *state, int *temphand)
// Note: adventurerAction function currently starts line 1282 from dominion.c

void testRandAdventurerAction() {
  
  //--Change Number of Cycles
  int numberOfCycles = 100000;

  //Static Game Variables
  int k[10] = {adventurer, gardens, feast, village, minion, mine, steward,
        sea_hag, tribute, smithy};
  int temphand[MAX_HAND];
  struct gameState *randGameState = newGame();
  
  //Tally of Tests Passed/Failed
  int testsRun = 0;
  int test1Passed =0;
  int test1Failed =0;
  int test2Passed =0;
  int test2Failed =0;
  int test3Passed =0;
  int test3Failed =0;
  int test4Passed =0;
  int test4Failed =0;
  
  int currentRandomSeed;
  int randPlayer,numPlayers;
  int preDeckSize, preHandSize, preDiscardSize;
  int tempCard;
  int actualTreasureInHandPost, treasureInDeckAndDiscard, treasureInHandPre, expectedTreasure;
  int postDeckSize, postHandSize, postDiscardSize;
  int i, j;

  for(i=0; i < numberOfCycles; i++)
  {
    //Setup Initial Conditions.
    // Random Variables: numPlayers, randPlayer, currentRandomSeed, deckSize, handSize
    //                   discardSize, deck[MAXDECK]

    //----Reset Variables----
    memset(randGameState,0, sizeof(struct gameState));  //Clear bits in randGameState
    memset(temphand,0, MAX_HAND);
    treasureInHandPre = 0;
    actualTreasureInHandPost=0;
    treasureInDeckAndDiscard=0;
    expectedTreasure=0;
    postDeckSize= 0;
    postHandSize=0;
    postDiscardSize=0;

    //----Assign to Random Variables----
    numPlayers = (rand() % MAX_PLAYERS) +1;
    currentRandomSeed = rand();
    randPlayer = rand() % numPlayers;
    
    //----Initialize and Assign Cards----
    initializeGame(numPlayers, k, currentRandomSeed, randGameState);
    preDeckSize = (rand() % (MAX_DECK+1));  //Deck size set 0-MAX_HAND
    preHandSize = ((rand() % MAX_HAND)+1);  //Hand size set 1-MAX_HAND
    preDiscardSize = (rand() % 10);  //Discard size 0-9
    randGameState->whoseTurn = randPlayer;
    randGameState->deckCount[randPlayer] = preDeckSize;
    randGameState->handCount[randPlayer] = preHandSize;
    randGameState->discardCount[randPlayer] = preDiscardSize;

    //----Randomly Assign Deck----
    for(j=0; j < preDeckSize; j++)
    {
      tempCard = rand() % 27;  //Rand card index 0-26
      if(tempCard > 3 && tempCard < 7)
      {
        treasureInDeckAndDiscard++;  //Count discard and Hand Treasure Cards
      } 
      randGameState->deck[randPlayer][j] = tempCard;
    }
    //----Randomly Assign Discard----
    for(j=0; j < preDiscardSize; j++)
    {
      tempCard = rand() % 27;  //Rand card index 0-26
      if(tempCard > 3 && tempCard < 7)
      {
        treasureInDeckAndDiscard++;  //Adding treasure card
      } 
      randGameState->discard[randPlayer][j] = tempCard;
    }
    //----Randomly Assign Hand----
    for(j=0; j < preHandSize; j++)
    {
      tempCard = rand() % 27;  //Rand card index 0-26
      if(tempCard > 3 && tempCard < 7)
      {
        treasureInHandPre++;  //Adding treasure card
      } 
      randGameState->hand[randPlayer][j] = tempCard;
    }

    //--Normalize treasure cards in deck and discard
    if(treasureInDeckAndDiscard > 2){treasureInDeckAndDiscard=2;}  //Max extract 2 treasure cards

    //--Calucate expected based on how many treasure in deck/discard with control for more than 2
    // (i.e if there are no treasure cards in deck/discard, no extra expected)
    // (i.e if there are 100 treasure cards in deck/discard, 2+ extra expected)
    expectedTreasure = treasureInHandPre + treasureInDeckAndDiscard;  
    //----Call Tested Function----
    adventurerAction(randPlayer, randGameState, temphand);

    //----Gather Post Execution Data----
    postDeckSize= randGameState->deckCount[randPlayer];
    postHandSize= randGameState->handCount[randPlayer];
    postDiscardSize= randGameState->discardCount[randPlayer];

    for(j=0; j < postHandSize; j++)
    {
      tempCard = randGameState->hand[randPlayer][j];
      if(tempCard > 3 && tempCard < 7)
      {
        actualTreasureInHandPost++;  //Count treasure after
      } 
    }


  //-----RUN TESTS------

  //----TEST1---- Verify Correct Number Of Cards In Hand
  if(treasureInDeckAndDiscard == postHandSize - preHandSize)
    {
        test1Passed++;
        testsRun++;
    }
    else
    {
        test1Failed++;
        testsRun++;
    }

  //----TEST2---- Verify Correct Number Of Treasure Cards In Hand
  if(expectedTreasure == actualTreasureInHandPost)
    {
        test2Passed++;
        testsRun++;
    }
    else
    {
        test2Failed++;
        testsRun++;
    }

    //----TEST3---- Verify Correct Number Of Treasure Cards In Deck and Discard
  if((postDeckSize + postDiscardSize) == (preDeckSize + preDiscardSize)-treasureInDeckAndDiscard)
    {
        test3Passed++;
        testsRun++;
    }
    else
    {
        test3Failed++;
        testsRun++;
    }

  //----TEST4---- Verify No Cards Unaccounted for
  if((postDeckSize + postDiscardSize + postHandSize) == (preDeckSize + preDiscardSize + preHandSize))
    {
        test4Passed++;
        testsRun++;
    }
    else
    {
        test4Failed++;
        testsRun++;
    }




  }

  printf("Number of Tests Run: %i \n", testsRun);
  printf("Number of Tests Passed: %i \n",test1Passed+test2Passed+test3Passed+test4Passed);
  printf("Number of Tests Failed: %i \n",test1Failed+test2Failed+test3Failed+test4Failed);
  printf("Test 1- Verify # of Cards in Hand Passed:%i -- Failed:%i \n",test1Passed,test1Failed);
  printf("Test 2- Verify # of Treasure Cards in Hand Passed:%i -- Failed:%i \n",test2Passed,test2Failed);
  printf("Test 3- Verify # of Cards in Discard+Deck Passed:%i -- Failed:%i \n",test3Passed,test3Failed);
  printf("Test 4- Verify No Missing Cards Deck/Hand/Discard Passed:%i -- Failed:%i \n",test4Passed,test4Failed);



    return;
}



int main(int argc, char *argv[])
{
    printf("----Random Test adventurerAction Function-----\n");

    int randSeed;
    if(argc == 2)  //Will either assign rng seed from command line (if given), or produce random seed locally
    {
      randSeed = atoi(argv[1]);
      printf("Random Seed From Command Line: %i \n", randSeed);
    }
    else{
      srand(time(NULL));
      randSeed = rand();
      printf("Random Seed From Program: %i\t(--see command line options for Makefile)\n", randSeed);
    }

    //SET RANDOM SEED!!!
    srand(randSeed);
    testRandAdventurerAction();
    return 0;
}


