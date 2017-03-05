//Automated Random Test for the Village Card
// Compile --  gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c randomtestcard1.c rngs.c -o randomtestcard1 -lm -g
// find . -name "*.gcda" -print0 | xargs -0 rm
// ./randomtestcard1
// gcov randomtestcard1
#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

///////// Global Variable /////////
int test_passed = 0;
int cards_test_passed = 0;
////////////////////////////////


void check_results(int a)
{
  if(a == 0)
  {
    test_passed++;
  }

}

void cards_check(int c)
{
  if(c == 5) //should have 5 cards in hand
  {
    cards_test_passed++;
  }

}


int main(int argc, char *argv[])
{
  int a, b, c, playersn, randomSeed, userRandomSeed, value, countDeck, countHand;
  int currentplayer = 1;
  struct gameState game;

  int cards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

  userRandomSeed = 0;
  userRandomSeed = atoi(argv[1]);
  printf("User Inputed: %d \n", userRandomSeed);



  printf("\nAutomated Random Test -- Village\n-----------\nThere are 20 rounds of testing...\nEach round has 100 random tests...\n");


  for(int z = 0; z < 20 ; z++)
  {
    printf("Testing Round %d\n", (z+1));
    for(int i = 0; i < 100; i ++)
    {
      playersn = rand() % 4; // Randon Number of players

      if (userRandomSeed == 0) // Random Seed
      {
          randomSeed = rand() % 110000; // Random Seed
      }
      else
      {
        randomSeed = rand() % userRandomSeed;
      }

      a = initializeGame(playersn,cards, randomSeed, &game); // Initiliaze the game


      value = rand() % 6; // set a value random

      if(value == 1) // if the value is 1 set the deckCount to 0
      {
        game.deckCount[currentplayer] = 0;
        countDeck = 0 ;
      }
      else // otherwise pick a random value
      {
        countDeck = rand() % MAX_DECK;
        game.deckCount[currentplayer] = countDeck;
      }

      countHand = rand() % MAX_HAND;
      game.handCount[currentplayer] = countHand;


      game.discardCount[currentplayer] = rand() % MAX_DECK;

      b = cardEffect(village, 1, 1, 1, &game,0,0);

      check_results(b);

      c = numHandCards(&game);

      cards_check(c);
    }

  }
  printf("\nResults\n----------\n");
  printf("Test's - Card Effect - Passed: %d\n",test_passed );
  printf("Test's - Card Effect - Failed: %d\n",(1000 - test_passed) );
  printf("Total Number of Card Effect Test's: %d\n",1000 );
  printf("----------\n");
  printf("Test's - Number of Cards -  Passed: %d\n",cards_test_passed );
  printf("Test's - Number of Cards -  Failed: %d\n",(1000 - cards_test_passed) );
  printf("Total Number of Number of Cards Test's: %d\n",1000 );



}
