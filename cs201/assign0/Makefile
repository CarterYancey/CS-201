OBJS = integer.o sll.o test-sll.o
OBJS2 = integer.o dll.o test-dll.o
OBJS3 = integer.o dll.o stack.o test-stack.o
OBJS4 = integer.o sll.o queue.o test-queue.o
OOPTS = -Wall -Wextra -g -c
LOPTS = -Wall -Wextra -g

all : test-sll test-dll test-stack test-queue
test-sll : $(OBJS)
	gcc $(LOPTS) -o test-sll $(OBJS)

test-dll : $(OBJS2)
	gcc $(LOPTS) -o test-dll $(OBJS2)

test-stack : $(OBJS3)
	gcc $(LOPTS) -o test-stack $(OBJS3)

test-queue : $(OBJS4)
	gcc $(LOPTS) -o test-queue $(OBJS4)

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

test-sll.o : test-sll.c integer.h sll.h
		gcc $(OOPTS) test-sll.c

test-dll.o : test-dll.c integer.h dll.h
		gcc $(OOPTS) test-dll.c

test-stack.o : test-stack.c integer.h dll.h stack.h
	gcc $(OOPTS) test-stack.c

test-queue.o : test-queue.c integer.h sll.h queue.h
	gcc $(OOPTS) test-queue.c

clean   :
		rm -f $(OBJS) $(OBJS2) $(OBJS3) $(OBJS4) test-dll test-stack test-queue test-sll

test : 
		./test-sll
		./test-dll
		./test-stack
		./test-queue
