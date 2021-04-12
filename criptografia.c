#include "criptografia.h"

void* multiplicacao(void* parametros) {
    Parameters_multiplicacao *p = (Parameters_multiplicacao *) parametros;
    for (int i = 0; i < p->num_linhas; i++)
        for (int j = 0; j < 4; j++)
            p->matriz_codigo[i][p->coluna] += p->matriz_texto[i][j] * p->criptografia[j][p->coluna];
}

int **cria_matriz(int n_linhas) {
    int **matriz;
    // aloca um vetor de "linhas" ponteiros para linhas
    matriz = malloc (n_linhas * sizeof (int*));
    // aloca cada uma das linhas (vetores de COL inteiros)
    for (int i=0; i < n_linhas; i++){
        matriz[i] = malloc (4 * sizeof (int));
        for (int k = 0; k < 4; k++)
            matriz[i][k] = -1;
    }
    return matriz;
}

void libera_memoria(int **matriz, int n_linhas) {
	// libera a memória da matriz
    for (int i = 0; i < n_linhas; i++)
        free (matriz[i]);
    free (matriz);
}

p_vetor cria_vetor() {
    p_vetor v = malloc(sizeof(Array));
    v->array_first = NULL;
    v->array_last = NULL;
    v->size = 0;
    return v;
}

p_vetor inseri_dado(p_vetor vetor, char dado) {
    p_no p = malloc(sizeof(No));
    if (vetor->size == 0) {
        vetor->array_first = p;
        vetor->array_last = p;
        vetor->size += 1;
        p->c = dado;
        p->next = NULL;
        return vetor;
    } else {
        vetor->array_last->next = p;
        vetor->array_last = p;
        p->c = dado;
        p->next = NULL;
        vetor->size += 1;
        return vetor;
}