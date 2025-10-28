#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STRING_LEN 30
#define MAX_FILE_LEN 150

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
        fprintf(stderr, "erroer numero argomenti errato");
        exit(1);
    }

    FileParams params;

    int k = atoi(argv[2]);

    if(k  < 7 || k > 13){
        perror("errore valore k errato");
        exit(1);
    }

    strncpy(params.inputFile, argv[1], MAX_FILE_LEN - 1);
    params.inputFile[MAX_FILE_LEN - 1] = '\0';

    params.k = k;

    return params;

}


Node* insertlist(Node *head, char *str){
    Node* newnode = malloc(sizeof(Node));
    if(newnode == NULL){
        perror("errore durante allocazione");
        exit(EXIT_FAILURE);
    }

    newnode->next = NULL;
    newnode->prev = NULL;

    strncpy(newnode->str, str, MAX_STRING_LEN -1);
    newnode->str[MAX_STRING_LEN - 1] = '\0';

    if(head == NULL){
        return newnode;
    }

    Node *current = head;
    Node *previous = NULL;

    while(current != NULL && strcmp(current->str , str) <0){
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
        perror("errore durante apertura file");
        exit(1);
    }

    char buffer[MAX_STRING_LEN];

    Node* head = NULL;

    while(fgets(buffer, MAX_STRING_LEN, fp)){
        buffer[strcspn(buffer, "\n")] = '\0';

        head = insertlist(head, buffer);
    }
    fclose(fp);
    return head;
}

void printlist(Node* head){
    Node *current = head;

    while(current != NULL){
        if(strlen(current->str)==0){
            continue;
        }
        printf("%s\n", current->str);
        current = current->next;
    }
    
}

int main(int argc, char *argv[]){
    FileParams params = readinput(argc, argv);

    Node* head =buildlist(params.inputFile);
   
    printlist(head);
}