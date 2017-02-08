// Author: Steven Ha
// Date: Feb 5, 2017
// Class: CS362-400
// Random Quiz 2
// File Name: randomstring.c
// Description: This file documents random quiz 2.

/*
I started this random quiz by looking at the testme() function. Upon examination, I found that
the test required a character and a string. The character and string needed to be generated
randomly.

The character function randomly generates a integer value between 0 and 127 that is
cast to a character. That character is returned from the inputChar() function.

The character array needed to be a string that was terminated by a nul. The function set the last character
in the string to be '\0'. The remaining characters were generated between the characters a and z.

The key to getting the function to print out the error definitely stems from knowing the function
is comparing. If the inner workings of the testme() function was unknown and the only thing that was known
was that the input needed to be a character and a character array, it would've taken longer to test.














*/