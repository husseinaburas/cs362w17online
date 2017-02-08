to compile:

gcc -o testme testme.c

I developed my solution by first studying the code provided.
inputChar() -
REASONING: I assumed based on the code that this was looking for some type of
char from ASCII. Thus I developed used the rand function to give me a number that
fell in the ASCII range (I did not include the first 31 chars on the ASCII table
as I felt they did not apply).

OUTPUT: random ASCII value that correlated to some char.

inputString()-
REASONING: I assumed based on the code that the program was looking for the string
to be "reset". However, in order to ensure that the random unit test was somewhat
random I created an if statement so that 99.9% of the time it spit out a random
set of chars to create a string, but 0.01% of the time it would spit out reset.
I did this to ensure that at some point with out having the program run endlessly
that it would hit the error code or at least should.

OUTPUT: 99.9% of the time random string 5 chars long, 0.01% of the time string "reset"
