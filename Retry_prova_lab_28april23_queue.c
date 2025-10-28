#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRING_LEN 20
#define MAX_FILE_LEN   120

typedef struct {
    char inputFile[MAX_FILE_LEN];
    char a; 
    char b;
} FileParams;

typedef struct Node {
     char str[MAX_STRING_LEN];
     struct Node *next;
} Node;

typedef struct Queue {
    Node *tail;
    Node *head;
} Queue;

FileParams readinput(int argc, char *argv[]){
    if(argc != 4){
        fprintf(stderr, "errore numero argomentyi errto");
        exit(1);
    }

    FileParams params;
    

    char a = argv[2][0];
    char b = argv[3][0];

    if(a < 'a' || a > 'z' || b < 'a' || b > 'z' || a>b){
        perror("errore valore a e b erratp");
        exit(1);
    }

    strncpy(params.inputFile, argv[1], MAX_FILE_LEN - 1);
    params.inputFile[MAX_FILE_LEN - 1] = '\0';

    params.a = a;
    params.b = b;

    return params;


}

void enqueue(char *str, Queue *q){
    Node* newnode = malloc(sizeof(Node));
    if(newnode == NULL){
        perror("errooer durante alloaczione del nuovo nodo");
        exit(1);
    }
    strncpy(newnode->str, str, MAX_STRING_LEN);
    newnode->str[MAX_STRING_LEN] = '\0';

    newnode->next = NULL;

    if((q->tail) == NULL){
        q->head = q->tail = newnode;
        return;
    }

    q->tail->next = newnode;
    q->tail = newnode;
}

char * dequeue(Queue *q){
    char *str = malloc(sizeof(char)*MAX_STRING_LEN);
    if(str == NULL){
        perror("eroore alloacazione str");
        exit(1);
    }

    if(q->head == NULL){
        perror("errore queue vuoto");
        exit(1);
    }

    Node *temp = q->head;

    strncpy(str, temp->str, MAX_STRING_LEN);
    str[MAX_STRING_LEN] = '\0';

    q->head = (q->head)->next;
    free(temp);

    return str;
}

Queue* buildqueue(const char *filename){
    FILE *fp = fopen(filename, "r");
    if(!fp){
        perror("errore apertyra file");
        exit(1);
    }

    Queue *q = malloc(sizeof(Queue));
    q->head = NULL;
    q->tail = NULL;

    char buffer[MAX_FILE_LEN];

    while(fgets(buffer, MAX_STRING_LEN, fp)){
        buffer[strcspn(buffer, "\n")] = '\0';
        buffer[MAX_STRING_LEN - 1] = '\0';
        enqueue(buffer, q);
    }
    fclose(fp);
    return q;

}

void printqueue(Queue *q){
    char *str;

    while(q->head != NULL){
        str = dequeue(q);
        printf("%s \n", str);
        free(str);
        
        
    }
}


int main(int argc, char *argv[]){
    FileParams params = readinput(argc, argv);

    Queue *q = buildqueue(params.inputFile);


    printqueue(q);



}