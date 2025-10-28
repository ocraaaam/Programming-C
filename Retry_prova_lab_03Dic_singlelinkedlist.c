#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_LEN 120
#define MAX_STRING_LEN 30

typedef struct {
    char inputFile[MAX_FILE_LEN];
    int x;
    int y;
}FileParams;

typedef struct Node {
    char nome[MAX_STRING_LEN];
    char cognome[MAX_STRING_LEN];
    int eta;
    struct Node* next;
}Node;

FileParams readinput(int argc, char *argv[]){
    if(argc != 4){
        fprintf(stderr, "errore nuemro argometni errato");
        exit(1);
    }

    FileParams params;

    strncpy(params.inputFile, argv[1], MAX_FILE_LEN - 1);
    params.inputFile[MAX_FILE_LEN - 1] = '\0';

    int x = atoi(argv[2]);
    int y = atoi(argv[3]);

    if(x  < 10 || x > 50 || y < 10 || y > 60 || x>y){
        perror("valori x e y errati");
        exit(1);
    }

    params.x = x;
    params.y = y;

    return params;
}

Node* insertNode(Node* head, char* nome, char* cognome, int eta){
Node* newnode = malloc(sizeof(Node));
if(!newnode){
    perror("errreo allocazione nodo");
    exit(1);
}

strncpy(newnode->nome, nome, MAX_STRING_LEN);
newnode->nome[MAX_STRING_LEN] = '\0';

strncpy(newnode->cognome, cognome, MAX_STRING_LEN);
newnode->cognome[MAX_STRING_LEN] = '\0';

newnode->eta = eta;

if(head == NULL){
    return newnode;
}

Node* current = head;
Node* previous = NULL;

while(current != NULL && strcmp(current->cognome, newnode->cognome) <0 ){
    previous = current;
    current = current->next;
}

if(previous == NULL){
    newnode->next = head;
}else{
    newnode->next = current;
    previous->next = newnode;
}
return head;
}

Node* BuildList(const char* filename){
    FILE* fp = fopen(filename, "r");
    if(!fp){
        perror("errore apertura file");
        exit(1);
    }

    Node* head = NULL;

    char namebuffer[MAX_STRING_LEN];
    char surnamebuffer[MAX_STRING_LEN];
    int eta;


    while(fscanf(fp, "%s  %s  %d",namebuffer, surnamebuffer, &eta ) != EOF ){
        head = insertNode(head, namebuffer, surnamebuffer, eta);
    }

    fclose(fp);
    return head;
}

void PrintList(Node* head){
Node* current = head;
while(current != NULL){
    printf("%s %s %d \n", current->nome, current->cognome, current->eta);
    current = current->next;
}
}

void removebyage(Node* head, int x, int y){
Node* current = head;
Node* previous = NULL;

while(current != NULL){
    if(current->eta > x && current->eta < y){
        Node* to_delete = current;
        if(previous== NULL){
            head = current->next;
        }else{
            previous->next = current->next;
        }

        current = current->next;
        free(to_delete);
        
    }else{
    previous = current;
    current = current->next;
    }
}
}

int main(int argc, char*argv[]){
    FileParams params = readinput(argc, argv);


    Node* head = BuildList(params.inputFile);

    PrintList(head);

    removebyage(head, params.x, params.y);

    printf("\n\n\n--List Ordered--\n\n");
    PrintList(head);


}