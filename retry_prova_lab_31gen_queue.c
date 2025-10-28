#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 30

typedef struct {
    char a;
    char b;
    int x;
    int y;
    int n;
}FileParams;

typedef struct Node {
    char str[MAX_STRING_LEN];
    struct Node* next;
}Node;

typedef struct Queue {
    Node* head;
    Node* tail;
}Queue;

FileParams readinput(int argc, char* argv[]){
    if(argc != 6){
        fprintf(stderr, "errore numero argomenti errato");
        exit(1);
    }

    FileParams params;

    char a = argv[1][0];
    char b = argv[2][0];
    int x = atoi(argv[3]);
    int y = atoi(argv[4]);
    int n = atoi(argv[5]);

    if(a < 'a' || a > 'z' || b < 'a' || b > 'z' || a>b){
        perror("valore a e b errato");
        exit(1);
    }

    if(x < 5 || x > 30 || y < 5 || y > 30 || y-x<5){
        perror("valore x e y errato");
        exit(1);
    }

    if(n < 15 || n > 25){
        perror("valore n errato");
        exit(1);
    }
    params.a = a;
    params.b = b;
    params.x = x;
    params.y = y;
    params.n = n;

    return params;
}

char* genstring(int x, int y, char a, char b){
    int L = rand()%(y-x+1)+x;
    char* str = malloc(sizeof(char)*L);
    for(int i = 0; i<L; i++){
        str[i] = (char)(rand()%(b-a+1)+a);
    }
    return str;
}

Node* enqueue(Queue* q, char* str){
Node* newnode = malloc(sizeof(Node));
if(!newnode){
    perror("errore allocazione newnode");
    exit(1);
}

strncpy(newnode->str, str, MAX_STRING_LEN -1);
newnode->str[MAX_STRING_LEN-1] = '\0';

if(q->head == NULL){
    q->head = q->tail = newnode;
}

q->tail->next = newnode;
q->tail = newnode;

return newnode;
}



char* dequeue(Queue*q){
char* str = malloc(sizeof(char)* MAX_STRING_LEN);
if(!str){
    perror("errore allocazione str");
    exit(1);
}

if(q->head == NULL){
    perror("coda vuota");
    exit(1);
}

Node* tmp = q->head;

strncpy(str, tmp->str, MAX_STRING_LEN -1);
str[MAX_STRING_LEN-1] = '\0';

q->head = q->head->next;

free(tmp);

return str;
}



Queue* buildQueue(int n, char a, char b, int x, int y){

    Queue* q = malloc(sizeof(Queue));
    q->tail = NULL;
    q->head = NULL;

    for(int i = 0; i<n; i++){
        char* str = genstring(x, y ,a, b);
        q->tail = enqueue(q, str );
        printf("buildQueue(), (i=%d) : %s \n", i, str);
    }

    return q;
}

void elab(char* str){
    for(int i = 0; i<strlen(str); i++){
        if(str[i] == 'a' || str[i] == 'e' || str[i] == 'i'  || str[i] == 'o' || str[i] == 'u' ){
            str[i] = 'X';
        }
    }
}


void printstring(Queue *q){
    char* str;
    int counter = 0;
    while(q->head != NULL){
        str = dequeue(q);
        elab(str);
        printf("printStrings(), (i=%d) : %s \n", counter, str);
        counter++;
    }
}

int main(int argc, char* argv[]){
    FileParams params = readinput(argc, argv);

    Queue* q = buildQueue(params.n, params.a, params.b, params.x, params.y);

    printf("\n");
    printstring(q);
}