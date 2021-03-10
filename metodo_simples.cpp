#include <iostream>
#include "operation.cpp"
#include <chrono>
	
int ** multiply(int ** A, int ** B, int n){
    

    int ** C = initializeMatrix(n);
    
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            
            C[i][j] = 0;
            for (int k=0; k<n; k++) {
                C[i][j] += (A[i][k] * B[k][j]);
            }
            
        }
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

    for(int i=0; i<n; i++)
        delete[] A[i];
    delete[] A;

    for(int i=0; i<n; i++)
        delete[] B[i];
    delete[] B;

    for(int i=0; i<n; i++)
        delete[] C[i];
    delete[] C;

}

