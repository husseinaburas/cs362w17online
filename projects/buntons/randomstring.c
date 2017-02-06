/*
Name: Shirley Bunton
Date: 02/05/2017
Assignment: Random Test Quiz (Quiz 2)
Course: CS362 Software Engineering II

----------------------------------------
gcov results:
----------------------------------------
File 'testme.c'
Lines executed:97.22% of 36
Branches executed:100.00% of 52
Taken at least once:96.15% of 52
Calls executed:100.00% of 10
Creating 'testme.c.gcov'

----------------------------------------
char* inputString();
----------------------------------------
This function returns a pointer to an array of characters. Space is allocated
for an array of 6 characters (the last for the null character). In a for loop
that executes five times, a random number generator generates a number from 0
to 25, then 97 (corresponding to 'a') is added to the generated number, giving
random numbers from 97 to 122, which correspond to lowercase alphabetical
letters. A random lowercase letter is generated at each iteration of the loop
and added to the array of characters, resulting in a string of 5 letters and
the null character. A pointer to the array of characters is returned.
The testme() function checks if the string stored in the array is equal to
"reset\0" and if the state of the program is 9, then "error " is printed to the
console.

----------------------------------------
char inputChar();
----------------------------------------
This function returns a random character from ASCII characters 32 to 126
(from ' ' to '~'). The function is restricted to returning ASCII characters
that are printable by the console, since there are ASCII control characters.
These control characters are omitted from the list of possible characters to
return from inputChar(). A random number generator produces a number from 0 to
94, and 32 is added to the result (the equivalent of the ' ' character).
The testme() function uses the char returned from inputChar to go through the
state of the program.


*/