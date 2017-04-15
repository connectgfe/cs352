
mymake : mymake.o reachE8.o cs352.o
	gcc -g -o   mymake mymake.o reachE8.o cs352.o -Wall libcs352.a 


mymake.o : mymake.c funct.h cs352.h 
	gcc  -g -c -o mymake.o mymake.c

reachE8.o :  reachE8.c  funct.h cs352.h
	gcc  -g -c -o reachE8.o reachE8.c

cs352.o : cs352.c cs352.h 
	gcc -g -c -o  cs352.o cs352.c -l libcs352.a

clean : 
	rm *.o
