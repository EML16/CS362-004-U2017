CFLAGS = -Wall -fpic -coverage -lm

testme: testme.o
	gcc -o $@ $<

%.o: %.c
	gcc -c -g  -o $@ $<

clean:
	rm -f *.o
