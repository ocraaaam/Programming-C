#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_LEN 120
#define MAX_STRING_LEN 30

typedef struct {
    char inputFile[MAX_FILE_LEN];
} FileParams;

typedef struct Node {
    char str[MAX_STRING_LEN];
    struct Node *next;
} Node;

typedef struct Queue {
    Node *head;
    Node *tail;
} Queue;

FileParams readinput(int argc , char *argv[]){
    if(argc != 2){
        fprintf(stderr, "errore numero argomnti errato");
        exit(1);
    }

    FileParams params;

    strncpy(params.inputFile, argv[1], MAX_FILE_LEN);
    params.inputFile[MAX_FILE_LEN] = '\0';

    return params;
}

Node* enqueue(Queue *q, char *str){
Node* newnode = malloc(sizeof(Node));
if(newnode == NULL){
    perror("errore allocazione newnndeo");
    exit(1);
}

strncpy(newnode->str, str, MAX_STRING_LEN);
newnode->str[MAX_STRING_LEN] = '\0';

if(q->tail == NULL){
    q->tail = q->head = newnode;
}

q->tail->next = newnode;
q->tail = newnode;

return q->tail;
}

char *dequeue(Queue *q){
    char *str = malloc(sizeof(char)*MAX_STRING_LEN);
    if(str == NULL){
        perror("errore allocazione str");
        exit(1);
    }

    if(q->head == NULL){
        perror("errore coda vuota");
        exit(1);
    }

    Node *current = q->head;

    strncpy(str, current->str, MAX_STRING_LEN);
    str[MAX_STRING_LEN] = '\0';

    q->head = q->head->next;

    free(current);

    return str;
}

Queue *buildqueue(const char *filename){
    FILE *fp = fopen(filename, "r");
    if(!fp){
        perror("errore durante apertura file");
        exit(1);
    }

    Queue *q = malloc(sizeof(Queue));
    q->tail = NULL;
    q->head = NULL;

    char buffer[MAX_STRING_LEN];

    while(fgets(buffer, MAX_STRING_LEN, fp)){
        buffer[strcspn(buffer, "\n")] = '\0';
        q->tail = enqueue(q, buffer);
    }
    fclose(fp);
    return q;

}

void printqueue(Queue *q){
    Node* current = q->head;
    while(current != NULL){
        printf(" %s \n", current->str);
        current = current->next;
    }

}

int findsizearr(Queue *q){
   int counter = 0; 
   Node *current = q->head;
   while(current != NULL){
    counter ++;
    current = current->next;
   }
   return counter;
}

char** buildstringarray(Queue *q ,int size){
    char **arr =  malloc(sizeof(char*)* size);
for(int i = 0; i<size; i++){
//arr[i] = malloc(sizeof(char)* MAX_STRING_LEN);
    arr[i] = dequeue(q);
}
return arr;
}

void printarray(char** arr, int size){
    for(int i = 0; i<size; i++){
        printf(" %s \n", arr[i]);

    }
}

int main(int argc, char *argv[]){
FileParams params = readinput(argc,argv);

Queue *q = buildqueue(params.inputFile);

printqueue(q);

printf("\n\n");

int size = findsizearr(q);

char **arr = buildstringarray(q, size);

printarray(arr, size);
}