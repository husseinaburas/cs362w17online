/*
  File: randomstring.c
  Author: Daniel Eisenbach
  Course: CS 362
  Date: 2/5/17

  inputChar() OVERVIEW:
  I knew that to produce the error, I would have to eventually output the following characters in order: '[', '(', '{', ' ', 'a', 'x', '}', ')', ']'. To have th inputChar function randomly output each of these characters I simply created an array of chars that contained all of the possible values, and then used rand, bounded by the size of the char array, to randomly output values from the char array. Eventually this is done in order, as is needed to print the error message.

  inputString() OVERVIEW:
  I knew that to produce the error, I would have to eventually output "reset\0" from my inputString() function. To do this, I created an array of chars containing the letters in the string "reset", and used rand, bounded by the size of that string, to fill a string bounded by the length of "reset". Once the string was randomly filled, I then appended the null character '\0' and returned the created string. This eventually outputs "reset\0".

*/
