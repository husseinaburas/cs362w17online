CS 362 Winter 2017
Random Testing Quiz 2

Instructions: 
	Write up the development of your random tester and how it finds the error message as randomstring.c. 
	The randomstring.c is a text file that outlines how you developed your solution and how it works!

Answer:
	How I developed my solution:
		How I developed inputChar() solution: Looked up how to randomly generate code (googled that statement
		and looked through a few stackoverflow posts).  Looked through the ASCII table to determine the range
		(limited the generator to commonly used characters so the testing would not take too long).

		How I developed inputString() solution: Looked up how to fill an array with characters (googled that
		statement and looked through a few stackoverflow posts).  Upon errors, I realized that I had to append
		a \0 at the end of the character arrays so that took a bit more research.

	How the code works:
		How inputChar() works: I use rand() function to generate a random character from the ASCII table 32 to 126.
		Then I return that randomly generated character.

		How inputString() works: I set an array that holds 6 elements because "reset" takes 5 and a "\0" at the end
		takes 1 more.  I then create a test word that contained the word we want to test for, and additional letters.
		I fill the array with a rand() that grabs 5 random letters from the test word, and I manually insert "\0" as 
		the last element.  Then I return at randomly generated 5-letter word.
