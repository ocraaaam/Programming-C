#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 30
#define MAX_FILE_LEN 120

typedef struct {
    char inputFile[MAX_FILE_LEN];
} FileParams;

typedef struct Node {
    char str[MAX_STRING_LEN+1];
    struct Node *next;
} Node;

typedef struct Queue {
     Node *head;
     Node *tail;
} Queue;

FileParams readinput(int argc, char *argv[]){
if(argc != 2){
    fprintf(stderr, "eerroe: nuemro e+argoenti errato");
    exit(1);
}

FileParams params;

strncpy(params.inputFile, argv[1], MAX_FILE_LEN - 1);
params.inputFile[MAX_FILE_LEN - 1] = '\0';

return params;

}

Node* enqueueword(char *str, Queue *q){
    Node *newnode = malloc(sizeof(Node));
    if(newnode == NULL){
        perror("errore durante alloacazione str");
        exit(1);
    }
    strncpy(newnode->str , str, MAX_STRING_LEN + 1);
    newnode->str[MAX_STRING_LEN+1] = '\0';

    newnode->next = NULL;

    if(q->tail == NULL){
        q->tail = q->head = newnode;
    }

    q->tail->next = newnode;
    q->tail = newnode;

    return q->tail;
}

char* dequeueword(Queue *q){
    char *str = malloc(sizeof(char)*MAX_STRING_LEN);
    if(str == NULL){
        perror("errore alllocazioen str");
        exit(1);
    }

    if(q->head == NULL){
        perror("errore coda vuota");
        exit(1);
    }

    Node *temp = q->head;

    strncpy(str, temp->str, MAX_STRING_LEN);
    str[MAX_STRING_LEN] = '\0';

    q->head = q->head->next;
    free(temp);
    return str;

}

Queue* buildqueue(const char *filename){
    FILE *fp = fopen(filename, "r");
    if(!fp){
        perror("erroer durante aprtura file");
        exit(1);
    }

    Queue *q = malloc(sizeof(Queue));
    q->head = q->tail = NULL;

    char buffer[MAX_FILE_LEN];

    while(fgets(buffer, MAX_FILE_LEN, fp)){
        
        q->tail = enqueueword(buffer, q);
    }
    fclose(fp);
    return q;

}
int findsizearr(Queue *q){
    Node* current = q->head;
    int size = 0;

    while(current != NULL){
        size++;
        current = current->next;
        
    }
    return size;
}

char** buildstringarray(Queue *q, int* size){
    char **arr = malloc(sizeof(char*) *(*size));

    for(int i = 0; i< (*size); i++){
        char *str = dequeueword(q);
        arr[i] = malloc(sizeof(char) * (strlen(str) + 1));
        strcpy(arr[i], str);

    }
    return arr;
}

void printarray(char **arr, int size){
    for(int i = 0; i<size; i++){
        printf("%s \n", arr[i]);
    }
   
}
    



int main(int argc ,char *argv[]){
    FileParams params = readinput(argc, argv);

    Queue *q = buildqueue(params.inputFile);

    int size = findsizearr(q);

    char **arr = buildstringarray(q, &size);

    printarray(arr, size);
    
}

