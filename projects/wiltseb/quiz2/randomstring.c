
Brian Wiltse
CS 362 Quiz 2

My inputChar function returns a random character with ascii values from 0 to 126. 
This typically gets the state variable to 9 relatively quickly.

My inputString function returns a string of lowercase characters of length 5, plus a null terminator. 
This seemed resonable because the error state is achieved when the string returned is "reset". An argument could be made 
that a string is not limited to lowercase alphabetical characters, and if we are creating a random tester for any given
string, we should test all possible characters in strings of all possible lengths. However,
one of the assignment specifications is to "Implement a random tester for the function testme()
in testme.c that is capable of printing the error message." Using a string of all possible lengths with all possible
characters would probably not be capable of finding the error state since the set of all possible strings that can
be generated is so large.

Here is how I believe my solution satisfies the instruction specifications:
"Implement a random tester for the function testme() in testme.c that is capable of printing the error message."
inputChar gets the program to state == 9 quickly. For inputString, 
generating a string of lowercase alphabetical characters of length 5 will print the error message if given enough time. 

"You should implement inputChar() and inputString() to produce random values."
inputChar generates random characters from the set of all ASCII characters. This is the broadest interpretation of what
inputChar should do, but it gets to state == 9 quickly and reliably, so there was no need to modify it to satisfy the 
"capable of printing the error message" requirement. inputString also produces random values, but, as noted above,
is constrained to a size and pool of characters that will reach the error state in a reasonable amount of time.

Output from test:
Iteration 6308786: c = , s = reset, state = 9
error 

