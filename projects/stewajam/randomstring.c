I implemented my random tester as follows:

inputChar()
I calculated the ascii values for the characters that testme() was checking against and generated a random value with the range. This value was returned to testme().


inputString()
I calculated the ascii values for lower-case letters and created a string with 5 characters (+ 1 null character). I utilized a for loop to generate 5 random characters to populate the string. A pointer to the string was returned to testme().