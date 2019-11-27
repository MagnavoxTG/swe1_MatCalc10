#include <stdio.h>
#include <stdlib.h>

//function to display a matrix | input the matrix array, the rows and the columns of the matrix
void show_matrix(int mat[10][10],int rows, int columns);

//defines the name of the input file
#define filename "matrix.txt";

int main() {
    //initializing fptr as a file
    FILE *fptr;
    //initializing variables
    int ch, countstr = 0,countmat = 0, countmatrow = 0, countmatcol = 0, mat1rows = 0, mat1columns = 0, mat2rows = 0, mat2columns = 0, rowsoffile = -1;
    char str[100], operator = ' ';
    int matrix1[10][10], matrix2[10][10], matrixresult[10][10];
    char filenamechar[100] = filename;

    str[0] = '\0';  //making sure that the first symbol of the string is the string end symbol

    fptr = fopen(filenamechar, "r");    //opens a file into fptr for reading

    while ((ch = fgetc(fptr)) != EOF) {    //goes through a file character by character until end of file

        if (ch == '<'){     //searches for the beginning of the bracket in which the rows and columns are written
            while ((ch = fgetc(fptr)) != '>'){     //writes everything between the brackets into a string
                str[countstr] = (char)ch;   //casts the int into a char and puts it into the string
                countstr ++;    //increases the current string position counter
            }
            str[countstr] = '\0';   //string end symbol
            countstr = 0;   //resets char count of string

            if (str[0] != '\0' && countmat == 0) {      //if string is not empty and it contains the rows of matrix1
                countmat++;     //counter to tell which bracket it is (the first, second, third...)
                mat1rows = atoi(str);   //casts the string into an int
                str[0] = '\0';      //effectively setting string to empty
            }

            if (str[0] != '\0' && countmat == 1) {    //if string is not empty and it contains the columns of matrix1
                countmat++;     //counter to tell which bracket it is (the first, second, third...)
                mat1columns = atoi(str);    //casts the string into an int
                str[0] = '\0';      //effectively setting string to empty
            }

            if (str[0] != '\0' && countmat == 2) {    //if string is not empty and it contains the operator
                countmat++;     //counter to tell which bracket it is (the first, second, third...)
                operator = str[0];    //takes the operator char from the string and puts it into operator
                str[0] = '\0';      //effectively setting string to empty
            }

            if (str[0] != '\0' && countmat == 3) {    //if string is not empty and it contains the rows of matrix2
                countmat++;     //counter to tell which bracket it is (the first, second, third...)
                mat2rows = atoi(str);    //casts the string into an int
                str[0] = '\0';      //effectively setting string to empty
            }

            if (str[0] != '\0' && countmat == 4) {    //if string is not empty and it contains the columns of matrix2
                countmat++;     //counter to tell which bracket it is (the first, second, third...)
                mat2columns = atoi(str);    //casts the string into an int
                str[0] = '\0';      //effectively setting string to empty
            }
        }

        if (ch == '\n'){    //if its a new line in counts up by one
            rowsoffile++;   //variable to tell which row it is (first row is -1)
        }

        if (rowsoffile >= 0 && rowsoffile != mat1rows && rowsoffile != mat1rows+1){     //if it is not a row in which the matrix or the mathematical operator is located
            if (ch == '\n')     //if the first symbol is \n in gets skipped
                (ch = fgetc(fptr));     //advances to next character in the file
            while (ch != '\n' && ch != EOF){    //until we reach the next row
                while (ch != ' ' && ch != '\n' && ch != EOF){  //writes everything into a string until we reach a space
                    str[countstr] = (char)ch;       //casts the int into a char and writes it into a string
                    countstr ++;    //counts the currents position of the string
                    (ch = fgetc(fptr));    //goes to the next character
                }
                str[countstr] = '\0';   //sets string end symbol

                if (rowsoffile <= mat1rows)     //checks if the number belongs into the first matrix
                    matrix1[rowsoffile][countmatcol] = atoi(str);   //writes the string into the array as int
                if (rowsoffile > mat1rows)      //checks if the number belongs into the second matrix
                    matrix2[rowsoffile-(mat1rows+2)][countmatcol] = atoi(str);   //writes the string into the array as int | +2 because there a 2 rows between the first and second matrix

                countstr = 0;       //resets the char count
                str[0] = '\0';      //resets the string
                countmatcol++;      //counts in which column we are
                if (ch == ' ')     //only advances when ch is a space
                    (ch = fgetc(fptr));    //goes to the next character
            }
            countmatcol = 0;    //at the end of the line it resets the column count
            rowsoffile++;       //at the end of the line it increases the file row count
        }

    }

    if (operator == '+'){   //checks if the operator is addition
        if (mat1rows == mat2rows && mat1columns == mat2columns){    //checks if addition is possible
            for (int x = 0; x < mat1rows; ++x) {    //goes through all rows
                for (int y = 0; y < mat1columns; ++y) {     //goes through all columns
                    matrixresult[x][y] = matrix1[x][y] + matrix2[x][y];     //puts the sum of each addition into the reslut matrix
                }
            }
            printf("Your Reslut is: \n");   //displays message to make output more readable
            show_matrix(matrixresult,mat1rows, mat1columns);    //calls function to display matrix | needs matrix and the number of rows and columns
        } else {
            printf("\nAddition is not possible with these matrices");   //displays error message
        }
    }

    if (operator == '*'){   //checks if the operator is multiplication
        if (mat1columns == mat2rows){    //checks if multiplication is possible
            for (int x = 0; x < mat1rows; ++x) {    //does it as many times as matrix 1 has rows
                for (int y = 0; y < mat2columns; ++y) {     //does it as many times as matrix 2 has columns
                    int cachenumber = 0;    //initializing an int to cache the reslut of each multiplication
                    for (int z = 0; z < mat2columns; ++z) {     //does it as many times as matrix 2 has columns
                        cachenumber += matrix1[x][z] * matrix2[z][y];   //does matrix multiplication and writes reslut into cachenumber
                    }
                    matrixresult[x][y] = cachenumber;   //puts the multiplication result into correct position of the result matrix
                }
            }
            printf("Your Reslut is: \n");   //displays message to make output more readable
            show_matrix(matrixresult,mat1rows, mat2columns);    //calls function to display matrix | needs matrix and the number of rows and columns
        } else {
            printf("\nMultiplication is not possible with these matrices");     //displays error message
        }
    }

    return 0;
}

//function to display a matrix | input the matrix array, the rows and the columns of the matrix
void show_matrix(int (*mat)[10], int rows, int columns) {
    for (int x = 0; x < rows; x++) {    //goes though all the rows of the matrix
        printf("( ");   //adds ( at the beginning of the row
        for (int y = 0; y < columns; y++) {     //goes through all the columns of a matrix
            printf("%i ",mat[x][y]);    //prints the individual values for each position of the matrix
        }
        printf(")\n");      //adds a ) at the end of the row and starts a new one
    }
}