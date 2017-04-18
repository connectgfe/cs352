
mymake2 : mymake2.o reachE8.o 
	gcc -g    -o mymake2 mymake2.o reachE8.o  -Wall -L/home/cs352/spring17/Assignments/proj09 -lcs352 


mymake2.o : mymake2.c funct.h  
	gcc  -g  -c mymake2.c -o mymake2.o -Wall

reachE8.o :  reachE8.c  funct.h 
	gcc  -g  -c reachE8.c -o reachE8.o -Wall


coverage:
	gcc -fprofile-arcs -ftest-coverage -o  mymakegcov mymake2.c reachE8.c  -L/home/cs352/spring17/Assignments/proj09 -lcs352

clean : 
	rm -f *.o *.gcno *.gcov *.gcda mymake2 mymakegcov
