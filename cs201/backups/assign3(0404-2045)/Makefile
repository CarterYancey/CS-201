OBJS = comparator.o scanner.o real.o integer.o sll.o queue.o darray.o binomial.o dijkstra.o
OOPTS = -Wall -Wextra -g -c
LOPTS = -Wall -Wextra -g

all: dijkstra
dijkstra : $(OBJS)
	gcc $(LOPTS) -o dijkstra $(OBJS)

sll.o : sll.c sll.h
		gcc $(OOPTS) sll.c

queue.o : queue.c queue.h
	gcc $(OOPTS) queue.c

integer.o : integer.c integer.h
		gcc $(OOPTS) integer.c

real.o : real.c real.h
		gcc $(OOPTS) real.c

scanner.o : scanner.c scanner.h
	gcc $(OOPTS) scanner.c

comparator.o : comparator.c comparator.h
	gcc $(OOPTS) comparator.c

darray.o : darray.c darray.h
	gcc $(OOPTS) darray.c

binomial.o : binomial.c binomial.h
	gcc $(OOPTS) binomial.c

dijkstra.o : dijkstra.c integer.h sll.h queue.h darray.h binomial.h
	gcc $(OOPTS) dijkstra.c


clean   :
		rm -f *.o dijkstra 

test	:
		./dijkstra g1.txt
