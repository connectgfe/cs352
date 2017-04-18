
mymake : mymake.o reachE8.o 
	gcc -g    -o mymake mymake.o reachE8.o  -Wall -L/home/cs352/spring17/Assignments/proj09 -lcs352 


mymake.o : mymake.c funct.h  
	gcc  -g  -c mymake.c -o mymake.o -Wall

reachE8.o :  reachE8.c  funct.h 
	gcc  -g  -c reachE8.c -o reachE8.o -Wall


coverage:
	gcc -fprofile-arcs -ftest-coverage -o  mymakegcov mymake.c reachE8.c  -L/home/cs352/spring17/Assignments/proj09 -lcs352

clean : 
	rm -f *.o *.gcno *.gcov *.gcda mymake mymakegcov
