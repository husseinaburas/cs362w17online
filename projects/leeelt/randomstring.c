Elton Lee
2-4-2017
CS362 Winter Quarter 2017
Quiz 2

inputChar()
To reach state 9, random char must be able to generate all open and close brackets, as well as 
certain lower-case characters.To do this, I used a reference to the ASCII table of 
printable characters. These fall between 32 and 126. This is 95 total characters. 
rand() % 95 + 32 captures the range between 32 and 126.

*inputString()
The string to reach the error code is "reset\0". In C, strings are arrays of
chars. We need to allocate enough memory beforehand in the randomString to
hold 6 chars. Originally, I used a character set of a...z and used a loop to
create a random 5 character string and added "\0" to the end. This means there are
26^5 combinations (11,881,376). To make testing time faster, I shortened the
character set to "rest" instead which is 5^5 (1024). The function is written
so that modifying the lower_case_char_set will modify the range of characters tested.
More characters = longer testing time.