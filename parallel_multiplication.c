#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#include <stdint.h> 
#include <pthread.h>

pthread_t *threads;
pthread_attr_t attr;
int thread_id[]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
int *result;
int *matA;
int *matB;
int global_matrix_size = 0;
int global_num_threads = 0;

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

void *multiply(void *arg){
	int id = *((int *) arg);
	int block_size = global_matrix_size/global_num_threads;
	int block_start = id * (global_matrix_size * block_size);

	for(int z = 0; z < global_num_threads; z++){
		for(int i = 0; i < block_size; i++){		
			for(int j = 0; j < block_size; j++){
				result[block_start + i * (global_matrix_size) + z * block_size + j] = 0.0;
				for(int k = 0; k < global_matrix_size; k++){
					result[block_start + i * (global_matrix_size) + z * block_size + j] +=
					matA[block_start + i * global_matrix_size + k] * 
					matB[z * (global_matrix_size * block_size) + j * global_matrix_size + k];
				}
			}
		}			
	}

	pthread_exit(NULL);
	return 0;
}
 

void thread_creation_and_launch( int num_threads, int matrix_size){
    struct timeval start_time, stop_time;
    threads = (pthread_t *)malloc(num_threads * sizeof(pthread_t));
	pthread_attr_init(&attr);

	global_num_threads = num_threads;
	global_matrix_size = matrix_size;
    
    gettimeofday(&start_time, NULL);
	for(int k = 0; k < num_threads; k++){		
		pthread_create(&threads[k],&attr, multiply, &thread_id[k]); 
	}

	// Join on threads
	for (int k = 0; k < num_threads; k++) 
        pthread_join(threads[k], NULL);
        gettimeofday(&stop_time, NULL);
        printf ("\t\t\tCaching Time : %f seconds\n",
            (double) (stop_time.tv_usec - start_time.tv_usec) / 1000000 +
            (double) (stop_time.tv_sec - start_time.tv_sec)); 
   
}

int *decomposition_of_matrixA(int **readed_matriceA, int matrix_size){
    matA = (int *)malloc(matrix_size * matrix_size * sizeof(int));
    //Save matrix A in row order
    for(int k = 0; k < matrix_size; k++){
		for(int l = 0; l < matrix_size; l++){
			matA[l + matrix_size * k] = readed_matriceA[k][l];
		}
	}

    return matA;
}

int *decomposition_of_matrixB(int **readed_matriceB, int matrix_size){
    matB = (int *)malloc(matrix_size * matrix_size * sizeof(int));
    	// Save matrix B in column order
	for(int k = 0; k < matrix_size; k++){
		for(int l = 0; l < matrix_size; l++){
			matB[l+matrix_size * k] = readed_matriceB[l][k];
		}
	}

    return matB;
}
 

void write_result_to_file(int n, int *result_matrice){
    FILE* fpC = NULL; 
        char fileCnametext[20];  
        sprintf(fileCnametext, "resultparallel%d.txt", n);   
        fpC = fopen(fileCnametext, "w");   
        int row,column = 0; 
        for (row = 0; row < n; row++) {
            for(column = 0; column < n; column++){
                fprintf(fpC,"%d " , result_matrice[row*n + column]); 
            }
            fprintf(fpC, "\n"); 
        }
        fclose(fpC);
}



int main(int argc, char *argv[]){
    printf("MULTITHREADED APPLICATION \n");
    struct timeval start, stop, start_time, stop_time; 
    int thread_numbers = 1;
    int n = 0;
    int thread_counts[5] = {1, 2, 4, 8, 16};
    int **reading_matriceA;
    int **reading_matriceB;

    // -------- MATRIX SIZE = 128 --------------//
    printf("\nFor matrix size 128:\n\n");
    n = 128;    
    gettimeofday(&start, NULL);
    reading_matriceA = read_matrix_from_file(n, "a128.txt");
    gettimeofday(&stop, NULL);
    printf ("\tReading file for A matrix time is: %f seconds\n" ,
            (double) (stop.tv_usec - start.tv_usec) / 1000000 +
            (double) (stop.tv_sec - start.tv_sec));

    gettimeofday(&start, NULL);
    reading_matriceB = read_matrix_from_file(n, "b128.txt");
    gettimeofday(&stop, NULL);
    printf ("\tReading file for B matrix time is: %f seconds\n" ,
            (double) (stop.tv_usec - start.tv_usec) / 1000000 +
            (double) (stop.tv_sec - start.tv_sec));
    printf("\n");
    for (int i = 0; i < 5; i++){
        thread_numbers = thread_counts[i];
        printf("\t\t%d THREAD \n", thread_numbers);

        result = (int *)malloc(n * n * sizeof(int));
        gettimeofday(&start, NULL);
        gettimeofday(&start_time, NULL);
        matA = decomposition_of_matrixA(reading_matriceA, n);
        matB = decomposition_of_matrixB(reading_matriceB, n);
        gettimeofday(&stop_time, NULL);
        thread_creation_and_launch(thread_numbers, n);
        gettimeofday(&stop, NULL);
        printf ("\t\t\tDecomposition Time : %f seconds\n",
            (double) (stop_time.tv_usec - start_time.tv_usec) / 1000000 +
            (double) (stop_time.tv_sec - start_time.tv_sec));

        printf ("\t\t\tElapsed time : %f seconds\n",
            (double) (stop.tv_usec - start.tv_usec) / 1000000 +
            (double) (stop.tv_sec - start.tv_sec));
        write_result_to_file(n, result);
    }

    // -------- MATRIX SIZE = 256 --------------//
    printf("\nFor matrix size 256:\n\n");
    n = 256;    
    gettimeofday(&start, NULL);
    reading_matriceA = read_matrix_from_file(n, "a256.txt");
    gettimeofday(&stop, NULL);
    printf ("\tReading file for A matrix time is: %f seconds\n" ,
            (double) (stop.tv_usec - start.tv_usec) / 1000000 +
            (double) (stop.tv_sec - start.tv_sec));

    gettimeofday(&start, NULL);
    reading_matriceB = read_matrix_from_file(n, "b256.txt");
    gettimeofday(&stop, NULL);
    printf ("\tReading file for B matrix time is: %f seconds\n" ,
            (double) (stop.tv_usec - start.tv_usec) / 1000000 +
            (double) (stop.tv_sec - start.tv_sec));
    printf("\n");
    for (int i = 0; i < 5; i++){
        thread_numbers = thread_counts[i];
        printf("\t\t%d THREAD \n", thread_numbers);

        result = (int *)malloc(n * n * sizeof(int));
        gettimeofday(&start, NULL);
        gettimeofday(&start_time, NULL);
        matA = decomposition_of_matrixA(reading_matriceA, n);
        matB = decomposition_of_matrixB(reading_matriceB, n);
        gettimeofday(&stop_time, NULL);
        thread_creation_and_launch(thread_numbers, n);
        gettimeofday(&stop, NULL);
         printf ("\t\t\tDecomposition Time : %f seconds\n",
            (double) (stop_time.tv_usec - start_time.tv_usec) / 1000000 +
            (double) (stop_time.tv_sec - start_time.tv_sec));

        printf ("\t\t\tElapsed time : %f seconds\n",
            (double) (stop.tv_usec - start.tv_usec) / 1000000 +
            (double) (stop.tv_sec - start.tv_sec));
        write_result_to_file(n, result);
    }

    // -------- MATRIX SIZE = 512 --------------//
    printf("\nFor matrix size 512:\n\n");
    n = 512;    
    gettimeofday(&start, NULL);
    reading_matriceA = read_matrix_from_file(n, "a512.txt");
    gettimeofday(&stop, NULL);
    printf ("\tReading file for A matrix time is: %f seconds\n" ,
            (double) (stop.tv_usec - start.tv_usec) / 1000000 +
            (double) (stop.tv_sec - start.tv_sec));

    gettimeofday(&start, NULL);
    reading_matriceB = read_matrix_from_file(n, "b512.txt");
    gettimeofday(&stop, NULL);
    printf ("\tReading file for B matrix time is: %f seconds\n" ,
            (double) (stop.tv_usec - start.tv_usec) / 1000000 +
            (double) (stop.tv_sec - start.tv_sec));
    printf("\n");
    for (int i = 0; i < 5; i++){
        thread_numbers = thread_counts[i];
        printf("\t\t%d THREAD \n", thread_numbers);

        result = (int *)malloc(n * n * sizeof(int));
        gettimeofday(&start, NULL);
        gettimeofday(&start_time, NULL);
        matA = decomposition_of_matrixA(reading_matriceA, n);
        matB = decomposition_of_matrixB(reading_matriceB, n);
        gettimeofday(&stop_time, NULL);
        thread_creation_and_launch(thread_numbers, n);
        gettimeofday(&stop, NULL);
        printf ("\t\t\tDecomposition Time : %f seconds\n",
            (double) (stop_time.tv_usec - start_time.tv_usec) / 1000000 +
            (double) (stop_time.tv_sec - start_time.tv_sec));

        printf ("\t\t\tElapsed time : %f seconds\n",
            (double) (stop.tv_usec - start.tv_usec) / 1000000 +
            (double) (stop.tv_sec - start.tv_sec));
        write_result_to_file(n, result);
    }

    // -------- MATRIX SIZE = 1024 --------------//
    printf("\nFor matrix size 1024:\n\n");
    n = 1024;    
    gettimeofday(&start, NULL);
    reading_matriceA = read_matrix_from_file(n, "a1024.txt");
    gettimeofday(&stop, NULL);
    printf ("\tReading file for A matrix time is: %f seconds\n" ,
            (double) (stop.tv_usec - start.tv_usec) / 1000000 +
            (double) (stop.tv_sec - start.tv_sec));

    gettimeofday(&start, NULL);
    reading_matriceB = read_matrix_from_file(n, "b1024.txt");
    gettimeofday(&stop, NULL);
    printf ("\tReading file for B matrix time is: %f seconds\n" ,
            (double) (stop.tv_usec - start.tv_usec) / 1000000 +
            (double) (stop.tv_sec - start.tv_sec));
    printf("\n");
    for (int i = 0; i < 5; i++){
        thread_numbers = thread_counts[i];
        printf("\t\t%d THREAD \n", thread_numbers);

        result = (int *)malloc(n * n * sizeof(int));
        gettimeofday(&start, NULL);
        gettimeofday(&start_time, NULL);
        matA = decomposition_of_matrixA(reading_matriceA, n);
        matB = decomposition_of_matrixB(reading_matriceB, n);
        gettimeofday(&stop_time, NULL);
        thread_creation_and_launch(thread_numbers, n);
        gettimeofday(&stop, NULL);
        printf ("\t\t\tDecomposition Time : %f seconds\n",
            (double) (stop_time.tv_usec - start_time.tv_usec) / 1000000 +
            (double) (stop_time.tv_sec - start_time.tv_sec));

        printf ("\t\t\tElapsed time : %f seconds\n",
            (double) (stop.tv_usec - start.tv_usec) / 1000000 +
            (double) (stop.tv_sec - start.tv_sec));
        write_result_to_file(n, result);
    }

    // -------- MATRIX SIZE = 2048 --------------//
    printf("\nFor matrix size 2048:\n\n");
    n = 2048;    
    gettimeofday(&start, NULL);
    reading_matriceA = read_matrix_from_file(n, "a2048.txt");
    gettimeofday(&stop, NULL);
    printf ("\tReading file for A matrix time is: %f seconds\n" ,
            (double) (stop.tv_usec - start.tv_usec) / 1000000 +
            (double) (stop.tv_sec - start.tv_sec));

    gettimeofday(&start, NULL);
    reading_matriceB = read_matrix_from_file(n, "b2048.txt");
    gettimeofday(&stop, NULL);
    printf ("\tReading file for B matrix time is: %f seconds\n" ,
            (double) (stop.tv_usec - start.tv_usec) / 1000000 +
            (double) (stop.tv_sec - start.tv_sec));
    printf("\n");
    for (int i = 0; i < 5; i++){
        thread_numbers = thread_counts[i];
        printf("\t\t%d THREAD \n", thread_numbers);

        result = (int *)malloc(n * n * sizeof(int));
        gettimeofday(&start, NULL);
        gettimeofday(&start_time, NULL);
        matA = decomposition_of_matrixA(reading_matriceA, n);
        matB = decomposition_of_matrixB(reading_matriceB, n);
        gettimeofday(&stop_time, NULL);
        thread_creation_and_launch(thread_numbers, n);
        gettimeofday(&stop, NULL);
         printf ("\t\t\tDecomposition Time : %f seconds\n",
            (double) (stop_time.tv_usec - start_time.tv_usec) / 1000000 +
            (double) (stop_time.tv_sec - start_time.tv_sec));

        printf ("\t\t\tElapsed time : %f seconds\n",
            (double) (stop.tv_usec - start.tv_usec) / 1000000 +
            (double) (stop.tv_sec - start.tv_sec));
        write_result_to_file(n, result);
    }

    // -------- MATRIX SIZE = 4096 --------------//
    printf("\nFor matrix size 4096:\n\n");
    n = 4096;    
    gettimeofday(&start, NULL);
    reading_matriceA = read_matrix_from_file(n, "a4096.txt");
    gettimeofday(&stop, NULL);
    printf ("\tReading file for A matrix time is: %f seconds\n" ,
            (double) (stop.tv_usec - start.tv_usec) / 1000000 +
            (double) (stop.tv_sec - start.tv_sec));

    gettimeofday(&start, NULL);
    reading_matriceB = read_matrix_from_file(n, "b4096.txt");
    gettimeofday(&stop, NULL);
    printf ("\tReading file for B matrix time is: %f seconds\n" ,
            (double) (stop.tv_usec - start.tv_usec) / 1000000 +
            (double) (stop.tv_sec - start.tv_sec));
    printf("\n");
    for (int i = 0; i < 5; i++){
        thread_numbers = thread_counts[i];
        printf("\t\t%d THREAD \n", thread_numbers);

        result = (int *)malloc(n * n * sizeof(int));
        gettimeofday(&start, NULL);
        gettimeofday(&start_time, NULL);
        matA = decomposition_of_matrixA(reading_matriceA, n);
        matB = decomposition_of_matrixB(reading_matriceB, n);
        gettimeofday(&stop_time, NULL);
        thread_creation_and_launch(thread_numbers, n);
        gettimeofday(&stop, NULL);
         printf ("\t\t\tDecomposition Time : %f seconds\n",
            (double) (stop_time.tv_usec - start_time.tv_usec) / 1000000 +
            (double) (stop_time.tv_sec - start_time.tv_sec));

        printf ("\t\t\tElapsed time : %f seconds\n",
            (double) (stop.tv_usec - start.tv_usec) / 1000000 +
            (double) (stop.tv_sec - start.tv_sec));
        write_result_to_file(n, result);
    }
  
}