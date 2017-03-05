//
// Created by Rob Navarro on 2/1/17.
//
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>


//Testing int getCost(int cardNumber)
int main() {
    printf("\n*** Unit Test 4: Testing getCost ***\n");

    printf("Testing cost for Curse\n");
    customAssert(getCost(curse) == 0);

    printf("Testing cost for Estate\n");
    customAssert(getCost(estate) == 2);

    printf("Testing cost for Duchy\n");
    customAssert(getCost(duchy) == 5);

    printf("Testing cost for Province\n");
    customAssert(getCost(province) == 8);

    printf("Testing cost for Copper\n");
    customAssert(getCost(copper) == 0);

    printf("Testing cost for Silver\n");
    customAssert(getCost(silver) == 3);

    printf("Testing cost for Gold\n");
    customAssert(getCost(gold) == 6);

    printf("Testing cost for Adventurer\n");
    customAssert(getCost(adventurer) == 6);

    printf("Testing cost for Council Room\n");
    customAssert(getCost(council_room) == 5);

    printf("Testing cost for Feast\n");
    customAssert(getCost(feast) == 4);

    printf("Testing cost for Gardens\n");
    customAssert(getCost(gardens) == 4);

    printf("Testing cost for Mine\n");
    customAssert(getCost(mine) == 5);

    printf("Testing cost for Remodel\n");
    customAssert(getCost(remodel) == 4);

    printf("Testing cost for Smithy\n");
    customAssert(getCost(smithy) == 4);

    printf("Testing cost for Village\n");
    customAssert(getCost(village) == 3);

    printf("Testing cost for Baron\n");
    customAssert(getCost(baron) == 4);

    printf("Testing cost for Great Hall\n");
    customAssert(getCost(great_hall) == 3);

    printf("Testing cost for Minion\n");
    customAssert(getCost(minion) == 5);

    printf("Testing cost for Steward\n");
    customAssert(getCost(steward) == 3);

    printf("Testing cost for Tribute\n");
    customAssert(getCost(tribute) == 5);

    printf("Testing cost for Ambassador\n");
    customAssert(getCost(ambassador) == 3);

    printf("Testing cost for Cutpurse\n");
    customAssert(getCost(cutpurse) == 4);

    printf("Testing cost for Embargo\n");
    customAssert(getCost(embargo) == 2);

    printf("Testing cost for Outpost\n");
    customAssert(getCost(outpost) == 5);

    printf("Testing cost for Salvager\n");
    customAssert(getCost(salvager) == 4);

    printf("Testing cost for Sea Hag\n");
    customAssert(getCost(sea_hag) == 4);

    printf("Testing cost for Treasure Map\n");
    customAssert(getCost(treasure_map) == 4);

    printf("Testing that invalid negaitve value returns -1\n");
    customAssert(getCost(-1) == -1);

    printf("Testing that index outside of range returns -1\n");
    customAssert(getCost(27) == -1);

    return 0;
}
