CFLAGS = -Wall -Wshadow -O3 -g -march=native
LDLIBS = -lm

example: example.o fft.o

clean:
	$(RM) *.o
	$(RM) example fft *.exe