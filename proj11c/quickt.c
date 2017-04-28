#include <stdlib.h>
#include <stdio.h>
#include <string.h>



int main(){

char *test="    abc";

 while(*test==' '){
    test++;
 }

char *test2="@k 34 393943                      \n";
 int len=strlen(test2);

 int val;
 int fset; 
 test2=test2+2;
 sscanf(test2,"%d%n",&val,&fset);
 char other[1024]={'\0'}; 
 test2=test2+fset; 
 sscanf(test2,"%s",other);
 if(other[0]=='\0'){printf("yes\n"); }
 printf("%d %c\n",val,other[0]);

 return 0;
}

