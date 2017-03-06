/*
To compile: gcc testme.c -o testme

Development of random tester:
	 inputChar():
	 	I looked at the testme() function and understood it's relation with inputChar(). The testme() function requires 
	 	certain character to be equal in order to reach its next state. Using the required 9 characters and few other characters
	 	I created an array. Then used a randomizer to return one of these characters for the inputChar() function. 

	 inputString():
	 	Looking at testme() function, I realized the required string is "reset\0" to output the error print. So I created an array with 5 of the "reset" characters
	 	and few other characters. Then I created a for loop that strings together a 5 character word randomly using characters from the array. Then I added "\0" to the 
	 	end of the randomly generated string and returned it for the inputString() function.

	 Test:
	 	The testme() function's while loop will repeatedly call inputChar() for a randomly generated character until it meets the character requirement. Once this and the state 
	 	meets the requirement, it moves to the next state. This keeps repeating until it reaches the 9th state. Then the while loop will repeatedly call the inputString() function for a 
	 	randomly generated string, and once this string equals "reset\0" and state equals 9. Then it will print the error. 

	 	Iteration 1: 17578 
	 	Iteration 2: 12837 
	 	Iteration 3: 52504 
	 	Iteration 4: 5117
	 	Iteration 5: 31262
		
		Average(iteration): 23859.6 
*/
