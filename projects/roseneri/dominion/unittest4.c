#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define UNITTEST "getCost()"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

void assert_true(int val) {
    if (val == 0) {
        printf("TEST FAILED!\n\n");
    }
    else
        printf("TEST PASSED!\n\n");
}

int main() {

    printf("******* Begin Test, UNITTEST4 testing %s ******\n\n", UNITTEST);

    // initialize game
    struct gameState *testG = newGame();
    int cards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

    // Initialize game
    initializeGame(2, cards, 10, testG);
    int cost_expected;
    int cost_returned;
    char var;


    printf("****** test 1, test getCost(silver)*****\n");
    var = silver;
    cost_expected = 3;
    cost_returned = getCost(var);
    printf("return value = %d, expected return value = %d\n", cost_returned, cost_expected);
    assert_true(cost_returned == cost_expected);

    printf("****** test 12, test getCost(copper)*****\n");
    var = copper;
    cost_expected = 1;
    cost_returned = getCost(var);
    printf("return value = %d, expected return value = %d\n", cost_returned, cost_expected);
    assert_true(cost_returned == cost_expected);

    printf("****** test 3, test getCost(gold)*****\n");
    var = gold;
    cost_expected = 6;
    cost_returned = getCost(var);
    printf("return value = %d, expected return value = %d\n", cost_returned, cost_expected);
    assert_true(cost_returned == cost_expected);

    printf("****** test 4, test getCost(estate)*****\n");
    var = estate;
    cost_expected = 2;
    cost_returned = getCost(var);
    printf("return value = %d, expected return value = %d\n", cost_returned, cost_expected);
    assert_true(cost_returned == cost_expected);

    printf("****** test 5, test getCost(duchy)*****\n");
    var = duchy;
    cost_expected = 5;
    cost_returned = getCost(var);
    printf("return value = %d, expected return value = %d\n", cost_returned, cost_expected);
    assert_true(cost_returned == cost_expected);

    printf("****** test 6, test getCost(province)*****\n");
    var = province;
    cost_expected = 8;
    cost_returned = getCost(var);
    printf("return value = %d, expected return value = %d\n", cost_returned, cost_expected);
    assert_true(cost_returned == cost_expected);

    printf("****** test 7, test getCost(curse)*****\n");
    var = curse;
    cost_expected = 0;
    cost_returned = getCost(var);
    printf("return value = %d, expected return value = %d\n", cost_returned, cost_expected);
    assert_true(cost_returned == cost_expected);

    printf("****** test 8, test getCost(village)*****\n");
    var = village;
    cost_expected = 3;
    cost_returned = getCost(var);
    printf("return value = %d, expected return value = %d\n", cost_returned, cost_expected);
    assert_true(cost_returned == cost_expected);

    printf("****** test 9, test getCost(feast)*****\n");
    var = feast;
    cost_expected = 4;
    cost_returned = getCost(var);
    printf("return value = %d, expected return value = %d\n", cost_returned, cost_expected);
    assert_true(cost_returned == cost_expected);

    printf("****** test 10, test getCost(adventurer)*****\n");
    var = adventurer;
    cost_expected = 6;
    cost_returned = getCost(var);
    printf("return value = %d, expected return value = %d\n", cost_returned, cost_expected);
    assert_true(cost_returned == cost_expected);

    printf("****** test 11, test getCost(smithy)*****\n");
    var = smithy;
    cost_expected = 4;
    cost_returned = getCost(var);
    printf("return value = %d, expected return value = %d\n", cost_returned, cost_expected);
    assert_true(cost_returned == cost_expected);

    printf("****** test 12, test getCost(sea_hag)*****\n");
    var = sea_hag;
    cost_expected = 4;
    cost_returned = getCost(var);
    printf("return value = %d, expected return value = %d\n", cost_returned, cost_expected);
    assert_true(cost_returned == cost_expected);

    printf("****** test 13, test getCost(cutpurse)*****\n");
    var = cutpurse;
    cost_expected = 4;
    cost_returned = getCost(var);
    printf("return value = %d, expected return value = %d\n", cost_returned, cost_expected);
    assert_true(cost_returned == cost_expected);

    printf("****** test 14, test getCost(remodel)*****\n");
    var = remodel;
    cost_expected = 4;
    cost_returned = getCost(var);
    printf("return value = %d, expected return value = %d\n", cost_returned, cost_expected);
    assert_true(cost_returned == cost_expected);

    printf("****** test 15, test getCost(tribute)*****\n");
    var = tribute;
    cost_expected = 5;
    cost_returned = getCost(var);
    printf("return value = %d, expected return value = %d\n", cost_returned, cost_expected);
    assert_true(cost_returned == cost_expected);

 

    printf("******  UNITTEST4 SUCCESSFULLY COMPLETED ******\n\n");
    return 0;

}