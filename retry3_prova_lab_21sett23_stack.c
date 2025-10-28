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
    fprintf(stderr, " errore numero argomenti errato");
    exit(1);
}

FileParams params;

int k = atoi(argv[2]);

if(k < 5 || k > 15){
    perror( "erroer valore k errato");
    exit(1);
}

strncpy(params.inputFile, argv[1], MAX_FILE_LEN);
params.inputFile[MAX_FILE_LEN] = '\0';

params.k = k;

return params;
}

Stack* pushword(Stack *top, char* str){
Stack *newnode = malloc(sizeof(Stack));
if(newnode == NULL){
    perror("errore allocazione newnode");
    exit(1);
}

strncpy(newnode->str, str, MAX_STRING_LEN);
newnode->str[MAX_STRING_LEN] = '\0';

newnode->next = top;

return newnode;
}

char* pop(Stack **top){
char *str = malloc(sizeof(char)*MAX_STRING_LEN);
if(str == NULL){
    perror("erreo allocazione str");
    exit(1);
}

Stack *current = *top;

strncpy(str, current->str, MAX_STRING_LEN);
str[MAX_STRING_LEN] = '\0';

*top = (*top)->next;

free(current);

return str;
}

Stack* buildstack(const char *filename){
FILE *fp = fopen(filename, "r");
if(!fp){
    perror("erroe pertura file");
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

int findsizearr(Stack *top){
int counter = 0;
Stack *current = top;
while( current != NULL){
    counter++;
    current = current->next;
}
return counter;
}

char** buildstringarr(Stack *top, int size){
    char** str = malloc(sizeof(char*)*size);
    for(int i = 0; i<size; i++){
        str[i] = pop(&top);
    }
return str;
}

void printstack(Stack *top){
char *str;
while(top != NULL){
    str = pop(&top);
    printf(" %s \n", str);
}
}

int main(int argc, char *argv[]){
FileParams params = readinput(argc, argv);

Stack *top = buildstack(params.inputFile);

printstack(top);
}