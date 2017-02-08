/****************************************************************************************************

To implement the random tester for the function testme(), it was necessary to determine what random characters 
and possible string combinations to be making. In order to do this, the range of characters in both the char c 
and char *s were taken into consideration individually. The range for char c started at the space character and 
proceeded through to '}'. To get a random character, the initial value of the space character was added to a random 
number generated modulo 94 to account for the 93 desired potential characters to be returned.

Implementing the randomly generated string was done in a similar fashion. In this case, we were interested in 
getting 5 random lower case letters with a null terminator to signify the end of the string. Here a character array 
of size 6 was declared. The array will filled with 5 random characters from a-z, then a null terminator added to the 
end of the array. 

When called, the testme() function runs until the state makes it way up to 9 and eventually lands on the string 
'reset'; once those conditions are met, the error message is printed and the program exits. Even though there are 
more characters for the state changes and several states to get through, those happen quickly compared to finding 
the exact string 'reset'.

Reference:
http://stackoverflow.com/questions/19724346/generate-random-characters-in-c

******************************************************************************************************/
