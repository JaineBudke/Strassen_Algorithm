#include <iostream>
#include "operation.cpp"
#include <chrono>


// Função para multiplicar duas matrizes 
int ** multiply(int ** A, int ** B, int n){        
    	
    int ** C = initializeMatrix(n);
    
    // caso base: matrizes 1x1 
    if (n == 1) {

        C[0][0] = A[0][0] * B[0][0];

    } else {

        int k = n/2;
        // declaração sub-blocos das matrizes
        int ** A11 = initializeMatrix(k);
        int ** A12 = initializeMatrix(k);
        int ** A21 = initializeMatrix(k);
        int ** A22 = initializeMatrix(k);
        int ** B11 = initializeMatrix(k);
        int ** B12 = initializeMatrix(k);
        int ** B21 = initializeMatrix(k);
        int ** B22 = initializeMatrix(k);

        // Divide matriz A em 4 blocos
        split(A, A11, 0 , 0, k);
        split(A, A12, 0 , n/2, k);
        split(A, A21, n/2, 0, k);
        split(A, A22, n/2, n/2, k);
        
        // Divide matriz B em 4 blocos
        split(B, B11, 0 , 0, k);
        split(B, B12, 0 , n/2, k);
        split(B, B21, n/2, 0, k);
        split(B, B22, n/2, n/2, k);

        /** 
            Iremos fazer chamadas recursivas para essa função de modo a efetuar as seguintes operações:
            M1 = (A11 + A22)(B11 + B22)
            M2 = (A21 + A22) B11
            M3 = A11 (B12 - B22)
            M4 = A22 (B21 - B11)
            M5 = (A11 + A12) B22
            M6 = (A21 - A11) (B11 + B12)
            M7 = (A12 - A22) (B21 + B22)
        **/
        int ** M1 = multiply(add(A11, A22, k), add(B11, B22, k), k);
        int ** M2 = multiply(add(A21, A22, k), B11, k);
        int ** M3 = multiply(A11, sub(B12, B22, k), k);
        int ** M4 = multiply(A22, sub(B21, B11, k), k);
        int ** M5 = multiply(add(A11, A12, k), B22, k);
        int ** M6 = multiply(sub(A21, A11, k), add(B11, B12, k), k);
        int ** M7 = multiply(sub(A12, A22, k), add(B21, B22, k), k);

        /**
            Iremos fazer chamadas recursivas de modo a efetuar as operações:
            C11 = M1 + M4 - M5 + M7
            C12 = M3 + M5
            C21 = M2 + M4
            C22 = M1 - M2 + M3 + M6
        **/
        int ** C11 = add(sub(add(M1, M4, k), M5, k), M7, k);
        int ** C12 = add(M3, M5, k);
        int ** C21 = add(M2, M4, k);
        int ** C22 = add(sub(add(M1, M3, k), M2, k), M6, k);

        
        // junta os 4 sub-blocos numa única matriz
        join(C11, C, 0 , 0, k);
        join(C12, C, 0 , n/2, k);
        join(C21, C, n/2, 0, k);
        join(C22, C, n/2, n/2, k);

        // libera a memória ocupada pelas matrizes
        freeMemory(A11, A12, A21, A22, B11, B12, B21, B22,
               M1, M2, M3, M4, M5, M6, M7, C11, C12, C21, C22, k );

    }

    return C;

}
	
int** matrixGenerate( int n ){

    int** M = initializeMatrix(n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            // gera valores aleatorios entre 1 e 100
            M[i][j] = rand() % 100 + 1;
            
    return M;
		
}
	
int main(){

    int n = 1000;
    
    int** A = matrixGenerate(n);
	int** B = matrixGenerate(n);


    int** C = initializeMatrix(n);

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    C = multiply(A, B, n);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;

}
