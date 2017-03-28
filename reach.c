/*
* File: reach.c
* Author: Giulio Esposito
* Purpose: use a graph to find if nodes are connected
*/

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
int flag;

int sAlpha(char*);
void addlist(struct Graph*,int);
void addvert(vert*,char*,struct Graph*);
void printG(struct Graph*);
void printVlist(vert*);
void addedge(vert*,struct Graph*,char*,char*);
int getindex(vert*,char*);
void isconn(struct Graph*,int*,int,int);
int checkargs(char*);
int selfLoop(int,struct Graph*);
int isempty(char*);


int main(int argc, char **argv){

  status=0;
  numV=1;
  flag=0; 


  struct Graph *graph=malloc(sizeof(struct Graph));
  graph->numofV=0; 
  graph->arr=(list*)malloc(sizeof(list));
  graph->arr->head=NULL;
  
  vert *verhead=malloc(sizeof(vert)); 
  verhead->vname=NULL; 
  verhead->vval=0;
  verhead->next=NULL; 

  char *names="@n";
  char *edges="@e";
  char *path ="@q";
 

  int mrkr=0;
  FILE *fp;

  if(argc>1){
   fp=fopen(*(argv+1), "r");
   if(fp==NULL){
    fprintf(stderr,"Error with file\n"); return 1;}
   if(argc>2){status=1;}
  mrkr=1;
  }


  int *vtx=NULL;
  int val=0;
  char *line=NULL;
  size_t len=0;
  char *op=NULL;
  char *templn=NULL;
  char *str=NULL;
  char *str2=NULL;


//  loop    
 
    while(val>-1){

      if(mrkr==1){
         val=getline(&line,&len,fp);

        }else{

        val=getline(&line,&len,stdin);}

    
      if(val>1){

       if(strlen(line)<=3){
         fprintf(stderr,"Error: (1) bad input\n");
        status=1;
        continue;}
       
       if(isempty(line)==1){
         fprintf(stderr,"Error: (2) bad input\n");
        status=1;
        continue;}
       
      
      op=(char*)malloc(65*sizeof(char)); 
      sscanf(line,"%64s",op);
       
       templn=line; 
       templn+=strlen(op);  
      
      // check if op is legal       


      if(strcmp(op,names)!=0 && strcmp(op,edges)!=0 && strcmp(op,path)!=0){
        fprintf(stderr,"Error: (3) bad input\n");
        status=1;
        free(op); 
        continue;}

  

   //  add vertex
      
      if(strcmp(op,names)==0){ 
        


    // check for correct number of args    
   
       if(checkargs(templn)!=1){
          fprintf(stderr,"Error: (1) bad no of args\n");
          status=1;

           free(op);
          continue;} 

         str=(char*)malloc(64*sizeof(char)); 
         sscanf(templn,"%s",str);
         
         if(sAlpha(str)==1){
          fprintf(stderr,"(1) Bad name selection\n");
          free(str);
          free(op);
          status=1;
          continue;}   

         if(getindex(verhead,str)!=0){
          fprintf(stderr,"(2) Bad name selection\n");
          free(str);
          free(op);
          status=1;
          continue;}      

   
          addvert(verhead,strdup(str),graph);
          free(str);
         } 
      


     // add edge

      if(strcmp(op,edges)==0){
 
      if(checkargs(templn)!=2 ){
          fprintf(stderr,"Error: (2) bad no of args\n");
          status=1;
         free(op); 
           continue;} 

       str=(char*)malloc(64*sizeof(char)); 
       str2=(char*)malloc(64*sizeof(char)); 
        sscanf(templn,"%s %s",str,str2); 
       

              
        if(getindex(verhead,str)==0 || getindex(verhead,str2)==0){
           fprintf(stderr,"Error: bad edge assign\n");
           status=1;
           free(str);
           free(str2);
           free(op);
           continue;}
         addedge(verhead,graph,str,str2);
         free(str);
         free(str2); 
     
      }

      // check for directed path

      if(strcmp(op,path)==0){
        if(checkargs(templn)!=2){
          fprintf(stderr,"Error: (3) bad no of args\n");
          status=1;
          free(op); 

           continue;} 

        int i;
        vtx=(int*)malloc(numV*sizeof(int)); 
        for(i=0;i<numV;i++){
          *(vtx+i)=i;
         } 
       
      str=(char*)malloc(64*sizeof(char)); 
      str2=(char*)malloc(64*sizeof(char)); 
 

        sscanf(templn,"%s %s",str,str2); 
       
       if(getindex(verhead,str)==0 || getindex(verhead,str2)==0){
           fprintf(stderr,"Error: bad path attempt\n");
           status=1;
           free(str);
           free(str2);           
           free(op); 
           free(vtx);
            vtx=NULL;
           
            continue;}
        
         if(strcmp(str,str2)==0){

          flag=1;
            printf("%d\n",flag); 
           flag=0;
       
         free(str);
         free(str2); 
         free(op); 
         free(vtx);
         vtx=NULL;   
          continue; 
           }

 
         isconn(graph,vtx,getindex(verhead,str),getindex(verhead,str2));
           printf("%d\n",flag); 
           flag=0;
       
         free(str);
         free(str2); 
         free(vtx);
         vtx=NULL;         
       }



        free(op);
      } 

   }
   if(mrkr==1){fclose(fp);}

  free(line);


   int i;

   
    vert *temp;
     while(verhead!=NULL){
        temp=verhead;
       verhead=verhead->next;
       free(temp->vname);  
       free(temp);
      }

// free graph

    for(i=0;i<numV;i++){
    node *temp;
     while(graph->arr[i].head!=NULL){
        temp=graph->arr[i].head;
        graph->arr[i].head=graph->arr[i].head->next;
        free(temp);
   }
}


    free(verhead);
    free(graph->arr);

    free(graph); 

    
     return status;


}

void addlist(struct Graph *graph, int val){
  
  graph->arr=(list*)realloc(graph->arr,(numV+1)*sizeof(list));
  graph->arr[numV].head=malloc(sizeof(node));
  graph->arr[numV].head->ind=val;
  graph->arr[numV].head->weight=0;
  
  graph->arr[numV].head->next=malloc(sizeof(node)); 
  graph->arr[numV].head->next->ind=0;
  graph->arr[numV].head->next->weight=0;
  graph->arr[numV].head->next->next=NULL;

  numV++;
}

void addvert(vert *verhead, char *name, struct Graph *graph){
  
  vert *cur=verhead;
  while(cur->next!=NULL){
     cur=cur->next;}
  
  cur->vval=numV;
  cur->vname=name;
  cur->next=malloc(sizeof(vert));
  cur->next->vname=NULL;
  cur->next->vval=0;
  cur->next->next=NULL;
 
 addlist(graph,numV); 


}

void addedge(vert *verhead, struct Graph *graph, char *n1, char *n2){

  int v, vadd;
  vert *cur=verhead;
  while(cur->next!=NULL){
    if(strcmp(cur->vname,n1)==0){
    v=cur->vval;}
    if(strcmp(cur->vname,n2)==0){
    vadd=cur->vval;}
    cur=cur->next;}


  node *cur2=graph->arr[v].head;
  while(cur2->next!=NULL){
  cur2=cur2->next;
  }
  cur2->ind=vadd;
  cur2->next=malloc(sizeof(node));
  cur2->next->ind=0;
  cur2->next->weight=0;
  cur2->next->next=NULL;
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

void printVlist(vert *verhead){

  vert *cur=verhead;
  while(cur->next!=NULL){
  printf("%s %d\n",cur->vname, cur->vval);
  cur=cur->next;
  }

}

int getindex(vert *verthead, char *name){

  vert *cur=verthead;
  while(cur->next!=NULL){
  if(strcmp(cur->vname,name)==0){
   return cur->vval;}
  cur=cur->next;}
  return 0;

}

void isconn(struct Graph *graph,int *vtx,int ptA,int ptB){

  node *cur=graph->arr[ptA].head;
  
  *(vtx+ptA)=0; 
  while(cur->next!=NULL){
  int nptA=cur->next->ind;
    if(*(vtx+nptA)==0 && nptA!=0){
       cur=cur->next; 
       nptA=cur->next->ind;
     }
   if(nptA==0){
     return ;}
   if(nptA==ptB){ 
   flag=1; return ;} 
   
   isconn(graph,vtx,nptA,ptB);
   cur=cur->next;
   }

}

int checkargs(char *line){

    char *temp=line;
    int cnt=0; 
    int offset=0;
    char *str=(char*)malloc(64*sizeof(char));

    while( sscanf(temp,"%s%n",str,&offset)==1){
       temp+=offset;
      cnt++;
   free(str);
    str=(char*)malloc(64*sizeof(char));
    if(cnt>1027){break;}
    }
    free(str);
    
    return cnt;

}

int sAlpha(char *str){

  int size=strlen(str);
   int cnt=0;

   while(*str){
    if(isalpha(*str)!=0){
    cnt++;
    }
   if(isdigit(*str)!=0){
    cnt++;
    }
   str++;
  }


  if(cnt!=size){
    return 1;
  }


return 0;
}

int selfLoop(int pos, struct Graph *graph){
    node *cur=graph->arr[pos].head;
    int cnt=0;
    while(cur->next!=NULL){
     if(cur->ind==pos){cnt++;}
     cur=cur->next;}
     if(cnt>=2){return 1;}

     return 0;

}

int isempty(char *str){
   size_t len1=strlen(str);
   int cnt=0;
   while(*str){

   if(*str==' '){
   cnt++;}
   str++;
   }
  if(cnt==(len1-1)){return 1;}
  return 0;
} 
