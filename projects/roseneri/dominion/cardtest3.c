#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TESTCARD "steward"

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

    int seed = 10;
    int num_players = 2;
    int current_player = 0;
    int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    struct gameState G, testG;


    int handpos = 0;
    int bonus = 0;


  
    int num_discarded = 0;
    //int gained_coins = 0;
    int shuffledCards = 0;




    // initialize game
    printf("******* Begin Test, testing %s ******\n", TESTCARD);
    initializeGame(num_players, cards, seed, &G);

//*********** test 1: +2 cards, choice1=1 *******************
    printf("Test 1: Add 2 cards\n");
    memcpy(&testG, &G, sizeof(struct gameState));

    // trigger function that executes switch case
    cardEffect(steward, 1, 0, 0, &testG, handpos, &bonus);
    int gained_coins = 0;
    int gained_cards = 2;

    // compare the number of cards in hand
    printf("hand count = %d, expected = %d\n", testG.handCount[current_player], G.handCount[current_player] + gained_cards - num_discarded);
    int test_input  = testG.handCount[current_player] == G.handCount[current_player] + gained_cards - num_discarded;
    assert_true(test_input);

    // campare the number of cards in player's deck
    printf("deck count = %d, expected = %d\n", testG.deckCount[current_player], G.deckCount[current_player] - gained_cards + shuffledCards);
    test_input = testG.deckCount[current_player] == G.deckCount[current_player] - gained_cards + shuffledCards;
    assert_true(test_input);

    // compare number of coins
    printf("coins = %d, expected = %d\n", testG.coins, G.coins + gained_coins);
    assert_true(testG.coins == G.coins + gained_coins);

 //************ test 2: +2 coins choice1=2 ********************
    printf("Test 2: Gain two coins\n");

    // duplicate game state
    memcpy(&testG, &G, sizeof(struct gameState)); 
    cardEffect(steward, 2, 0, 0, &testG, handpos, &bonus);
    gained_cards = 0; 
    gained_coins = 2; 


    // compare the number of cards in hand
    printf("hand count = %d, expected = %d\n", testG.handCount[current_player], G.handCount[current_player] + gained_cards - num_discarded);
    assert_true(testG.handCount[current_player] == G.handCount[current_player] + gained_cards - num_discarded);

    // compare the number of cards in player's deck
    printf("deck count = %d, expected = %d\n", testG.deckCount[current_player], G.deckCount[current_player] - gained_cards + shuffledCards);
    assert_true(testG.deckCount[current_player] == G.deckCount[current_player] - gained_cards + shuffledCards);

    // compare count of coins
    printf("coins = %d, expected = %d\n", testG.coins, G.coins + gained_coins); 
    assert_true(testG.coins == G.coins + gained_coins); 

//******************* test 3: trash 2 cards choice1=3 ***************
    printf("Test 3: Trash two cards\n");

    // duplicate game state
    memcpy(&testG, &G, sizeof(struct gameState)); 
    cardEffect(steward, 3, 0, 0, &testG, handpos, &bonus);

    printf("hand count = %d, expected = %d\n", testG.handCount[current_player], G.handCount[current_player] + gained_cards - num_discarded);
    assert_true(testG.handCount[current_player] == G.handCount[current_player] + gained_cards - num_discarded);
    
    printf("deck count = %d, expected = %d\n", testG.deckCount[current_player], G.deckCount[current_player] - gained_cards + shuffledCards);
    assert_true(testG.deckCount[current_player] == G.deckCount[current_player] - gained_cards + shuffledCards);

//**************************** end of test *****************
    printf("CARDTTEST3 SUCCESSFULLY COMPLETED\n\n");
    return 0;


}