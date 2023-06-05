
# makefile BSTree

TARGET= BSTree.out
CC= gcc
CFLAGS= -ansi -g -pedantic
OBJS= BSTree.o BSTree_test.o 

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

BSTree.o: BSTree.c BSTree.h
	$(CC) $(CFLAGS) -c BSTree.c
	
BSTree_test.o: BSTree_test.c BSTree.h
	$(CC) $(CFLAGS) -c BSTree_test.c
	
clean:
	rm -f $(TARGET) $(OBJS)