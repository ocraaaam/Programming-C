#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 30
#define MAX_FILE_LEN 120

typedef struct {
    char inputFile[MAX_FILE_LEN];
    int k;
} FileParams;

typedef struct Stack {
    char str[MAX_STRING_LEN];
    struct Stack *next;
} Stack;

FileParams readinput(int argc, char *argv[]){
    if(argc != 3){
        fprintf(stderr, "errore numero argomenti errato");
        exit(1);
    }

    FileParams params;

    int k = atoi(argv[2]);

    if(k < 5 || k > 15){
        perror("errore : valore k errato");
        exit(1);
    }

    strncpy(params.inputFile, argv[1], MAX_FILE_LEN);
    params.inputFile[MAX_FILE_LEN] = '\0';

    params.k = k;

    return params;
}

Stack* pushword(Stack *top, char *str){
    Stack* newnode = malloc(sizeof(Stack));
    if(newnode == NULL){
        perror("errore durante alloaczione newnode");
        exit(1);
    }

    strncpy(newnode->str, str, MAX_STRING_LEN);
    newnode->str[MAX_STRING_LEN] = '\0';

    newnode->next = NULL;

    newnode->next = top;

    top = newnode;

    return top;
}

char* popword(Stack **top){
    if(*top == NULL ){
        perror("errore: satck vuoto");
        exit(1);
    }

    char *str = malloc(sizeof(char)* MAX_STRING_LEN);
    if(str == NULL){
        perror("erroer durante allocazione stringa");
        exit(1);
    }

    Stack *temp = *top;

    strncpy(str, temp->str, MAX_STRING_LEN - 1);
    str[MAX_STRING_LEN - 1] = '\0';

    *top = (*top)->next;

    free(temp);

    return str;

}

Stack* buildstack(const char *filename){
    FILE *fp = fopen(filename, "r");
    if(!fp){
        perror("errore durante apertura fp");
        exit(1);
    }

    Stack *top = NULL;

    char buffer[MAX_STRING_LEN];

    while(fgets(buffer, MAX_STRING_LEN, fp)){
        buffer[strcspn(buffer, "\n")] = '\0';
        top = pushword(top, buffer);
    }
    fclose(fp);
    return top;

}

void sortword(char *str){
    char hold;
    for(int i = 0; i<strlen(str); i++){
        for(int j = 0; j<strlen(str) - 1; j++){
            for(int k = 0; k<strlen(str) - j - 1; k++){
                if(str[k]>str[k + 1]){
                    hold = str[k];
                    str[k] = str[k + 1];
                    str[k+1] = hold;
                }
            }
        }
    }
}

void printstack(Stack *top,int k){
    char *str;
    while(top != NULL){
        str = popword(&top);
            if(strlen(str)>= k){
             sortword(str);
            }
        printf("%s \n", str);
        free(str);
        
    }
    if(top != NULL){
    top = top->next;
    }
}


int main(int argc, char *argv[]){
    FileParams params = readinput(argc, argv);

    Stack *top = buildstack(params.inputFile);

    printstack(top, params.k);

    


}