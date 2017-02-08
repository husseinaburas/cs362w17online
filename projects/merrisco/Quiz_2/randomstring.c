/* randomstring.c is a text file that outlines how I developed my solution for the Random Testing Quiz 2

Author: Scott Merrill

For this assignment we needed to create a random test to find the error in testme.c.
While looking over the code I realized that it was set up as a state machine. There are 
10 state which require a specific character to be returned from inputChar() to move to the next one. 
The final state checks for the string "reset" to be returned from inputString(). This will print the error
message that we are looking for. 

I was required to write inputChar() and inputString():

in inputChar() all I needed to to was return a random character. For this I used the rand()
function to pick a random value off of the ascii table. I did not feel that adding other values that 
could break the code would be useful to this assignment as we are only looking for the a way to 
create the error.

in inputString() I needed to return a random array of characters. The end result was that I was hoping to 
produce the string "reset" which would invoke the error. I used the same procedure as in inputChar() to
generate the characters, but this time they were saved in an array length 5 (This could have been longer 
but would habe exponentially increased the amount of time it would take to generate the string I was 
trying to produce). The last character was the null-charcter to end the string. 

In addtion to these to functions I made one last change so that the error message would appear on it's
own line. This doesnt really change the code in any way; rather to make it more visually appealing when
completed. 
*/ 