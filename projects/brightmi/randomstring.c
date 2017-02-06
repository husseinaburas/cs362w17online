/**
 * Miles Bright
 * randomstring.c
 * Quiz 2 - Random Testing
 * 2/5/17
 */

/*

The inputChar() function by generating a random number in range 0-93 and then adding that
number to the ' ' char. That creates a random character in range 32-126 (' ' to '~'). The
function then returns the generated character.

The inputString() function initializes a C-style string (character array) with 6 spaces
malloc'd. The inputChar() function is called on the first 5 spaces in the string. This 
allows enough characters for the string r-e-s-e-t to be produced in the testme() function. 
Then the 6th space is assigned a null terminator '\0' character. The string is returned.

When the program is started and testme() is called, state 9 is reached when the appropriate
characters are assigned to c by the inputChar() function, which increments the state. This
state is achieved relatively quickly. To reach the error message and exit statement, the 
return string must be assigned the value "reset". This happens after a few hours of the
program being run in the terminal.

*/
