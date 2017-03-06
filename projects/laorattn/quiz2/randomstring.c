/*
Quiz 2: Namtalay Laorattanavech, ID:laorattn

Testme() function is a function that do the infinite while loop to check if the random inputs match its condition or not.
If the inputs match it condition, it will increment state counter by one from state 0-9, which make it 10 states in total.
There are two set of input. First is inputChar which can contains character between " "(ASCII 32) and "~"(ASCII 126).
Another input is inputString which is an array of string of length 6. Its first five characters can be any characters from
"a"(ASCII 97) to "z"(ASCII 122). The last character(inputString[6]) must be "\0".

From this information, I made the inputString() and inputChar() function to randomly generate characters that they required with 
rand function. They way rand function works is that it randoms a number in range of max-min+1 start from min.

After I ran the testme.c code, the test worked pretty well. It took a total of 5,804,191 tests to broke the condition and gave us an error.
It took most time of state 9, which made total sense since it had to perfectly generate the word "reset".
To sum up, this program has a very low chance of getting a bug. 1 out of 5.8m times or ~1.7*10^-7 % chances of getting a bug. Extreamly low in my opinion. 
*/