writestring.c

Royce Hwang
CS 362
Quiz 2
2/5/2017

The method inputChar() returns a random printable ASCII character (ASCII values
range from 32-127). This assumption reduces the number of total possible 
characters by more than half (original range would be from 0-255). The validity 
of this assumption is confirmed by looking at testme() and seeing that all of 
the conditions use characters within the ASCII range 32-127. 

The method inputString() returns a string of length 6 (including the '\0'
terminating character), where the first five characters in the string are random
characters returned by calls to inputChar(). Again, this method assumes that all
chars being used by the conditional check for the string are printable ASCII
characters (i.e. range from 32-127), which decreases the input space.
Additionally, by looking at the code in testme(), we can see that the string
being tested is of length 6, including the '\0' character, so we can make
testing faster by just creating random 5 letter strings with the last character
being '\0'. While it may not be justified in cases where we do not know enough
about the conditions of the software under test, this is necessary to make the 
test terminate in a somewhat reasonable time. This will be further discussed in
a later section below.

Looking at testme() itself, it is clear that in order to trigger the error 
message, a specific sequence of characters must be returned by inputChar() calls
in order to increment the state variable. This sequence is '[' -> '(' -> '{' ->
' ' -> 'a' -> 'x' -> '}' -> ')' -> ']'. If a character is returned from
inputChar() that does not match the next character in the sequence, the state 
variable is not incremented, and the loop will eventually iterate again without
doing anything else (since subsequent statements require the previous one to be
satisfied at least once). As mentioned before, we see that all of these chars
in the sequence are printable ASCII characters in the range 32-127, so I 
applied that simplification to the input space. While we could go even farther
and keep reducing the possible input chars returned by inputChar(), that carries
the risk of making the test too specialized for the specific problem. I felt
that this was a somewhat reasonable compromise between comprehensiveness and
speed.

As for inputString(), inspection of testme() shows that the string that forces
the error message is "reset", which is length 6 when '\0' is included. While
I had originally intended to randomize string lengths as well as characters,
I realized that this would add much more time than would be reasonable for
a short execise such as this, so the length of every string generated is 6.
Even though the input space is very large (96^5 possibilities, since the ASCII
range of 32-127 works out to 96 different chars), it is smaller than the one 
for a test using variable length strings (1 + 96^1 + 96^2 + ... 96^(n-1)), where
n is the length of the string including the '\0' char. This simplification of
harcoding string lengths can be justified by the fact that we were able to look
at the code being tested, but the same may not be true for black box testing,
which would necessitate a more general approach.

Even so, 96^5 possibilities works out to a 1/8153726976 chance of generating
the exact string that will trigger the error message. Rather than wait that
long for the result to show, I tested the program by hardcoding a string
"reset" and having inputString() return it, and testme() did print the error
message, as expected. While it is unrealistic, since real testing situations
are not nearly this straightforward, it does give me a high degree of
confidence that my test will eventually uncover the error message (without
having to run the program all night).
