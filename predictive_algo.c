#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
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

void pred_Search(char *P,char* T){
    int m = strlen(P);
    int n = strlen(T);
    int i  = 0;
    int comp = 0;
    bool P_flag = true;
    iNode *head = NULL;
    while ((i+m)-1 < n){
        comp ++;
        /*Compares the first character of the pattern with T[i]*/
        //If a MISMATCH occurs
        if(P[0] != T[i]){
            if(T[i] == ' '){
                i ++;
            }
            else{
                i+=2;
            }
        }
        //If a MATCH occurs 
        else{
            comp ++;
            //Match at last character in pattern
            if(P[m-1] == T[i+(m-1)]){
                //Compare remaining characters from right to left
                int j;
                for(j = (m-1)-1; j>=0; j--){
                    comp++;
                    if( P[j] != T[i+j]){
                        P_flag = false;
                        //skip past mismatch
                        i = i + j;
                        break;
                    }       
                }
                if(P_flag == true){
                    addNode(&head,i,comp);
                    i++;  
                }        
            }
            //MISMATCH at last character in pattern
            else{
                 if(T[i+(m-1)] == ' '){
                     i  = i + (m-1) + 1;
                 }
                else{
                    if (T[i+(m+1)-1] == ' '){
                        i = i+(m-1) + 2;
                    }   
                    else{
                        i = i + 2;
                    }
                }        
            }
        }
    }
    printNodes(head);
    freeNodes(&head);
    printf("Total Comparisons made: %i\n",comp);
    return;
}


int main(int argc, char *argv[]) {
    
    char t[] = "Off with her head !, the Queen shouted at the top of her voice.";
    char p[]= "Queen";
    pred_Search(p,t);
   return 0;
}