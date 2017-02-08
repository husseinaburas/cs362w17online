/*
Name: Patrick Olarey
Assignment: Random Testing Quiz
Class: CS362-400
Date: 2/5/17
*/

Inspection of the testme() function revealed that the “error” would be produced when the 
string s contained “reset” (ending with a null terminator) and state contained 9. In order 
to get state to contain 9, first c would need to equal each of a series of characters (e.g. 
first c would need to equal a left bracket, then a subsequent iteration it would need 
to equal a left parenthesis, and so on).

Therefore, I determined that the function inputChar() should generate and return a random 
character with each call. This set of possible characters generated should at least contain 
each of the characters c would be compared to in testme(). To achieve this, I generated random 
characters from (space) (ASCII Code:  32 ) to right curly-bracket (ASCII Code: 125) with the 
simple line of code: return rand() % 94 + 32;.

Similarly, as noted previously, inputString() will need to generate the string “reset” in order 
to produce the bug. Therefore, I implemented inputString() to generate a string of five random 
lowercase alphabetic characters. The 6th character is always set to the null terminator. The function 
then returns this string to the calling function. 

With these implementations of inputChar() and inputString(), when run, testme() will quickly arrive 
to state 9. However, since the chance of 5 random characters equaling “reset” is particularly low (1/26^5), 
it takes on average a couple of minutes (and millions of iterations) before s contains “reset” and triggers the error.  


Implementations:

char inputChar()
{
	//generates values between 32 and 125
	//which correspond to ASCII ch codes for space through right-curly bracket.
	return rand() % 94 + 32;
}

char *inputString()
{
	char* s = malloc(sizeof(char)*6);

	//assign five random alphabetic characters (lowercase) to the string
	int i;
	for (i = 0; i < 5; i++) 
		s[i] = rand() % 26 + 97;
	
	//null terminate the string
	s[5] = '\0';
	
	return s;
}
