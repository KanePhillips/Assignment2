//Author: Kane Phillips
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//Generates a matrix with row/column parameters
void GenerateRandomMatrices(int *matrixPtr, int row, int col){

    printf("Contents of matrix generated: \n");
    for (int i = 0; i < row; i++){
            for(int j = 0; j < col; j++){
                //Random values generated capped at 30 to make output more readable
                *((matrixPtr+i*col)+j) = rand() % 30;
                printf("%d\t", *((matrixPtr+i*col)+j));
            }
            printf("\n");
        }
    printf("End of generated matrix. \n\n");
}

//Multiplies 2 matrices together
void MultiplyMatrices(int *firstMatrixPtr, int *secondMatrixPtr, int *finalMatrixPtr, int firstRow, int firstCol){

    printf("Multiplied Matrix values: \n");
    for (int m = 0; m < firstRow; m++){
        for(int n = 0; n < firstRow; n++){
            *((finalMatrixPtr+m*firstRow)+n) = 0;
            //matrix3[m][n] = 0;

            for (int k = 0; k < firstCol; k++){
                *((finalMatrixPtr+m*firstRow)+n) += *((firstMatrixPtr+m*firstCol)+k) * *((secondMatrixPtr+k*firstRow)+n);
            }
            
            printf("%d\t", *((finalMatrixPtr+m*firstRow)+n));

        }

        printf("\n");
    }
    printf("End of multiplied matrix.\n\n");
}

//Prints already multiplied matrix to a file
void PrintMatrixToFile(int *matrixPtr, int row, int col){

    FILE *matrixOutputFile = fopen("matrix3.txt", "w");
    fprintf(matrixOutputFile, "Multiplied Matrix: \n");
    for (int i = 0; i < row; i++){
            for(int j = 0; j < col; j++){
                
                fprintf(matrixOutputFile, "%d\t", *((matrixPtr+i*col)+j));
            }
            fprintf(matrixOutputFile, "\n");
        }
    fprintf(matrixOutputFile, "End of generated matrix.");
}

int main(int argc, char *argv[]){

    //Values are manually entered to match the default files used for matrix1.txt and matrix2.txt
    const int numRow = 3;
    const int numCol = 2;

    //Matrix 4+5 are the randomly generated matrices, but are referred to in-prompt as matrices 1+2 for the user
    int matrix4[numRow][numCol];
    int matrix5[numCol][numRow];
    char userInput[20];
    FILE *matrix1File;
    FILE *matrix2File;

    //Prompt user
    printf("This program will multiply two matrices from files or from randomly generated matrices.\nThen the final matrix will be displayed.\n");
    printf("Please enter an integer to generate a matrix (the integer entered will be a value used to generate matrices) or the name of the first file containing a matrix: \n");
    scanf("%s", userInput);

    //atoi() returns 0 if string isn't an int, so if checks whether user entered an int or a string for file name
    if(atoi(userInput)){

        int userValueTwo = 1;
        printf("The value you entered will be the first matrix's rows and the second matrix's columns.\nPlease enter another integer to be the first matrix's columns and the second matrix's rows: \n");
        scanf("%d", &userValueTwo);

        //Convert input to int
        int userValueOne = atoi(userInput);

        //Initialize both matrices to be generated
        int matrix4[userValueOne][userValueTwo];
        int matrix5[userValueTwo][userValueOne];

        //Put random values in the 2 matrices, limited to 100 for smaller values
        GenerateRandomMatrices(*matrix4, userValueOne, userValueTwo);
        GenerateRandomMatrices(*matrix5, userValueTwo, userValueOne);

        //Initialize final matrix and multiply for values
        int matrix3[userValueOne][userValueOne];
        MultiplyMatrices(*matrix4, *matrix5, *matrix3, userValueOne, userValueTwo);
        PrintMatrixToFile(*matrix3, userValueOne, userValueOne);
    }
    else{
        
        //else statement controls the file I/O
        matrix1File = fopen(userInput, "r");

        //Makes sure 1st file was found/typed correctly
        if (matrix1File==NULL){
            printf("That file name does not exist. Program will now close.\n");
            exit(0);
        }

        //Gets contents of file 1 and prints it to console
        printf("Contents of %s: \n", userInput);
        for (int o = 0; o < numRow; o++){
            for (int p = 0; p < numCol; p++){
                fscanf(matrix1File, "%d", &matrix4[o][p]);
                printf("%d\t", matrix4[o][p]);
            }
            printf("\n");
        }
        printf("End of %s.\n\n", userInput);

        //Informs user of successful file opening and prompts user for 2nd file
        printf("File opened successfully. Please enter the second file name: \n");
        scanf("%s", userInput);
        matrix2File = fopen(userInput, "r");

        //Makes sure 2nd file was found/typed correctly
        if (matrix2File==NULL){
            printf("That file name does not exist. Program will now close.\n");
            exit(0);
        }

        //Gets contents of 2nd file and prints it to console
        printf("Contents of %s: \n", userInput);
        for (int o = 0; o < numCol; o++){
            for (int p = 0; p < numRow; p++){
                fscanf(matrix2File, "%d", &matrix5[o][p]);
                printf("%d\t", matrix5[o][p]);
            }
            printf("\n");
        }
        printf("End of %s.\n\n", userInput);
        
        //Close both files
        fclose(matrix1File);
        fclose(matrix2File);
        
        //Initialize final matrix and find result
        int matrix3[numRow][numRow];
        MultiplyMatrices(*matrix4, *matrix5, *matrix3, numRow, numCol);
        PrintMatrixToFile(*matrix3, numRow, numRow);
       
    }

    return 0;
}