#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FILE_LEN 125
#define MAX_STRING_LEN 30

typedef struct {
    char inputFile[MAX_FILE_LEN];
    int k;
} FileParams;

typedef struct Node {
    char str[MAX_STRING_LEN];
    struct Node *next;
    struct Node *prev;
} Node;

FileParams readinput(int argc, char *argv[]){
    if(argc != 3){
        fprintf(stderr, "errore numero argomenti errato");
        exit(1);
    }
    FileParams params;

    int k = atoi(argv[2]);

    if(k < 7 || k > 13){
        perror("errore valore k errato");
        exit(1);
    }

    strncpy(params.inputFile, argv[1], MAX_FILE_LEN);
    params.inputFile[MAX_FILE_LEN] = '\0';

    params.k = k;

    return params;

}

Node *insertlist(Node* head, char *str){
    Node *newnode = malloc(sizeof(Node));
    if(newnode == NULL){
        perror("errore durante allocazione newnode");
        exit(1);
    }
    strncpy(newnode->str, str, MAX_STRING_LEN);
    newnode->str[MAX_STRING_LEN] = '\0';

    newnode->next = NULL;
    newnode->prev = NULL;

     if(head == NULL){
        return newnode; ///FONDAENTALE
     }

    Node *current = head;
    Node *previous = NULL;


    while(current != NULL){
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
    perror("errore nella apertur del file");
    exit(1);
    }

    Node *head = NULL;

    char buffer[MAX_FILE_LEN];

    while(fgets(buffer, MAX_FILE_LEN, fp)){
        buffer[strcspn(buffer, "\n")] = '\0';
        head = insertlist(head, buffer);
    }
    fclose(fp);
    return head;

}

void printlist(Node *head){
    Node *current = head;
    while(current != NULL){
        printf(" %s \n", current->str);

        current = current->next; //FONDAMENTALE

    }
}

void elab(Node *head,int k){
    Node *current = head;
    int counter = 0;

    while(current != NULL){
        if(strlen(current->str)>k){
        counter++;
        }

        current= current->next;
    }

}


int main(int argc, char *argv[]){
    FileParams params = readinput(argc, argv);

    Node *head = buildlist(params.inputFile);

    printlist(head);
}