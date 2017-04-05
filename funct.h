
typedef struct Node{
  int ind;
  char *name;
  struct Node *next;
}node;

typedef struct List{
  struct Node *head;
}list;

typedef struct Graph{

  struct List *ver;
  struct Graph *nextv;
}graph;

typedef struct Vert{
  char *vname;
  int vind;
  struct Cmnd *cmd;
  struct Vert *next;
}vert;

typedef struct Cmnd{
  char *comnd;
  struct Cmnd *nextc;
}cmnd;


int status;
extern int numV;
int flag;
int mrkr;

void addlist(struct Graph*,char*);
void addvert(vert*,char*,struct Graph*);
void printG2(struct Graph*);
void printVlist(vert*);
void addedge2(vert*,struct Graph*,char*,char*);
int getindex(vert*,char*);
void isconn(struct Graph*,int*,int,int);
void setcmnd(vert*,char*,char*);
char *getcmnd(vert*,char*);
