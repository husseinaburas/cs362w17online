/*
Name: Andew Bagwell
Course: CS362
Description: randomString.c
*/

Compile with: gcc -std=c99 testme.c -o 31% ./testMe

inputChar() - This function returns a random ASCII character between the ASCII values of 32 (space) 
and 126 (~). To do this, I took the modulo of a random value produce by the rand() and 94 (126 - 32) +

inputString() - This function returns a random string of lowercase letters. The testme function looks at the 6th byte of a string,
my strings were only of length 6 (5 byte plus the \0 null byte to terminate the string). I then looped over the string, filling in the bytes of 
the string with a lowercase ascii value (modulus of random val and 26 plus the asci val for 'a')

The program reached state nine rather quickly. It took substantially longer to get the string to match reset. 
I had a little trouble with the str return from inputString going out of scope. The program did terminate and reached the error case after 4 test runs at the following number of iterations: 
	(1) 15203681
	(2) 2486837
	(3) 8073228
	(4) 12055451