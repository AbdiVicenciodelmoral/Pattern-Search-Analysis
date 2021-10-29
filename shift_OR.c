
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define WORD 32 // Word size in bits 
#define EOS 0 // End of string 
#define B 1 // Number of bits per state 
#define MAXSYM 128 // Size of the alphabet (ASCII) 
#define ASIZE 128


typedef struct indexNode {
    int index;
    int cmp;
    struct indexNode *next;
} iNode;

void printNodes(iNode *head){
    iNode *c = head;

    while (c) {
        printf("Pattern found at index %i and %i comparisons were performed\n", c->index,c->cmp);
        c = c->next;
        if(c){
        }
    }
}
void addNode(iNode **head, int index,int comp) {
    iNode *c = *head;
    iNode *newNode = (iNode *) malloc(sizeof(iNode));
    newNode->index = index;
    newNode->cmp = comp;
    newNode->next = NULL;
    if(*head == NULL){
        *head = newNode;
        return ;     
    }
    while (c->next != NULL) {
        c = c->next;
    }
    c->next = newNode;
}

void freeNodes(iNode **head){
    iNode* c = *head;
    iNode* temp = NULL;
    while (c != NULL)
    {
        temp = c->next;
        free(c);
        c = temp;
    }
    head = NULL;
}




// Search pat[1..m] in text[1..n] 
void sosearch( char *text, int n, char *pat, int m ) {
  unsigned int T[MAXSYM];
  unsigned int j, lim,state; 
  int i; 
  iNode *head = NULL;
  if( m > WORD ){
    perror( "Use pat size <= word size" );
  }
  for (i = 0; i < MAXSYM; ++i){
    T[i] = ~0; 
  } 
      
  for( lim=0, j=1, i=0; i<m; ++i, j <<= B){
      T[pat[i]] &= ~j;
      lim |= j ;
  }
  lim = ~(lim>>1); 

   /* Searching */ 
  /*for (state = ~0, j = 0; j < n; ++j) { 
      state = (state<<1) | T[text[j]]; 
      if (state < lim) 
        printf("%i\n",j - m + 1); 
  }*/
  

  int k = 0;
  state = ~0;
  int comparisons = 0;
  do {
      state = (state << B) | T[text[k]]; // Next state
      comparisons++;
      if( state < lim ){
        addNode(&head,k - m + 1,comparisons);
      }
      k++;
  } while( k < n );
  printNodes(head);
  freeNodes(&head);
  printf("Total comparisons made is %i\n",comparisons);
}

  int preSo(char *x, int m, unsigned int S[]) { 
    unsigned int j, lim; 
    int i; 
    for (i = 0; i < ASIZE; ++i) 
      S[i] = ~0; 
    for (lim = i = 0, j = 1; i < m; ++i, j <<= 1) { 
      S[x[i]] &= ~j; 
      lim |= j; 
    } 
    lim = ~(lim>>1); 
    return(lim); 
  } 

  void SO(char *x, int m, char *y, int n) { 
    unsigned int lim, state; 
    unsigned int S[ASIZE]; 
    int j; 
    if (m > WORD) 
      perror("SO: Use pattern size <= word size"); 

    /* Preprocessing */ 
    lim = preSo(x, m, S); 

    /* Searching */ 
    for (state = ~0, j = 0; j < n; ++j) { 
      state = (state<<1) | S[y[j]]; 
      if (state < lim) 
        printf("%i\n",j - m + 1); 
    } 
  } 


int main(int argc, char *argv[]) {
    char T[]="THREE TEST TEST TEST ";
    char P[] = "TEST";
    int n = strlen(T);
    int m = strlen(P);
    //Search(T,P);
    sosearch(T,n,P,m);
    //SO(P, m, T, n);
    //printf("MATCHED AT %i\n",match);
    return 0;
}
