/*

	Micheal Willard
	CS 362
	Quiz 2
	to compile:  gcc testme.c -o testme
	to run: ./testme

	Objective:
		We need to build functions inputChar() and inputString().
		These functions need to cause the function testme() to execute the if clause
		which prints out the error.

  Results:
    The testme() function got to State 9 relatively quickly.  However it took
    a while to get to the correct order of {r,e,s,e,t,\0}
    A test run produced:
    Iteration 7972624: c = {, s = reset, state = 9

	Description:
		These functions are called within testMe().
		testme() initilizes the following variables:
		int tcCount = 0;
		char *s;
		char c;
		int state = 0;
		testme() then enters while loop where inputChar() and inputString() are called at each new
		loop, thus producing a new input character and input string for each loop.
		There are 9 if clauses that check the value of int state.
		These clauses increment the value of state if the inputChar() variable, c, is the correct
		value and the state is at the right value.  Thus the inputChar() value of c must be
		reached in a specific order.
		Once the value of state reaches 9, then the value of inputString() is checked.
		The inputString() is checked for a specific order of characters: r, e, s, e, t, \0.
		If that order is met, then the error statement is printed.

	inputChar():
		Based on the definiton of testme() the inputChar() function will generate a random
		character from the list of following characters:
		'[', '(', '{', ' ', 'a', 'x', '}', ')', ']'

	inputString():
		Based on the rules of the testme() function, inputString() must produce a randomly
		selected character string of lowercase letters that is a length of six.
		A bit of an assumption was made in that the final character of the string is "\0".
		The function builds an allocated string of length 6.  It places a randomly selected
		letter in each of the first 5 slots of the string/character array.
		It then places a "\0" newline in the final slot and returns.


*/
