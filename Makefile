CFLAGS = -Wall
LIBS = -lm

mainTest: mainTest.o tile.o error.o coordinate.o
	gcc -o $@ $^ $(LIBS)

clean:
	rm *.o mainTest
