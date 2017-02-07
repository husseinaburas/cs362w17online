/* 
CS362-400
02/05/2017
Joseph Rebolledo
Random Testing Quiz 2
*/

/*
How I developed my solution and how it works:

To get the function testme to print the error message, a few actions must occur in order.
First, the integer state must be incremented from 0 to 9. In order for this to happen, the correct character must be returned from inputChar(). 
The characters needed are: [,(,{, , a, x, },),]. Returning these characters, in the order represented here, from inputChar(), will increment the state from 0-9.
Once the state has reached 9, then the string returned from inputString() must represent the word: reset followed by a terminating null character. Once this occurs, the error message will print.
If this does not occur, then a new call to inputString() will be made, and will continue to be made, until the needed string is returned. 

As mentioned above, inputChar() and inputString() need to return the correct values in order for the error message to print:

For the inputChar() function: I decided to return a random value between that of 32 and 126. I chose these values because to increment state
required inputChar() to return characters ranging from the SPACE character to that of the right closing curly bracket. 
The way the function works is by using a rand() call paired with a % 95 to get a value ranging from 0 to 94.
Then, to get this value to range from 32 and 126, I added 32 to this value.
This allowed the function to return a value ranging from 32 to 126, thus allowing us increment the state integer.

For the inputString() function: I decided to have the function return a random 6 letter string that is terminated with a null character.
The random characters within this string ranged from a-z. I accomplished this by first creating a string and then randomly placing the values: 97-122 within that string.
This worked well for creating a random 6 character string. Yet, to increase the likelihood of the word 'reset' followed by a null terminating character being returned from the function,
I implemented an initial rand() call that returns a character between 0 and 999. If this rand() call returns 1, then the word 'reset' followed by a null terminating character is returned.
This allows the inputString function to test thousands of random inputs while still producing the error once in a few thousand iterations.


*/
