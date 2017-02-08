/*Clare Brown
CS 362
Random Testing Quiz


COMPILE WITH: 
	gcc testme.c -o testme

RUN WITH:
	testme



To develop my ranom tester, I first spent some time reading through the testme function.
I noticed that the if statements cascade in a way where the first one has to be true to 
change the state which will in turn allow the next one to be true in a different iteration
of the loop. Eventually, each of the if statements has to be true once in an iteration of
the while loop to get the error message to print. The first 9 if statements rely on the 
random character and state while the last if statement relies on the result from inputString 
and the state. The last if statement checks if inputString is contain the word "reset" 
with a null terminator at the end. 

In implementing inputChar, I first looked at what characters the if statement checked against. 
The characters were not just from the set of lower case or upper case letters, they included
parentheses and brackets as well. Looking at an ASCII table, I decided that an acceptable range
of characters was between 32 (space) and 126 (~). The values in that range actually output visible
characters and not keyboard commands like delete or cancel. To pick a character in that range, 
I used the rand() operator and the modulus operator with the statement (rand() % 95) + 32. This 
gave a random number between 32 and 126 inclusive. Once I had a random character, it was returned
to be used in the testme function.

In implementing inputString, I first had the function pick a random string length and then fill
the string with random lower case letters. I soon realized that the test was running for too long
and was not very likely to print the error statement. I then restricted the length of the string
to 6 characters which corresponded to the number of characters being checked in the last if statement.
After testing this, it still took too long to get the error statement to print because there are 
a lot of possible combinations of 6 letters out of a total of 27. To make the test hit the error
statement faster, I restricted the possible letters to choose from to r, e, s, t, and /0, the 
5 characters that make up the desired statement. After implementing this, the test ran a lot faster
and printed the error statement reliably.

There are more ways to make the functions do more "random" testing but for the purpose of this task,
I wanted to have some randomness but still be able to get the error statement to print. This is why
I analyzed the code before writing the functions and catered the functions to what the code was looking for.

*/