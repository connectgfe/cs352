
mymake : inputM9d.o reachE8.o cs352.o
	gcc -g -o   mymake inputM9d.o reachE8.o cs352.o -Wall libcs352.a 


inputM9d.o : inputM9d.c funct.h cs352.h 
	gcc  -g -c -o inputM9d.o inputM9d.c

reachE8.o :  reachE8.c  funct.h cs352.h
	gcc  -g -c -o reachE8.o reachE8.c

cs352.o : cs352.c cs352.h 
	gcc -g -c -o  cs352.o cs352.c -l libcs352.a

clean : 
	rm *.o
