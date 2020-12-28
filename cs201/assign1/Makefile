OBJS = comparator.o scanner.o real.o integer.o sll.o dll.o stack.o queue.o sqsort.o
OOPTS = -Wall -Wextra -g -c
LOPTS = -Wall -Wextra -g

all: sqsort 
sqsort : $(OBJS)
	gcc $(LOPTS) -o sqsort $(OBJS)

sll.o : sll.c sll.h
		gcc $(OOPTS) sll.c

dll.o : dll.c dll.h
		gcc $(OOPTS) dll.c

stack.o : stack.c stack.h
	gcc $(OOPTS) stack.c

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

sqsort.o : sqsort.c integer.h sll.h dll.h stack.h queue.h
	gcc $(OOPTS) sqsort.c


clean   :
		rm -f *.o sqsort 

test : 
	./sqsort -d testInteger1.txt
	./sqsort -d testInteger2.txt
	./sqsort -d testInteger3.txt
	./sqsort -d testInteger4.txt
	./sqsort -r testReal1.txt
	./sqsort -r testReal2.txt
	./sqsort -s testString1.txt
	./sqsort -s testString2.txt
