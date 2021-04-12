#include "criptografia.h"

int main() {
    Parameters_multiplicacao p;
    p.criptografia = {{1, 3, 4, 5}, {7, 9, 0, 1}, {3, 4, 1, 9}, {9, 3, 1, 9}};
    p.coluna = 0;
    p.num_linhas = 10;
    p.matriz_codigo = malloc(10 *sizeof(int *));
    for (int i = 0; i < 10; i++)
        p.matriz_codigo[i] = malloc(4 * sizeof(int));
    p.matriz_texto = malloc(10 *sizeof(int *));
    for (int i = 0; i < 10; i++)
        p.matriz_texto[i] = malloc(4 * sizeof(int));
}