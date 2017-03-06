/* CS362-400-W17 Software Engineering II
   Chris Kearns (kearnsc@oregonstate.edu
   Quiz 2 discussion on testme.c

1. What are we testing?

We are given a function testme() that receives it's inputs via calls to inputChar() and inputString().
An inspection of testme()'s code reveals its purpose is as a guard that prints an error message
followed by a system exit if a specific set of characters, namely the set:

{ "[", "]", "(", ")", "{",  "}", ' ', "a", "x" }

is received followed by a specific string of length 6, equivalent to "reset\0".

2. How shall we test it?

We note that for the error to be generated, the expectation is the individual character input from
the set { "[", "]", "(", ")", "{",  "}", ' ', "a", "x" } must be made, but that the variable
"state" retains its incrementing value, thus "walks up" to state == 9.  Once this occurs, the
random string s can be evaluated since the last test condition evaluated is "does state == 9".

Further, this observation reveals that simply repeatedly injecting the set { "[", "]", "(", ")",
"{",  "}", ' ', "a", "x" } as input in a random fashion will in short order "walk" state up to 9.
Then, the characters r, e, s, t, and '\0' randomly introduced via function inputString() as a 
combination are evaluated - essentially choose a specific 6 chars from the set of input characters,
choices are not exclusive, that is a character choice once made can be made again.

The final observation is the set of characters to be introduced to the testme() function must 
include the combined aforementioned set in combination with the set { "r", "e", "s", "t", '\0' }.
If we combine these into one required input set, we have { "[", "]", "(", ")", "{",  "}", ' ',
"a", "x",  "r", "e", "s", "t", '\0' }. Since the final if statement in function testme() tests a
string, we shall omit the null terminator and assume the string was properly formed.  Our 
inputString() function is thusly designed - the string terminator is always '\0'.  Obviously, 
there could be cases where the string is not formed correctly, that is, without a null terminator,
but in that case, function testme() would never generate the error.  We shall test for that case,
just to see.

3. Results of these ideas and the chosen testing method.

Initially, we injected the entire ASCII set of characters as input to the testme() function.
This ran on a flip server, but for an excessively long period of time and at iteration
1,000,000+ was stopped by the tester since the PuTTy terminal window repeatedly became unstable.
It would have eventually worked, but it's unlikely this approach would prove satisfactory.
One additional piece of information that could be sought by the tester is what is the character
set the function could conceivably be exposed to.  

Working our way down to just the random input of the combined character set from above, in random
fashion, proved most effective, that is, proving testme() would indeed produce the error given a
random set of characters that contain the combined character set [and in a reasonable period of
time].

Average iterations on a 20 attempt test battery is typically under 100,000 and thus a matter of
seconds, but was observed to run as many as approximately 750,000 iterations before the error 
message was generated.  Clearly, the more characters contained in the input set, the longer the 
number of iterations and time required to generate the error message.  Also, omitting the '\0'
string terminator resulted in early termination by the tester as the behaviour is similar to not
having one of the required characters in the input set. Additionaly, randomly introducing '\0' with 
the idea of randomly generating the final string terminator proved inneffective.  The test ran,
but many strings were diplayed as "short terminated", and thus while just the right combination 
could eventually be achieved, it's unlikely the time to do so would be satisfactory.

Note: testme() was modified with two calls of free(s); in order to pass Valgrind memory testing.
*/