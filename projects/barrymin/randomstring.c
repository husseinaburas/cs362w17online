/*
Minna Barry
CS362 - quiz2

inputChar() uses rand() to produce random numbers between 32 and 126 which represent all non special ASCII characters.

inputString() creates a 5 character string and assign it random values that represent all the lower case alphabetic characters.

To reach the error, the program passes all states quickly since inputChar() returns random single characters. It then takes a long
time to reach the string combination that reaches the error since it returns a combination of 5 random characters each iteration.
It took the program 20435874 iterations to reach the error with this implementation. the following is the last few lines of the program's output and its execution time


Iteration 20435866: c = [, s = ymkxv, state = 9
Iteration 20435867: c = 5, s = lzizp, state = 9
Iteration 20435868: c = D, s = ergnv, state = 9
Iteration 20435869: c = j, s = nvwvz, state = 9
Iteration 20435870: c = H, s = cjrob, state = 9
Iteration 20435871: c = !, s = kycyr, state = 9
Iteration 20435872: c = d, s = xakjp, state = 9
Iteration 20435873: c = O, s = uxmpd, state = 9
Iteration 20435874: c = ~, s = reset, state = 9
error
Process returned 200 (0xC8)   execution time : 1221.977 s
Press any key to continue.

*/
