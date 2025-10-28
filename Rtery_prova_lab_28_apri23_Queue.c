#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 30
#define MAX_FILE_LEN 120

typedef struct {
    char inputfile[MAX_FILE_LEN];
    char a;
    char b;
} FileParams;

typedef struct Node {
    char str[MAX_STRING_LEN];
    struct Node *next;
} Node;

typedef struct Queue {
    struct Node *head;
    struct Node *tail;
} Queue;

FileParams readinput(int argc, char *argv[]){
    if(argc != 4){
        fprintf(stderr, "errore: numero argomenti errato %s", argv[0]);
        exit(1);
    }

FileParams params;

char a = argv[2][0];
char b = argv[3][0];

if(a > b ){
    perror("errore valore di a o b errto");
    exit(1);
}

params.a = a;
params.b = b;

strncpy(params.inputfile, argv[1], MAX_FILE_LEN - 1);
params.inputfile[MAX_STRING_LEN - 1] = '\0';

return params;

}

void enqueue(Queue *q, char *str){
    Node *newnode = malloc(sizeof(Node));
    if(newnode == NULL){
        perror("errore durante l'allocazione del nuvo nodo");
        exit(1);
    }

    strncpy(newnode->str, str, MAX_STRING_LEN);
    newnode->str[MAX_STRING_LEN] = '\0';
    newnode->next = NULL;

    if(q->head == NULL){
        q->head = q->tail = newnode;
        return;
    }

    q->tail->next = newnode; //inserimento in coda l 'ultimo elemento della coda punta a newnode
    q->tail = newnode; // la nuova coda diventa newnode

}

char* dequeue(Queue *q){
     if (q->head == NULL) {
        return NULL;  // Coda vuota  ||se non controllo otterro segmentation fault||
    }
    char *str = malloc(sizeof(char)*MAX_STRING_LEN);
    if(str == NULL){
        perror("errore nella allocazione della stringa");
        exit(1);
    }

    Node* temp = q->head;

    strncpy(str, temp->str, MAX_STRING_LEN);
    str[MAX_STRING_LEN] = '\0';

    q->head = (q->head)->next;
    free(temp);

    return str;
}

Queue* buildQueue(const char *filename){
    FILE *fp = fopen(filename ,"r");
    if(!fp){
        perror("errore durante l'apertura del file");
        exit(1);
    }
 
    Queue *q = malloc(sizeof(Queue));
    q->head = NULL;
    q->tail = NULL;

    char buffer[MAX_FILE_LEN];

    while(fgets(buffer, MAX_STRING_LEN, fp)){
        buffer[strcspn(buffer ,"\n")] = '\0';
        buffer[MAX_STRING_LEN - 1] = '\0';

        enqueue(q, buffer);
    }

    return q;
}
void elab(char *str,int a, int b){
    for(int j = 0; j<strlen(str); j++){
            if(str[j] > a && str[j] < b){
                str[j] = '0';
            }
        }
    }


void printqueue(Queue *q,int a,int b){
    char *str;

    while(q->head != NULL){
        str = dequeue(q);

        elab(str,a,b);
        printf(" %s \n",str);
        free(str);

    }

}




int main(int argc, char *argv[]){
    FileParams params = readinput(argc, argv);

    Queue *head = buildQueue(params.inputfile);

    printqueue(head,params.a,params.b);



    



}