CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out
	
randomtestresults: dominion.o randomtestcard1.c
	echo "randomtestcard1.c:" &> randomtestresults.out
	gcc -g -o randomtestcard1 rngs.c dominion.c randomtestcard1.c $(CFLAGS)
	randomtestcard1 >> randomtestresults.out
	gcov dominion.c -b -f >> randomtestresults.out
	
	echo "randomtestcard2.c:" >> randomtestresults.out
	gcc -g -o randomtestcard2 rngs.c dominion.c randomtestcard2.c $(CFLAGS)
	randomtestcard2 >> randomtestresults.out
	gcov dominion.c -b -f >> randomtestresults.out
	
	echo "randomtestcard3.c:" >> randomtestresults.out
	gcc -g -o randomtestcard3 rngs.c dominion.c randomtestcard3.c $(CFLAGS)
	randomtestcard3 >> randomtestresults.out
	gcov dominion.c -b -f >> randomtestresults.out
	
unittestresults: unittest1.c unittest2.c unittest3.c unittest4.c unittest5.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c cardtest5.c dominion.o
	echo "unittest1.c:" &> unittestresults.out
	gcc -o unittest1 dominion.c rngs.c unittest1.c -g $(CFLAGS)
	unittest1 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out

	echo "unittest2.c:" >> unittestresults.out
	gcc -o unittest2 dominion.c rngs.c unittest2.c -g $(CFLAGS)
	unittest2 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out

	echo "unittest3.c:" >> unittestresults.out
	gcc -o unittest3 dominion.c rngs.c unittest3.c -g $(CFLAGS)
	unittest3 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out

	echo "unittest4.c:" >> unittestresults.out
	gcc -o unittest4 dominion.c rngs.c unittest4.c $(CFLAGS)
	unittest4 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out

	echo "unittest5.c:" >> unittestresults.out
	gcc -o unittest5 dominion.c rngs.c unittest5.c -g $(CFLAGS)
	unittest5 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out

	echo "cardtest1.c:" >> unittestresults.out
	gcc -o cardtest1 dominion.c rngs.c cardtest1.c -g $(CFLAGS)
	cardtest1 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out

	echo "cardtest2.c:" >> unittestresults.out
	gcc -o cardtest2 dominion.c rngs.c cardtest2.c -g $(CFLAGS)
	cardtest2 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out

	echo "cardtest3.c:" >> unittestresults.out
	gcc -o cardtest3 dominion.c rngs.c cardtest3.c -g $(CFLAGS)
	cardtest3 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out

	echo "cardtest4.c:" >> unittestresults.out
	gcc -o cardtest4 dominion.c rngs.c cardtest4.c -g $(CFLAGS)
	cardtest4 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out

	echo "cardtest5.c:" >> unittestresults.out
	gcc -o cardtest5 dominion.c rngs.c cardtest5.c -g $(CFLAGS)
	cardtest5 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe unittest1 unittest2 unittest3 unittest4 unittest5 cardtest1 cardtest2 cardtest3 cardtest4 cardtest5 unittest1.exe unittest2.exe unittest3.exe unittest4.exe unittest5.exe cardtest1.exe cardtest2.exe cardtest3.exe cardtest4.exe cardtest5.exe randomtestcard1 randomtestcard1.exe randomtestcard2 randomtestcard2.exe randomtestcard3 randomtestcard3.exe
