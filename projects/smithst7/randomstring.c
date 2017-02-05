/*

randomtest.c
Stephen Vaught-Smith
smithst7
cs362 Winter 2017


My test implementations use a call to rand() (using modulus to limit the range) and a 
switch statement to select a random character or string to return.

After examining the source code of testme() (huzzah for whitebox testing) I decided
to limit the domain of inputChar() to only return one of the nine characters checked for in testme().

Similarly, I limited the domain of inputString() to one of three five-character strings, one of which is the 
string ('reset') that will trigger the error message once calls to inputChar() advance state to 9.
I was tempted to have inputString() return only the critical string to save time, but the assignment
specifies that inputChar() and inputString() must return random values, and so I have added two other possible
strings for the function to return.

*/
