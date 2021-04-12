#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int **criptografia;
	int **matriz_texto;
	int num_linhas; // numero de linhas da matriz a ser criptografada.
	int coluna; // numero da coluna que está sendo criptografada
	int **matriz_codigo; // endereco da matriz que sera usada para armazenar o resultado final da multiplicacao
} Parameters_multiplicacao;

struct parameters_transforma_texto {
	int*** matriz_resultado; // endereco da matriz que armazena o resultado
	int caracter_inicial; // indice do primeiro caracter que sera mapeado pela thread
	int caracter_final; // indice do ultimo caracter que sera mapeado pela thread
};

struct parameters_transforma_codigo {
	char** texto; // endereco da string que vai armazenar o resultado
	int coluna_inicial; // indice da primeira coluna que sera mapeada pela thread;
	int coluna_final; // indice da ultima coluna que sera mapeada pela thread;
	int linha_inicial; // indice da primeira linha que sera mapeada pela thread;
	int linha_final; // indice da ultima linha que sera mapeada pela thread;
};

/**
 * funcao usada pela thread pra multiplicar a 
 * matriz de entrada pela matriz de criptografia
 */
void* multiplicacao(void* parametros); 

/** 
 * funcao que transforma a mensagem de entrada em 
 * uma matriz numerica; realiza o maping entre as 
 * letras da mensagem e numeros
 */
void* transforma_texto(void* texto); 

/**
 * funcao que transforma o codigo criptografado de volta em texto; 
 * realiza o maping entre numeros do codigo e letras
 */
void* transforma_codigo(void* codigo); 
