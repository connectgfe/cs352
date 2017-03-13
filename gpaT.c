#include <stdio.h>

int main(){

  float grade=0;
  float cred=0;
  float gr=grade;
  float cr=cred;  

  
  while(scanf("%f %f",&grade,&cred)!=-1){
   gr+= grade*cred;
   cr+= cred;  
 //  printf("%d %d\n",gr,cr);  
}
 printf("%f %f\n",gr,cr);  
  float gpa=(gr/cr);
  printf("%f\n",gpa);

return 0;
}
