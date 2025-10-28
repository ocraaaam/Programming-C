#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 30
#define MAX_FILE_LEN 120

typedef struct {
    int N;
    char a;
    char b;
} FileParams;

typedef struct stack {
    char a;
    struct stack* next;
} stack;

FileParams readinput(int argc, char *argv[]){
    if(argc != 4){
        fprintf(stderr, "errore numero argometni errato");
        exit(1);
    }

    FileParams params;

    int N = atoi(argv[1]);

    if(N < 5 || N > 10){
        perror("valore N errato");
        exit(1);
    }

    char a = argv[2][0]; //     errore COSI SI INSERISCE UN CARATTERE
    //char b;
    char b = argv[3][0];


    //strcpy(a, argv[2]); NON COSI
    

     if( a < 'a' || a > 'z'){
        perror("valore a errato");
        exit(1);
    }

    if( b < 'a' || b > 'z'){
        perror("valore b errato");
        exit(1);
    }

    params.N = N;
    params.a = a;
    params.b = b;

    return params;

}

char genvowel(){
    char vowel[] = "aeiou";
    int index = rand()%4;
    return vowel[index];
}

char genconsonant(){
    char consonant[] = "bcdhlmnpqrstvzk";
    int index = rand()%15;
    return consonant[index];
}

stack* push(stack* top, char a){
    stack* newnode = malloc(sizeof(stack));
    if(newnode == NULL){
        perror("errore alllocazione stack");
        exit(1);
    }

    //strncpy(newnode->a, a, MAX_STRING_LEN); //non e una stringa
    //newnode->a[MAX_STRING_LEN];
    newnode->a = a;

    newnode->next = top;

    return newnode;

}

stack* fillstack(int N,stack *top, char a, char b){
    for(int i= 0; i<N; i++){
        int x = rand()%10;
        if(x >= 1 && x <= 4){
            for(int i = 0; i<x; i++){
                char c = genvowel();
                if(c == a){
                    c = '*';
                }
                top = push(top, c);
                
            }
        }
        if(x >= 5 && x <= 9){
            for (int i = 0; i<x; i++){
                char c = genconsonant();
                if(c == b){
                    c = '?';
                }
                  top = push(top, c);
            }
        }
    }
    return top;

}

void printstack(stack* top){
    while(top != NULL){
        printf("%c ", top->a);
        top = top->next;
    }
}


int main(int argc, char *argv[]){
    FileParams params = readinput(argc ,argv);

   stack *top = NULL;
  top = fillstack(params.N, top, params.a, params.b); //RICORDATI DI INIZIALIZZAREA NULL LO STACK

    printstack(top);

}