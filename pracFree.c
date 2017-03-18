#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
  int val;
  struct Node *next;
}node;

void prlist(node*);

int main(){
  
  node *head=malloc(sizeof(node));
  int i;
  for(i=0;i<2;i++){
     node *cur=head;
     while(cur->next!=NULL){
     printf("%p\n",cur);

       cur=cur->next;}
     cur->val=i;
     cur->next=malloc(sizeof(node));}

  prlist(head);   
     
   free(head->next->next);
      
  prlist(head); 



return 0;
} 

void prlist(node *head){
    node *cur=head;
    while(cur->next!=NULL){
      printf("%d %p\n",cur->val,cur);
      cur=cur->next;}
}
