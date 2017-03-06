/*
 * unittest3.c
 */

/*
 * Include the following lines in your makefile:
 *
 * unitest3: unittest3.c dominion.o rngs.o
 *      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

void updateHand(int player, struct gameState* state, int newhand[4]){

	for (int i = 0; i < 4; i++){
		state->hand[player][i] = newhand[i];
	}
	state->handCount[player]=4;

	return;
}


void testUpdateCoins(){
	struct gameState MyGame;
	int ReturnValue;
	
	// Setup a Game for testing
	int p1Hand[4] = {smithy, adventurer, duchy, estate};
	int p2Hand[4] = {copper, adventurer, duchy, estate};
	int p3Hand[4] = {silver, adventurer, duchy, estate};
	int p4Hand[4] = {silver, copper, duchy, estate};
	int p5Hand[4] = {silver, silver, duchy, estate};
	int p6Hand[4] = {gold, adventurer, duchy, estate};
	int p7Hand[4] = {gold, silver, copper, estate};


    printf("\n=== BEGINNING UNIT TESTS for UpdateCoins()\n\n");
	/* --- TEST 1 from Checklist --- */
	updateHand(0, &MyGame, p1Hand);
	ReturnValue = updateCoins(0, &MyGame, 0);

	if (ReturnValue == 0 && MyGame.coins == 0)
        printf("updateCoins(): PASS TEST 1.\n");
    else
        printf("updateCoins(): FAIL TEST 1. Value of Coins = %i\n", MyGame.coins);
	/* --- TEST 1 from Checklist --- */

	/* --- TEST 2 from Checklist --- */
	ReturnValue = updateCoins(0, &MyGame, 1);

	if (ReturnValue == 0 && MyGame.coins == 1)
        printf("updateCoins(): PASS TEST 2.\n");
    else
        printf("updateCoins(): FAIL TEST 2. Value of Coins = %i\n", MyGame.coins);
	/* --- TEST 2 from Checklist --- */

	/* --- TEST 3 from Checklist --- */
	updateHand(0, &MyGame, p2Hand);
	ReturnValue = updateCoins(0, &MyGame, 0);

	if (ReturnValue == 0 && MyGame.coins == 1)
        printf("updateCoins(): PASS TEST 3.\n");
    else
        printf("updateCoins(): FAIL TEST 3. Value of Coins = %i\n", MyGame.coins);
	/* --- TEST 3 from Checklist --- */

	/* --- TEST 4 from Checklist --- */
	ReturnValue = updateCoins(0, &MyGame, 1);

	if (ReturnValue == 0 && MyGame.coins == 2)
        printf("updateCoins(): PASS TEST 4.\n");
    else
        printf("updateCoins(): FAIL TEST 4. Value of Coins = %i\n", MyGame.coins);
	/* --- TEST 4 from Checklist --- */

	/* --- TEST 5 from Checklist --- */
	updateHand(0, &MyGame, p3Hand);
	ReturnValue = updateCoins(0, &MyGame, 0);

	if (ReturnValue == 0 && MyGame.coins == 2)
        printf("updateCoins(): PASS TEST 5.\n");
    else
        printf("updateCoins(): FAIL TEST 5. Value of Coins = %i\n", MyGame.coins);
	/* --- TEST 5 from Checklist --- */

	/* --- TEST 6 from Checklist --- */
	updateHand(0, &MyGame, p4Hand);
	ReturnValue = updateCoins(0, &MyGame, 0);

	if (ReturnValue == 0 && MyGame.coins == 3)
        printf("updateCoins(): PASS TEST 6.\n");
    else
        printf("updateCoins(): FAIL TEST 6. Value of Coins = %i\n", MyGame.coins);
	/* --- TEST 6 from Checklist --- */

	/* --- TEST 7 from Checklist --- */
	ReturnValue = updateCoins(0, &MyGame, 1);

	if (ReturnValue == 0 && MyGame.coins == 4)
        printf("updateCoins(): PASS TEST 7.\n");
    else
        printf("updateCoins(): FAIL TEST 7. Value of Coins = %i\n", MyGame.coins);
	/* --- TEST 7 from Checklist --- */

	/* --- TEST 8 from Checklist --- */
	updateHand(0, &MyGame, p5Hand);
	ReturnValue = updateCoins(0, &MyGame, 0);

	if (ReturnValue == 0 && MyGame.coins == 4)
        printf("updateCoins(): PASS TEST 8.\n");
    else
        printf("updateCoins(): FAIL TEST 8. Value of Coins = %i\n", MyGame.coins);
	/* --- TEST 8 from Checklist --- */

	/* --- TEST 9 from Checklist --- */
	updateHand(0, &MyGame, p6Hand);
	ReturnValue = updateCoins(0, &MyGame, 0);

	if (ReturnValue == 0 && MyGame.coins == 3)
        printf("updateCoins(): PASS TEST 9.\n");
    else
        printf("updateCoins(): FAIL TEST 9. Value of Coins = %i\n", MyGame.coins);
	/* --- TEST 9 from Checklist --- */

	/* --- TEST 10 from Checklist --- */
	updateHand(0, &MyGame, p7Hand);
	ReturnValue = updateCoins(0, &MyGame, 0);

	if (ReturnValue == 0 && MyGame.coins == 6)
        printf("updateCoins(): PASS TEST 10.\n");
    else
        printf("updateCoins(): FAIL TEST 10. Value of Coins = %i\n", MyGame.coins);
	/* --- TEST 10 from Checklist --- */
    printf("\n=== COMPLETED UNIT TESTS for UpdateCoins()\n\n");
    
	return;
}

int main(){
	testUpdateCoins();
	return 0;
}