# makefile hash

TARGET= hash.out
CC= gcc
CFLAGS= -ansi -g -pedantic
OBJS= hash.o hash_test.o 

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

hash.o: hash.c hash.h
	$(CC) $(CFLAGS) -c hash.c
	
hash_test.o: hash_test.c hash.h
	$(CC) $(CFLAGS) -c hash_test.c
	
clean:
	rm -f $(TARGET) $(OBJS)
