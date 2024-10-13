#include <stdio.h>

// Define the size of the matrices
#define SIZE 5
#define M SIZE
#define N SIZE
#define Q SIZE
#define R SIZE

// Function prototypes
void addMatrices(int m1[M][N], int m2[M][N], int m[M][N]);
void multiplyMatrices(int m1[M][N], int m2[Q][R], int m[M][R]);
void transposeMatrix(int m[M][N], int mT[N][M]);

void printMatrix(int m[SIZE][SIZE]);    
void run(int m1[M][N], int m2[Q][R], char operation);

/*
 * Main function. Defines two matrices, asks the user 
 * for input and calls the run function.
 */
int main()
{   
    // Define the first matrix
    int m1[SIZE][SIZE] = {
        {1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20},
        {21, 22, 23, 24, 25}
    };

    // Define the second matrix
    int m2[SIZE][SIZE] = {
        {25, 24, 23, 22, 21},
        {20, 19, 18, 17, 16},
        {15, 14, 13, 12, 11},
        {10, 9, 8, 7, 6},
        {5, 4, 3, 2, 1}
    };

    // Create a variable to store the operation to perform
    char operation;

    // Ask the user for the operation to perform
    printf("Do you want to (a)add, (m)multiply, or (t)transpose these matrices?:");
    scanf("%c", &operation);

    // Call the run function
    run(m1, m2, operation);
}

/*
 * Takes in two matrices and a character that represents an operation.
 * Performs the operation on the two matrices and prints the result.
 * If the matrices are not compatible for the operation, prints an error message.
 */
void run(int m1[M][N], int m2[Q][R], char operation)
{   
    // Check which operation to perform
    switch (operation) 
    {
        // Multiply the two matrices
        case 'm': {
            // Check if the matrices are compatible for multiplication
            // If so,  multiply the two matrices
            if (N == Q)
            {   
                // Create a new matrix to store the result
                int m[M][R];
                // Multiply the two matrices
                multiplyMatrices(m1, m2, m);
                // Print the result
                printf("Restult:\n");
                // Print the result
                printMatrix(m);
                break;
            }
            // Otherwise, print an error message
            else
            {   // Print an error message if the matrices are not compatible
                printf("These two matrices cannot be multiplied together!\n");
            }
        }
        // Add the two matrices
        case 'a': {
            // Check if the matrices are compatible for addition
            // If so, add the two matrices
            if (M == Q && N == R)
            {   
                // Create a new matrix to store the result
                int m[M][R];
                // Add the two matrices
                addMatrices(m1, m2, m);
                // Print the result
                printf("Result:\n");
                printMatrix(m);
                break;
            }
            // Otherwise, print an error message
            else
            {   
                // Print an error message if the matrices are not compatible
                printf("These two matrices cannot be added together!\n");
            }
        }
        // Transpose the two matrices
        case 't': {
            // Transpose the first matrix and print the result
            printf("Result:\n");
            // Create a new matrix to store the result
            int mT[N][M];
            // Transpose the first matrix
            transposeMatrix(m1, mT);
            // Print the result
            printMatrix(mT);

            // Transpose the second matrix and print the result
            printf("Result:\n");
            // Create a new matrix to store the result
            int m2T[R][Q];
            // Transpose the second matrix
            transposeMatrix(m2, m2T);
            // Print the result
            printMatrix(m2T);
            break;
        }
    }
}

/*
 * Takes in two matrices and returns
 * a pointer to a new matrix that is the sum of 
 * the two matrices.
 */
void addMatrices(int m1[M][N], int m2[M][N], int m[M][N])
{
    // Iterate through the rows of the matrices
    for (int i = 0; i < M; i++)
    {   
        // Iterate through the columns of the matrices
        for (int j = 0; j < N; j++)
        {   
            // Add the two matrices and store in m
            m[i][j] = m1[i][j] + m2[i][j];
        }
    }
}

/*  
 * Takes in one matrix and returns 
 * a pointer to a new matrix that is the transpose.
 */
void transposeMatrix(int m[M][N], int mT[N][M])
{
    // Create a temporary variable to store the value of m[i][j]
    int temp;

    // Iterate through rows the matrix
    for (int i = 0; i < M; i++)
    {   
        // Iterate through the columns of m
        for (int j = 0; j < N; j++)
        {   
            // Perform the transpose operation for each element
            // Swap the rows and columns of m and store in mT
            mT[j][i] = m[i][j];
        }
    }
}

/* 
 * Takes in two matrices and returns a pointer to
 * a new matrix that is the product of the two.
 */
void multiplyMatrices(int m1[M][N], int m2[Q][R], int m[M][R])
{   
    // Create a variable to store m2T
    int m2T[Q][N];
    // Transpose m2 to be used in the multiplication
    transposeMatrix(m2, m2T);

    // Multiply the two matrices
    // m[i][j] = m1[i][k] * m2[k][j]
    // Iterate through the rows of m1
    for (int i = 0; i < M; i++)
    {   
        // Iterate through the columns of m2
        for (int j = 0; j < R; j++)
        {   
            // Initialize the sum to zero for each element
            static int elem = 0;
            // Sum the products of the corresponding elements of the two matrices   
            for (int k = 0; k < N; k++)
            {   
                // Multiply and add to the sum
                elem += m[i][k] * m2T[j][k];
            }
            // Store the result as the i, jth element of the resulting matrix
            m[i][j] = elem;
        }
    }
}

int num_digits(int num)
{
    // If the number is 0, return 1
    if (num == 0)
    {
        return 1;
    }
    int digit_count = 1;
    // If the number is negative, make it positive
    if (num < 0)
    {
        num *= -1;
        // Increment digit count for negative sign
        digit_count++;
    }
    // While the number is greater than 0
    while (num > 10)
    {
        // Divide the number by 10
        num /= 10;
        // Increment the digit count
        digit_count++;
    }
    // Return the digit count
    return digit_count;
}

/*  
 * Prints out a matrix.
 */
void printMatrix(int m[SIZE][SIZE])
{  
    // Find the maximum number in the matrix
    int maxNum = 0;
    // Iterate through the rows of the matrix
    for (int i = 0; i < SIZE; i++)
    {
        // Iterate through the columns of the matrix
        for (int j = 0; j < SIZE; j++)
        {
            // Find the maximum number in the matrix
            if (maxNum < m[i][j])
            {
                maxNum = m[i][j];
            }
        }
    }
    // Find the number of digits in the maximum number
    int maxNumDigits = num_digits(maxNum);


    // Iterate through the rows of the matrix
    for (int i = 0; i < SIZE; i++)
    {   
        // Iterate through the columns of the matrix
        for (int j = 0; j < SIZE; j++)
        {
            // Print the element
            printf("%-*d", maxNumDigits + 2, m[i][j]);
        }
        // Print a new line after each row
        printf("\n");
    }
    printf("\n");
}