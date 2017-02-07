/*

Antonina (Toni) York
OSU CS 362 Winter 2017
Random Testing Quiz
randomstrings.c

"Description: Implement a random tester for the function testme() in testme.c
that is capable of printing the error message.  You should implement inputChar()
and inputString() to produce random values. Write up the development of your
random tester and how it finds the error message as randomstring.c. Submit
testme.c and randomstring.c under your onid directory in class github. (under
your onid directory and not under dominion directory). The randomstring.c is a
text file that outlines how you developed your solution and how it works!"

The function testme() runs a loop that generates random characters and strings
and then checks these inputs for certain conditions. The loop exits with "error"
when a very specific set of conditions has been met in order by these random
inputs. The function uses a state variable to track how many of the following
list of conditions have been met. The conditions must be met in order, but there
can be any number of loop iterations with non-matching inputs in between valid
condition matches.

    Ordered List of Conditions
    --------------------------
      1. the character is '['
      2. the character is '('
      3. the character is '{'
      4. the character is ' '
      5. the character is 'a'
      6. the character is 'x'
      7. the character is '}'
      8. the character is ')'
      9. the character is ']'
     10. the string is "reset"

In order to randomly test the function and have a reasonable chance of seeing
these conditions met, we need to randomly generate these character and string
inputs such that they are likely to appear in this specific order within a
reasonable amount of time. I suspect that using the full set of 128 ASCII
characters to choose from is unlikely to do this. Since there are five letters
in the word reset, there is only a 1 in 128^5 = 34,359,738,368 chance of that
word being the generated string.

Instead, I implemented inputChar() to generate a character out of a set that
includes only those 13 characters that testme() seems to care about: ' ', 'a',
'e', 'r', 's', 't', 'x', '(', ')', '[', ']', '{', and '}'. I then implemented
inputString() to call inputChar() to pick five random characters from this set
to make up its generated string. Using this limited input set of only 13
characters, that gives inputString() a 1 in 13^5 = 371,293 chance of generating
the word reset.

I ran this random tester 10 times and saw the following results. The single
character conditions are met very quickly, since there is a 1 in 13 chance of
each of them occurring at each step. The program then spends a while in state 9,
waiting for inputString() to generate the word reset. When the word is finally
generated, the final condition is met and the program exits with an "error"
message. In ascending order, the following is the list of iteration numbers on
which each of the 10 test runs stopped.

    Iteration Number
    ----------------
         113,961
         221,749
         288,622
         312,811
         338,021
         559,607
         691,706
         696,435
       1,048,342
       1,166,200

This is an average of 474,574.8 iterations, which is roughly in the ballpark I
expected. The longest of the runs still took less than a full minute, which met
my goal for achieving the desired conditions in a reasonable amount of time.
Since it should take, on average, about 92,540 times longer using the full ASCII
character set to achieve the same result, that gives a rough estimate of around
2 months to run such a test. Considering this, I feel justified in using the
reduced set of 13 characters for this random tester.

*/