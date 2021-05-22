# ParallelDenseMatrixMultiplication
Multithreaded parallel application that performs dense matrix multiplication in shortest time.


run: 
 
1. gcc -o serial_multiplication.exe serial_multiplication.c
    ./serial_multiplication.exe
    
2. gcc -o parallel_multiplication.exe parallel_multiplication.c -pthread
    ./parallel_multiplication.exe
