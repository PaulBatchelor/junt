LIBS=/usr/local/lib/libjanet.a
CFLAGS=-Wall -pedantic -O3 -std=c99
CFLAGS += -I$(HOME)/.runt/include
LIBS += -L$(HOME)/.runt/lib -lrunt

OBJ=main.o

junt: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

clean:
	$(RM) junt
	$(RM) main.o
