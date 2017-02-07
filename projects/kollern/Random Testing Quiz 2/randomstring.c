/*
Random Testing Quiz 2
Name: Nick Koller
Description:
	Random Character Function:
		This function was designed using integer ASCII conversions via type casting 
		a randomly calculated int to a character. To include the blank space option I had to had a 
		bigger range than I did below in the independent string function. 
		
	Random String Function (dependant) (commented out):
		This version of my function accepted a passed parameter which will be the size of the random string 
		that will be returned from this function. It allocated memory for the string and assigned a \0 character
		to the final position. To randomize the selection it simply made calls to the above random character function.
	
	Bugs:	
		Memory Leak 
			After about 7 minutes and 32 million calls I hit a memory leak problem. I did not free the memory allocated 
			in the test me call. After the exeption call came, I tracked via Visual Studio process memory counter. 
		
		Resolution: Added free function call to testMe function and found out that my string wasn't actually being null terminated 
			since I was trying to add the null character to 1 position too far so I adjusted those.
		
	Random String Function (independant):
		This version of the string randomizer uses a fixed array of options and randomly selects one of the positions within that 
		array of lower case letters. I could adjust the ASCII values used above to be to be the lower case alphabet but I had 
		this system but I had this already designed and tested for a different program so I co-opted it for this aspect as an alternative
		independent test. I also replaced the arbitrary size checking with a fixed size of 5 to have it complete faster. 
		
		This is the approach I am using for the submission as it is significantly faster due to the restrictions I placed. 
		It finds the error message by checking these randomly assigned strings against the reset value.

Run Instructions:
	1. Use gcc to compile from the commandline by using the following command:
		gcc testme.c
	2. Followed by running the standard executable:
		a.out
*/