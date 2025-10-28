#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_LEN 120
#define MAX_STRING_LEN 30

typedef struct {
    char inputFile[MAX_FILE_LEN];
    int N;
    int M;
} FileParams;

FileParams readinput(int argc, char *argv[]){
    if(argc != 4){
        fprintf(stderr, "errore: numero argomenti errato");
        exit(1);
    }

    FileParams params;

    int N = atoi(argv[2]);
    int M = atoi(argv[3]);

    strncpy(params.inputFile, argv[1], MAX_FILE_LEN - 1);
    params.inputFile[MAX_STRING_LEN - 1] = '\0';

    params.N = N;
    params.M = M;

    return params;
}

double*** allocMatrix(int N, int M){
    double*** Matrix = malloc(sizeof(double**)*N);
    if(Matrix == NULL){
        perror("errrore durante l'allocazione della matrice");
        exit(1);
    }
    for(int i = 0; i<N; i++){
        Matrix[i] = malloc(sizeof(double*)*M);
        if(Matrix[i] == NULL){
            perror("errore durante l'lallocazione delle colonne dell matrice");
            exit(1);
        }
        for(int j=0; j<M; j++){
            Matrix[i][j] = malloc(sizeof(double));
            if(Matrix[i][j] == NULL){
            perror("errore durante  l'allocazione di spazio per il valore della casella della matrice"),
            exit(1);
            }
        }
    }
    return Matrix;
}
double*** fillmatrix(const char *filename,int N, int M){
    FILE *fp = fopen(filename, "r");
    if(!fp){
        perror("errore durante lapertura del file");
        exit(1);
    }

    double ***Matrix = allocMatrix(N,M);


    for(int i = 0; i<N; i++){
        for(int j = 0; j<M; j++){  // ERRORE!!!! per un ìa matyrice devo prendere dal file in qusìesto modo
            fscanf(fp, "%lf", Matrix[i][j]);
        }
    }    

        fclose(fp);

        return Matrix;
}

void printmatrix(double*** Matrix, int N, int M){

    for(int i = 0; i<N; i++){
        for(int j = 0; j<M; j++){
            printf(" %lf", *Matrix[i][j]);

        }  
        printf("\n");  
    }

}

double*** normalize(double*** A, int N, int M){

double*** B = allocMatrix(N,M);
double max;

        for(int j = 0; j<M; j++){
            *A[0][j] = max;

        for(int i = 1; i<N; i++){
            if(*A[i][j] > max){
                max = *A[i][j];
            }
       }
       for(int i = 0; i<N; i++){
        *B[i][j] = *A[i][j] /max;
       }

    }
}   


void sortMatrix(double ***A, int N, int M){
    double hold;

     for(int i = 0; i<M; i++){ // scorre tutte el colonne
        for(int j = 0; j<N - 1; j++){ // scorre tutte le righe di ogni colonna
            for(int k =0; k<N - j -1; k++){ // controlla lo scambio degli elementi delle colonne
                if(*A[k][j] > *A[k+1][j]){
                    hold = *A[k][j];
                    *A[k][j] = *A[k+1][j];
                    *A[k+1][j] = hold;
                }

            }
           

        }  
     
    }

    

}
    




int main(int argc, char *argv[]){
    FileParams params = readinput(argc, argv);

    double*** Matrix = fillmatrix(params.inputFile, params.N, params.M);

    printmatrix(Matrix, params.N, params.M);
}