
# makefile heap

TARGET= genHeap.out
CC= gcc
CFLAGS= -ansi -g -pedantic 
OBJS= genHeap.o genHeap_test.o genericVector.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

genHeap.o: genHeap.c genHeap.h genericVector.h
	$(CC) $(CFLAGS) -c genHeap.c
	
genHeap_test.o: genHeap_test.c genHeap.h genericVector.h
	$(CC) $(CFLAGS) -c genHeap_test.c

genericVector.o: genericVector.c genericVector.h 
	$(CC) $(CFLAGS) -c genericVector.c

	
clean:
	rm -f $(TARGET) $(OBJS)
