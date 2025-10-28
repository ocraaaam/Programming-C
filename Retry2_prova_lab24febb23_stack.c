#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 2

typedef struct {
    int N;
    char a;
    char b;
} FileParams;

typedef struct Stack {
    char data[MAX_STRING_LEN];
    struct stack *next;
} Stack;

FileParams readinput(int argc, char *argv[]){
    if(argc != 4){
        fprintf(stderr, "errore numero argomebtj erratp");
        exit(1);
    }

    FileParams params;

    int N = atoi(argv[1]);
    char a = argv[2][0];
    char b = argv[3][0];

    if(N < 5 || N > 10){
        perror("valore n errato");
        exit(1);
    }

    if(a<'a' || a>'z' || b<'a' || b>'z'){
        perror("valore n errato");
        exit(1);
    }

    params.a = a;
    params.b = b;
    params.N = N;

    return params;

}

char genvowel(){
    char vowel[] = "aeiou";
    int index = rand()%5;
    return vowel[index];

}

char genconsonant(){
    char consonant[] = "bcdfghlmnpqrstvz";
    int index = rand()%15;
    return consonant[index];
}

Stack* push(Stack *head, char *str){
    Stack *newnode = malloc(sizeof(Stack));
    if(newnode == NULL){
        perror("errore allocazione");
        exit(1);
    }

    newnode->next = NULL;

    strncpy(newnode->data, str, MAX_STRING_LEN);
    newnode->data[MAX_STRING_LEN] = '\0';

   newnode->next = head;
   return newnode;

    

}

Stack *fillstack(Stack *head,int N, char a , char b){
for(int i= 0; i<N; i++){
    int x = rand()%10;
    for(int j = 0; j<x; j++){
        char c;
        if(x >1 && x < 4){
            c = genvowels();
        }
        else{
            c = genconsonant();
        }
         // Sostituisci 'a' e 'b' con '*' e '?' rispettivamente
            if (c == a) {
                c = '*';
            } else if (c == b) {
                c = '?';
            }
            head = push(head ,c);
        }
    }
return head;
}

void printstack(Stack *head){
    Stack *current = head;
    while(current != NULL){
        print("%s", head->data);
        current = current->next;
    }

}

int main(int argc, char *argv[]){
    FileParams params = readinput(argc, argv);

    Stack *head = fillstack(head, params.N,params.a,params.b);

    printstack(head);


}