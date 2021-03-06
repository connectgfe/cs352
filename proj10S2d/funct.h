
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
  int targ;
  int edgeof;
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
FILE *fp;
char *testln;
char *targ;

void addlist(struct Graph*,char*,vert*);
void addvert(vert*,char*,struct Graph*,int);
void printG2(struct Graph*);
void printVlist(vert*);
void addedge2(vert*,struct Graph*,char*,char*);
int getindex(vert*,char*);
void isconn(vert*,struct Graph*,int*,int,int);
void setcmnd(vert*,char*,char*,graph*);
char *getcmnd(vert*,char*);
void settarg(vert*,char*);
void buildm(vert*,struct Graph*,int*,int,int);
int istarg(vert*,char*);
void myfree(vert*,graph*);
