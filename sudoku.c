/**
 * Primeiro trabalho de MC504 2021s1
 * Desenvolvimento:
 * David Santos, Lucas Martins e Saymon Felipe
 */

#include <stdio.h>
#include <stdlib.h>

int verify_rows(int matrix[9][9]);
int n_is_in_row(int n, int i, int matrix[9][9]);
int verify_columns(int matrix[9][9]);
int n_is_in_column(int n, int j, int matrix[9][9]);
int verify_block(int matrix[9][9]);
int n_is_in_block(int r, int s, int n, int matrix[9][9]);
int solve_sudoku(int i, int j, int n, int matrix[9][9]);
void display_sudoku(int sudoku[9][9]);

int main() {
    int sudoku[9][9];
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            sudoku[i][j] = 0;

    solve_sudoku(0, 0, 9, sudoku);
    display_sudoku(sudoku);

}
/** This function receive a sudoku and return 0 if
 * in rows of table
 * 
 * 
 */

int verify_rows(int matrix[9][9]) {
    for (int i = 0; i < 9; i++)
        for (int n = 1; n <= 9; n++) {
            if (n_is_in_row(n, i, matrix))
                continue;
            return 0;
        }
    return 1;
}

int n_is_in_row(int n, int i, int matrix[9][9]) {
    for (int j = 0; j < 9; j++)
        if (matrix[i][j] == n) 
            return 1;
    return 0;
}

int verify_columns(int matrix[9][9]) {
    for (int j = 0; j < 9; j++) {
        for (int n = 1; n <= 9; n++) {
            if (n_is_in_column(n, j, matrix))
                continue;
            return 0;
        }
    }
}

int n_is_in_column(int n, int j, int matrix[9][9]) {
    for (int i = 0; i < 9; i++)
        if (matrix[i][j] == n) 
            return 1;
    return 0;
}

int verify_block(int matrix[9][9]) {
    for (int r = 0; r <= 2; r ++) {
        for (int s = 0; s <= 2; s++) {
            for (int n = 1; n <= 9; n++) {
                if (n_is_in_block(r, s, n, matrix))
                    continue;
                return 0;
            }
        }
    }
    return 1;
}

int n_is_in_block(int i, int j, int n, int matrix[9][9]) {
    int r, s;
    if (i >= 0 && i < 3)
        r = 0;
    else if (i > 2 && i < 6)
        r = 1;
    else if (i > 5 && i < 9)
        r = 2;
    if (j >= 0 && j < 3)
        s = 0;
    else if (j > 2 && j < 6)
        s = 1;
    else if (j > 5 && j < 9)
        s = 2;
    for (int i = 0; i <= 2; i++) {
        for (int j = 0; j <= 2; j++) {
            if (matrix[3*r+i][3*s+j] == n)
                return 1;
        }
    }
    return 0;
}

int solve_sudoku(int i, int j, int n, int matrix[9][9]) {
    if (i > 8 && j > 8)
        return 0;
    if (n_is_in_row(n, i, matrix))
        solve_sudoku(i, j, rand()%9+1, matrix);
    if (n_is_in_column(n, j, matrix)) 
        solve_sudoku(i, j, rand()%9+1, matrix);
    if (n_is_in_block(i, j, n, matrix))
        solve_sudoku(i, j, rand()%9+1, matrix);
    matrix[i][j] = n;
    display_sudoku(matrix);
    if (j < 8)
        solve_sudoku(i, j+1, rand()%9+1, matrix);
    else
        solve_sudoku(i+1, 0, rand()%9+1, matrix);


}

void display_sudoku(int sudoku[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (j < 8)
                if (j == 2 || j == 5 || j == 8)
                    printf("%d%s", sudoku[i][j], "|");
                else
                    printf("%d ", sudoku[i][j]);
            else
                printf("%d", sudoku[i][j]);
        }
        printf("\n");
        if (i == 2 || i == 5 || i == 8) {
            for  (int i = 0; i < 17; i++)
                printf("%s", "-");
            printf("\n");
        }
    }
}