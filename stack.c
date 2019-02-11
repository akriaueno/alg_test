#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_ELEM 128

typedef int StElmType;

struct StackAP {
  StElmType *bottom, *limit, *current;
};
typedef struct StackAP *pStackAP;

pStackAP StAPCreate(int n) {
  pStackAP p;
  p = (pStackAP)malloc(sizeof(struct StackAP));
  p->bottom = (StElmType *)malloc(n*sizeof(StElmType));
  p->current = &p->bottom[-1];
  p->limit = &p->bottom[n-1];
  return p;
}

StElmType Top (pStackAP s) {
  return *s->current;
}

StElmType Pop (pStackAP s) {
  if (s->current == s->bottom) {
    printf("stack underflow\n");
    exit(1);
  }
  return *(s->current--);
}

void Push (StElmType x, pStackAP s) {
  if (s->current == s->limit) {
    printf("stack overflow\n");
    exit(1);
  }
  *(++s->current) = x;
}

int IsEmpty (pStackAP s) {
  return s->current == &s->bottom[-1];
}

void PrintStack(pStackAP s) {
  StElmType *p = s->bottom;
  printf("[");
  while (p != s->current) {
    printf("%d ", *p);
    p++;
  }
  printf("%d]\n", *s->current);
}

int main() {
  pStackAP s = StAPCreate(MAX_ELEM);
  char buf[128];
  char ope[128];
  StElmType x = 0;
  printf("usage:\n\tpush <number>\n\tpop\n");
  while(fgets(buf,sizeof(buf),stdin)!=NULL) {
    sscanf(buf, "%s %d ", ope, &x);
    if (strcmp(ope, "push") == 0) {
      Push(x, s);
    } else if (strcmp(ope, "pop") == 0) {
      printf("%d \n", Pop(s));
    }
    PrintStack(s);
    x = 0;
  } 
  printf("%s, %d\n", ope, x);
}
