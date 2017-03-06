/*
 * Name: Grace Thompson
 * CS 362 Random Testing Quiz 2
 * randomstring.c
 * Explanation of Random Tester in testme.c
 *
 * Random input for inputChar():
      For this random character generator, in order to keep the test values relevant, I chose to use only the characters that were
      involved in the condition branches of testme(), plus one extra for testing values not listed in that function. Then, the
      function returns one randomly selected character from that list. This way, we can be sure that each of the characters
      in the branch statements will appear at least once in the iteration (they must appear at least once when the state value
      is at the appropriate value in order for the function to move forward, it will keep looping until that happens).
 * Random input for inputString():
      This function was a bit more complicated to figure out. The string only comes into play when the state variable is set to
      9, and the branch only executes if the string spells out 'reset' with a null terminator at the end. In order to keep the
      random set of strings produced to a reasonable amount, I decided to randomize the order of the characters in the set to
      form randomly created strings of varying length (as the null terminator is included in the randomized placement, some
      strings might be seen as fewer characters than others). Eventually, the characters will end up in spelling 'reset' and
      the error message executes.
 * How it works:
      When the testme.c program is compiled (gcc -std=c99 testme.c -o testme), it immediately begins grabbing the random values
      and checking against the if statements. Since state increments by 1 under specific conditions, the function must
      iterate over and over again until the conditions are met for each value of state up to 9, at which it iterates over
      and over until the string 'reset' is found. Running the program a few times, you can see that the number of iterations varies
      on execution, due to the random generation of the characters and strings. It may run maybe 300 times, it may run over 1000 times.
      Eventually, it always finds the error message.
 * Note: In order to free the memory allocated when creating the random strings, I added a line in the testme function
      that frees up the memory once it's done with it.
 *
 *
 *
 *
 *
*/
