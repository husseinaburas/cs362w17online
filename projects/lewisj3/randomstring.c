I set the range of values that inputChar() gives to be from 0 - 127 which is regular ASCII. 
The domain of strings that inputString() returns is:
	a 6 byte string always with the last byte being the null terminator
	and
	each character other than the null terminator is a random character between 96 and 127 which is essentially just all lowercase letters.
This works because the error only relies on getting a string that is 'reset' with a null terminator when the state is 9.
We reach state 9 by getting all of the necessary chars from inputChar() which we will get because the range it outputs includes all of these characters.