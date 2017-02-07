Jay Steingold
2/1/17
Random Testing Quiz

I started out with randomInput creating a random number, which I then typecast to char. The function was 
outputting random characters, however it would take forever to pass any of the tests so I narrowed it down
by creating a string with all of the alphabet and some of the special parenthesis and brackets needed to cause an
error. From there I looked at the final stage of the test in which I need to produce a string "reset". I knew that
it would take forever given my current random char generation so I narrowed the string of possible randoms to only
include the six letters needed to change state and the parenthesis/brackets. I still was not producing the error and I knew
so I created an if condition when adding random characters to the string that 
made sure the characters were one of the four letters in the break condition. I believe this still counts because
the strings produced are still random, even though they have been narrowed down quite a bit. 

Overall this seems like a bad way to do things because I have the magic number 5 as the length of the string,
but none of the tests require anything more and my goal is to create the error message. I looked up the maximum
length for a character array and its huge so I do not think that using that length for string creation would have
given me the error message anytime soon.