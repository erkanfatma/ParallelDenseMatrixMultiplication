#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#include <stdint.h> 
  
int generate_random_number(){ 
   return (rand() % (9 - 1)) + 1;
}

void matrix_creator(int n, int **A, int **B){
    // filling matrices 
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            A[i][j] = generate_random_number(); 
            B[i][j] = generate_random_number();
        }
    }
    // writing to files 
    FILE* fpA = NULL; 
    FILE* fpB = NULL; 
    char fileAnametext[20];  
    char fileBnametext[20];  
    sprintf(fileAnametext, "a%d.txt", n);   
    sprintf(fileBnametext, "b%d.txt", n);   
    fpA = fopen(fileAnametext, "w");  
    fpB = fopen(fileBnametext, "w");   
    int row,column = 0; 
      for (row = 0; row < n; row++) {
        for(column = 0; column < n; column++){
            fprintf(fpA,"%d " , A[row][column]); 
            fprintf(fpB,"%d " , B[row][column]); 
        }
        fprintf(fpA, "\n"); 
        fprintf(fpB, "\n"); 
    }
    fclose(fpA);
    fclose(fpB);   
}

void serial_multiplication(int n, int **A, int **B, int **C){
    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            C[i][j] = 0.0;
            for(int k = 0; k <n; k++){
                C[i][j] = C[i][j] + A[i][k] * B[k][j]; 
            } 
        }
    }
}

// void cache_friendly_multiplication(int n, int **A, int **B, int **C){ 
//     printf("With the order of k,i,j");
//     for(int k = 0; k < n; k++){
//         for(int i = 0; i < n; i++){
//             int temp = A[k][i];
//             for(int j = 0; j < n; j++){
//                 C3[i][j] += temp * B[i][j];
//             }
//         }
//     }
 
// }

void write_result_to_file(int n, int **R){
     FILE* fpC = NULL; 
        char fileCnametext[20];  
        sprintf(fileCnametext, "result%d.txt", n);   
        fpC = fopen(fileCnametext, "w");   
        int row,column = 0; 
        for (row = 0; row < n; row++) {
            for(column = 0; column < n; column++){
                fprintf(fpC,"%d " , R[row][column]); 
            }
            fprintf(fpC, "\n"); 
        }
        fclose(fpC);
}

int main(int argc, char *argv[]){
    printf("SERIAL APPLICATION \n\n");
    printf("Matrix multiplication time comparison \n");
    struct timeval start, stop;

    // m = 128 
    printf("\nMatrix size 128:\n\n");
    int n1 = 128;
    int **A1;
    int **B1;
    int **C1;
    A1 = (int **)malloc(n1 *sizeof(int *));
    B1 = (int **)malloc(n1 *sizeof(int *));
    C1 = (int **)malloc(n1 *sizeof(int *));
    for(int i = 0; i< n1; i++){
        A1[i] = (int *)malloc(n1  *sizeof(int));
        B1[i] = (int *)malloc(n1  *sizeof(int));
        C1[i] = (int *)malloc(n1  *sizeof(int));
    } 
    matrix_creator(n1, A1, B1);
    gettimeofday(&start, NULL);
    serial_multiplication(n1, A1, B1, C1);
    gettimeofday(&stop, NULL);
       printf ("\tElapsed time : %f seconds\n",
            (double) (stop.tv_usec - start.tv_usec) / 1000000 +
            (double) (stop.tv_sec - start.tv_sec)); 
    write_result_to_file(n1, C1);

    // m = 256
    printf("\nMatrix size 256:\n\n");
    int n2 = 256;
    int **A2;
    int **B2;
    int **C2;
    A2 = (int **)malloc(n2 *sizeof(int *));
    B2 = (int **)malloc(n2 *sizeof(int *));
    C2 = (int **)malloc(n2 *sizeof(int *));
    for(int i = 0; i< n2; i++){
        A2[i] = (int *)malloc(n2  *sizeof(int));
        B2[i] = (int *)malloc(n2  *sizeof(int));
        C2[i] = (int *)malloc(n2  *sizeof(int));
    } 
    matrix_creator(n2, A2, B2);
    gettimeofday(&start, NULL);
    serial_multiplication(n2,A2,B2,C2);
    gettimeofday(&stop, NULL);
         printf ("\tElapsed time : %f seconds\n",
            (double) (stop.tv_usec - start.tv_usec) / 1000000 +
            (double) (stop.tv_sec - start.tv_sec)); 
    write_result_to_file(n2,C2);

    // m = 512
    printf("\nMatrix size 512:\n\n");
    int n3 = 512;
    int **A3;
    int **B3;
    int **C3;
    A3 = (int **)malloc(n3 *sizeof(int *));
    B3 = (int **)malloc(n3 *sizeof(int *));
    C3 = (int **)malloc(n3 *sizeof(int *));
    for(int i = 0; i< n3; i++){
        A3[i] = (int *)malloc(n3  *sizeof(int));
        B3[i] = (int *)malloc(n3  *sizeof(int));
        C3[i] = (int *)malloc(n3  *sizeof(int));
    } 
    matrix_creator(n3, A3, B3);
    gettimeofday(&start, NULL);
    serial_multiplication(n3,A3,B3,C3);
    gettimeofday(&stop, NULL);
          printf ("\tElapsed time : %f seconds\n",
            (double) (stop.tv_usec - start.tv_usec) / 1000000 +
            (double) (stop.tv_sec - start.tv_sec)); 
    write_result_to_file(n3, C3);

    // m = 1024
    printf("\nMatrix size 1024:\n\n");
    int n4 = 1024;
    int **A4;
    int **B4;
    int **C4;
    A4 = (int **)malloc(n4 *sizeof(int *));
    B4 = (int **)malloc(n4 *sizeof(int *));
    C4 = (int **)malloc(n4 *sizeof(int *));
    for(int i = 0; i< n4; i++){
        A4[i] = (int *)malloc(n4  *sizeof(int));
        B4[i] = (int *)malloc(n4  *sizeof(int));
        C4[i] = (int *)malloc(n4  *sizeof(int));
    } 
    matrix_creator(n4, A4, B4);
    gettimeofday(&start, NULL);
    serial_multiplication(n4, A4, B4, C4);
    gettimeofday(&stop, NULL);
          printf ("\tElapsed time : %f seconds\n",
            (double) (stop.tv_usec - start.tv_usec) / 1000000 +
            (double) (stop.tv_sec - start.tv_sec)); 
    write_result_to_file(n4, C4);

    // m = 2048
    printf("\nMatrix size 2048:\n\n");
    int n5 = 2048;
    int **A5;
    int **B5;
    int **C5;
    A5 = (int **)malloc(n5 *sizeof(int *));
    B5 = (int **)malloc(n5 *sizeof(int *));
    C5 = (int **)malloc(n5 *sizeof(int *));
    for(int i = 0; i< n5; i++){
        A5[i] = (int *)malloc(n5  *sizeof(int));
        B5[i] = (int *)malloc(n5  *sizeof(int));
        C5[i] = (int *)malloc(n5  *sizeof(int));
    } 
    matrix_creator(n5,A5, B5);
    gettimeofday(&start, NULL);
    serial_multiplication(n5, A5, B5, C5);
    gettimeofday(&stop, NULL);
       printf ("\tElapsed time : %f seconds\n",
            (double) (stop.tv_usec - start.tv_usec) / 1000000 +
            (double) (stop.tv_sec - start.tv_sec)); 
    write_result_to_file(n5, C5);

    // m = 4096
    printf("\nMatrix size 4096:\n\n");
    int n6 = 4096;
    int **A6;
    int **B6;
    int **C6; 
    A6 = (int **)malloc(n6 *sizeof(int *));
    B6 = (int **)malloc(n6 *sizeof(int *));
    C6 = (int **)malloc(n6 *sizeof(int *));
    for(int i = 0; i< n6; i++){
        A6[i] = (int *)malloc(n6  *sizeof(int));
        B6[i] = (int *)malloc(n6  *sizeof(int));
        C6[i] = (int *)malloc(n6  *sizeof(int));
    } 
    matrix_creator(n6,A6,B6);
    gettimeofday(&start, NULL);
    serial_multiplication(n6, A6,B6,C6);
    gettimeofday(&stop, NULL);
       printf ("\tElapsed time : %f seconds\n",
            (double) (stop.tv_usec - start.tv_usec) / 1000000 +
            (double) (stop.tv_sec - start.tv_sec)); 
    write_result_to_file(n6, C6);


    return 0;
}
