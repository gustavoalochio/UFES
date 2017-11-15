#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#define TAM_N 9 

#define GOOD_SOLUTION {\
    {6, 2, 4, 5, 3, 9, 1, 8, 7},\
    {5, 1, 9, 7, 2, 8, 6, 3, 4},\
    {8, 3, 7, 6, 1, 4, 2, 9, 5},\
    {1, 4, 3, 8, 6, 5, 7, 2, 9},\
    {9, 5, 8, 2, 4, 7, 3, 6, 1},\
    {7, 6, 2, 3, 9, 1, 4, 5, 8},\
    {3, 7, 1, 9, 5, 6, 8, 4, 2},\
    {4, 9, 6, 1, 8, 2, 5, 7, 3},\
    {2, 8, 5, 4, 7, 3, 9, 1, 6}\
}

#define BAD_SOLUTION {\
    {6, 2, 4, 5, 3, 9, 1, 8, 7},\
    {5, 1, 9, 7, 2, 8, 6, 3, 4},\
    {8, 3, 7, 6, 1, 4, 2, 9, 5},\
    {1, 4, 3, 8, 6, 5, 7, 2, 9},\
    {9, 5, 8, 2, 1, 7, 3, 6, 1},\
    {7, 6, 2, 3, 9, 1, 4, 5, 8},\
    {3, 7, 1, 9, 5, 6, 8, 4, 2},\
    {4, 9, 6, 1, 8, 2, 5, 7, 3},\
    {2, 8, 5, 4, 7, 3, 9, 1, 6}\
}

typedef struct{
    int row;
    int column;
    int contador;
}Parameters;

char s[TAM_N][TAM_N] = GOOD_SOLUTION;
//char s[TAM_N][TAM_N] = BAD_SOLUTION;

void *check_row(void *param) {
    int vetV[TAM_N] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Parameters position = *((Parameters*) param);
    int i = position.row;
    int count = 0;

    for(int j = 0; j < TAM_N; j++){
        for (int k = 0; k < TAM_N; k++){
            if(vetV[k] == s[i][j]){
                vetV[k] = 0;
                count++;
            }
        }
    }
    if(count == 9)
        printf("Row %d Sucessful\n",i);
    else
        printf("Row %d Failed\n",i);

    free(param); 
    pthread_exit(0);
}

void *check_column(void *param) {
    int vetV[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Parameters position = *((Parameters*) param);
    int i = position.column;
    int count = 0;

    for(int j = 0; j < TAM_N; j++){
        for (int k = 0; k < TAM_N; k++){
            if(vetV[k] == s[j][i]){
                vetV[k] = 0;
                count++;
            }
        }
    }
    if(count == 9)
        printf("Column %d Sucessful\n",i);
    else
        printf("Column %d Failed\n",i);

    free(param);
    pthread_exit(0); 
}

void *check_block(void *param) {
    int vetV[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Parameters position = *((Parameters*) param);
    int i = position.row;
    int j = position.column;
    int count = 0;

    for(int z = i; z < i + 3; z++){
        for (int k = j; k < j + 3; k++){
            for (int m = 0; m < TAM_N; m++){
                if(vetV[m] == s[z][k]){
                    vetV[m] = 0;
                    count++;
                }
            }
        }
    }
    if(count == 9)
        printf("Block %d Sucessful\n",position.contador);
    else
        printf("Block %d Failed\n",position.contador);

    free(param);
    pthread_exit(0); 
}


int main(void) {
    pthread_t workers[27];
    pthread_attr_t attr;
    int i,j = 0, z = 0;
    int count = 0;
    pthread_attr_init(&attr);


    //                ROW
    //--------------------------------------------------------------
    for (i = 0; i < 9; i++) {
        Parameters *param = malloc(sizeof *param);
        param->row = i;
        pthread_create(&workers[count], &attr, check_row, param);
        count++;

    }
    //---------------------------------------------------------------


    //                COLUMN
    //--------------------------------------------------------------
    for (i = 0; i < 9; i++) {
        Parameters *param = malloc(sizeof *param);
        param->column = i;
        pthread_create(&workers[count], &attr, check_column, param);
        count++;
    }
    //--------------------------------------------------------------


    //                BLOCK
    //--------------------------------------------------------------
    int contador = 0;
    for(int i = 0; i < 3;i++){
        z = 0;
        for (int k = 0; k < 3; k++){
            Parameters *param = malloc(sizeof *param);
            param->row = j;
            param->column = z;
            param->contador = contador;
            pthread_create(&workers[count], &attr, check_block, param);
            z += 3;
            contador++;
            count++;
        }
        j += 3;
    }
    //--------------------------------------------------------------

     for (i = 0; i < 27; i++) {
        pthread_join(workers[i], NULL);
    }

    return 0;
}
