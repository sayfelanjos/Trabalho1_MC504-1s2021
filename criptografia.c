#include "criptografia.h"

void* multiplicacao(void* parametros) {
    Parameters_multiplicacao *p = (Parameters_multiplicacao *) parametros;
    for (int i = 0; i < p->num_linhas; i++)
        for (int j = 0; j < 4; j++)
            p->matriz_codigo[i][p->coluna] += p->matriz_texto[i][j] * p->criptografia[j][p->coluna];
}