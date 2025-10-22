#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MIN_DIMENSION 2
#define MAX_DIMENSION 10
#define MAXIMUM_PIXEL 256

bool isValidMatrix(int dimension);
int getMatrixData();
void generateRandomMatrix(int *matrix, int n);
void displayMatrix(int *matrix, int n);
void transposeMatrix(int *matrix, int n);
void reverseMatrixRow(int *matrix, int n);
void rotateMatrix90DegreesClockWise(int *matrix, int n);
void encodeSmoothedData(int* matrix, int n);
void decodeSmoothedData(int* matrix, int n);
void smoothingFilter(int* matrix, int n);
int calculateNeighborAvg(int* matrix, int n, int row, int col);

int main()
{
    int matrixSize = getMatrixData();
    
    int *sonarMatrix = (int*)malloc(matrixSize * matrixSize * sizeof(int));
    
    if(sonarMatrix == NULL){
        printf("Memory is not allocated.\n");
        return 1;
    }

    generateRandomMatrix(sonarMatrix, matrixSize);
    printf("\nOriginal Randomly Generated Matrix:\n");
    displayMatrix(sonarMatrix, matrixSize);
    
    rotateMatrix90DegreesClockWise(sonarMatrix, matrixSize);
    printf("Matrix after 90 degree Clockwise Rotation:\n");
    displayMatrix(sonarMatrix, matrixSize);
    
    smoothingFilter(sonarMatrix, matrixSize);
    printf("Matrix after Applying 3*3 Smoothing Filter:\n");
    displayMatrix(sonarMatrix, matrixSize);
    
    free(sonarMatrix);

    return 0;
}

bool isValidMatrix(int dimension) {
    return (dimension >= MIN_DIMENSION && dimension <= MAX_DIMENSION);
}

int getMatrixData() {
    int size;
    
    while(1){
        printf("Enter matrix size (%d-%d): ", MIN_DIMENSION, MAX_DIMENSION);
        if (scanf("%d", &size) != 1) {
            while (getchar() != '\n');
            size = -1; 
        }

        if (isValidMatrix(size)) {
            return size;
        }
        
        printf("Invalid matrix size. Please try between %d and %d.\n", MIN_DIMENSION, MAX_DIMENSION);
    }
}

void generateRandomMatrix(int *matrix, int n) {
    srand(time(NULL)); 
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            *(matrix + i * n + j) = rand() % MAXIMUM_PIXEL; 
        }
    }
}

void displayMatrix(int *matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%4d", *(matrix + i * n + j));
        }
        printf("\n");
    }
    printf("\n");
}

void transposeMatrix(int *matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int *a = matrix + i * n + j;
            int *b = matrix + j * n + i;
            int temp = *a;
            *a = *b;
            *b = temp;
        }
    }
}

void reverseMatrixRow(int *matrix, int n) {
    for (int i = 0; i < n; i++) {
        int *rowStart = matrix + i * n;
        int *rowEnd = rowStart + n - 1;
        while (rowStart < rowEnd) {
            int temp = *rowStart;
            *rowStart = *rowEnd;
            *rowEnd = temp;
            rowStart++;
            rowEnd--;
        }
    }
}

void rotateMatrix90DegreesClockWise(int *matrix, int n) {
    transposeMatrix(matrix, n);
    reverseMatrixRow(matrix, n);
}

int calculateNeighborAvg(int* matrix, int n, int row, int col) {
    int sum = 0, count = 0;

    for (int deltaRow = -1; deltaRow <= 1; deltaRow++) {
        for (int deltaCol = -1; deltaCol <= 1; deltaCol++) {

            int newRow = row + deltaRow;
            int newCol = col + deltaCol;

            if (newRow >= 0 && newRow < n && newCol >= 0 && newCol < n) {
                
                sum += *(matrix + newRow * n + newCol) % MAXIMUM_PIXEL;
                count++;
            }
        }
    }
    return sum / count;
}

void encodeSmoothedData(int* matrix, int n) {
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            int avg = calculateNeighborAvg(matrix, n, row, col);
            
            *(matrix + row * n + col) += avg * MAXIMUM_PIXEL;
        }
    }
}

void decodeSmoothedData(int* matrix, int n) {
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            
            *(matrix + row * n + col) /= MAXIMUM_PIXEL;
        }
    }
}

void smoothingFilter(int* matrix, int n) {
    encodeSmoothedData(matrix, n);
    decodeSmoothedData(matrix, n);
}
