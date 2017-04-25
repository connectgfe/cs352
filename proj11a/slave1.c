#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>

int main(){

char line[40];

int ipid=getpid();

printf("%d\n",ipid);
char cpid[10];
snprintf(cpid, 10, "%d",ipid);
//cpid[7]='\0';

printf("%lu\n",strlen(cpid));


int fd1=open("slave_pid", O_WRONLY | O_CREAT | O_TRUNC); 
write(fd1,cpid,6); 


/*
read(0,line,30);

printf("NEW: %s\n",line); 
*/


return 0;

}
