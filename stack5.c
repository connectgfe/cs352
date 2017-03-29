#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "8functions.h"

typedef struct Node{
     char *val;
     struct Node *next;
}node;

void push(node**,char*);
char* pop(node**);
int isnum(char*);
int isopcom(char*);
void printlst(node*);
void printlst2(node*);
char *strmath(char*,char*,char*);
int status;


int main(){

   char *sub="-";
   char *add="+";

   status=0;
   char *line=NULL;
   size_t len=0;
   int val=0;
   node *head=malloc(sizeof(node));
   head->val=NULL;
   head->next=NULL;   


   
   while(val>-1){
      val=getline(&line,&len,stdin); 
     
// printf("val %d\n",val);
      if(val<2){ 
        if(val==-1){break;} 
        fprintf(stderr,"Error in input (1)\n");
        status=1; 
        continue;} 
      char templn[val];
      strcpy(templn,line);
      templn[val-1]='\0'; 
//printf("%s\n",templn);  
     
     if(isnum(templn)==0){ 
//printf("yes num\n"); 
           push(&head,strdup(templn));
     }
     else if(isopcom(templn)!=0){
//printlst(head);

       int retval=isopcom(templn);   
      if(retval==1){
       if(head->val==NULL){
        fprintf(stderr,"Error in operator (1)\n");
        status=1;
        continue;}
       if(head->next->val==NULL){
        fprintf(stderr,"Error in operator (2)\n");
        status=1;
        continue;}
        char *temp1=pop(&head);
        char *temp2=pop(&head);
        push(&head,strmath(sub,temp2,temp1)); 
        free(temp1);
        free(temp2); 
       }
      if(retval==2){
       if(head->val==NULL){
        fprintf(stderr,"Error in operator (1)\n");
        status=1;
        continue;}
       if(head->next->val==NULL){
        fprintf(stderr,"Error in operator (2)\n");
        status=1;
        continue;}
      
        char *temp1=pop(&head);
        char *temp2=pop(&head);
        push(&head,strmath(add,temp1,temp2)); 
        free(temp1);
        free(temp2); 
       }
      if(retval==3){
      if(head->val==NULL){
          printf("Stack Empty\n");
          continue;}
       
        node *temp;
        while(head!=NULL){
          temp=head;
          head=head->next;
          free(temp->val); 
          free(temp);
        }  
          free(head); 

   head=malloc(sizeof(node));
   head->val=NULL;
   head->next=NULL;   


      } 
      if(retval==4){
        if(head->val==NULL){
         printf("Error: Stack Empty\n");
         continue;
        }
      
      free(pop(&head)); 
      } 
      if(retval==5){
       if(head->val==NULL){
       printf("Stack Empty\n");}else{
       printf("%s\n",head->val);
      }}
      if(retval==6){
        if(head->val==NULL){
       printf("Stack Empty\n");}else{
       printlst2(head);
      }}     
      } 
     else{
       fprintf(stderr,"Error in input (2)\n");
       status=1;
       continue;
     }
    

   } 

   free(line); 
 
  if(head!=NULL){
       node *temp;
        while(head!=NULL){
          temp=head;
          head=head->next;
          free(temp->val); 
          free(temp);
        }  

   } 

   free(head);


  return status;

}

int isnum(char *str){
    
   while(*str){
    if(isdigit(*str)==0){
     return 1;}  
    str++; 
   }
  return 0;

}
int isopcom(char *str){
   if(strcmp(str,"-")==0){
      return 1;}
   if( strcmp(str,"+")==0){
      return 2;}

  if(strcmp(str,"c")==0){
     return 3;}

  if(strcmp(str,"u")==0){
     return 4;} 
  if(strcmp(str,"p")==0){ 
     return 5;}
  if(strcmp(str,"a")==0){
      return 6;}

 return 0;
}
void push(node **head,char *str){
//    printf("%s\n",str); 
 
    node *temp=malloc(sizeof(node));
    temp->val=str;
    temp->next=*head; 
    *head=temp;
} 

void printlst2(node *head){
   if(head->next==NULL){
      return;}
    printlst2(head->next);
   printf("%s\n",head->val);

}



void printlst(node *head){
   node *cur=head;
   while(cur->next!=NULL){
     printf("%s\n",cur->val);
     cur=cur->next;}


}
char* pop(node ** head) {
      
    node *next_node = NULL;
    node *cur=*head; 
    if (cur->val == NULL) {
     status=1;
     fprintf(stderr,"Error: nothing to pop (1) stack.c\n"); 
     return NULL;
    }

    next_node = (*head)->next;
    char* retval = strdup((*head)->val);
    free((*head)->val);
    free(*head);
    *head = next_node;

    return retval;
}


char  *strmath(char *op, char *instr1, char *instr2){

     int neg=0;
     int neg2=0; 
     int neg3=0;
     char *str1=NULL;
     char *str2=NULL; 

//printf("str's :%s\n%s\n%s\n\n",op,instr1,instr2);

   char *zero=NULL;
   char z[2]="0"; 
    if(strcmp(instr1,"0")==0 && strcmp(instr2,"0")==0){
      
     return zero;
      }
  // deal with neg input
   if(strcmp(op,"-")==0 && (*instr2)=='-' && (*instr1)!='-'){
      op="+";
      instr2=instr2+1;
      }

   if(strcmp(op,"+")==0 && (*instr2)=='-' && (*instr1)!='-'){
      op="-";
      instr2=instr2+1;
      }

   if(strcmp(op,"+")==0 && (*instr1)=='-'&& (*instr2)!='-'){
      op="-"; 
      instr1=instr1+1;
      neg3=1;   
       }

   if(strcmp(op,"-")==0 && (*instr1)=='-'&& (*instr2)!='-'){
      op="+"; 
     instr1=instr1+1;
 
     neg2=1;   
      }

   if(strcmp(op,"+")==0 && (*instr1)=='-'&& (*instr2)=='-'){
      op="+"; 
     instr1=instr1+1;
     instr2=instr2+1; 
     neg2=1;   
      }

   if(strcmp(op,"-")==0 && (*instr1)=='-'&& (*instr2)=='-'){
      op="-"; 
      instr1=instr1+1;
      instr2=instr2+1; 
      neg3=1;   
       }

   if(strcmp(op,"-")==0 && (*instr1)=='-'&& (*instr2)=='-'){
      instr1=instr1+1;
      instr2=instr2+1; 
      neg3=1;   
       }





//printf("str's :%s\n%s\n%s\n\n",op,instr1,instr2);


    // remove zeros
    while(*(instr1)=='0'){
     instr1=instr1+1;
      }
    while( *(instr2)=='0'){
     instr2=instr2+1;
    }

     if(strcmp(op,"-")==0 && strcmp(instr2,instr1)==0){
      zero=strdup(z); 
      return zero;
     }




//printf("str's -0's:\n%s\n%s\n\n",str1,str2);

    size_t len1= strlen(instr1);
    size_t len2= strlen(instr2);

//printf("str's len %lu %lu\n\n",len1,len2);

    if(len1==len2){
     str1=(char*)malloc((len1+1)*sizeof(char*));  
     str2=(char*)malloc((len1+1)*sizeof(char*));  
     int mrkr=0; 
       if( strcmp(op,"-")==0 ){
//printf("no1\n");     
        char *temp1=instr1;
        char *temp2=instr2; 
       while(*(temp1)!='\0'){
// printf("no2\n");      
          if(  (*temp1-'0') < (*temp2-'0') ){
//printf("no3\n");
        
             strcpy(str1,instr2);
             strcpy(str2,instr1);
       
//printf("sub switch needed:\n%s\n%s\n\n",str1,str2);
              if(neg3==0){   
//printf("no4\n");
                 neg=1;}
//printf("no5\n");
           mrkr=1; 
          break;}
       temp1++; 
       temp2++;}    
// printf("no6\n");  
           if(mrkr==0){
           if(neg3==1){   
                 neg=1;}

             strcpy(str1,instr1);
            strcpy(str2,instr2);
           }
        }else{
//printf("no7\n");
       strcpy(str1,instr1);
       strcpy(str2,instr2);
      }
    }

   // prepend zeros & special case for sub
    if(len2>len1){
     if( strcmp(op,"-")==0 && neg3==0){
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
     if( strcmp(op,"-")==0 && neg3==1){
        neg=1;}
 
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


//printf("%s\n%s\n\n",str1,str2);

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
    char num[len1+1];
    char ons,tns;


  // this addes
    if(strcmp(op,"+")==0){
//      printf("add\n");
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
//   printf("sub\n");
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






//    printf("(1) num:   %s\n",num);

//    free(num);

   
    if(num[n-1]=='0'){ num[n-1]='\0';}   

    size_t nlen=strlen(num);

   char finum[nlen+2];
   // printf("%lu ",nlen);

 //   for(i=nlen-1;i>-1;i--){
 //   if(num[i]=='0'){ nlen=( nlen -1) ;}else{break;}}



//printf("op %s\n",op);
    int cnt=0;
    for(i=nlen-1;i>-1;i--){
      if(neg==1){
      finum[0]='-'; 
      neg=0; 
      cnt++; 
      i++; 
      continue;}

    if(neg2==1){
      finum[0]='-'; 
      neg2=0; 
      cnt++; 
      i++; 
      continue;}

  
   finum[cnt]=num[i];
    cnt++;}
   finum[cnt]='\0';




//   printf("(2) finum: %s\n",finum);

   char *finum2= strdup(finum); 


   free(str1);
   free(str2);


   return finum2;
}
