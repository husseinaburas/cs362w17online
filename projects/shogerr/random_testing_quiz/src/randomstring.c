/*

Random Testing Quiz
Ross Shoger

For this problem we had access to the source of the program being tested; this
source is an accessible oracle that defines several constraints on the
generation process. The constraints offered are that the characters must be
of the ascii charset and must include the lower bound 'space' value of 32 and
upper of 127, sans the DEL byte.

From the oracle we also know the string to be guessed will be of a common
pattern: consonant, vowel, consonant, vowel, ...., repeating. The word is 5
characters.

This is an acceptable enough constraint, and reasonable given that Ascii readliy
supports the English character set.

We do not restrict the availability of vowels for 0 or the even positions, but
even elements of the inputString() return are always vowels.

This has the effect of limiting the range of generated words, but increases the
efficiency of the generation. For the test case provided we find that with
dynamic lengths of strings and no restrictions on generation pattern, the puzzle
will not be solved in any reasonable time period. Using the constraints provided
above we often find that our error can be thrown routinely under 200,000
iterations.

*/
