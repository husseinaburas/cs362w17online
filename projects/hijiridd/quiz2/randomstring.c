/* BEGINNING OF TEXT ********************

David Hijirida (hijiridd)
cs362 Random testing quiz2
Feb 5, 2016

Purpose: This is text file to document how I developed the random test for testme.c 

// ------------------------------------------
// What is the program testme() trying to accomplish?
// ------------------------------------------
We should start by getting grounded on the purpose of the testme program. It is seeking separate character and string inputs and if these inputs meet a certain criteria will change the "state" of the program from 0 to 9 and then to an "error" message. The character input should be the only input that drives the state from 0 to 9 and the string input should be the only input that drives the program from state 9 to an "error state" (or in this case an error message).

// ------------------------------------------
// What is the input space that we need to consider?
// ------------------------------------------

Input Space #1: c = inputChar()

Standard Inputs:
Here we expect a character input. In ANSI C, the possible input for a char variable is an 8 bit value. This is equivalent for an int value between 0 (0000 0000) and 255 (1111 1111). The standard input space should be the 8 bit space between 0 and 255

Non-Standard Inputs:
Ideas include testing negative values for char or what happens if we assign an integer value greater than 8 bits.

Input Space #2: s = inputString()

Standard Inputs: Here we expect a string but the length of the string is unspecified. A string is composed of a set # of characters and terminated by a null character '\0'. The standard input space should be testing strings with characters (in the standard input space #1 above) with variable length between (inclusive) 1 character and up to some standard maximum - I'll choose up to  509 characters for my "standard space" [ref 1]

[ref 1] https://bytes.com/topic/c/answers/786961-size-limits-string-literals. The maximum size of a string literal or wide string literal (after
concatenation, e.g. from "foo" "bar" to "foobar") that an implementation
*must* support is 509 in C90. This has been increased to 4095 in C99.

Non-Standard Inputs: 
Ideas include string that includes only the null character '\0' and a string that is longer than standard length 509.

// ------------------------------------------
// What is the approach for random testing?
// ------------------------------------------

If we stuck to our standard input space...

******************************************************
*** Testing to get us from state 0 to state 9
******************************************************

Hypothesis #1: It's relatively easy (few thousand iterations) for random characters to get us from state 0 to state 9. 

In this case, there is a path dependency so the random character input "c = inputChar()" must be generated in a certain order (e.g., '[' must be randomly selected first to go from state 0 to state 1, and only then will '(' get you from state 1 to state 2, etc.)

Quick back of the envelope to check myself on order of magnitude
Average case: If there is equal probability of any one single char getting selected, I'll assume you on average you need 256 iterations to hit the special character for each of 9 "if" statements, then it might take (256 * 9 = 2304) 2304 iterations (or order of magnitude is a few thousand iternations)

Real life tests:
Indeed our real life test proves Hypothesis #1 out. Across 5 trails where, see that it takes on average three thousand iterations to hit state = 9.
Trial 1: 3336
Trial 2: 3754
Trial 3: 2950
Trial 4: 1682
Trial 5: 3184
Trial 6: 2223
Trial 7: 1531
Trial 8: 4654
Trial 9: 3325
Trial 10: 3562
Average across 10 trials: 3021

Conclusion:
So we can brute force this test in the standard input space.

******************************************************
*** Testing to get us from state 9 to the error message
******************************************************

The random string should not matter as we traverse from state 0 to state 9. Therefore the tests for random string could be of any length and for any set of characters.

However because we are looking for a specific set of characters in order, even if we restricted the random string to be 5 characters, the # of trials would need to be (256 chars to the 5th power or 256^5 = 10^2) 10^2 or a trillion trials! If we then added more degrees of freedom to include strings of different lengths, the number of trials would explode much larger!!

In this case truly randomly generating characters for any length string will take too long to probe the input space that is truly interesting to us.

The way through this...
If we think of this as a queueing problem (similar to the bounded queue in udacity video). where we are testing different values across a queue, we can define a general and specific cases of the queue state that we want to test randomly.

First, assume that we have some max char length for the string. For our purpose, let's assume MAXCHARLENGTH = 10+1 (last one for the null character that is the end of the string). Then we have special cases where we ant to test in the input space (see below).

first some definitions
Case x == each case 0 through 6 represents an area input space that we are interested in testing
[i] == the character position in the string (where i is from 0 to 10)
? == random character between 0 and 255 int

TESTING TABLE
Case X:  [0] [1] [2] [3] [4] [5] [6] [7] [8] [9] [10]
Case 0:   ?   ?   ?   ?   ?   ?   ?   ?   ?   ?   /0
Case 1:  'r'  ?   ?   ?   ?   ?   ?   ?   ?   ?   /0
Case 2:  'r' 'e'  ?   ?   ?   ?   ?   ?   ?   ?   /0
Case 3:  'r' 'e' 's'  ?   ?   ?   ?   ?   ?   ?   /0
Case 4:  'r' 'e' 's' 'e'  ?   ?   ?   ?   ?   ?   /0
Case 5:  'r' 'e' 's' 'e' 't'  ?   ?   ?   ?   ?   /0
Case 6:  'r' 'e' 's' 'e' 't' '\0' ?   ?   ?   ?   /0

One potential approach would be to assign some % of our random test to each case.
Example if we evenly divided the %, each case would get about 14-15% of trial distributions.
Within each case, we would randomly select characters in the positions marked with "?".

NOTE: because one of the characters we are randomly pulling is the '/0' character (or the ASCII Character value of 0) in cases 0 through 4 we are implicitly testing string lengths less than 5. Also for cases 0 through 5 we are implicitly testing strings with lengths greater than 5.  Thus we are also exploring the cases where string lengths are longer and shorter without spending too much of our trial budget on these cases.

Alternative to assigning equal probability for each case: Instead of peanut butter probability, we could assign assign a lower % of bias for case 6. Instead of 14%, lower it down to 1% and distribute the other 99% across cases 0 through 5. This way we don't quite probing too early.

Other thoughts on non standard cases:
We could also test funky values of random characters (e.g., negative values or greater than 8 bits) but (from what I understand of the assignment) the purpose here is not to tyr to *break* the program, but to instead probe the input space that makes sense to probe. So I'm ignoring non standard inputs for character for now.

However I will be implicitly testing the edge case where a string is composed only of the null character (as part of case 0). I will not be trying to stress the maximum number of characters available for a string, so I'll use some max length of 100 that seams reasonably long to test.

// ------------------------------------------
// Code snippets showing how I've implemented the random inputs
// ------------------------------------------
I have listed the inputChar and inputString code below. Not for inputString, I've tested different max string lengths such as 40 (see below). Also it's relatively simple to change the % of trials that we want to push to different test cases. In the example below, I've allocated 1% to test case 6 and the rest relatively evenly to cases 0 through 5. These % can be changed based on how much time we have to run tests and compute power, etc. For example a more robust test might allocate a much larger % (e.g., 99%) to case 0 where all the characters are chosen at random.

// *********************
// inputChar - selects a random 8 bit char
// input: none
// return: char ranging from 0000 0000 to 1111 1111
// Note this is the same as randChar() but decided to implement this separately
// this allows us easy options to test different algorithms later and not couple code.
// *********************
char inputChar()
{
	// char values can be 8 bits, range from 0 to 255
	int lowRange = 0;
	int highRange = 255;
	char randChar = getRandIntLowHigh (lowRange, highRange);
	return randChar;
}



// *********************
// inputString - creates random string
// input: none
// return: c string with a set # of characters, randomly selected based on testing scenarios
// *********************
char *inputString()
{
	int maxCharsInString = 40; // must be greater than 5
	// allocate memory for string + 1 for null character at end of string
	char *randString = (char*) malloc(maxCharsInString * sizeof(char) + 1);

	// get a random # between 1 and 100 to distribute random test cases
	int randCaseDistribution = getRandIntLowHigh (1, 100);
	int testCase = 0; // default test case is zero

	if (randCaseDistribution == 100) {
		testCase = 6;  // allocate 1% of trials to test case 6
	} else if ((randCaseDistribution >= 1) && (randCaseDistribution <= 16)){
		testCase = 5; // allocate 16% of trials to test case 5
	} else if ((randCaseDistribution >=17) && (randCaseDistribution <= 32)){
		testCase = 4; // allocate 16% of trials to test case 4
	} else if ((randCaseDistribution >=33) && (randCaseDistribution <= 48)){
		testCase = 3; // allocate 16% of trials to test case 3
	} else if ((randCaseDistribution >=49) && (randCaseDistribution <= 64)){
		testCase = 2; // allocate 16% of trials to test case 2
	} else if ((randCaseDistribution >=65) && (randCaseDistribution <= 80)){
		testCase = 1; // allocate 16% of trials to test case 1
	} else if ((randCaseDistribution >=81) && (randCaseDistribution <= 99)){
		testCase = 0; // allocate the remaining % of trials to test case 0
	}
	//printf ("testCase = %d\n", testCase);

	switch (testCase) {
		case 0 :
			// Case 0: fill all positions with random characters
			for (int i = 0; i<maxCharsInString; i++) { randString[i] = randChar (); }
			randString[maxCharsInString+1] = '\0'; // add the end of string
			break;
		case 1:
			// Case 1: fill first position with 'r' and the rest with random characters
			randString[0] = 'r';
			for (int i = 1; i<maxCharsInString; i++) { randString[i] = randChar (); }
			randString[maxCharsInString+1] = '\0'; // add the end of string
			break;
		case 2:
			// Case 2: fill first 2 with 'r', 'e' and the rest with random characters
			randString[0] = 'r';
			randString[1] = 'e';
			for (int i = 2; i<maxCharsInString; i++) { randString[i] = randChar (); }
			randString[maxCharsInString+1] = '\0'; // add the end of string
			break;
		case 3:
			// Case 3: fill first 3 with 'r', 'e', 's' and the rest with random characters
			randString[0] = 'r';
			randString[1] = 'e';
			randString[2] = 's';
			for (int i = 3; i<maxCharsInString; i++) { randString[i] = randChar (); }
			randString[maxCharsInString+1] = '\0'; // add the end of string
			break;
		case 4:
			// Case 4: fill first 4 with 'r', 'e', 's', 'e' and the rest with random characters
			randString[0] = 'r';
			randString[1] = 'e';
			randString[2] = 's';
			randString[3] = 'e';
			for (int i = 4; i<maxCharsInString; i++) { randString[i] = randChar (); }
			randString[maxCharsInString+1] = '\0'; // add the end of string
			break;
		case 5:
			// Case 5: fill first 5 with 'r', 'e', 's', 'e', 't' and the rest with random characters
			randString[0] = 'r';
			randString[1] = 'e';
			randString[2] = 's';
			randString[3] = 'e';
			randString[4] = 't';
			for (int i = 5; i<maxCharsInString; i++) { randString[i] = randChar (); }
			randString[maxCharsInString+1] = '\0'; // add the end of string
			break;
		case 6:
			// Case 6: fill first 6 with 'r', 'e', 's', 'e', 't', '\0' and the rest random characters
			randString[0] = 'r';
			randString[1] = 'e';
			randString[2] = 's';
			randString[3] = 'e';
			randString[4] = 't';
			randString[5] = '\0';
			for (int i = 6; i<maxCharsInString; i++) { randString[i] = randChar (); }
			randString[maxCharsInString+1] = '\0'; // add the end of string
			break;
	}
    return randString;
}

* END OF TEXT DOCUMENT ************/
