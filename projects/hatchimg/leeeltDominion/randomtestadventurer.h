#ifndef _RANDOMTESTADVENTURER_H
#define _RANDOMTESTADVENTURER_H

/* Author: Elton Lee
 * randomtestadventurer.h
 * header file for randomtestadventurer.h
 */

// runs random testing
// returns 0 if all tests passed
// returns -1 if any test cases fail 
int runCardTest(int deckTreasure, int deckTreasureCount, int deckSize, int discardTreasure, int discardTreasureCount, int discardSize);

// checks val1 == val2
// true returns 0
// false returns -1
int asserttrue(int val1, int val2);

#endif