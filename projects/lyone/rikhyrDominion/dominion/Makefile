CFLAGS = -Wall -fpic -coverage -lm 

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)
	
#tester_dominion.o: tester_dominion.h tester_dominion.c rngs.o
#	gcc -c tester_dominion.c -g  $(CFLAGS)

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
	
compareStates.o: compareStates.h compareStates.c
	gcc -c compareStates.c -g $(CFLAGS)

unittest1: unittest1.c dominion.o rngs.o compareStates.o
	gcc -o unittest1 unittest1.c dominion.o rngs.o compareStates.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o compareStates.o
	gcc -o unittest2 unittest2.c dominion.o rngs.o compareStates.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o compareStates.o
	gcc -o unittest3 unittest3.c dominion.o rngs.o compareStates.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o compareStates.o
	gcc -o unittest4 unittest4.c dominion.o rngs.o compareStates.o $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o compareStates.o
	gcc -o cardtest1 cardtest1.c dominion.o rngs.o compareStates.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o compareStates.o
	gcc -o cardtest2 cardtest2.c dominion.o rngs.o compareStates.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o compareStates.o
	gcc -o cardtest3 cardtest3.c dominion.o rngs.o compareStates.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o compareStates.o
	gcc -o cardtest4 cardtest4.c dominion.o rngs.o compareStates.o $(CFLAGS)
	
randomtestcard1: randomtestcard1.c dominion.o compareStates.o	
	gcc -o randomtestcard1 randomtestcard1.c dominion.o rngs.o compareStates.o $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o compareStates.o	
	gcc -o randomtestcard2 randomtestcard2.c dominion.o rngs.o compareStates.o $(CFLAGS)

randomtestcard3: randomtestcard3.c dominion.o compareStates.o	
	gcc -o randomtestcard3 randomtestcard1.c dominion.o rngs.o compareStates.o $(CFLAGS)


runtests: testDrawCard 
	./testDrawCard > unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittestresults.out: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	./unittest1 > unittestresults.out
	gcov -b -c -f unittest1.c >> unittestresults.out
	./unittest2 >> unittestresults.out
	gcov -b -c -f unittest2.c >> unittestresults.out
	./unittest3 >> unittestresults.out
	gcov -b -c -f unittest3.c >> unittestresults.out
	./unittest4 >> unittestresults.out
	gcov -b -c -f unittest4.c >> unittestresults.out
	./cardtest1 >> unittestresults.out
	gcov -b -c -f cardtest1.c >> unittestresults.out
	./cardtest2 >> unittestresults.out
	gcov -b -c -f cardtest2.c >> unittestresults.out
	./cardtest3 >> unittestresults.out
	gcov -b -c -f cardtest3.c >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov -b -c -f cardtest4.c >> unittestresults.out
	gcov -b -c -f dominion >> unittestresults.out

randomtestcard1.out: randomtestcard1
	./randomtestcard1 > randomtestcard1.out
	gcov -b -c -f randomtestcard1.c >> randomtestcard1.out
	
randomtestcard2.out: randomtestcard2
	./randomtestcard2 > randomtestcard2.out
	gcov -b -c -f randomtestcard2.c >> randomtestcard2.out	
	
randomtestcard3.out: randomtestcard3
	./randomtestcard3 > randomtestcard3.out
	gcov -b -c -f randomtestcard3.c >> randomtestcard3.out
	
player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 unittestresults.out randomtestcard1.out randomtestcard2.out randomtestcard3.out

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 randomtestcard1 randomtestcard2 randomtestcard3 unittestresults.out randomtestcard1.out randomtestcard2.out randomtestcard3.out

