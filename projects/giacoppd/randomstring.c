Quick question: why is this a .c of all things? But anyways

inputChar: Picks a char randomly from a set pre selected by myself tailored to what actually progresses the states. 
It's not really that random a selection of characters, but in general I find it to take upwards of 1 million tries to 
complete anyways, so I consider it to be more that I used prudence in selecting a more applicable range of inputs 
than literally anything possible. 

inputString: Calls inputChar 5 times to fill a string, then tacks a null term on the end. Again, not the most random
it could be, I could have given it variable length. But I will play the prudent range of input card; if the program
is designed to only strings up to length 5, then there is no reason to test for longer than 5.
