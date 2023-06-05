
# makefile BSTree

TARGET= genQueue.out
CC= gcc
CFLAGS= -ansi -g -pedantic
OBJS= genQueue.o genQueue_test.o 
VECTOR_PATH=../genVector


$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

BSTree.o: genQueue.c genQueue.h
	$(CC) $(CFLAGS) -I $(VECTOR_PATH) -c genQueue.c
	
BSTree_test.o: genQueue_test.c genQueue.h
	$(CC) $(CFLAGS) -I $(VECTOR_PATH) -c genQueue_test.c
	
clean:
	rm -f $(TARGET) $(OBJS)
