/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * testUpdateCoins: testUpdateCoins.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "asserttrue.h"
#include "rngs.h"


// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int constantSeedForRandomSeed = 1;
    int numPlayer = 2;
    int maxBonus = 10;
    int arrayOfKindomCardsAvailableDuringGamePlay[10] = {adventurer, council_room, feast, gardens, mine
        , remodel, smithy, village, baron, great_hall};
    struct gameState NewGameStateStruct;
    struct gameState OldVersionOfGameStruct;
    
    int maxHandCount = 5;
    
    // arrays of all coppers, silvers, and golds
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    int estates[MAX_HAND];
    
    int i;
    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;        // Copper Treasure Card (Should give value of 1)
        silvers[i] = silver;        // Silver Treasure Card (Should give value of 2)
        golds[i] = gold;            // Gold Treasure Card (Should give value of 3)
        estates[i] = estate;        // Non Treasure Card (Should give value of 0)
    }
    
    printf ("TESTING updateCoins():\n");
    int currentPlayer, handCount, bonus;
    
    /* LOOP OVER EACH OF THE 2 PLAYERS*/
    for (currentPlayer = 0; currentPlayer < numPlayer; currentPlayer++)
    {
        /* LOOP OVER THE NUMBER OF UNUSED CARDS THE CURRENT PLAYER CURRENTLY HAS IN HIS HAND */
        for (handCount = 1; handCount <= maxHandCount; handCount++)
        {
            /* LOOP OVER ALL POSSIBLE BONUS AMOUNTS FOR THE GAME */
            for (bonus = 0; bonus <= maxBonus; bonus++)
            {
                
                
                
                /***************************************************************************
                 Init the test for this loop
                 ***************************************************************************/
#if (NOISY_TEST == 1)
                printf("Test player %d with %d treasure card(s) and %d bonus.\n", currentPlayer, handCount, bonus);
#endif
                memset(&NewGameStateStruct, 23, sizeof(struct gameState));  // clear the game state
                memset(&OldVersionOfGameStruct, 23, sizeof(struct gameState));  // clear the old game state (used to compare before after effect of method call)
                
                asserttrue(initializeGame(numPlayer, arrayOfKindomCardsAvailableDuringGamePlay, constantSeedForRandomSeed, &NewGameStateStruct) == 0); // initialize a new game
                NewGameStateStruct.handCount[currentPlayer] = handCount;    // set the number of cards on hand FOR THE CURRENT PLAYER
                
                
                
                
                
                /***************************************************************************
                 Unit Test condition 1: TEST THE GAME STATE STRUCT'S COIN PROPERTY IF THE CURRENT PLAYER HAD ALL COPPER COINS ($1 EACH) IN THEIR HAND
                 ***************************************************************************/
                memcpy(NewGameStateStruct.hand[currentPlayer], coppers, sizeof(int) * handCount); // set all the cards to copper
                OldVersionOfGameStruct = NewGameStateStruct;                    // Save the Old State of the Game Struct to Compare effect of updateCoins()
                
                updateCoins(currentPlayer, &NewGameStateStruct, bonus);
#if (NOISY_TEST == 1)
                printf("NewGameStateStruct.coins = %d, expected = %d\n", NewGameStateStruct.coins, handCount * 1 + bonus);
#endif
                asserttrue(NewGameStateStruct.coins == handCount * 1 + bonus); // check if the number of coins is correct
                
#if (NOISY_TEST == 1)
                printf("NewGameStateStruct.coins = %d, expected = %d\n", NewGameStateStruct.coins, handCount * 1 + bonus);
#endif
                asserttrue(NewGameStateStruct.coins == handCount * 1 + bonus); // check if the number of coins is correct
                
                /************ Properties that Should not Change ************/
                printf("    Testing Properties that should Not change...\n");
                
                /* Make sure whoseTurn is the same */
#if (NOISY_TEST == 1)
                printf("    NewGameStateStruct.whoseTurn = %d, expected = %d\n", NewGameStateStruct.whoseTurn, OldVersionOfGameStruct.whoseTurn);
#endif
                asserttrue(NewGameStateStruct.whoseTurn == OldVersionOfGameStruct.whoseTurn); // check if the number of coins is correct
                
                /* Make sure numPlayers is the same */
#if (NOISY_TEST == 1)
                printf("    NewGameStateStruct.numPlayers  = %d, expected = %d\n", NewGameStateStruct.numPlayers , OldVersionOfGameStruct.numPlayers );
#endif
                asserttrue(NewGameStateStruct.numPlayers  == OldVersionOfGameStruct.numPlayers ); // check if the number of coins is correct
                
                /* LOOP OVER EACH OF THE 2 PLAYERS to make sure handCount the same*/
                for (int currentPlayerAgain = 0; currentPlayerAgain < numPlayer; currentPlayerAgain++)
                {
#if (NOISY_TEST == 1)
                    printf("    NewGameStateStruct.handCount[%d] = %d, expected = %d\n", currentPlayerAgain, NewGameStateStruct.handCount[currentPlayerAgain], OldVersionOfGameStruct.handCount[currentPlayerAgain]);
#endif
                    asserttrue(NewGameStateStruct.whoseTurn == OldVersionOfGameStruct.whoseTurn); // check if the number of coins is correct
                }
                
                
                
                
                /***************************************************************************
                 Unit Test condition 2: TEST THE GAME STATE STRUCT'S COIN PROPERTY IF THE CURRENT PLAYER HAD ALL SILVER COINS ($2 EACH) IN THEIR HAND
                 ***************************************************************************/
                memcpy(NewGameStateStruct.hand[currentPlayer], silvers, sizeof(int) * handCount); // set all the cards to silver
                OldVersionOfGameStruct = NewGameStateStruct;                    // Save the Old State of the Game Struct to Compare effect of updateCoins()
                
                
                updateCoins(currentPlayer, &NewGameStateStruct, bonus);
#if (NOISY_TEST == 1)
                printf("NewGameStateStruct.coins = %d, expected = %d\n", NewGameStateStruct.coins, handCount * 2 + bonus);
#endif
                asserttrue(NewGameStateStruct.coins == handCount * 2 + bonus); // check if the number of coins is correct
                
                /************ Properties that Should not Change ************/
                printf("    Testing Properties that should Not change...\n");
                
                /* Make sure whoseTurn is the same */
#if (NOISY_TEST == 1)
                printf("    NewGameStateStruct.whoseTurn = %d, expected = %d\n", NewGameStateStruct.whoseTurn, OldVersionOfGameStruct.whoseTurn);
#endif
                asserttrue(NewGameStateStruct.whoseTurn == OldVersionOfGameStruct.whoseTurn); // check if the number of coins is correct
                
                /* Make sure numPlayers is the same */
#if (NOISY_TEST == 1)
                printf("    NewGameStateStruct.numPlayers  = %d, expected = %d\n", NewGameStateStruct.numPlayers , OldVersionOfGameStruct.numPlayers );
#endif
                asserttrue(NewGameStateStruct.numPlayers  == OldVersionOfGameStruct.numPlayers ); // check if the number of coins is correct
                
                /* LOOP OVER EACH OF THE 2 PLAYERS to make sure handCount the same*/
                for (int currentPlayerAgain = 0; currentPlayerAgain < numPlayer; currentPlayerAgain++)
                {
#if (NOISY_TEST == 1)
                    printf("    NewGameStateStruct.handCount[%d] = %d, expected = %d\n", currentPlayerAgain, NewGameStateStruct.handCount[currentPlayerAgain], OldVersionOfGameStruct.handCount[currentPlayerAgain]);
#endif
                    asserttrue(NewGameStateStruct.whoseTurn == OldVersionOfGameStruct.whoseTurn); // check if the number of coins is correct
                }
                
                
                
                
                /***************************************************************************
                 Unit Test condition 3: TEST THE GAME STATE STRUCT'S COIN PROPERTY IF THE CURRENT PLAYER HAD ALL GOLD COINS ($3 EACH) IN THEIR HAND
                 ***************************************************************************/
                memcpy(NewGameStateStruct.hand[currentPlayer], golds, sizeof(int) * handCount); // set all the cards to gold
                OldVersionOfGameStruct = NewGameStateStruct;                    // Save the Old State of the Game Struct to Compare effect of updateCoins()
                
                
                updateCoins(currentPlayer, &NewGameStateStruct, bonus);
#if (NOISY_TEST == 1)
                printf("NewGameStateStruct.coins = %d, expected = %d\n", NewGameStateStruct.coins, handCount * 3 + bonus);
#endif
                asserttrue(NewGameStateStruct.coins == handCount * 3 + bonus); // check if the number of coins is correct
                
                /************ Properties that Should not Change ************/
                printf("    Testing Properties that should Not change...\n");
                
                /* Make sure whoseTurn is the same */
#if (NOISY_TEST == 1)
                printf("    NewGameStateStruct.whoseTurn = %d, expected = %d\n", NewGameStateStruct.whoseTurn, OldVersionOfGameStruct.whoseTurn);
#endif
                asserttrue(NewGameStateStruct.whoseTurn == OldVersionOfGameStruct.whoseTurn); // check if the number of coins is correct
                
                /* Make sure numPlayers is the same */
#if (NOISY_TEST == 1)
                printf("    NewGameStateStruct.numPlayers  = %d, expected = %d\n", NewGameStateStruct.numPlayers , OldVersionOfGameStruct.numPlayers );
#endif
                asserttrue(NewGameStateStruct.numPlayers  == OldVersionOfGameStruct.numPlayers ); // check if the number of coins is correct
                
                /* LOOP OVER EACH OF THE 2 PLAYERS to make sure handCount the same*/
                for (int currentPlayerAgain = 0; currentPlayerAgain < numPlayer; currentPlayerAgain++)
                {
#if (NOISY_TEST == 1)
                    printf("    NewGameStateStruct.handCount[%d] = %d, expected = %d\n", currentPlayerAgain, NewGameStateStruct.handCount[currentPlayerAgain], OldVersionOfGameStruct.handCount[currentPlayerAgain]);
#endif
                    asserttrue(NewGameStateStruct.whoseTurn == OldVersionOfGameStruct.whoseTurn); // check if the number of coins is correct
                }
                
                
                
                
                
                
                
                /***************************************************************************
                 Unit Test condition 4: TEST THE GAME STATE STRUCT'S COIN PROPERTY IF THE CURRENT PLAYER HAD NO TREASURE COINS ($0 EACH) IN THEIR HAND
                 ***************************************************************************/
                memcpy(NewGameStateStruct.hand[currentPlayer], estates, sizeof(int) * handCount); // set all the cards to copper
                OldVersionOfGameStruct = NewGameStateStruct;                    // Save the Old State of the Game Struct to Compare effect of updateCoins()
                
                
                updateCoins(currentPlayer, &NewGameStateStruct, bonus);
#if (NOISY_TEST == 1)
                printf("NewGameStateStruct.coins = %d, expected = %d\n", NewGameStateStruct.coins, 0 + bonus);
#endif
                asserttrue(NewGameStateStruct.coins == 0 + bonus); // check if the number of coins is correct
                
                /************ Properties that Should not Change ************/
                printf("    Testing Properties that should Not change...\n");
                
                /* Make sure whoseTurn is the same */
#if (NOISY_TEST == 1)
                printf("    NewGameStateStruct.whoseTurn = %d, expected = %d\n", NewGameStateStruct.whoseTurn, OldVersionOfGameStruct.whoseTurn);
#endif
                asserttrue(NewGameStateStruct.whoseTurn == OldVersionOfGameStruct.whoseTurn); // check if the number of coins is correct
                
                /* Make sure numPlayers is the same */
#if (NOISY_TEST == 1)
                printf("    NewGameStateStruct.numPlayers  = %d, expected = %d\n", NewGameStateStruct.numPlayers , OldVersionOfGameStruct.numPlayers );
#endif
                asserttrue(NewGameStateStruct.numPlayers  == OldVersionOfGameStruct.numPlayers ); // check if the number of coins is correct
                
                /* LOOP OVER EACH OF THE 2 PLAYERS to make sure handCount the same*/
                for (int currentPlayerAgain = 0; currentPlayerAgain < numPlayer; currentPlayerAgain++)
                {
#if (NOISY_TEST == 1)
                    printf("    NewGameStateStruct.handCount[%d] = %d, expected = %d\n", currentPlayerAgain, NewGameStateStruct.handCount[currentPlayerAgain], OldVersionOfGameStruct.handCount[currentPlayerAgain]);
#endif
                    asserttrue(NewGameStateStruct.whoseTurn == OldVersionOfGameStruct.whoseTurn); // check if the number of coins is correct
                }
            }
        }
    }
    
    printf("All TESTS PASSED...\n");
    
    return 0;
}
