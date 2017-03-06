#ifndef _RANDOMTESTCARD2_H
#define _RANDOMTESTCARD2_H

/* Author: Elton Lee
 * randomtestcard2.h
 * random testing for council_room
 */

// runs random testing
// returns 0 if all tests passed
// returns -1 if any test cases fail
int runCardTest(int deckSize, int discardSize);

// checks val1 == val2
// true returns 0
// false returns -1
int asserttrue(int val1, int val2);

#endif