#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRING_LEN 30
#define MAX_FILE_LEN 255


typedef struct {
    char inputFile[MAX_FILE_LEN];
    char outputFile[MAX_FILE_LEN];
    int n;
    int m;
} FileParams;


FileParams readinput(int argc, char* argv[]){
    if(argc != 5){
        fprintf(stderr, " erroer numero argomenti errato");
        exit(1);
    }

    FileParams params;

    strncpy(params.inputFile, argv[1], MAX_FILE_LEN - 1);
    params.inputFile[MAX_FILE_LEN - 1] = '\0';

    strncpy(params.outputFile, argv[2], MAX_FILE_LEN - 1);
    params.outputFile[MAX_FILE_LEN - 1] = '\0';

    int n = atoi(argv[3]);
    int m = atoi(argv[4]);


    params.n = n;
    params.m = m;

    return params;
}

double*** AllocMatrix(int n, int m){
double*** Matrix = malloc(sizeof(double**)*n);
if(Matrix == NULL){
    perror("errore allocazione matrice");
    exit(1);
}
for(int i = 0; i<n; i++){
    Matrix[i] = malloc(sizeof(double*)*m);
    if(Matrix == NULL){
        perror("errore allocazione matrice");
        exit(1);
    }
    for(int j = 0; j<m; j++){
        Matrix[i][j] = malloc(sizeof(double));
    }
}
return Matrix;
}


double*** fillMatrix(const char* filename, int n, int m){
   
    FILE *fp = fopen(filename, "r");
    if(!fp){
        perror("errore durante apertura del file");
        exit(1);
    }

    double*** Matrix = AllocMatrix(n ,m);
    
    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            fscanf(fp, "%lf", Matrix[i][j]);
        }
    }
    fclose(fp);
    return Matrix;
}

void Sparsify(double*** A, int n, int m){

    double average = 0.0;
    double sum = 0.0;
    int count = 0;

    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            if(A[i][j] != NULL){
                sum = sum + *A[i][j];
                count++;
            }
        }
        average = sum / count;
    }

    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            if(*A[i][j] < average){
                A[i][j] = NULL;
            }
        }
    }
}

double** collect(double ***A, int n, int m){
    int count = 0;

    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            if(A[i][j] != NULL){
                count++;
            }
        }
    }

    double** arr =  malloc(sizeof(double*)*count);
    for(int i = 0; i<count; i++){
        arr[i] = malloc(sizeof(double));
    }

    int index = 0;
    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            if(A[i][j] != NULL){
            arr[index] = A[i][j];
            index++;
            }
        }
    }
        return arr;
}


    int findsize(double*** A, int n, int m){
        int count = 0;

    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            if(A[i][j] != NULL){
                count++;
            }
        }
    }
    return count;
    }

    void WriteToFile(const char* filename, double** arr, int n){
        FILE* fp = fopen(filename, "w");
        if(!fp){
            perror("erreo apertura file");
            exit(1);
        }

        for(int i = 0; i<n; i++){
            fprintf(fp, "%lf  ", *arr[i]);
        }
        fclose(fp);
    }





int main(int argc, char *argv[]){
    FileParams params = readinput(argc, argv);

    double*** Matrix = fillMatrix(params.inputFile, params.n, params.m);

    printf("Matrice Iniziale:\n");
    for (int i = 0; i < params.n; i++) {
        for (int j = 0; j < params.m; j++) {
            printf("%lf ", *Matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    Sparsify(Matrix, params.n, params.m);

    printf("Matrice Sparsificata:\n");
    for (int i = 0; i < params.n; i++) {
        for (int j = 0; j < params.m; j++) {
            if(Matrix[i][j] == NULL){
                printf("NULL ");
            }else{
            printf("%lf ", *Matrix[i][j]);
            }
        }
        printf("\n");
    }

    printf("\n");

    double** arr = collect(Matrix, params.n, params.m);
    int size = findsize(Matrix, params.n, params.m);

    printf("Array Degli Elementi Della Matrice: \n");
    for(int i = 0; i<size; i++){
        printf("%lf ", *arr[i]);
    }
    

    WriteToFile(params.outputFile, arr, size);

}