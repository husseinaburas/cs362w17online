First off, I don't know why this is supposed to be a C file if it's just a text file.

Anyways, I developed inputChar() using C's rand function.

I seed the random number generator with the current time and then generate
a random number between 0 and 94; this range is the same range as is between
the first and last readable ASCII characters. 

I then add 32 to put the random number I generated into the real range of 
ASCII characters (32-126).

Then I simply cast that number to a char and return it.


inputString() uses a random number to decide how many characters will be in the
string; between 1 and 6. Then it calls inputChar() in a loop to generate each 
character.

There is a line I commented out which waits (using sleep(1)) a second for each 
character; this allows different characters to be generated within the string.
If you don't wait, then the time value stays the same and the seed isn't updated,
which is needed for a new random character to be generated.

The only way you could possibly trigger the error message is if you had that
sleep line enabled; otherwise the string will be full of the same character,
that is unless your machine is really slow.
