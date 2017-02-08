/************************
** Name: Eddie C. Fox
** Class: CS 362: Software Engineering II
** Title: Quiz 2
*************************/

/********************************
** Explanation of development: It was clear that I would need to make inputChar() return a character and inputString() return a string, 
** but what were the exact specifications? First, I took a look at the testme.c document in its original form to determine 
** under what conditions the error message would be printed. After looking at the code longer, I realized that it was a while loop that
** would continue to iterate with characters and strings returned from the respective functions until it printed the error message, as
** that was the only condition that would be sufficient to exit the loop. the state variable starts at zero, and with every successive
** match to a particular character returned from the function, it would increment by 1. The state would need to pass 9 such stages and
** have a value of 9 before 1 of the 2 error message printing conditions was fulfilled. The other condition that needed to pass was 
** the string returned from the string function to be 'reset' with a null terminator at the end. This meant that I needed a string with
** 6 spaces, that went from index 0 to 5, and then change index 5 to the null terminator before returning the string. I used an ASCII
** table to help me determine the range of values I needed to randomize for both the string and character functions. For the character
** array, it the lowest ASCII value was 32, corresponding to space ' ', which is needed along with state 3 to transform state 3 to state
** 4. The highest ASCII value needed was 125, corresponding to '}', which is needed along with state 6 to transform state 6 to state 7.
** The character function, therefore, was a simple matter of randomizing a character in the range of ASCII 32 - 125, and returning it.
** A similar approach worked for the string function. The lowest value on the ASCII table that is needed for 'reset' is 101 for lowercase
** e, and the highest is 116 for lowercase t. We don't need letters a-d and u-z to spell reset, so this should be a bit more streamlined
** for testing exactly what we need to test. This is important because it might require lots of iterations to print the error message, so
** we want each iteration to go as fast as possible. I decided to put max and min variables and assign the ASCII for e and t their values
** just in case someone wants to change it from a to z in the future.
*********************************/