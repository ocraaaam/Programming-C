#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 30
#define MAX_FILE_LEN 125

typedef struct {
    char inputFile[MAX_FILE_LEN];
    int k;
} FileParams;

typedef struct stack {
    char str[MAX_STRING_LEN];
    struct stack *next;
} stack;

FileParams readinput(int argc, char *argv[]){
    if(argc != 3){
        fprintf(stderr, "errore: numero argomenti errati");
        exit(1);
    }

    FileParams params;

    int k = atoi(argv[2]);

    if(k < 5 || k > 15){
        fprintf(stderr, "errore valore k errato");
        exit(1);
    }

    strncpy(params.inputFile, argv[1], MAX_FILE_LEN  -1);
    params.inputFile[MAX_FILE_LEN  -1] = '\0';

    params.k = k;

    return params;
}

stack* pushword(const char *str, stack *top){
    stack* newnode = malloc(sizeof(stack));
    if(newnode ==  NULL){
        perror("errore duarente l'allocazione del nuovo nodo");
        exit(1);
    }

    strncpy(newnode->str, str, MAX_STRING_LEN);
    newnode->str[MAX_STRING_LEN] = '\0';

    newnode->next = top;
    top = newnode;

    return newnode;
}

char *popword(stack **top){
    if( *top == NULL){
        perror(" stack vuota");
        exit(1);
    }

     stack *temp = *top;

    char *str = malloc(sizeof(char)*MAX_STRING_LEN);
    if(str == NULL){
        perror("errroe durante allocazione stringa");
        exit(1);
    }


    strncpy(str, temp->str, MAX_STRING_LEN);
    str[MAX_STRING_LEN] = '\0';

    *top = (*top)->next;
    free(temp);

    return str;
}

stack* buildstack(const char *filename, stack *top){
    FILE *fp = fopen(filename, "r");
    if(!fp){
        perror("errore durante l'apertuar del file");
        exit(1);
    }

    char buffer[MAX_STRING_LEN];

    while(fgets(buffer, MAX_STRING_LEN, fp)){
        buffer[strcspn(buffer, "\n")] = '\0';
        top = pushword(buffer, top);
    }
    fclose(fp);
    return top;

}

void printstack(stack **top){

    while(top != NULL){
       char* str = popword(top);
       printf("%s", str);
       free(str);
    }
    
}

int main(int argc, char *argv[]){
    FileParams params = readinput(argc, argv);

    stack *top = NULL;

    top = buildstack(params.inputFile, top);

    printstack(&top);
}

