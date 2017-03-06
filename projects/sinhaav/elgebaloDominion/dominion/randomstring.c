Omar Elgebaly
Random Testing Quiz

Description: Implement a random tester for the function testme() in testme.c that is capable of printing the error message.  You should implement inputChar() and inputString() to produce random values. Write up the development of your random tester and how it finds 
the error message as randomstring.c. Submit testme.c and randomstring.c under your onid directory in class github. (under your onid directory and not under dominion directory).

For the inputChar() function, I used the rand function to get a random number between 32 and 126.
For the inputstring() function, I created an array of chars that will store the characters that the testme() function will
find before it prints out an error. Then, I allocated space for the randomstring array as it is used in a for loop that iterates
through the array of random chars and stores the values until the program prints error