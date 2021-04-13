#include <stdio.h>
#include <stdlib.h>

typedef struct No {
	char c;
	struct No *next;
} No;

typedef struct No *p_no;

typedef struct Array {
	p_no array_first;
	p_no array_last;
	int size;
} Array;

typedef struct Array *p_vetor;

typedef struct {
	int **criptografia;
	int **matriz_texto;
	int num_linhas; // numero de linhas da matriz a ser criptografada.
	int coluna; // numero da coluna que está sendo criptografada
	int **matriz_codigo; // endereco da matriz que sera usada para armazenar o resultado final da multiplicacao
} Parameters_multiplicacao;

typedef struct parameters_transforma_texto {
    p_vetor mensagem; // endereco do vetor que contem a mensagem
	int** matriz_resultado; // endereco da matriz que armazena o resultado
	int caracter_inicial; // indice do primeiro caracter que sera mapeado pela thread
	int caracter_final; // indice do ultimo caracter que sera mapeado pela thread
} parameters_transforma_texto;    

typedef struct parameters_transforma_codigo {

	char* texto; // endereco da string que vai armazenar o resultado
    int** matriz_codificada; // endereco da matriz codificada 
	int coluna_inicial; // indice da primeira coluna que sera mapeada pela thread;
	int coluna_final; // indice da ultima coluna que sera mapeada pela thread;
	int linha_inicial; // indice da primeira linha que sera mapeada pela thread;
	int linha_final; // indice da ultima linha que sera mapeada pela thread;
} parameters_transforma_codigo;

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

/**
 * cria um array 2D
 */
int **cria_matriz(int n_linhas);

/**
 * recebi um array 2D e desaloca memória
 */
void destroi_matriz(int **matriz, int n_linhas);

/**
 * cria array 1D
 */
p_vetor cria_vetor();

/**
 * inseri um dado no vetor
 */
p_vetor inseri_dado(p_vetor vetor, char dado);

/**
 * destroi vetor
 */
void destroi_vetor(p_vetor vetor);

void* transforma_texto(void* texto);

void* transforma_codigo(void* codigo);
