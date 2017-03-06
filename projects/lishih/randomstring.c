/*
Shihhui Li
onid:lishih
Quiz2

file can be compile with gcc testme.c -o testme

Function: testme()
it is an infinite while loop that check the inputChar() and inputString()
the loop exsit under the condition of the passed character matches and the state variable matches.

char inputChar()
it random generates the random number of interger 0 to 25. Than add 97 to match the starting lowest aphabate in ASCII.
Also, convert it to the charcter. Than, this function retuen to randChar.

char *inputString()
The array input value can be changed. it meory allocation the max lenth of the array size 
iteration through the array to generates the random string. Than return to randString.

The final if condtion end the whsile loop condition. The error message will display 
The error checks against a string s that is calling by the inputString() function. when 
the string randomly become \0, the final condtion is met and the execution exits loops with the error.
*/
