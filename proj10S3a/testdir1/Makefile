
mymakeT : mymake.o reachE8.o 
	gcc  -g  -o mymakeT mymake.o reachE8.o  

mymake.o : mymake.c   
	gcc  -g  -c mymake.c -o mymake.o -Wall

reachE8.o :  reachE8.c   
	gcc  -g  -c reachE8.c -o reachE8.o -Wall

coverage:
	gcc -fprofile-arcs -ftest-coverage -o  mymakegcov mymake.c reachE8.c  

clean : 
	rm -f *.o *.gcno *.gcov *.gcda mymakeT mymakegcov
