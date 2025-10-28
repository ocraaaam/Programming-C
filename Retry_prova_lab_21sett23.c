#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_STRING_LEN 30
#define MAX_FILE_LEN 250

typedef struct {
    char inputFile[MAX_FILE_LEN + 1];
    int k;
} FileParams;

typedef struct stack{
    char str[MAX_STRING_LEN];
    struct stack *next;
} stack;

FileParams readinput(int argc, char *argv[]){
    if(argc != 3){
        perror("errore numero argomenti errato");
        exit(1);
    }

    int k = atoi(argv[2]);

    if(k < 5 || k > 15){
        perror("errore durante allocaziome");
        exit(1);
    }

    FileParams params;

    strncpy(params.inputFile, argv[1], MAX_FILE_LEN + 1);
    params.inputFile[MAX_FILE_LEN + 1] = '\0';

    params.k = k;
    
    return params;
}

stack* pushword(stack *top, const char *str){

    stack *newnode = (stack*)malloc(sizeof(stack));
     if(newnode== NULL){
        perror("errore allocazione stringa");
        exit(1);
    }


    strncpy(newnode->str, str, MAX_STRING_LEN);
    newnode->str[MAX_STRING_LEN] = '\0';
    

    newnode->next = top;
    top = newnode;

    return newnode;
}


char* popword(stack **top){

    stack *temp = *top;

     char *str = malloc(sizeof(char)* MAX_STRING_LEN);
     if (str == NULL) {
        fprintf(stderr, "Errore di allocazione della memoria\n");
        exit(EXIT_FAILURE);
    }

    strncpy(str,temp->str, MAX_STRING_LEN);
    str[MAX_STRING_LEN] ='\0';

    *top = (*top)->next;

    free(temp);

    return str;
}

stack* buildstack(stack *top, const char* filename){
FILE *fp = fopen(filename, "r");
if(!fp){
    perror("errore apertura file");
    exit(1);
}

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
        for(int j = 0; j<strlen(str) - i - 1; j++){
            if(str[j] > str[j + 1]){
              hold = str[j];
              str[j] = str[j + 1];
             str[j + 1] = hold;
            }
        }
    }   
}

void printstack(stack **top, int k){
    char *str;

 while(*top != NULL){

    str = popword(top);
    if(strlen(str) >= k){
        sortword(str); 
    }
    printf("%s \n", str);
    free(str);
 }
 
}

int main(int argc, char *argv[]){
    FileParams params = readinput(argc, argv);

    stack *top = NULL;
    top = buildstack(top, params.inputFile);

    printstack(&top, params.k);

    return 0;

}