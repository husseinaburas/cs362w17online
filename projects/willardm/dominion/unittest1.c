// Micheal Willard
// CS362 - Assignment #3
// Unit Test 1
// Testing: Get Cost


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define UNITTEST "getCost()"

void asserttrue (int bln, char* msg) {
  if (bln) {
    printf("%s:  PASS\n", msg);
  }
  else {
    printf("%s:  FAIL\n", msg);
  }
}

int main(int argc, char **argv) {

  printf("----------------- Testing Function:  %s ----------------\n", UNITTEST);

    asserttrue(getCost(curse) == 0, "Curse Value:  ");
    asserttrue(getCost(estate) == 2, "estate Value:  ");
    asserttrue(getCost(duchy) == 5, "duchy Value:  ");
    asserttrue(getCost(province) == 8, "province Value:  ");
    asserttrue(getCost(copper) == 0, "copper Value:  ");
    asserttrue(getCost(silver) == 3, "silver Value:  ");
    asserttrue(getCost(gold) == 6, "gold Value:  ");
    asserttrue(getCost(adventurer) == 6, "adventurer Value:  ");
    asserttrue(getCost(council_room) == 5, "council_room Value:  ");
    asserttrue(getCost(feast) == 4, "feast Value:  ");
    asserttrue(getCost(gardens) == 4, "gardens Value:  ");
    asserttrue(getCost(mine) == 5, "mine Value:  ");
    asserttrue(getCost(remodel) == 4, "remodel Value:  ");
    asserttrue(getCost(smithy) == 4, "smithy Value:  ");
    asserttrue(getCost(village) == 3, "village Value:  ");
    asserttrue(getCost(baron) == 4, "baron Value:  ");
    asserttrue(getCost(great_hall) == 3, "great_hall Value:  ");
    asserttrue(getCost(minion) == 5, "minion Value:  ");
    asserttrue(getCost(steward) == 3, "steward Value:  ");
    asserttrue(getCost(tribute) == 5, "tribute Value:  ");
    asserttrue(getCost(ambassador) == 3, "ambassador Value:  ");
    asserttrue(getCost(cutpurse) == 4, "cutpurse Value:  ");
    asserttrue(getCost(embargo) == 2, "embargo Value:  ");
    asserttrue(getCost(outpost) == 5, "outpost Value:  ");
    asserttrue(getCost(salvager) == 4, "salvager Value:  ");
    asserttrue(getCost(sea_hag) == 4, "sea_hag Value:  ");
    asserttrue(getCost(treasure_map) == 4, "treasure_map Value:  ");
    printf("\n >>>>> Testing complete %s <<<<<\n\n", UNITTEST);
}
