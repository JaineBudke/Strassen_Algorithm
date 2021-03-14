#include <iostream>


// Função para multiplicar duas matrizes 
int ** multiply(int ** A, int ** B, int n){        
    	
    int ** C = initializeMatrix(n);

    if (n <= 2) {

        //C[0][0] = A[0][0] * B[0][0];
        C = multiplyNaive(A, B, n);
        return C;

    } 
    int k = n/2;
    
    // Declaração submatrizes
    int ** A11 = initializeMatrix(k);
    int ** A12 = initializeMatrix(k);
    int ** A21 = initializeMatrix(k);
    int ** A22 = initializeMatrix(k);
    int ** B11 = initializeMatrix(k);
    int ** B12 = initializeMatrix(k);
    int ** B21 = initializeMatrix(k);
    int ** B22 = initializeMatrix(k);

    // Divide matriz original em submatrizes
    for(int i=0; i<n/2; i++) {
        for(int j=0; j<n/2; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j+n/2];
            A21[i][j] = A[i+n/2][j];
            A22[i][j] = A[i+n/2][j+n/2];
            
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j+n/2];
            B21[i][j] = B[i+n/2][j];
            B22[i][j] = B[i+n/2][j+n/2];    
        }        
    }  
    
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

    // Junta as 4 submatrizes numa única matriz 
    for(int i=0; i<n/2; i++) {
        for(int j=0; j<n/2; j++) {
            C[i][j] = C11[i][j];
            C[i][j+n/2] = C12[i][j];
            C[i+n/2][j] = C21[i][j];
            C[i+n/2][j+n/2] = C22[i][j];        
        }        
    }

    // libera a memória ocupada pelas matrizes
    freeMemory(A11, A12, A21, A22, B11, B12, B21, B22,
            M1, M2, M3, M4, M5, M6, M7, C11, C12, C21, C22, k );

    return C;

}