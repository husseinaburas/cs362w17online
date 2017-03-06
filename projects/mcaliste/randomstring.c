// randomstring.c

My initial idea was to generate two sets of numbers:
- 0 through 125 for inputChar()
- 0 through 122 for inputString()

For the first, I then shifted the valid range to 32-125, which would encapsulate
all of the characters needed for the first set of character states 1-9.  This
one was pretty straightforward and generated the necessary characters.  I had
some minor difficulty printing the ASCII characters from their integer
counterparts using the int + '0' trick, so I went for casting them to char with
(char) instead.  This got states 1-9 working.

After that, I used the same idea to generate numbers that corresponded to 'a'
through 'z' lowercase (97 - 122).  However, after many tests that went through
a few million iterations, it was pretty clear that the chances of generating a
specific series of 5-letters of a real word was pretty low.  I found a website
that demonstrated the chance of randomly generating ANY 5-letter word to be
about 0.3%.  With chances that low, I instead went to the approach of generating
random series of characters with 'e', 'r', 's' and 't', just to ensure it was
working correctly.  At this point, it worked properly in roughly 1000
iterations.  This is where I ultimately stopped.

This test could potentially be improved by weighting certain letters with their 
relative frequencies in the English language, but this is kind of outside the
scope of this assignment and would require a lot more work for each letter.
