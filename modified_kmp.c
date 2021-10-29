#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <string.h>


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



/*  This function computes the Longest prefix suffix
    in the given pattern                             */
void COMPUTELPSARRAY(char *P,int m,int *c){
    int j = 0;
    int i = j + 1;
    c[0] = 0;
    while ( i < m-1 ){
        while ( P[i] != P[j] && i < (m) ){
            c[i]= 0;
            i++;
        }
        if (P[i] == P[j]){
            c[i] = j + 1;
            i++;
            j++;
        }
    }
    int k;
    while (j> 0 && P[i] != P[j] ){
            k = c[i-1];
            j = c[k];
    }
    if(P[i] == P[j]){
            j++;
            c[i] = j;
    }
}

/*Modified KMP Algorithm*/
void mod_KMP(char *P,char* T){
    int m = strlen(P);
    int n = strlen(T);
    int c[m];
    int j = 0;
    iNode *head = NULL;
    int comparison = 0;
    COMPUTELPSARRAY(P,m,c);
    int i = 0;
    while(i < n){
        if(P[j] == T[i]){
            comparison ++;
            j ++;
            i ++;
        }
        if(j == m){
            int idx = i-j;
            addNode(&head,idx,comparison);
            j = c[j - 1];
        }
        else if(i < n && P[j] != T[i]){
            comparison ++;
            if(j != 0){
                j = c[j - 1];
            }
            else{
               i++; 
            }
        }      
    }
    printNodes(head);
    freeNodes(&head);
    printf("Total Comparisons made: %i\n",comparison);
}




/* main function to call above defined function */
int main(int argc, char *argv[]) {
    char t[] = "Off with her head !, the Queen shouted at the top of her voice.";
    char p[]= "Queen";
    mod_KMP(p,t);

   return 0;
}