randomstring.c
Quiz 2 implementation explanation
Michael Tarantino

inputChar()
For the inputChar() function I simply use the rand() function to generate a number between 32
and 125.  This is the ascii range that starts at the space character and goes through most 
printable characters, numbers, upper and lower case letters, and ends at the closing curly brace. 
In my testing of the function it took about 500 to 700 iteration at most to get up to state 9.

inputString()
I tried many different implementations to get this to work, just using random characters was not sufficient. I was 
getting into several million iterations and not even getting close to generating the string need to cause the error. 
It obviously required some bias be introduced to help nudge towards the required string. I was unable to find an 
effective solution that used inputChar() in the inputString() function, as the range of values was too large. 

What I ended up doing is creating another character generator that only did lower case letters. Even using just this 
I was unable to get it to generate the string needed, again waiting millions and millions of iterations. My final 
implementation involves generating a random lower case letter in any string index that had an even number (0, 2, and 
4). Then in the odd numbered indexes (1 and 3) I generate a random vowel (a,e,i,o,u). Using this implementation of 
generating a lower case letter, then a vowel, then lower case, etc I was finally able to produce the error.

I tested this many times and found a wide range of iterations required. It ran in as short as a few thousand 
iterations, and the longest was about 1.5 million iterations. I would say that it typically encounters the error in 
200 to 300 thousand iterations, which takes around 15 to 20 seconds.
