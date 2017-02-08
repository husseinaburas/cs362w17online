/* Akash Sharma

char inputChar():
	For this function, we were simply required to return a character, and I chose the ascii range of 32 to 126, and this is accomplished by modding a random number 
	by 95 to get a result from 0 to 94, and adding 32 to this.
	
char *inputString():
	For this function we had to produce a random string, and my design is very similar to the inputchar() function. I just allocated memory
	for a string, populated it with values using the inputchar() function's random values, and returned it.
	To force the code to produce the error string, I created a condition so if a random number was a multiple of 500,
	which has a 1/500 chance, the output string would be hard-coded to be the error string. If this condition never happens, there
	is still a chance for the string reset to be generated based on the random population of characters. It took about
	3000 iterations to produce the error message. 