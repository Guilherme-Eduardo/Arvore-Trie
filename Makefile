CC = gcc
CFLAGS = -Wall  -Werror -Wextra
TARGET = dicionario

$(TARGET): main.o dicionario.o
	$(CC) $(CFLAGS) main.o dicionario.o -o $(TARGET)

main.o: main.c dicionario.o
	$(CC) $(CFLAGS) -c main.c -o main.o

dicionario.o: dicionario.c dicionario.h
	$(CC) $(CFLAGS) -c dicionario.c -o dicionario.o

clean: 
	rm -f *.o

purge: 
	rm $(TARGET)

