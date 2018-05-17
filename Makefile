CFLAGS = -Wall
LIBS = -lm

mainTest: mainTest.o tile.o error.o
	gcc -o $@ $^ $(LIBS)

clean:
	rm *.o mainTest
