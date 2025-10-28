#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 30
#define MAX_FILE_LEN   120

typedef struct {
    char inputFile[MAX_FILE_LEN];
}FileParams;

typedef struct Node {
    char str[MAX_STRING_LEN];
    struct Node *next;
} Node;

typedef struct Queue {
    Node *head;
    Node *tail;
} Queue;

FileParams readinput(int argc, char *argv[]){
    if(argc != 2){
        fprintf(stderr, "errore: numero argomenti errato");
        exit(1);
    }

    FileParams params;
    strncpy(params.inputFile, argv[1], MAX_FILE_LEN);
    params.inputFile[MAX_FILE_LEN] = '\0';

    return params;

}
Node* enqueue(Queue *q, char *str){
    Node *newnode = malloc(sizeof(Node));
    if(newnode == NULL){
        perror("errore allocazione nuovo nodo");
        exit(1);
    }

    newnode->next = NULL;

    strncpy(newnode->str, str, MAX_STRING_LEN - 1);
    newnode->str[MAX_STRING_LEN -1] = '\0';

    if(q->tail == NULL){
        q->head = q->tail = newnode;
    }

    q->tail->next = newnode;
    q->tail = newnode;
    return q->tail;

}

char* dequeue(Queue *q){
    char *str = malloc(sizeof(char)*MAX_STRING_LEN);
    if(str == NULL){
        perror("errore allocazione str");
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
    perror("errore durante apertura di file");
    exit(1);
    }

    char buffer[MAX_STRING_LEN];

    Queue *q = malloc(sizeof(Queue));
    q->head = NULL;
    q->tail = NULL;

    while(fgets(buffer, MAX_STRING_LEN, fp)){
        buffer[strcspn(buffer, "\n")] = '\0';
        q->tail = enqueue(q, buffer);
    }
    fclose(fp);
    return q;
}

int findesizearr(Queue *q){
    int counter = 0;
    Node *current = q->head;
    while(current != NULL){
        counter++;
        current = current->next;

    }
    return counter;
}

char** buildstringarr(Queue *q, int size){
    char **arr = malloc(sizeof(char*)* size);
    for(int i = 0; i<size; i++){
    
        arr[i] = malloc(sizeof(char)* MAX_STRING_LEN);
        arr[i] = dequeue(q);
        
    }
    return arr;

}

void sortarr(char **arr,int size){
    for(int i = 0; i<size; i++ ){
        for(int j = 0; j<size - i -1; j++){
            if(strcmp(arr[j], arr[j + 1]) > 0){
            char hold = arr[j];
            arr[j] = arr[j+1];
            arr[j+1] = hold;
            }
        }
    }
}

void printarray(char **arr, int size){
    for(int i= 0; i<size; i++){
        sortarray(arr, size);
        printf(" %s \n", arr[i]);
    }

}

int main(int argc, char *argv[]){
    FileParams params = readinput(argc, argv);

    Queue *q = buildqueue(params.inputFile);

    int size = findesizearr(q);

    char **arr = buildstringarr(q, size);

    printarray(arr, size);


}

