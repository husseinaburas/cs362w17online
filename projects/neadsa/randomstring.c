I tackled the function inputChar() by simply producing a
random number in the range of 0 to 255. This produces characters
well past standard ASCII, most of which aren't even printable characters.
I made this decision as it was technically a fully random input.

However, on the other hand I wrote inputString() differently. I made the
decision to only have a character range of lowercase letters(97-122), as
it seemed the most logical given the constraints placed within testme().
Had the required characters fallen outside of this range I would've made
it differently.

With the given implementation for inputChar() and inputString(), on average
it was able to hit the error message in about 6.5 million iterations. Had I
opted to increase the randomization of inputString() it would've been
exponentially longer to hit the exit call. Thus, a smaller range of random
was required to hit the exit call in a semi-reasonable amount of time.
