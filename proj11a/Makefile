all: _master1 _slave1

_master1: master1.o
	gcc -g -o _master1 master1.o

master1.o: master1.c
	gcc -g -c master1.c -o master1.o

_slave1: slave1.o
	gcc -g -o _slave1  slave1.o

slave1.o: slave1.c
	gcc -g -c slave1.c -o slave1.o

clean:
	rm -f _master1 _slave1 *.o 
