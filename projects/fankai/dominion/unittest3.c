/*test functionint getCost(int cardNumber)
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

*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main() {
    //struct gameState G;
    int i,cost;
    //int seed = 1000;
    int k[] = {curse, estate, duchy, province, copper, silver, gold, adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall, minion, steward, tribute, ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map};
    int costs[] = {0, 2, 5, 8, 0, 3, 6, 6, 5, 4, 4, 5, 4, 4, 3, 4, 3, 5, 3, 5, 3, 4, 2, 5, 4, 4, 4};
    //initializeGame(1, k, seed, &G);
    printf ("-----------------TESTING getCost():-----------------\n");
    for(i=1; i<= 27;i++){
         cost = getCost(k[i]);
        printf("cost = %d, expected = %d \n", cost, costs[i]);

    }
    printf ("TESTING getCost(-999)\n");
    cost=getCost(-999);
    printf("cost = %d, expected = -1 \n", cost );
    printf ("TESTING getCost(0)\n");
    cost=getCost(0);
    printf("cost = %d, expected = -1 \n", cost );
    printf ("-----------------TESTING getCost(): END-----------------\n");
}

