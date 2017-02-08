/*
Cs 362 - 400
Software Engineering II

Richard Moot

char inputChar()
- For this function, I simply return a random integer that falls withing the standard ASCII values (32 through 125).

char *inputString()
- For this function, I would return a random integer for 5 lower case characters. In order to make everything work, it was essential to
	use malloc() for allocating the string(char pointer) so that it would display in the logging of testme().

The random testing for the inputChar would rapidly hit to state 9, since randomly returning a given characters out of the set would be rather high
for a few thousand iterations.

The inputString had to be restricted to 5 characters, as having more would make achieving the final state take more time than is practical. Including all ASCII
values would have made the program run way too many iterations to finally return a string of 'reset\0'. By narrowing the scope of the random ASCII set,
it is able to return an error in a few minutes at most.

 */
