#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#include <stdint.h>  

int **read_matrix_from_file(int n, char *filename){ 
    FILE * fp = fopen(filename, "r");
    
    int **result_matrix;
    result_matrix = (int **)malloc(n *sizeof(int *)); 
    for(int i = 0; i< n; i++){ 
        result_matrix[i] = (int *)malloc(n  *sizeof(int));
    }

    for(int i = 0; i< n; i++){
        for(int j = 0; j<n; j++){
            fscanf(fp, "%d", &result_matrix[i][j]);
        }
    }

    fclose(fp);
    return result_matrix;
}

void cache_only_multiplication(int n, int **A, int **B, int **C){
    for(int k = 0; k < n; k++){
        for(int i = 0; i < n; i++){
            int temp = A[k][i];
            for(int j = 0; j < n; j++){
                C[i][j] += temp * B[i][j];
            }
        }
    }
}

int main(int argc, char *argv[]){
    printf("CACHE ONLY APPLICATION \n\n");
    printf("Matrix multiplication time comparison \n");
    struct timeval start, stop;
    int **A;
    int **B;
    int **C;
    int n ;

    // m = 128 
    printf("\nMatrix size 128:\n\n");
    n = 128;
   
    A = (int **)malloc(n *sizeof(int *));
    B = (int **)malloc(n *sizeof(int *));
    C = (int **)malloc(n *sizeof(int *));
    for(int i = 0; i< n; i++){
        A[i] = (int *)malloc(n  *sizeof(int));
        B[i] = (int *)malloc(n  *sizeof(int));
        C[i] = (int *)malloc(n  *sizeof(int));
    } 
    
    A = read_matrix_from_file(n, "a128.txt");
    B = read_matrix_from_file(n, "b128.txt");
    gettimeofday(&start, NULL);
    cache_only_multiplication(n, A,B, C);
    gettimeofday(&stop, NULL);
       printf ("\tElapsed time : %f seconds\n",
            (double) (stop.tv_usec - start.tv_usec) / 1000000 +
            (double) (stop.tv_sec - start.tv_sec)); 


    // m = 256 
    printf("\nMatrix size 256:\n\n");
    n = 256;
   
    A = (int **)malloc(n *sizeof(int *));
    B = (int **)malloc(n *sizeof(int *));
    C = (int **)malloc(n *sizeof(int *));
    for(int i = 0; i< n; i++){
        A[i] = (int *)malloc(n  *sizeof(int));
        B[i] = (int *)malloc(n  *sizeof(int));
        C[i] = (int *)malloc(n  *sizeof(int));
    } 
    
    A = read_matrix_from_file(n, "a256.txt");
    B = read_matrix_from_file(n, "b256.txt");
    gettimeofday(&start, NULL);
    cache_only_multiplication(n, A,B, C);
    gettimeofday(&stop, NULL);
       printf ("\tElapsed time : %f seconds\n",
            (double) (stop.tv_usec - start.tv_usec) / 1000000 +
            (double) (stop.tv_sec - start.tv_sec)); 

    // m = 512
    printf("\nMatrix size 512:\n\n");
    n = 512;
   
    A = (int **)malloc(n *sizeof(int *));
    B = (int **)malloc(n *sizeof(int *));
    C = (int **)malloc(n *sizeof(int *));
    for(int i = 0; i< n; i++){
        A[i] = (int *)malloc(n  *sizeof(int));
        B[i] = (int *)malloc(n  *sizeof(int));
        C[i] = (int *)malloc(n  *sizeof(int));
    } 
    
    A = read_matrix_from_file(n, "a512.txt");
    B = read_matrix_from_file(n, "b512.txt");
    gettimeofday(&start, NULL);
    cache_only_multiplication(n, A,B, C);
    gettimeofday(&stop, NULL);
       printf ("\tElapsed time : %f seconds\n",
            (double) (stop.tv_usec - start.tv_usec) / 1000000 +
            (double) (stop.tv_sec - start.tv_sec)); 

     // m = 1024 
    printf("\nMatrix size 1024:\n\n");
    n = 1024;
   
    A = (int **)malloc(n *sizeof(int *));
    B = (int **)malloc(n *sizeof(int *));
    C = (int **)malloc(n *sizeof(int *));
    for(int i = 0; i< n; i++){
        A[i] = (int *)malloc(n  *sizeof(int));
        B[i] = (int *)malloc(n  *sizeof(int));
        C[i] = (int *)malloc(n  *sizeof(int));
    } 
    
    A = read_matrix_from_file(n, "a1024.txt");
    B = read_matrix_from_file(n, "b1024.txt");
    gettimeofday(&start, NULL);
    cache_only_multiplication(n, A,B, C);
    gettimeofday(&stop, NULL);
       printf ("\tElapsed time : %f seconds\n",
            (double) (stop.tv_usec - start.tv_usec) / 1000000 +
            (double) (stop.tv_sec - start.tv_sec)); 

     // m = 2048 
    printf("\nMatrix size 2048:\n\n");
    n = 2048;
   
    A = (int **)malloc(n *sizeof(int *));
    B = (int **)malloc(n *sizeof(int *));
    C = (int **)malloc(n *sizeof(int *));
    for(int i = 0; i< n; i++){
        A[i] = (int *)malloc(n  *sizeof(int));
        B[i] = (int *)malloc(n  *sizeof(int));
        C[i] = (int *)malloc(n  *sizeof(int));
    } 
    
    A = read_matrix_from_file(n, "a2048.txt");
    B = read_matrix_from_file(n, "b2048.txt");
    gettimeofday(&start, NULL);
    cache_only_multiplication(n, A,B, C);
    gettimeofday(&stop, NULL);
       printf ("\tElapsed time : %f seconds\n",
            (double) (stop.tv_usec - start.tv_usec) / 1000000 +
            (double) (stop.tv_sec - start.tv_sec)); 

    // m = 4096 
    printf("\nMatrix size 4096:\n\n");
    n = 4096;
   
    A = (int **)malloc(n *sizeof(int *));
    B = (int **)malloc(n *sizeof(int *));
    C = (int **)malloc(n *sizeof(int *));
    for(int i = 0; i< n; i++){
        A[i] = (int *)malloc(n  *sizeof(int));
        B[i] = (int *)malloc(n  *sizeof(int));
        C[i] = (int *)malloc(n  *sizeof(int));
    } 
    
    A = read_matrix_from_file(n, "a4096.txt");
    B = read_matrix_from_file(n, "b4096.txt");
    gettimeofday(&start, NULL);
    cache_only_multiplication(n, A,B, C);
    gettimeofday(&stop, NULL);
       printf ("\tElapsed time : %f seconds\n",
            (double) (stop.tv_usec - start.tv_usec) / 1000000 +
            (double) (stop.tv_sec - start.tv_sec)); 
}
