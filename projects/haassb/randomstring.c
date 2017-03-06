Benjamin Haass
Quiz 2

The testme function consists of 2 sections of logic that must be navigated successfully in order to produce the error message. The first section consists of a series of if statements,
that iterate and increment a counter called 'state' when the randomly generated character is equal to various ASCII characters. Only once all the characters match the logical tests can 
the state variable be incremented successfully to allow control to flow to the next section of logic. The second section of logic is triggered once the state reaches the last increment. 
At that point, the randomly generated string is checked to see if it equals "reset\0", and if so, the error message is triggered. 

A random test to successfully trigger the error message will have to first properly generate the proper combination of ASCII characters and then generate the string "reset". Because it
is a random test, I couldn't hard-code in the characters for the first logical test or hard-code the "reset" string for the second test. Accordingly, I took the brute force approach.
For the first function, inputchar(), I applied a random number generator to generate ASCII codes. In order to reduce the run time of the brute force test, I limited to ASCII codes to
only printable characters. For the second function, inputstring(), I applied create a random string, where each character of the string is sourced from a randomly generated ASCII code.
In order to further limit the run time of the brute force test, I limited the random string to 5 characters long (excluding the null terminator), and I limited the possible characters
to only alphabetic characters. 

Sources Cited:
http://www.ascii-code.com/
http://stackoverflow.com/questions/7560114/random-number-c-in-some-range
http://stackoverflow.com/questions/2911089/null-terminating-a-string
https://www.tutorialspoint.com/cprogramming/c_for_loop.htm
http://stackoverflow.com/questions/17312336/warning-function-returns-address-of-local-variable-enabled-by-default
http://stackoverflow.com/questions/1856599/when-to-use-static-keyword-before-global-variables
