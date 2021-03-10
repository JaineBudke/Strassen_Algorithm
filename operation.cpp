#include <iostream>


// Função para inicializar uma matriz
int** initializeMatrix(int n) {
    int** M = new int*[n];
    for(int i=0; i<n; i++)
        M[i] = new int[n];
    return M;
}

// Função para subtrair duas matrizes
int ** sub(int ** A, int ** B, int n) {

    int ** C = initializeMatrix(n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];

    return C;
}


// Função para somar duas matrizes
int ** add(int ** A, int ** B, int n) {

    int ** C = initializeMatrix(n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];

    return C;

}


// Função para dividir uma matriz em sub-blocos
void split(int ** M, int ** C, int iM, int jM, int nC) { // MUDEI AQUI, ADICIONEI nC, tem q passar o tamanho de C tbm

    int i2 = iM;
    for(int i1 = 0; i1 < nC; i1++, i2++) {
        int j2 = jM;
        for(int j1 = 0; j1 < nC; j1++, j2++)
            C[i1][j1] = M[i2][j2];
    }
        
}

// Função para juntar os sub-blocos em uma única matriz
void join(int ** C, int ** M, int iM, int jM, int nC) {

    int i2 = iM;
    for(int i1 = 0; i1 < nC; i1++, i2++) {
        int j2 = jM;
        for(int j1 = 0; j1 < nC; j1++, j2++)
            M[i2][j2] = C[i1][j1];
    }
        
}    

void freeMemory(int ** A11, int ** A12, int ** A21, int ** A22,
                int ** B11, int ** B12, int ** B21, int ** B22,
                int ** P1,  int ** P2,  int ** P3,  int ** P4,
                int ** P5,  int ** P6,  int ** P7,  int ** C11,
                int ** C12, int ** C21, int ** C22, int k ){
                    
    for(int i=0; i<k; i++) {
        delete[] A11[i];
        delete[] A12[i];
        delete[] A21[i];
        delete[] A22[i];
        delete[] B11[i];
        delete[] B12[i];
        delete[] B21[i];
        delete[] B22[i];
        delete[] P1[i];
        delete[] P2[i];
        delete[] P3[i];
        delete[] P4[i];
        delete[] P5[i];
        delete[] P6[i];
        delete[] P7[i];
        delete[] C11[i];
        delete[] C12[i];
        delete[] C21[i];
        delete[] C22[i];
    }
        
    delete[] A11;
    delete[] A12;
    delete[] A21;
    delete[] A22;
    delete[] B11;
    delete[] B12;
    delete[] B21;
    delete[] B22;
    delete[] P1;
    delete[] P2;
    delete[] P3;
    delete[] P4;
    delete[] P5;
    delete[] P6;
    delete[] P7;
    delete[] C11;
    delete[] C12;
    delete[] C21;
    delete[] C22;
}