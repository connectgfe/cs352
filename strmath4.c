/*
* File: strmath.c
* Author: Giulio Esposito
* Pupose: do binary operations + - on strings of ints
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//int status;


char  *strmath(char *op, char *instr1, char *instr2){

  //  status=0;
    int neg=0;
    size_t len=0;
    char *line=NULL;
    
   //  char *instr1,*instr2,*op;
     char *str1,*str2; 
//     instr1="0000000001";
//     instr2="0000010000000000000000000000000000000000000000000000";
//     op="-"; 

//printf("str's:\n%s\n%s\n\n",str1,str2);

    char *zero="0";

    if(strcmp(instr1,"0")==0 && strcmp(instr2,"0")==0){
     return zero;
      }

     if(strcmp(op,"-")==0 && strcmp(instr2,instr1)==0){
      return zero;
     }


    // remove zeros
    while(*(instr1)=='0'){
     instr1=instr1+1;
      }
    while( *(instr2)=='0'){
     instr2=instr2+1;
    }

//printf("str's -0's:\n%s\n%s\n\n",str1,str2);

    size_t len1= strlen(instr1);
    size_t len2= strlen(instr2);

//printf("str's len %lu %lu\n\n",len1,len2);

    if(len1==len2){
     str1=(char*)malloc((len1+1)*sizeof(char*));  
     str2=(char*)malloc((len1+1)*sizeof(char*));  
     
       if( strcmp(op,"-")==0 ){
        char *temp1=instr1;
        char *temp2=instr2; 
       while(*(temp1)!='\0'){
       
       if(  (*temp1-'0') < (*temp2-'0') ){

        
       strcpy(str1,instr2);
       strcpy(str2,instr1);
       
printf("sub switch needed:\n%s\n%s\n\n",str1,str2);
     neg=1;
      break;}
       temp1++; temp2++;}    
   
     }else{
       strcpy(str1,instr1);
       strcpy(str2,instr2);
      }
    }

   // prepend zeros & special case for sub
    if(len2>len1){
     if( strcmp(op,"-")==0 ){
        neg=1;}
 
     str1=(char*)malloc((len2+1)*sizeof(char*));  
     str2=(char*)malloc((len2+1)*sizeof(char*));  
     char temp[len2+1];
     int j=0;
     for(j=0;j<(len2-len1);j++){
       temp[j]='0';}
     temp[(len2-len1)]='\0'; 
     strcat(temp,instr1);
   //  printf("L%s ",strtemp);
     strcpy(str1,instr2);
     strcpy(str2,temp); 
      len1=len2;
//printf("(1) preppend zero's:\n%s\n%s\n\n",str1,str2);
     }


   // prepend zeros
    if(len1>len2){
     str1=(char*)malloc((len1+1)*sizeof(char*));  
     str2=(char*)malloc((len1+1)*sizeof(char*));  
     char temp[len1+1]; 
     int j=0;
     for(j=0;j<(len1-len2);j++){
       temp[j]='0';}
     temp[(len1-len2)]='\0'; 
     strcat(temp,instr2);
     strcpy(str1,instr1); 
     strcpy(str2,temp); 
     len2=len1;
//printf("(2) preppend zero's:\n%s\n%s\n\n",str1,str2);
     }


printf("%s\n%s\n\n",str1,str2);

/*
   char test[len];

    test[0]='2';
    test[1]='w';
    int ind=strlen(test);
    test[ind]='\0'; 
 printf("len %lu\n",strlen(test));

*/


    int l1=len1;
    char st1[l1];
    strcpy(st1,str1);

    int i=0;
    int ones=0;
    int tens=0;
    int n=0;
    char num[len+1];
    char ons,tns;


  // this addes
    if(strcmp(op,"+")==0){
      printf("add\n");
 //   printf("len1:%d\n", l1);
    for(i=(l1-1);i>-1;i--){
//    printf("%c\n",*(str1+i));


    int intt=tens + *(str1+i)-'0'+*(str2+i)-'0';
 //  printf("intt %d\n ",intt);

    if(intt>=10){
       ones=(intt%10);
  //     printf("int ones %d\n",ones);
        tens=1;}
      else{ 
        ones=intt;
        tens=0;}

   
     ons=ones + '0';
     tns=tens + '0';
//    printf("char ones %c\n",ons);

    // note: will print the carried 1 later
    num[n]=ons;
    
    n++;

    if(i==0 && tens==1){
    num[n]=tns;
    n++;}
    
     }

   num[n]='\0';
   }
//   printf("%d %d\n",n,l1);

   char tstr1[len1];
   char tstr2[len1];
   strcpy(tstr1,str1);
   strcpy(tstr2,str2); 
   // this sub
   if(strcmp(op,"-")==0){
   printf("sub\n");
   //int intt2,tens2;
  // printf("len1:%lu\n",len1);

   if(len1==1){
    int temp3=(tstr1[0]-'0') - (tstr2[0]-'0');
     num[n]=temp3+'0';}

   for(i=(len1-1);i>-1;i--){


   if(tstr1[i]-'0' >= tstr2[i]-'0' ){

        int  intt2=(tstr1[i]-'0') - (tstr2[i]-'0');
        num[n]=intt2+'0';
        n++;
        continue;}

   if(tstr1[i-1]=='0'){
           int k=1;

            while(tstr1[i-k]=='0'){
             tstr1[i-k]='9';
             k++;}

      int temp2=(tstr1[i-k]-'0')-1;
 //     printf("%d\n",temp2);
      tstr1[i-k]=temp2+'0';
//       printf("%s\n",st1);
//   char *temp=st1;
//   str1=temp;
//   printf("%s\n",str1);
    int temp3=10+((tstr1[i]-'0')- (tstr2[i]-'0'));


    num[n]=temp3+'0';
    n++;
   continue;}
//   printf("no1\n");
    int temp3=10+(tstr1[i]-'0')- (tstr2[i]-'0');
//    printf("%d\n",temp3);
    num[n]=temp3+'0';
    n++;
    int temp2=(tstr1[i-1]-'0')-1;
//    printf("%d\n",temp2);
    tstr1[i-1]=temp2+'0';
//     printf("%s\n",st1);
//     char *temp=st1;
//     str1=temp;
   }
   num[n]='\0'; 
   }






    printf("(1) num:   %s\n",num);

//    free(num);

   
    if(num[n-1]=='0'){ num[n-1]='\0';}   

    size_t nlen=strlen(num);

   char finum[nlen+2];
   // printf("%lu ",nlen);

 //   for(i=nlen-1;i>-1;i--){
 //   if(num[i]=='0'){ nlen=( nlen -1) ;}else{break;}}



    int cnt=0;
    for(i=nlen-1;i>-1;i--){
      if(neg==1){
      finum[0]='-'; 
      neg=0; 
      cnt++; 
      i++; 
      continue;}

    finum[cnt]=num[i];
    cnt++;}
   finum[cnt]='\0';




   printf("(2) finum: %s\n",finum);

   char *finum2= strdup(finum); 


   free(str1);
   free(str2);


   return finum2;
}
