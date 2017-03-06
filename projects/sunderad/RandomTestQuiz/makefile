default: prog

debug:
	gcc -Wall -std=c99 -o testme testme.c -coverage -fpic -lm

prog:
	gcc -Wall -std=c99 -o testme testme.c 
		
clean:
	rm testme

cleanall: 
	rm testme testme.gcda testme.gcno testme.c.gcov