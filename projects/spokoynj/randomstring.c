/***********************************************************************
 * Jessica Spokoyny
 * CS 362
 * Random Testing Quiz 2
 * ********************************************************************/
/* 
 How I developed the solution:
 
	inputChar(): This function first assigns an array of characters 
	called chars. The array contains 12 characters (all of the 9 
	characters required to produce the error as well as a few others 
	for testing). Then, it randomly generates a number from 0 to the 
	size of the array (12). And finally, it finds the randomly generated 
	number as an index and returns the character located at that index 
	position in the array.
	
	inputString(): This function first allocates space for a char* 
	string and assigns an array of characters called chars. The array 
	contains 10 characters (all of the 4 characters required to produce 
	the error as well as a few others for testing). Then, it randomly 
	generates a number from 0 to the size of the array (10) and finds 
	the randomly generated number as an index and places the character 
	located at that index position in the array into the string. Lastly, 
	it adds the null terminator to the last position in the string and 
	returns the string.
	
 
 How it finds the error message:
 
	1. The testme() program sets the state to 0. 
	2. It enters into a while loop that continues until an error is 
		encountered
	3. Within the loop, it calls inputChar() and inputString() which 
		randomly assign and return a character and a string, 
		respectively (as described above)
	4. In order to move from the initial state 0 to the next state 
		(state 1), the char returned in the previous step must == '['.
	5. Because the chars returned are randomly generated, there is no 
		guarantee of how many iterations it will take to move on to the 
		next step
	6. Once we do encounter the iteration where c == '[' && state == 0, 
		we move on to state = 1
	7. This process (steps 3-6) is repeated with the characters 
		{ '[','(','{',' ','a','x','}',')',']' } incrementing the state 
		each time until state = 9
	8. In order make the function print the error message, the string 
		returned from calling inputString() must == "reset\0"
	9. Because the strings returned are randomly generated, there is no 
		guarantee of how many iterations it will take to print the error
	10. Once the string "reset\0" is generated and state == 9, the 
		program prints an error message and exits
		
Changes made throughout the design process:
	
	I originally had the arrays of chars in inputChar() & inputString() 
	as the entire ASCII set of characters but this took a very long time 
	and wasn't handled well by the flip server. I modified the arrays to 
	contain just the required chars plus a few extras added to ensure
	the proper functionality.
*/	