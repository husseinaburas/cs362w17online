// Written by: Adam Sunderman
//----------------------------------------------------------------------------------------------------------------------------------
// The function inputString() uses the function inputChar() to build up it's random strings. Both functions 
// track the state number of the test loop to set some conditions upon the string that is built. If the test
// loop is in state 0 through 8 then inputChar() will produce a random character or symbol from ASCII 32(dec) to 126(dec)
// and inputString() will create a random string length string anywhere from 1 to 10 characters in length. If the 
// test loop state is 9 then inputChar() will only use lowercase letters ASCII 97(dec) to 122(dec) and inputString() 
// will only build strings of length 5. This still keeps a level of randomness to the strings but there needed to be 
// these extra conditions in order to randomly create the string 'r''e''s''e''t' in a reasonable amount of time. 
//----------------------------------------------------------------------------------------------------------------------------------
//==================================================================================================================================
//----------------------------------------------------------------------------------------------------------------------------------
// There is a make file included in this directory just enter the command 'make' to build and then enter './testme' to run the test.
// If you wish to have coverage information available then enter 'make debug' instead to build.
//----------------------------------------------------------------------------------------------------------------------------------