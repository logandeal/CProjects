
output: main.o facebook.o
	gcc main.o facebook.o -o output

main.o: main.c
	gcc -c main.c

message.o: message.c message.h
	gcc -c message.c

target: dependencies
	action

clean: 
	rm *.o output