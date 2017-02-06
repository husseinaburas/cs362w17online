Joshua Couture
CS 362-400 
Quiz 2

For this assignment we needed to cause testme() in testme.c to produce its error statement by implementing the functions inputChar() and inputString().

testme() in testme.c requires the following conditions to generate the error message "error".  
The only way to trigger the error message and exit (200) conditions is by meeting the doncitions of an if statement that requires the variable "state" to be equal to 9 and for the characters in the string s to be arranged as follows:

s[0] = 'r'
s[1] = 'e'
s[2] = 's'
s[3] = 'e'
s[4] = 't'
s[5] = '\0'

The variable 'state' starts at 0 and increments by 1 each time c equals a specific character such as [ or ).  The specific characters must be matched in order for example [ must be matched before a.

Therefore it becomes clear that to trigger the error message we must feed in the appropriate characters to c via the inputChar() function and the appropriate string "reset" to s via the inputString() function.

inputChar():
For my implementation of inputChar() I first create a character array of all the possible values that c must be to increase the state counter.  inputChar() returns a random character from this array and will eventually increment state to 9 if fed through the loop in testme().

inputString():
For my implementation of inputString() I create a string of length 5 where each character is r, e, s, or t which is then returned to s in testme() via the function. Note that due to the way strings work in c s[5] does not need to be set because it will always be assumed to be '\0'.  To do a good test it does not matter whether you include '\0' in the allowed characters in s.  

Both functions would also work if the characters that were allowed were expanded to include all characters or a large subset of all characters, however because the conditions for this test were simply to generate the error using unspecified random input values that did not seem to be necessary. 