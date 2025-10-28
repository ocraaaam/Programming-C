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
    if (argc != 3){
        fprintf(stderr, "errore numero di argoe ti errato");
        exit(1);
    }
    FileParams params;

    int k= atoi(argv[2]);

    if(k < 5 || k >15){
        perror("errore valore di k errato");
        exit(1);
    }

    strncpy(params.inputFile, argv[1], MAX_FILE_LEN);
    params.inputFile[MAX_FILE_LEN] = '\0';

    params.k = k;

    return params;
}

Stack* pushword(Stack *top, char *str){
Stack *newnode = malloc(sizeof(Stack));
if(newnode == NULL){
    perror("errore allocazion newnode");
    exit(1);
}

strncpy(newnode->str, str, MAX_STRING_LEN);
newnode->str[MAX_STRING_LEN] = '\0';

newnode->next = top;
top = newnode;

return newnode;
}

char *pop(Stack **top){
    char* str = malloc(sizeof(char)*MAX_STRING_LEN);
    if(str == NULL){
        perror("errore durante allocaziones str");
        exit(1);
    }

    if(*top == NULL){
        perror("errroe lista vuota");
        exit(1);
    }

    Stack *temp = *top;

    strncpy(str, (*top)->str, MAX_STRING_LEN);
    str[MAX_STRING_LEN] ='\0';

    *top = (*top)->next;
    free(temp);

    return str;
}

Stack* buildstack(const char *filename){
FILE* fp = fopen(filename, "r");
if(!fp){
    perror("errore fp non aperto");
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


void elab(char *str){
       char hold;
    for(int i = 0; i<strlen(str); i++){
        for(int j = 0; j<strlen(str) - i - 1; j++){
            if(str[j] > str[j + 1]){
              hold = str[j];
              str[j] = str[j + 1];
             str[j + 1] = hold;
            }
        }
    }   
}

void printstack(Stack *top,int k){
    char *str;
while(top != NULL){

    str = pop(&top);
    if(strlen(str)>=k){
        elab(str);
    }
    
    printf("%s \n", str);
    
    
}
}

int main(int argc, char *argv[]){
FileParams params = readinput(argc, argv);

Stack *top = NULL; 
top = buildstack(params.inputFile);


printstack(top, params.k);



}


