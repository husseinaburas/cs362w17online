Allister Laurel
CS 362
Random Testing Quiz 2

For inputChar(), the char will randomly generate numbers between 0 and 94. Because 
the ACII table has 128 characters, the first 32 are control characters that I 
elimiated from the random generator. First I divided the randomizer by 128-33 
which gives 95 and the range of 0-94. Then I added 32 so the characters will 
be printable. Finally it returns the random character. 

For inputString(), I initially created a char of 5 characters that held each 
of the letters in "reset" to end the program (r,e,s,t) plus the null terminator. 
I created a second char array to hold all of the indexed chars that contain all 
of the characters from the first array. Then I had to allocated memory for the 
return string. After that, I created a for loop that will take the characters 
from the set of characters into the return string. And finally, the last index 
is set to the null terminator. 