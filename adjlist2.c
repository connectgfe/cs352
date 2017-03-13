#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
  int ind;
  int weight; 
  struct Node *next;
}node;

typedef struct List{
  struct Node *head;
}list;

struct Graph{
  int numofV;
  struct List *arr;
};

typedef struct Vert{
  char *vname;
  int vval;
  struct Vert *next;
}vert;

int status;
int numV;

void addlist(struct Graph*,int);
void addvert(vert*,char*,struct Graph*);
void printG(struct Graph*);
void printVlist(vert*);
void addedge(vert*,struct Graph*,char*,char*);


int main(){
  status=0;
  numV=1;
  struct Graph *graph=malloc(sizeof(struct Graph));
  vert *ver=malloc(sizeof(vert)); 
  
  char *v1name="John"; 
  addvert(ver,v1name,graph);  
  char *v2name="Ed"; 
  addvert(ver,v2name,graph);  
  char *v3name="Phil"; 
  addvert(ver,v3name,graph);  




  printG(graph); 
  printVlist(ver);
  addedge(ver,graph,v3name,v1name); 
  printG(graph);
  return status;


}

void addlist(struct Graph *graph, int val){
  
  graph->arr=(list*)realloc(graph->arr,numV*sizeof(list));
  // must realloc 
  graph->arr[numV].head=malloc(sizeof(node));
  graph->arr[numV].head->ind=val;
  graph->arr[numV].head->next=malloc(sizeof(node)); 
  numV++;
}

void addvert(vert *ver, char *name, struct Graph *graph){
  
  vert *cur=ver;
  while(cur->next!=NULL){
     cur=cur->next;}
  
  cur->vval=numV;
  cur->vname=name;
  cur->next=malloc(sizeof(vert));
  
  addlist(graph,numV); 


}

void addedge(vert *ver, struct Graph *graph, char *n1, char *n2){

  int v, vadd;
  vert *cur=ver;
  while(cur->next!=NULL){
    if(strcmp(cur->vname,n1)==0){
    v=cur->vval;}
    if(strcmp(cur->vname,n2)==0){
    vadd=cur->vval;}
    cur=cur->next;}

  printf("%s %d %s %d\n",n1,v,n2,vadd);

  node *cur2=graph->arr[v].head;
  while(cur2->next!=NULL){
  cur2=cur2->next;
  }
  cur2->ind=vadd;
  cur2->next=malloc(sizeof(node));
}




void printG(struct Graph *graph){

  int i;
  for(i=1;i<numV;i++){
    
    node *cur=graph->arr[i].head;
    while(cur->next!=NULL){ 
    printf("%d ", cur->ind);
    cur=cur->next;  
    }
    printf("\n"); 
    }
}

void printVlist(vert *ver){

  vert *cur=ver;
  while(cur->next!=NULL){
  printf("%s %d\n",cur->vname, cur->vval);
  cur=cur->next;
  }

}





