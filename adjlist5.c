#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

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
void addlist(struct Graph*,int);
void addvert(vert*,char*,struct Graph*);
void printG(struct Graph*);
void printVlist(vert*);
void addedge(vert*,struct Graph*,char*,char*);
int getindex(vert*,char*);
void isconn(struct Graph*,int*,int,int);
int checkargs(char*);

int main(int argc, char **argv){
  status=0;
  numV=1;
  flag=0; 
  struct Graph *graph=malloc(sizeof(struct Graph));
  vert *verhead=malloc(sizeof(vert)); 
  graph->arr=(list*)malloc(sizeof(list));

  char *names="@n";
  char *edges="@e";
  char *path ="@q";
 
/*  printf("no of args: %d\n",argc);
  int i;
  for(i=0;i<argc;i++){
   printf("%s\n",*(argv+i));}
*/
 
  int mrkr=0;
  FILE *fp=fopen(*(argv+1), "r");

  if(argc>1){
   if(fp==NULL){
    fprintf(stderr,"Error with file\n"); return 1;}
   if(argc>2){status=1;}
  mrkr=1;
  }

  int val=0;
  char *line=NULL;
  size_t len=0;
  while(val>-1){
//    printf("no1\n");

    if(mrkr==1){
     val=getline(&line,&len,fp);
 //    printf("no2\n");

     }else{
  //   printf("no3\n");

     val=getline(&line,&len,stdin);}
//     printf("%s",line);
    
    if(val>1){
   //  printf("no4\n");
 
      char *op=(char*)malloc(64*sizeof(char)); 
      sscanf(line,"%s",op);
    //  printf("this is op %s",op);
       line+=strlen(op);  
      // check if op is legal       

      if(strcmp(op,names)!=0 && strcmp(op,edges)!=0 && strcmp(op,path)!=0){
        fprintf(stderr,"Error: bad input\n");
        status=1;
        line=NULL;  
        continue;}

      char *str=(char*)malloc(64*sizeof(char)); 
      char *str2=(char*)malloc(64*sizeof(char)); 
 
      int offset=0; 
    // check for correct number of args    
      
      if(strcmp(op,names)==0){ 
        if(checkargs(line)>1){
          fprintf(stderr,"Error: bad no of args\n");
          status=1;
          line=NULL; 
          continue;} 
         while(sscanf(line,"%s%n",str,&offset)==1){
 //          printf("%s\n",str); 
            
           addvert(verhead,strdup(str),graph);
           line+=offset;
       // printf("%s\n",str); 
          free(str);
          str=(char*)malloc(64*sizeof(char)); 
          } 
      }

      if(strcmp(op,edges)==0){
       if(checkargs(line)>2){
          fprintf(stderr,"Error: bad no of args\n");
          status=1;
          line=NULL;
          continue;} 
 
        sscanf(line,"%s %s",str,str2); 
       
        if(getindex(verhead,str)==0 || getindex(verhead,str2)==0){
           fprintf(stderr,"Error: bad edge assign\n");
           status=1;
           line=NULL; 
           continue;}
         addedge(verhead,graph,str,str2);
         free(str);
         str=(char*)malloc(64*sizeof(char)); 
         free(str2); 
         str2=(char*)malloc(64*sizeof(char)); 

      }

      if(strcmp(op,path)==0){
        if(checkargs(line)>2){
          fprintf(stderr,"Error: bad no of args\n");
          status=1;
          line=NULL; 
          continue;} 

        int i;
        int *vtx=(int*)malloc(numV*sizeof(int)); 
        for(i=0;i<numV;i++){
          *(vtx+i)=i;} 
  
        sscanf(line,"%s %s",str,str2); 
        
       if(getindex(verhead,str)==0 || getindex(verhead,str2)==0){
           fprintf(stderr,"Error: bad path attempt\n");
           status=1;
           line=NULL; 
           continue;}
         
        isconn(graph,vtx,getindex(verhead,str),getindex(verhead,str2));
           printf("%d\n",flag); 
           flag=0;
         free(str);
         str=(char*)malloc(64*sizeof(char)); 
         free(str2); 
         str2=(char*)malloc(64*sizeof(char)); 

       }

     free(op);
     free(str);
     free(str2);
     line=NULL; 
     len=0; 
      } 
 //  printf("no5\n");

   }
   if(mrkr==1){fclose(fp);}
  // printf("no6\n");

   free(line); 
















//  printG(graph); 
//  printVlist(verhead);

//  printf("return val %d\n",getindex(verhead,"Mary"));

//  printt("no7\n"tt

 















 returt status;


}

void addlist(struct Graph *graph, int val){
  
  graph->arr=(list*)realloc(graph->arr,(numV+1)*sizeof(list));
  // must realloc 
  graph->arr[numV].head=malloc(sizeof(node));
  graph->arr[numV].head->ind=val;
  graph->arr[numV].head->next=malloc(sizeof(node)); 
  numV++;
}

void addvert(vert *verhead, char *name, struct Graph *graph){
  
  vert *cur=verhead;
  while(cur->next!=NULL){
     cur=cur->next;}
  
  cur->vval=numV;
  cur->vname=name;
  cur->next=malloc(sizeof(vert));
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

//  printf("%s %d %s %d\n",n1,v,n2,vadd);

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
  
//  printf("vtx %d\n",*(vtx+ptA)); 
  *(vtx+ptA)=0; 
  while(cur->next!=NULL){
  int nptA=cur->next->ind;
    if(*(vtx+nptA)==0 && nptA!=0){
 //      printf("here\n"); 
       cur=cur->next; 
       nptA=cur->next->ind;
     }
  // printf("%d\n",nptA);  
   if(nptA==0){
     return ;}
   if(nptA==ptB){ 
  // printf("found\n"); 
   flag=1; return ;} 
   
   isconn(graph,vtx,nptA,ptB);
   cur=cur->next;
   }

}

int checkargs(char *line){

    char *temp=strdup(line);
    int cnt=-1; int offset=0;
    char *str=(char*)malloc(64*sizeof(char));
//    printf("%s\n",temp);

    while(*temp){
       sscanf(temp,"%s%n",str,&offset);
       temp+=offset;
  //  printf("%d %s %s\n",offset,temp,str);
      cnt++;
    free(str);
    str=(char*)malloc(64*sizeof(char));
    if(cnt>1027){break;}
    }
//    free(temp);
    free(str);
    
   // printf("word cnt: %d\n",cnt);
    return cnt;

}
