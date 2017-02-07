/*
CS362 - Random Testing Quiz
Gary Smith
randomstring.c


InputChar()
Generate a random integer between 32 & 126 (ASCII values)
Cast that to a character and return that.
Characters 32-126 include all the keyboard letters but exclude the first 32 control characters.


InputString()
Generate a string of random length 
Fill that string with characters between 32 & 126


I started off with a very wide net...  random characters and a random length string.
The random length string ended up being too long and would never find a string of length 5.
So I limited down the size of the string to 5 characters (6 inclduing the \0 character).
Even after that, 5 million random string attempts were not enough.  So I limited the character
set down to just lower case letters.  

The characters pattern will eventually cause the state to be 9, so it's just a matter of randomly
generating the string 'reset'.  If we do some quick calculations, we can tell roughly how many 
attempts we will need.  choosing 'r' out of the alphabet is 1/26.   Repeate for each character and we
get 1/(26^5) or 11,881,376.  So I just let the program run for over 12 million attempts.  

Running the program is successful occasionally below 12 million attempts.  I was able to generate the 
string 'reset' at 9 million and 3 million.  

I implemented a counter in the testme function to stop after a defined number of attempts to prevent an
infinite while loop.


*/