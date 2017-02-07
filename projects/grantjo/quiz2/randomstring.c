/******************************************************************************************
 * Student: Jordan Grant
 * onid: grantjo
 * date: 02-05-2017
 *
 * Assignment: Quiz 2
 * *****************************************************************************************/

/*
 *
  I tackled this assignment by first looking over the testme() function. The program will only exit from
from an infinite loop if a series of random characters appear in the right order from inputChar and then then 
the correct string is returned from intputString. I saw that there is a distinct subset of 9 characters that 
control the state  and a distinct subset of 5 characters that make up the target string "reset\0". In order 
for the error message to be displayed the inputChar must match the current state variable before it can 
proceed.

[ goes with 0
( with 1
{ with 2
' ' with 3
a with 4
x with 5
} with 6
) with 7
] with 9

Once you reach a state you never go back and the program must reach state 9 prior to the string helping at all.
Once you are at state 9 the inputString must be 6 characters long in the order "reset\0"

The instructions say that the inputString and inputChar must be randomly generated. I decided that limiting the
choices of the string to the 5 relevant characters r, s, e, t, \0 and limiting the inputChar options to the 
ones displayed above the program will have a better chance of reaching the error message. To achieve the random
specification of the assigment I was able to just randomly index an array of the relevant characters.

inputChar: 
  I created an array of char's containing the 9 state characters and every time inputChar is called i create a 
random index between 0 and 8, using rand() % 8, and then return the character at that index in the array.

inputString:
  I created an array of char's containing the 5 needed to build the desired string (r, s, e, t, \0). I then 
allocate a string of length 6 and randomly index the character option array to build the random string. 
The string is then returned.


To compile this program run the following:

gcc testme.c -o testme
 *
 */
