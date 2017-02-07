Ben Ford
2/5/2017
Random Testing Quiz

The first part of testme looks a the output of inputChar(). There are 9 states that cascade if the previous state is meet. 
inputChar has a random char generator that will create a char that has an asciii value between 32 (space) and 126(~). Once a state is meet
the state increases up until the state is 9.

The second part of testme looks at a random string that is the output of inputString(). inputString creates a string that is 5 chars and a null terminator.
The way the string is generated is by appending  random chars with ascii values between 97 (a) and 122(z). During the main loop an error gets throwin if the string
is reset\0.  When I tested my code it took 20530718 iterations before I cuaght the error.