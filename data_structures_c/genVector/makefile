# makefile genericVector

TARGET= genericVector.out
CC= gcc
CFLAGS= -ansi -g -pedantic
OBJS= genericVector_test.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) -lm -L ../libgends -lgends
		
genericVector_test.o: genericVector_test.c genericVector.h
	$(CC) $(CFLAGS) -c genericVector_test.c
	
clean:
	rm -f $(TARGET) $(OBJS)
