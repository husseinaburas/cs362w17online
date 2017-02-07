/*Parker Bruni write up 
Random Testing Quiz 2

inputChar():
This function will return a char value.
The char value is generated through a random number generator
with mod 95 + 32 applied. This will skip the first 32 characters
of the ascii alphabet.


inputString():
This will use the rand function to generate a number between 1 and 500
If r is equal to 1, return a string "reset". This essenitally means
"reset" error message has a 1 in 500 chance of being ran.
Else, the function generates character array of size 6 chars and
uses inputChar() to generate 6 random characters to fill the array
and returns that character array.


*/