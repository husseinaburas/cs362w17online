#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"

//Unit test for update coins found in dominion.c
// Funciton call: int updateCoins(int player, struct gameState *state, int bonus)
//Note: updateCions function currently starts line 1252 from dominion.c


void testUpdateCoins() {
    printf("----TEST updateCoins Function-----\n");

    int k[10] = {adventurer, gardens, feast, village, minion, mine, steward,
        sea_hag, tribute, smithy};
    int seed = 40;
//---GS1 TEST---- 3 treasure cards and bonus, +inital coin value
    // Expect coin output: 8 (Copper+Silver+Gold+Bonus = 1+2+3+2=8)
    int coinExpectedForGS1 = 8;
    struct gameState *GS1 = newGame();
    initializeGame(2,k,seed,GS1);
    int playerGS1 = 0;  //Maxplayers is 4, test 0-3 array indexing
    int bonusGS1 = 2;  
    GS1->coins = 1000; //Used to verify a prexisting coin amount, should be set reset
    GS1->handCount[playerGS1] = 5;  //Test hand of 5 cards (average).
    GS1->hand[playerGS1][0] = copper;  //Coin value is 1
    GS1->hand[playerGS1][1] = silver;  //Coin value is 2
    GS1->hand[playerGS1][2] = gold;  //Coin value is 3
    GS1->hand[playerGS1][3] = adventurer; //Coin value is 0
    GS1->hand[playerGS1][4] = province; //test invalid card

   

//---GS2 TEST---- No cards with bonus
    // Expect coin output:1 0 (No cards in hand)
    //GS2 Tests for a player with no cards.  No cards in the hand array are assigned,
    //as it is assumed there are no cards.  The bonus is set to 10, eventhough the player has no cards, test outcome.
    int coinExpectedForGS2 = 10;
    struct gameState *GS2 = newGame();
    initializeGame(2,k,seed,GS2);
    int playerGS2 = 1;  //Maxplayers is 4, test 0-3 array indexing
    int bonusGS2 = 10; 
    GS2->coins = 5; //Used to verify a prexisting coin amount, should be set back to 0
    GS2->handCount[playerGS2] = 0;  //Test hand of 0 cards (average).
 

//---GS3 TEST---- Heavy lifting - checks for 75 treasure cards accurate coin values.
    // Expect coin output: 151 (25*Copper+25*Silver+25*Gold+Bonus = 25+50+75+1 = 151)
    int coinExpectedForGS3 = 151;
    struct gameState *GS3 = newGame();
    initializeGame(2,k,seed,GS3);
    int playerGS3 = 2;  //Maxplayers is 4, test 0-3 array indexing
    int bonusGS3 = 1;  
    GS3->coins = 0; 
    GS3->handCount[playerGS3] = 75;  
    
    for(int cop=0; cop < 25; cop++)  //Assigns 0-24 indexs to copper cards
    {
        GS3->hand[playerGS3][cop] = copper;
    }
    for(int sil=0; sil < 25; sil++)  //Assigns 25-49 indexs to silver cards
    {
        GS3->hand[playerGS3][sil+25] = silver;
    }
    for(int gol=0; gol < 25; gol++)  //Assigns 50-74 indexs to gold cards
    {
        GS3->hand[playerGS3][gol+50] = gold;
    }

//---GS4 TEST---- Test coin and bonus w/ estate/adv cards
    // Expect coin output: 8 (Copper+Silver+Gold+Bonus = 1+2+3+1+2+3=12)
    int coinExpectedForGS4 = 12;
    struct gameState *GS4 = newGame();
    initializeGame(2,k,seed,GS4);
    int playerGS4 = 3;  //Maxplayers is 4, test 0-3 array indexing
    int bonusGS4 = 0;  
    GS4->coins = 0; //Verify an inital 0 amount
    GS4->handCount[playerGS4] = 10;  
    GS4->hand[playerGS4][0] = copper;  //Coin value is 1
    GS4->hand[playerGS4][1] = silver;  //Coin value is 2
    GS4->hand[playerGS4][2] = gold;  //Coin value is 3
    GS4->hand[playerGS4][3] = adventurer; //Coin value is 0
    GS4->hand[playerGS4][4] = smithy; //Coin value is 0
    GS4->hand[playerGS4][5] = copper;  //Coin value is 1
    GS4->hand[playerGS4][6] = silver;  //Coin value is 2
    GS4->hand[playerGS4][7] = gold;  //Coin value is 3
    GS4->hand[playerGS4][8] = adventurer; //Coin value is 0
    GS4->hand[playerGS4][9] = village; //Coin value is 0




    updateCoins(playerGS1, GS1, bonusGS1); // Expect coin output: 8 (Copper+Silver+Gold+Bonus = 1+2+3+2=8)
    if(GS1->coins == coinExpectedForGS1){
        printf("PASS for parameters in Game State 1 sent.  Coins Expected:%i  Coins Returned:%i \n", coinExpectedForGS1, GS1->coins);
    }
    else
    {
        printf("FAIL for parameters in Game State 1 sent.  Coins Expected:%i  Coins Returned:%i \n", coinExpectedForGS1, GS1->coins);
    }

    updateCoins(playerGS2, GS2, bonusGS2); // Expect coin output: 8 (Copper+Silver+Gold+Bonus = 1+2+3+2=8)
    if(GS2->coins == coinExpectedForGS2){
        printf("PASS for parameters in Game State 2 sent.  Coins Expected:%i  Coins Returned:%i \n", coinExpectedForGS2, GS2->coins);
    }
    else
    {
        printf("FAIL for parameters in Game State 2 sent.  Coins Expected:%i  Coins Returned:%i \n", coinExpectedForGS2, GS2->coins);
    }

    updateCoins(playerGS3, GS3, bonusGS3); // Expect coin output: 8 (Copper+Silver+Gold+Bonus = 1+2+3+2=8)
    if(GS3->coins == coinExpectedForGS3){
        printf("PASS for parameters in Game State 3 sent.  Coins Expected:%i  Coins Returned:%i \n", coinExpectedForGS3, GS3->coins);
    }
    else
    {
        printf("FAIL for parameters in Game State 3 sent.  Coins Expected:%i  Coins Returned:%i \n", coinExpectedForGS3, GS3->coins);
    }

    updateCoins(playerGS4, GS4, bonusGS4); // Expect coin output: 8 (Copper+Silver+Gold+Bonus = 1+2+3+2=8)
    if(GS4->coins == coinExpectedForGS4){
        printf("PASS for parameters in Game State 4 sent.  Coins Expected:%i  Coins Returned:%i \n", coinExpectedForGS4, GS4->coins);
    }
    else
    {
        printf("FAIL for parameters in Game State 4 sent.  Coins Expected:%i  Coins Returned:%i \n", coinExpectedForGS4, GS4->coins);
    }
 
    return;
}

int main(int argc, char *argv[])
{
    testUpdateCoins();
    return 0;
}



