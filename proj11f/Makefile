all: master slave

master: master1.o parsemas.o
	gcc -g -o master master1.o parsemas.o -Wall

master1.o: master1.c funct11.h
	gcc -g -c master1.c -o master1.o

parsemas.o: parsemas.c funct11.h
	gcc -g -c parsemas.c -o parsemas.o


slave: slave1.o
	gcc -g -o slave  slave1.o -Wall

slave1.o: slave1.c
	gcc -g -c slave1.c -o slave1.o

clean:
	rm -f master slave *.o 
