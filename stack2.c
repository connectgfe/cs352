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
int isop(char*);
int iscom(char*);
void printlst(node*);

int main(){

   char *sub="-";
   char *add="+";

   int status=0;
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
printlst(head);

       int retval=isopcom(templn);   
      if(retval==1){
        push(&head,strmath(sub,pop(&head),pop(&head))); 
       }
     }
     else{
       fprintf(stderr,"Error in input (2)\n");
       status=1;
       continue;
     }


   } 

   free(line); 
printlst(head);
/*
   printf("pop %s\n",pop(&head));
   printlst(head);
   printf("pop %s\n",pop(&head));
   printlst(head);
*/


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
    printf("%s\n",str); 
 
    node *temp=malloc(sizeof(node));
    temp->val=str;
    temp->next=*head; 
    *head=temp;
} 
void printlst(node *head){
   node *cur=head;
   while(cur->next!=NULL){
     printf("st: %s\n",cur->val);
     cur=cur->next;}


}
char* pop(node ** head) {
      
    node *next_node = NULL;

    if (*head == NULL) {
        return NULL;
    }

    next_node = (*head)->next;
    char* retval = (*head)->val;
    free(*head);
    *head = next_node;

    return retval;
}
