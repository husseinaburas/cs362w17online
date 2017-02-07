Steven Hunt
Quiz 2

Random testing for testme.c

inputChar():
 testme() must pass through several characters which range from SPACE to an end curly bracket before it is complete, thus inputChar() returns a character from ASCII 32 (' ') to ASCII 125 ('}').

inputString():
 These values must pass through the range of letters in "reset" (e - 101 - through t - 116). The for loop generates a string of characters in this range.

The narrowing of the character selection is not as random as could otherwise be achieved with a larger sample, but it is more time efficient.
