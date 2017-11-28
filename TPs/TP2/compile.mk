EXEC1 = procesar_tweets
EXEC2 = procesar_usuarios

CC = gcc
CFLAGS := -g -std=c99 -Wall
CFLAGS += -Wconversion -Wno-sign-conversion -Werror -Wbad-function-cast -Wshadow
CFLAGS += -Wpointer-arith -Wunreachable-code -Wformat=2
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes

all: $(EXEC1) $(EXEC2)

run_tweets: $(EXEC1)
	cat tweets.txt | ./$(EXEC1) 30000 100
	
time_tweets: $(EXEC1)
	cat tweets.txt | time ./$(EXEC1) 30000 100

valgrind_tweets: $(EXEC1)
	 less tweets_head.txt | valgrind $(VFLAGS) ./$(EXEC1)  30000 100
	
run_usuarios: $(EXEC2)
	./$(EXEC2) tweets.txt
	
time_usuarios: $(EXEC2)
	time ./$(EXEC2) tweets.txt

valgrind_usuarios: $(EXEC2)
	valgrind $(VFLAGS) ./$(EXEC2) tweets_head.txt
	
clean:
	rm -f $(wildcard *.o) $(EXEC1) $(EXEC2) 

$(EXEC1): procesar_tweets.c count_min_sketch.c strutil.c heap.c hash.c lista.c heap_aux.c
$(EXEC2): procesar_usuarios.c strutil.c hash.c lista.c heap_aux.c heap.c

