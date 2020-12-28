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
	./dijkstra single.0 > myOutSingle.txt
	./dijkstra two.0 > myOutTwo.txt
	./dijkstra unweighted.0 > myOutUnweighted.txt
	./dijkstra g6.0 > myOutG6.txt
	./dijkstra g7.0 > myOutG7.txt
	./dijkstra g8.0 > myOutG8.txt
	./dijkstra g9.0 > myOutG9.txt
	./dijkstra g10.0 > myOutG10.txt
	./dijkstra g11.0 > myOutG11.txt
	./dijkstra g12.0 > myOutG12.txt
	./dijkstra g13.0 > myOutG13.txt
	./dijkstra g14.0 > myOutG14.txt
	./dijkstra g15.0 > myOutG15.txt
	diff outSingle.txt myOutSingle.txt
	diff outTwo.txt myOutTwo.txt
	diff outUnweighted.txt myOutUnweighted.txt
	diff outG6.txt myOutG6.txt
	diff outG7.txt myOutG7.txt
	diff outG8.txt myOutG8.txt
	diff outG9.txt myOutG9.txt
	diff outG10.txt myOutG10.txt
	diff outG11.txt myOutG11.txt
	diff outG12.txt myOutG12.txt
	diff outG13.txt myOutG13.txt
	diff outG14.txt myOutG14.txt
	diff outG15.txt myOutG15.txt
