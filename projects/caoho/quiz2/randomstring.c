/*
 *  randomstring.c
 *
 *  Created on: Feb 5, 2017
 *  Author: caoho
 *	course: CS 362 Software Engineering II
 *	Random Testing Quiz 2
 *
 *	In order to identify the errors, I firstly implement the inputChar() method.
 *	I cite the maximum and minimum printable characters value of ascii-code table (http://www.ascii-code.com/).
 *	I find the maximum printable character is '~', which is 126, and the minimum printable characters is ' ', which is 34.
 *	So, I identified the range of the testme() method is accessible.
 *	I randomly get one character from the inputChar method, and put it into the String.
 *
 *	Secondly, I implemented the function inputString(). In order to stop the testme function, I use a random generator to obtain an integer,
 *	if the result of this integer mod 1000 is 1, then I will set the string value into the "reset", which will make the testme() method exit.
 *	Furthermore, I defined the output string length = 6, and in build up a loop to obtain one character from the inputChar(). And the final combination
 *	of these characters will be treated as output.
 *
 *	When running testme, the program would generally exit in around 1000~1500 iterations.
 */


