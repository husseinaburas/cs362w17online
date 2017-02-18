/******************************************************
randomstring.c
Random Test Quiz 2
ruizry

inputChar() function: I randomized a value between 32-158 to represent a random ascii value assigned
to our character variable. Ascii 32 respesent ' ' which is the lowest value to trigger an incremented state.
Ascii value 158 is past the '}' value which is our largest value to possibly trigger a state. The loop
will continue generating random character values in the ascii range from 32-158 until the program
reaches state 9.

inputString() function: This function takes the character array value of "reset" and randomly scrambles it
to form a new character array with a '\0' as the last character. While in state 9 this function will
be called and form a randomly scrambled string until "reset\0" is returned. At this point the program
will be at state 9 and fufill the conditions to print the error message.
********************************************************/