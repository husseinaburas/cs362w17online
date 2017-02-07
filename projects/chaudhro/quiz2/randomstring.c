/*

Rohit Chaudhary
Quiz 2

Implementations:

inputChar():

I needed to create a function that returns a randomly ascii char. The possible ascii int values range from 32 being space to 126 being ~.
Thus, all I had to do was return a character with an ascii value within that range. I used space is my base case, and added rand() % 94 which
is just 126-32 to return a random character.

inputString():

I used a similar design as inputChar() with some small changes to create this function. First of all, looking at the test function, I saw that we only
check up to the 6th element of the string so I decided to generate a string that is 5 characters long plus the end string character. I filled the string
up by allocating the necessary memory, then iterating through it and filling each element with a random character. However, I limited the range to just
lowercase ascii values as looking at the test case we only had to generate the string "reset\0" to get into the error statement. 

With these two implementations, getting into state 9 is really simple as the character only has to match a few specific characters in order. Getting the string
"reset" takes much longer however since there are many more combinations. There are 26^5 total combitions using only lowercase ascii values, which means
we have a 1/11881376 chance of any one string being "reset". Using more than 5 characters for the random string wouldn't change the probability
of the first 5 being "reset", but it would take more time and memory to generate. If we used the same range as I did for inputChar(), it would be 94^5 which is 617 times bigger.
I was able to get the error message printed out in 20241056 iterations. This is in the same general scale as 11881376 which makes sense.
*/