randomstring.c
Brent Nolan
nolanbr
CS362 -- Quiz 2 -- Random Testing 
2/04/2017

For the error message in testme() to occur first the state must be changed to 9.  This only will occur by the incrementing of the state from 0 to 9 
with each if statement that uses inputChar.Thus inputChar must eventually produce a result of: "[", "(", "{", " ", "a", "x", "}", ")", "]".  
This is done by having inputChar randomly generate a number corresponding to the anscii codes of: " " to "}".  

After the state is in 9, which will not change, since the if statements that change the state only have state 0-8, then the inputString 
must be: reset\0.  To speed the string creation up I only included the anscii codes corresponding to "e" to "t" and then added a the null
character to the end of the string.

Certainly I could increase the randomness by utilizing all ASCII characters, but this creates a more efficient test for the values we need 
to test to create the error result. Even just limiting from e to t made it take 4,488,374 iterations before producing the error message.