#include <iostream>
#include "operation.cpp"
#include "metodo_simples.cpp"
#include "strassenNovo.cpp"

#include <chrono>
#include <math.h>


int** matrixGenerate( int n ){

    int** M = initializeMatrix(n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            // gera valores aleatorios entre 1 e 100
            M[i][j] = rand() % 100 + 1;
            
    return M;
		
}

void printMatrix( int ** M, int n){

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++)
            // gera valores aleatorios entre 1 e 100
            std::cout << M[i][j] << " ";
        std::cout << "\n";
    }   
}

int main(){


    for (int i=0; i<13; i++){

        std::cout << "Iter: " << i << "\n";

        int n = pow(2, i);
        
        int** A = matrixGenerate(n);
        int** B = matrixGenerate(n);

        int** C = initializeMatrix(n);

        std::chrono::steady_clock::time_point begin1 = std::chrono::steady_clock::now();
        C = multiplyNaive(A, B, n);
        std::chrono::steady_clock::time_point end1 = std::chrono::steady_clock::now();

        std::cout << "Time naive = " << std::chrono::duration_cast<std::chrono::microseconds>(end1 - begin1).count() << "[µs]" << std::endl;

        //printMatrix(C, n);

        
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        C = multiply(A, B, n);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        std::cout << "Time strassen = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
        //printMatrix(C, n);
    }
}
