#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(){

char *line="please trim me      \n";
int n=strlen(line);
char cutline[64];
strcpy(cutline,line);
cutline[n-1]='\0';
n=n-2;
while(cutline[n]==' '){
  cutline[n]='\0'; 
  n--;
}
cutline[n+1]='\n';
printf("%s\n",cutline);



return 0;
}
