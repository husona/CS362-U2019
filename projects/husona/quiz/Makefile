CFLAGS= -g -Wall -fpic -coverage -lm -std=c99
	
testme : testme.c
	gcc -o testme testme.c $(CFLAGS)  
	testme
	gcov testme.c -b -f
	
all : testme

clean :
	rm -f testme *.gcov *.gcno *.gcda