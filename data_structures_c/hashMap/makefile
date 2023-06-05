
# makefile hashMap

TARGET= hashMap.out
CC= gcc
CFLAGS= -ansi -g -pedantic
OBJS= hashMap.o hashMap_test.o  genList.o listItr.o intFun.o 
LIST_PATH= ../genDoubleLinkList


$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

hashMap.o: hashMap.c hashMap.h $(LIST_PATH)/genList.h $(LIST_PATH)/listItr.h $(LIST_PATH)/list_functions.h
	$(CC) $(CFLAGS) -I $(LIST_PATH)  -c hashMap.c
	
hashMap_test.o: hashMap_test.c hashMap.h 
	$(CC) $(CFLAGS) -c hashMap_test.c
	
genList.o: $(LIST_PATH)/genList.c $(LIST_PATH)/genList.h $(LIST_PATH)/listInternal.h
	$(CC) $(CFLAGS) -I $(LIST_PATH) -c $(LIST_PATH)/genList.c

listItr.o: $(LIST_PATH)/listItr.c $(LIST_PATH)/listItr.h $(LIST_PATH)/genList.h $(LIST_PATH)/listInternal.h
	$(CC) $(CFLAGS) -I $(LIST_PATH) -c $(LIST_PATH)/listItr.c

intFun.o: $(LIST_PATH)/intFun.c  $(LIST_PATH)/list_functions.h $(LIST_PATH)/listInternal.h
	$(CC) $(CFLAGS) -I $(LIST_PATH) -c $(LIST_PATH)/intFun.c

clean:
	rm -f $(TARGET) $(OBJS)