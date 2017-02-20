#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1
#define TEST_NUM_CARDS 27

int _getCost(int cardNumber)
{
  switch( cardNumber ) 
  {
    case curse:
      return 0;
    case estate:
      return 2;
    case duchy:
      return 5;
    case province:
      return 8;
    case copper:
      return 0;
    case silver:
      return 3;
    case gold:
      return 6;
    case adventurer:
      return 6;
    case council_room:
      return 5;
    case feast:
      return 4;
    case gardens:
      return 4;
    case mine:
      return 5;
    case remodel:
      return 4;
    case smithy:
      return 4;
    case village:
      return 3;
    case baron:
      return 4;
    case great_hall:
      return 3;
    case minion:
      return 5;
    case steward:
      return 3;
    case tribute:
      return 5;
    case ambassador:
      return 3;
    case cutpurse:
      return 4;
    case embargo: 
      return 2;
    case outpost:
      return 5;
    case salvager:
      return 4;
    case sea_hag:
      return 4;
    case treasure_map:
      return 4;
  }

  return -1;
}

int main()
{
  int i;

  int k[TEST_NUM_CARDS] = {
                             curse,
                             estate,
                             duchy,
                             province,
                             copper,
                             silver,
                             gold,
                             adventurer,
                             council_room,
                             feast,
                             gardens,
                             mine,
                             remodel,
                             smithy,
                             village,
                             baron,
                             great_hall,
                             minion,
                             steward,
                             tribute,
                             ambassador,
                             cutpurse,
                             embargo, 
                             outpost,
                             salvager,
                             sea_hag,
                             treasure_map
                          };

  printf ("Testing getCost.\n");

  for (i = 0; i < TEST_NUM_CARDS; i++)
    assert(getCost(k[i]) == _getCost(k[i]));

  printf ("Finished.\n");

  return 0;
}
