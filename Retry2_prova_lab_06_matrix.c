#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_FILE_LEN 120

typedef struct{
    char inputFile[MAX_FILE_LEN];
    int N;
    int M;
}FileParams;


FileParams readinput(int argc, char* argv[]){
    if(argc != 4){
        fprintf(stderr, "errore numero argomenti errati");
        exit(1);
    }

    FileParams params;

    strncpy(params.inputFile, argv[1], MAX_FILE_LEN - 1);
    params.inputFile[MAX_FILE_LEN - 1] = '\0';

    int N = atoi(argv[2]);
    int M = atoi(argv[3]);

    if(N < 5 || N > 10 || M < 5 || M > 10){
        perror("errore valore m o n errato");
        exit(1);
    }

    params.M = M;
    params.N = N;

    return params;
}

double*** allocMatrix(int N, int M){
double*** matrix = malloc(sizeof(double**)*N);
if(!matrix){
    perror("errore allocazione matrice");
    exit(1);
}
for(int i = 0; i<N; i++){
    matrix[i] = malloc(sizeof(double*)*M);
    if(!matrix[i]){
    perror("errore allocazione matrice");
    exit(1);
    }
    for(int j = 0; j<M; j++){
        matrix[i][j] = malloc(sizeof(double));
        if(!matrix[i][j]){
        perror("errore allocazione matrice");
        exit(1);
        }
    }
}
return matrix;
}

double*** fillmatrix(const char* filename, int N, int M){
FILE* fp = fopen(filename, "r");
if(!fp){
    perror("errore aperture file");
    exit(1);
}

double*** matrix = allocMatrix(N,M);

for(int i = 0; i<N; i++){
    for(int j = 0; j<M; j++){
        fscanf(fp, "%lf", matrix[i][j]);

    }
}
fclose(fp);
return matrix;
}


void printMatrix(double*** matrix, int N, int M){
for(int i = 0; i<N; i++){
    for(int j = 0; j<M; j++){
        printf("%lf ", *matrix[i][j]);
    }
    printf("\n");
}
}


double*** normalize(double*** A, int N, int M){
double*** B = allocMatrix(N,M);



for(int j = 0; j<M; j++){
 double max = *A[0][j];

    for(int i= 1; i<N; i++){
        if(*A[i][j] > max){
            max = *A[i][j];
        }
    }

    for( int i = 0; i<N; i++){
        *B[i][j] = *A[i][j] / max;
     
        }
    }

return B;
}


void bubblesort(double*** matrix, int N, int M){
for(int j = 0; j<M; j++){
    for(int i = 0; i<N -1; i++){
        for(int k = 0; k<N -1 -i; k++){
            if(*matrix[k][j] > *matrix[k+1][j]){
                double hold = *matrix[k][j];
                *matrix[k][j] = *matrix[k+1][j];
                *matrix[k+1][j] = hold;
            }
        }
    }
}
}




int main(int argc, char*argv[]){
    FileParams params = readinput(argc, argv);

    double*** Matrix = fillmatrix(params.inputFile, params.N, params.M);

    printf("---------------------- MATRIX A -----------------------------\n");

    printMatrix(Matrix, params.N, params.M);

    double*** B = normalize(Matrix, params.N, params.M);

    printf("\n\n---------------------- MATRIX B -----------------------------\n");

    printMatrix(B, params.N, params.M);

    bubblesort(B, params.N, params.M);

    printf("\n\n---------------------- MATRIX B(sorted) -----------------------------\n");

    printMatrix(B, params.N, params.M);






    
}