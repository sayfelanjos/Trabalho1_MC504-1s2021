#include "criptografia.h"

void* multiplicacao(void* parametros) {
    Parameters_multiplicacao *p = (Parameters_multiplicacao *) parametros;
    for (int i = 0; i < p->num_linhas; i++)
        for (int j = 0; j < 4; j++)
            p->matriz_codigo[i][p->coluna] += p->matriz_texto[i][j] * p->criptografia[j][p->coluna];
}

int **cria_matriz(int n_linhas) {
    int **mensagem_convertida;
    // aloca um vetor de "linhas" ponteiros para linhas
    mensagem_convertida = malloc (n_linhas * sizeof (int*));
    // aloca cada uma das linhas (vetores de COL inteiros)
    for (int i=0; i < n_linhas; i++){
        mensagem_convertida[i] = malloc (4 * sizeof (int));
    }
    return mensagem_convertida;
}

void libera_memoria(int **matriz, int n_linhas) {
	// libera a memória da matriz
    for (int i = 0; i < n_linhas; i++)
        free (matriz[i]) ;
    free (matriz);
}
