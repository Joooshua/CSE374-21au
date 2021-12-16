OPTS = -g -Wall -std=c11

all: t9

t9: main.o Trie.o
	gcc $(OPTS) -o t9 main.o Trie.o

main.o: main.c Trie.h
	gcc $(OPTS) -c main.c

Trie.o: Trie.c Trie.h
	gcc $(OPTS) -c Trie.c

clean:
	rm *.o