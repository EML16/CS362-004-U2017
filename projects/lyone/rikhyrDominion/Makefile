CFLAGS = -Wall -fpic -coverage -lm

rngs.o: dominion/rngs.h dominion/rngs.c
	gcc -c dominion/rngs.c -g  $(CFLAGS)

dominion.o: dominion/dominion.h dominion/dominion.c rngs.o
	gcc -c dominion/dominion.c -g  $(CFLAGS)

playdom: dominion.o dominion/playdom.c
	gcc -o playdom dominion/playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: dominion/testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  dominion/testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: dominion/badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  dominion/badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: dominion/testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  dominion/testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o dominion/testSuite.c
	gcc -o testSuite dominion/testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: dominion/interface.h dominion/interface.c
	gcc -c dominion/interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion/dominion.c >> unittestresult.out
	cat dominion/dominion.c.gcov >> unittestresult.out


player: dominion/player.c interface.o
	gcc -o player dominion/player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

################################################################################
# Unit Tests (Assignment 3)
################################################################################
asserttrue.o: asserttrue.h asserttrue.c
	gcc -c asserttrue.c $(CFLAGS)

unittest1: dominion.o unittest1.c asserttrue.o
	gcc -o unittest1 unittest1.c dominion.o rngs.o asserttrue.o $(CFLAGS)
unittest2: dominion.o unittest2.c asserttrue.o
	gcc -o unittest2 unittest2.c dominion.o rngs.o asserttrue.o $(CFLAGS)
unittest3: dominion.o unittest3.c asserttrue.o
	gcc -o unittest3 unittest3.c dominion.o rngs.o asserttrue.o $(CFLAGS)
unittest4: dominion.o unittest4.c asserttrue.o
	gcc -o unittest4 unittest4.c dominion.o rngs.o asserttrue.o $(CFLAGS)

unittestresults.out: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	./unittest1 > unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	gcov dominion/dominion.c >> unittestresults.out
	cat dominion/dominion.c.gcov >> unittestresults.out

################################################################################

################################################################################
# Random Tests (Assignment 4)
################################################################################

randomtestcard1: randomtestcard1.c asserttrue.o dominion.o rngs.o
	gcc -g -o randomtestcard1 randomtestcard1.c dominion.o rngs.o asserttrue.o $(CFLAGS)

randomtestcard2: dominion.o randomtestcard2.c asserttrue.o rngs.o
	gcc -g -o randomtestcard2 randomtestcard2.c dominion.o rngs.o asserttrue.o $(CFLAGS)

randomtestadventurer: dominion.o randomtestadventurer.c asserttrue.o rngs.o
	gcc -g -o randomtestadventurer randomtestadventurer.c dominion.o rngs.o asserttrue.o $(CFLAGS)

randomtestcard1.out: randomtestcard1
	./randomtestcard1 > randomtestcard1.out
	gcov -f dominion/dominion.c >> randomtestcard1.out 
	cat dominion/dominion.c.gcov >> randomtestcard1.out 

randomtestcard2.out: randomtestcard2
	./randomtestcard2 > randomtestcard2.out
	gcov -f dominion/dominion.c >> randomtestcard2.out 
	cat dominion/dominion.c.gcov >> randomtestcard2.out 

randomtestadventurer.out: randomtestcardadventurer
	./randomtestcardadventurer > randomtestcardadventurer.out
	gcov -f dominion/dominion.c >> randomtestcardadventurer.out 
	cat dominion/dominion.c.gcov >> randomtestcardadventurer.out 

################################################################################

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
