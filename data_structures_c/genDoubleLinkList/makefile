# makefile genList

TARGET= genList.out
CC= gcc
CFLAGS= -ansi -g -pedantic
OBJS= genList.o genList_test.o listItr.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

listItr.o: listItr.c listItr.h
	$(CC) $(CFLAGS) -c listItr.c

genList.o: genList.c genList.h
	$(CC) $(CFLAGS) -c genList.c
	
genList_test.o: genList_test.c genList.h
	$(CC) $(CFLAGS) -c genList_test.c
	
clean:
	rm -f $(TARGET) $(OBJS)
