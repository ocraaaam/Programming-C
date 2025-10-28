#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 30
#define MAX_FILE_LEN 120

typedef struct {
    char inputFile[MAX_FILE_LEN];
    double number;
} FileParams;

typedef struct Node {
    double number;
    char str[MAX_STRING_LEN];
    struct  Node* next;
    struct  Node* prev;
} Node;

FileParams readinput(int argc, char *argv[]){

    if(argc != 3){
        fprintf(stderr, "errore: numero di argomenti errato");
        exit(1);
    }

    FileParams params;

    double number = atof(argv[2]);

    if(number < 1.0 || number > 20.0){
        fprintf(stderr, "errore valore di number errato");
        exit(1);
    }

    strncpy(params.inputFile, argv[1], MAX_STRING_LEN - 1);
    params.inputFile[MAX_STRING_LEN - 1] = '\0';

    params.number = number;

    return params;
}

Node* insertNode(char* str, double number, Node* head){
    Node *newnode = malloc(sizeof(Node));
    if(newnode == NULL){
        perror("errore durantre allocazione di newnode");
        exit(1);
    }
    strncpy(newnode->str, str, MAX_STRING_LEN);
    newnode->str[MAX_STRING_LEN] = '\0';

    newnode->number = number;

    newnode->next = NULL;
    newnode->prev = NULL;

    if(head == NULL){
        return newnode;
    }

    Node *current = head;
    Node *previous = NULL;

    while(current != NULL && strcmp(current->str, str) <0 ){

        previous = current;
        current = current->next;
    }

    if(previous == NULL){
        newnode->next = head;
        head->prev = newnode;
        return newnode;
    }
    else{

        newnode->next = current;
        newnode->prev = previous;
        previous->next = newnode;

        if(current != NULL){
            current->prev = newnode;
        }

    }
    return head;
}

Node* buildlist(const char *filename){
    FILE *fp = fopen(filename, "r");
    if(!fp){
        perror("errore duramte apertura file");
        exit(1);
    }

    char buffer[MAX_STRING_LEN];
    double buffer1;

    Node* head = NULL;    

    while(fscanf(fp, "%lf %s", &buffer1, buffer) == 2){  // ERRORE RICORDATI DI INSERIRE QUACLOSA IN WHILE PER NON FARE FARE CICLO INFINITO
        head = insertNode(buffer, buffer1, head);
    }
    fclose(fp);
    return head;
}

void printlist(Node* head, double number){
    Node* current = head;

    while(current != NULL){

        printf("%s\n  %f\n", current->str, current->number);
        current= current->next;
    }

}

int* elab(Node* head, double number){
    int *counter;
    Node* current = head;
    while(current != NULL){
        if(current->number >= number){
        counter++;
        }
        current = current->next;
    }
    return counter;
}

int main (int argc, char *argv[]){
    FileParams params = readinput(argc, argv);

    Node *head = buildlist(params.inputFile);

    printlist(head, params.number);
}