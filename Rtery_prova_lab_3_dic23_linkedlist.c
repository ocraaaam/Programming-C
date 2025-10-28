#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 30
#define MAX_FILE_LEN 250

typedef struct {
    char inputFile[MAX_FILE_LEN];
    int x;
    int y;
} FileParams;

typedef struct Node {
    char nome[MAX_STRING_LEN + 1];
    char cognome[MAX_STRING_LEN +1];   //inserire + 1 per il terminatore string
    int eta;
    struct Node *next;
} Node;


FileParams readinput(int argc, char *argv[]){
    if(argc != 4){
        fprintf(stderr, "\n usage: %s <filename> <x> <y>", argv[1]);
        exit(1);
    }

    FileParams params;

    int y = atoi(argv[3]);
    int x = atoi(argv[2]);

    if( y < 10 || x > 60 || y< 10 || y >60 || x>y ){
        perror("errore valore x o y errato");
        exit(1);
    }

    strncpy(params.inputFile, argv[1], MAX_FILE_LEN -1 );
    params.inputFile[MAX_FILE_LEN + -1] = '\0';

    params.x = x;
    params.y = y;

    return params;
}

void insertRecord(const char *nome,const char *cognome,int eta,Node* head ){
  Node* newnode = malloc(sizeof(Node));
    if(newnode == NULL){
    perror("errore durante allocazione nenwode");
    exit(1);
    }
      strncpy(newnode->nome, nome, MAX_STRING_LEN);
      strncpy(newnode->cognome, cognome, MAX_STRING_LEN);
      newnode->eta = eta;

    newnode->next = NULL;

    Node* current = head;
    Node* previous = NULL;

    if(head == NULL){
        head = newnode;
        return;
    }

    while(current != NULL && strcmp(newnode->cognome, current->cognome)>0 ){

        previous = current;
        current = current->next;
    }

    if(previous == NULL){
        newnode->next = current;
       head = newnode;
    }
    else{
        previous->next = newnode;
        newnode->next = current;
    }
}

void printlist(Node **head){
    Node *current = *head;

    while(current != NULL){
        printf("%s %s %d \n", current->nome, current->cognome, current->eta);

        current = current->next;
    }

}

void removebyage(Node **head, int x, int y) {
    Node *current = *head;
    Node *previous = NULL;

    while (current != NULL) {
        if (current->eta >= x && current->eta <= y) {
            // Nodo da rimuovere
            Node *temp = current;
            if (previous == NULL) {
                // Rimuovere il primo nodo
                *head = current->next;
            } else {
                // Rimuovere un nodo intermedio o finale
                previous->next = current->next;
            }
            current = current->next;
            free(temp);
        } else {
            // Nodo non da rimuovere
            previous = current;
            current = current->next;
        }
        
    }
}


Node* buildlist(const char* filename){
    FILE *fp = fopen(filename, "r");
    if(!fp){
        fprintf(stderr, "\n error opening file %s ", filename);
        exit(1);
    }

    char nome[MAX_STRING_LEN + 1];
    char cognome[MAX_STRING_LEN + 1];
    int eta;

    struct Node *head = NULL;



       while (fscanf(fp, "%s %s %d", nome, cognome, &eta) == 3) { // or != EOF
        insertRecord(nome, cognome, eta, head);
        }
        
    
    fclose(fp);
    return head;
}

int main(int argc ,char *argv[]){
    FileParams params = readinput(argc, argv);

    Node *head = buildlist(params.inputFile);

    printlist(&head);

    removebyage(&head, params.x, params.y);

    printf("\n lista ordinata \n");

    printlist(&head);
}