/*
Goal: Implement inputChar() and inputString() so that testme() prints the "error" message.

Explanations:
-- inputChar() and inputString() are random character/string generators, respectively. 
-- testme() runs an infinite loop, where each iteration calls inputChar() and inputString() 
to generate a random character c and a random string s, respectively.
-- the loop in testme() is terminated when the following conditions are met:
	+) The following values are generated for c, in that order but not nessarily consecutive:
			'[', '(', '{', ' ', 'a', 'x', '}', ')', ']'
	+) Once the above condition is satisfied, the first 6 characters of s have generated
		value 'r', 'e', 's', 'e', 't', '/0', in that order.
-- upon termination, testme() prints the message "error" and exits the program.

Outline of development:
-- I noted that inputChar() is only used to generate one character c, and inputString() to generate
one string s. I also noted that only the first 6 characters of s are used, thus it's OK for
inputString() to return a 6-character string (or 5-character with the last character being '/0').
-- I initially implemented inputChar() to return a random character chosen in the full ASCII 
character range (32-126), and inputString() to return a random 5-character, null-terminated string
constructed from the full ASCII range. This took the program to run many (trillions?) unsuccessful
iterations. I terminated the program after 30 seconds without successfully printing "error".
-- I then realized inputChar() and inputString() could be implemented more efficiently, as the only
relevant characters (i.e. those values of c that get tested and that push testme() closer to 
termination) are those in the set:
			'[', '(', '{', ' ', 'a', 'x', '}', ')', ']'		(I)
Likewise, the only relevant letters for the outputs of inputString() are those in the set:
			'r', 'e', 's', 't', '/0'						(II)
-- Following this observation, I implemented inputChar() to return only values in set (I),
and inputString() to construct values only from set (II). This significantly improves runtime; my
five test runs both have the program print "error" within 3000 iterations.
*/

