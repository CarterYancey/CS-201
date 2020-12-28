OBJS = comparator.o scanner.o real.o integer.o sll.o dll.o stack.o queue.o bst.o vbst.o rbt.o bstrees.o
OOPTS = -Wall -Wextra -g -c
LOPTS = -Wall -Wextra -g

all: bstrees 
bstrees : $(OBJS)
	gcc $(LOPTS) -o bstrees $(OBJS)

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

bst.o : bst.c bst.h
	gcc $(OOPTS) bst.c

vbst.o : vbst.c vbst.h
	gcc $(OOPTS) vbst.c

rbt.o : rbt.c rbt.h
	gcc $(OOPTS) rbt.c


bstrees.o : bstrees.c integer.h sll.h dll.h stack.h queue.h bst.h vbst.h rbt.h
	gcc $(OOPTS) bstrees.c


clean   :
		rm -f *.o bstrees 

test : 
	./bstrees -v corpus2.txt commands.txt
	./bstrees -r corpus2.txt commands.txt
	./bstrees -v sampleCorpus1.txt sampleCommands1.txt myOutput1.txt
	./bstrees -v sampleCorpus2.txt sampleCommands2.txt myOutput2.txt
	./bstrees -v sampleCorpus3.txt sampleCommands3.txt myOutput3.txt
	./bstrees -v sampleCorpus4.txt sampleCommands4.txt myOutput4.txt
	./bstrees -v sampleCorpus4.txt sampleCommands5.txt myOutput9.txt
	./bstrees -r sampleCorpus1.txt sampleCommands1.txt myOutput5.txt
	./bstrees -r sampleCorpus2.txt sampleCommands2.txt myOutput6.txt
	./bstrees -r sampleCorpus3.txt sampleCommands3.txt myOutput7.txt
	./bstrees -r sampleCorpus4.txt sampleCommands4.txt myOutput8.txt
	./bstrees -r sampleCorpus4.txt sampleCommands5.txt myOutput10.txt
	./bstrees -v clean.0 display btest3.txt
	./bstrees -r clean.0 display btest4.txt
	./bstrees -v spaces.0 display btest5.txt
	./bstrees -r spaces.0 display btest6.txt
	./bstrees -v empty commands.0 btest7.txt
	./bstrees -r empty commands.0 btest8.txt
	./bstrees -v s9.0 display btest9.txt
	./bstrees -r s10.0 display btest10.txt
	./bstrees -v s11.0 display btest11.txt
	./bstrees -r s12.0 display btest12.txt
	./bstrees -v s13.0 display btest13.txt
	./bstrees -r s14.0 display btest14.txt
	./bstrees -v s15.0 display btest15.txt
	./bstrees -r w16.0 display btest16.txt
	./bstrees -v w17.0 display btest17.txt
	./bstrees -r w18.0 display btest18.txt
	./bstrees -v w19.0 display btest19.txt
	./bstrees -r w20.0 display btest20.txt
	./bstrees -v w21.0 display btest21.txt
	./bstrees -r w22.0 display btest22.txt
	./bstrees -v w23.0 display btest23.txt
	./bstrees -r w24.0 display btest24.txt
	./bstrees -v clean.0 c25.0 btest25.txt
	./bstrees -r clean.0 c26.0 btest26.txt
	./bstrees -v clean.0 c27.0 btest27.txt
	./bstrees -r clean.0 c28.0 btest28.txt
	./bstrees -v clean.0 c29.0 btest29.txt
	./bstrees -r clean.0 c30.0 btest30.txt
	./bstrees -v clean.0 c31.0 btest31.txt
	./bstrees -r clean.0 c32.0 btest32.txt
	@echo dun dun dunnnnn
#	./bstrees -r shakespeare.txt shakespeare.display btest33.txt
	@echo dun dun dunnnnn
#	./bstrees -r beowulf.txt display btest34.txt
	./bstrees -r clean.0 c35.0 btest35.txt
	@echo Test 36 runs alternate code in graded version
	./bstrees -v clean.0 c36.0 btest36.txt
	./bstrees -v clean.0 c37.0 btest37.txt
	#Testing against existing files
	diff btest3.txt test3.txt
	diff btest4.txt test4.txt
	diff btest5.txt test5.txt
	diff btest6.txt test6.txt
	diff btest7.txt test7.txt
	diff btest8.txt test8.txt
	diff btest9.txt test9.txt
	diff btest10.txt test10.txt
	diff btest11.txt test11.txt
	diff btest12.txt test12.txt
	diff btest13.txt test13.txt
	diff btest14.txt test14.txt
	diff btest15.txt test15.txt
	diff btest16.txt test16.txt
	diff btest17.txt test17.txt
	diff btest18.txt test18.txt
	diff btest19.txt test19.txt
	diff btest20.txt test20.txt
	diff btest21.txt test21.txt
	diff btest22.txt test22.txt
	diff btest23.txt test23.txt
	diff btest24.txt test24.txt
	diff btest25.txt test25.txt
	diff btest26.txt test26.txt
	diff btest27.txt test27.txt
	diff btest28.txt test28.txt
	diff btest29.txt test29.txt
	diff btest30.txt test30.txt
	diff btest31.txt test31.txt
	diff btest32.txt test32.txt
#	diff btest33.txt test33.txt
#	diff btest34.txt test34.txt
	diff btest35.txt test35.txt
	diff btest36.txt test36.txt
	diff btest37.txt test37.txt
	@echo Testing Sequence complete.

showMyOutput :
	cat myOutput1.txt
	cat myOutput2.txt
	cat myOutput3.txt
	cat myOutput4.txt
	cat myOutput5.txt
	cat myOutput6.txt
	cat myOutput7.txt
	cat myOutput8.txt
	cat myOutput9.txt
	cat myOutput10.txt

showOutput :
	cat out1.txt
	cat out2.txt
	cat out3.txt
	cat out4.txt
	cat out5.txt
	cat out6.txt
	cat out7.txt
	cat out8.txt
	cat out9.txt
	cat out10.txt

diffOutputs :
	diff myOutput1.txt out1.txt
	diff myOutput2.txt out2.txt
	diff myOutput3.txt out3.txt
	diff myOutput4.txt out4.txt
	diff myOutput5.txt out5.txt
	diff myOutput6.txt out6.txt
	diff myOutput8.txt out8.txt
	diff myOutput9.txt out9.txt
	diff myOutput10.txt out10.txt
