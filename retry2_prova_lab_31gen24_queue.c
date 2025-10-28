#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 30
#define MAX_FILE_LEN 100

typedef struct {
    char a;
    char b;
    int x;
    int y;
    int n;
} FileParams;

typedef struct Node{
    char str[MAX_STRING_LEN];
    struct Node *next;
} Node;

typedef struct Queue{
    Node *head;
    Node *tail;
} Queue;

FileParams readinput(int argc, char *argv[]){
if(argc != 6){
    fprintf(stderr, "errore numero argomeni errato");
    exit(1);
}

FileParams params;

char a = argv[1][0];
char b = argv[2][0];
int x = atoi(argv[3]);
int y = atoi(argv[4]);
int n = atoi(argv[5]);

if(a < 'a' || a > 'z' || b < 'a' || b > 'z' || a > b){
    perror("errore valore a e b");
    exit(1);
}

if(x < 5 || x > 30 || y < 5 || y > 30 || y-x<5){
    perror("erroe valore x e y errato");
    exit(1);
}

if(n < 15 || n > 25){
    perror("erroe valore n errato");
    exit(1);
}


params.a = a;
params.b = b;
params.x = x;
params.y = y;
params.n = n;

return params;
}

unsigned int get_random() { 
    static unsigned int m_w = 123456; 
    static unsigned int m_z = 789123; 
    m_z = 36969 * (m_z & 65535) + (m_z >> 16); 
    m_w = 18000 * (m_w & 65535) + (m_w >> 16); 
    return (m_z << 16) + m_w; 
    }

char* genstring(char a, char b, int x, int y){
int L = rand()%(y - x + 1) + x;

char *str = malloc(sizeof(char)*L);
    for(int i = 0; i<L; i++){
        str[i] = (get_random() % (b - a + 1) + a);
    }
return str;
}

Node* enqueue(char *str, Queue *q){
Node *newnode= malloc(sizeof(Node));
if(newnode == NULL){
    perror("errore allocazione newnode");
    exit(1);
}

if(q->tail == NULL){
    q->tail = q->head = newnode;
}

strncpy(newnode->str, str, MAX_STRING_LEN);
newnode->str[MAX_STRING_LEN] = '\0';

q->tail->next = newnode;
q->tail = newnode;

return newnode;
}

Queue* buildqueue(char a, char b, int x, int y, int n){
    Queue *q = malloc(sizeof(Queue));
    q->tail = NULL;
    q->head = NULL;
    //char *str; se la creo globale rispetto al ciclo rimarra solo a e b;

    for(int i = 0; i<n; i++){
      char *str = genstring(a, b, x, y);
        q->tail = enqueue(str, q);
        printf("%s \n", str);
    }
    return q;
}

int main(int argc, char *argv[]){
    FileParams params = readinput(argc, argv);

    Queue *q = buildqueue(params.a, params.b, params.x, params.y, params.n);

}
