#ifndef _RANDOMTESTADVENTURER_H
#define _RANDOMTESTADVENTURER_H

/* Author: Elton Lee
 * randomtestadventurer.h
 * header file for randomtestadventurer.h
 */

// Function: runCardTest()
// Description: Calls the adventurer card with the following user-provided pre-conditions.
// Pre-conditions: Pass it a deck treasure id, the number of treasures, the deck size, the discard treeasure, the number of treasures in the discard, and the discard pile size.
// Post-conditions: Returns 1 if test failed. Returns 0 if passed.
int runCardTest(int deckTreasure, int deckTreasureCount, int deckSize, int discardTreasure, int discardTreasureCount, int discardSize);

// Function: asserttrue()
// Description: Implementation of isEqual for integers used for testing.
//				Returns 1 if values are equal. Else return 0.
int asserttrue(int val1, int val2);

#endif