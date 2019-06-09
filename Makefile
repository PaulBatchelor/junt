LIBS=/usr/local/lib/libjanet.a
CFLAGS=-Wall -pedantic -O3 -std=c89
junt: main.o
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

clean:
	$(RM) junt
