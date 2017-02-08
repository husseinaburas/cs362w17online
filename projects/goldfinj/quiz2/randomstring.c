/****************************************************
 * Name: Jason Goldfine-Middleton
 * Email: goldfinj@oregonstate.edu
 * Course: CS 362
 * Term: Winter 2017
 ****************************************************/

inputChar() simply returns a random ASCII character, which allows for 128
different possible characters.

inputString() returns a string containing random lowercase characters that
is just long enough to satisfy the checks in the error condition of testMe().
That is, it returns a string containing six characters, including the null
terminator.

Through initial test runs I was able to see that the value to the 'state'
variable quickly reaches 9, which is effectively a direct consequence of the
inputChar() function being able to return the different values 'c' has to
equal in order to increment 'state'.  It was not necessary to restrict the 
character set that could be returned by inputChar() too much because the
'state' variable reached 9 quickly. Therefore, the real bulk of the work
needed to produce the error message came from inputString().  In order to
reduce the amount of time needed to produce the array 's' = "reset", I chose
to restrict the range of characters in the random string to just lowercase
letters.

The following are a set of five runs of the main() function indicating the
number of iterations needed to bring about the error message:

Iteration 9525949: c = h, s = reset, state = 9
error

Iteration 37195753: c = x, s = reset, state = 9
error

Iteration 3866939: c = 0, s = reset, state = 9
error

Iteration 32142861: c = , s = reset, state = 9
error

Iteration 5719469: c = D, s = reset, state = 9
error
