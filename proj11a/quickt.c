#include <stdlib.h>
#include <stdio.h>

int main(){

char *test="    abc";

 while(*test==' '){
    test++;
 }

 printf("%s\n",test);

 return 0;
}

