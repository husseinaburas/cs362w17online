/*
Chris Wuestner
CS 362 Software Engineering II
Random Testing Quiz 2
2/5/2017

To find the error message, I first implemented the function inputChar(). Within this function,
I used random() to choose a random ASCII character ranging between the ' ' (space) character
and the '}" character. This range ensured that every "state" in testme() was possible to
achieve. I considered making an array containing every necessary character, and randomly
choosing a chararcter from that array with each call, but was unsure whether this change would 
be an improvement.

My next task was to implement the function inputString(). To implement this function, I first
had the function allocate space for the string, based on the string's length (in terms of characters).
I also added lines within testme() to free this allocated space. I attempted to use inputChar to
create a random string of a random length that I thought seemed reasonable (between 1-15
characters), but it became clear that this strategy would take an unreasonable length of time
to produce the necessary string, "reset". I eventually decided to randomly choose letters from 
an array containing the characters 'e', 'r', 's', and 't', and to form a string containing between 4
and 6 characters (plus the null terminator) with these randomly chosen characters. This allows 
random strings to be generated and tested without there being such a small chance of the target 
string being generated in a reasonable length of time, and I believe adequately tests the testme() 
function.

I used gcov to check the coverage and found it to be 97.62%, meaning all but one line was
executed. I believe the line not executed is the final line in main(), 'return 0', because 
testme() causes the program to exit when it finishes executing, without returning to main().
*/