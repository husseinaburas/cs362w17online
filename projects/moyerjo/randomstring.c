The random testing quiz required generating a random character and a random string.
While there were no stated restrictions on the information, the character was
returned as a character, while the string was returned as a character pointer.
There were some options here to choose how to approach it. While one option was to
make inputChar() just generate any random character (and then use it to generate
random characters for inputString), but since inputChar() only needed to make a
handful of potential characters, I opted to just have it generate the characters
that were potentially useful, "[]{} ax()" (in hindsight, I probably could have done the full
range of characters from 0 - 126, but it would just have slowed reaching stage 9
in reality.)  For inputString I generated a random 5 digit alphabetic lowercase
string and returned it.  Again, I could have generated the full range of ascii
characters, but that would have slowed down finding the result.  While it wouldn't
have taken much longer to find the result doing this, I was worried about the fact
I created a mem leak in the program as it seemed to be the easiest way to approach
the restricted function layout.  Personally, I would have passed in the char* to
avoid a mem leak.  Since that was a concern, I opted for the fastest method to find
solution.  26^5 potential strings (around 11 million) with my method versus 126^5 (around 
30 billion) doing the full lower range of ascii codes.