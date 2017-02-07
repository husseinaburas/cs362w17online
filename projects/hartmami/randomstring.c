/*********************************************************************************
**
**  Author: Michael Hartman OSU ID# 932708868
**
**  Email: hartmami@oregonstate.edu
**
**  Date: 2017-02-02
**
**  Description: Random Testing Quiz 2
**
**********************************************************************************/

/*********************************************************************************

	I began by reading the testme() and main().  The main() calls testme(); in
	testme() there is a while loop that will continue forever unless the series of
	conditionals trigger the error message.  The conditionals involve the given
	char from inputChar(), an internal state varible, and the inputString().  To
	trigger the error message and break the loop the input char must set the state
	to: 9 and the string must be: 'reset\0'.

	The directions indiciate that our implementation of the functions should
	produce random values.  Using all possible character values would make
	the program take longer to display the error message.  For this reason I
	limited the domain of both the inputChar and inputString to only those
	characters which are used in the testme() conditionals.

	For inputChar these are:
		'[','(','{',' ','a','x','}',')',']'

	For inputString these are:
		'r', 'e', 's', 't', '\0'

	By limiting the domain in such a way; the error is usually produced in under
	10000 iterations.  Using a larger domain for the input characters should
	produce the same result after a much larger number of iterations.  It is also
	important to recoginize that the input domains used here are the bare minimum
	to trigger the error message.  If any character is removed it will not be
	triggered.

	To compile and run on flip:

	ensure testme.c is in the current directory

	gcc testme.c -o tester

	tester

**********************************************************************************/
