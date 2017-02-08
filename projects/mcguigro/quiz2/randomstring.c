/*
Explanation for implementation of testme.c

Overview: I implemented inputChar() and inputString(), and added the freeing of
   dynamically allocated memory into testme().  The laws of probability dictate
   that the error message will be eventually printed; the average run consists
   of approximately 10^10 iterations (since 1/10^10 is approximately the odds of
   a length-5 string equalling "reset", and the time it takes for state to equal 
   9 via 9 random-char matches is negligible in comparison) but there is no upper
   bound on the number of iterations any run of testme will take.

inputChar(): This returns a random character.  The assignment specifications do
   not indicate which characters are considered "valid", so I assumed that I
   should only use the normal, printable characters with ASCII codes from 32
   to 126.  The expression in inputChar() returns a random number between these
   two values, inclusive.

inputString(): This returns a string of length 5, whose characters are of the
   same type as those returned by inputChar().  The assignment specifications
   leave it up to me to determine which strings to test, and testing strings of
   arbitrary length is not feasible in terms of the number of iterations one
   would expect to go through before the error message is printed.  Even using
   just strings of length 5, the loop will go through on average approximately
   10^10 times before terminating, which I think is reasonable enough.  The
   implementation populates the string with 5 random characters and adds on a null
   character.  The memory for the string is allocated dynamically since it is
   returned out of a method (I thought it better to do this than to change the
   signature of inputString(), the assignment specifications make no mention
   either way.)

testme(): Added two lines (one in either branch of the 'if' block) to free the
   memory allocated for the string.  As noted above, dynamic allocation is
   necessary, and not freeing the memory would cause a massive memory leak.
*/