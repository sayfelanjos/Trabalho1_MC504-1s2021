#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOTAL 20 // TOTAL = LIN x 4
#define ESCAPE -1
//#define LIN 5

struct parameters_transforma_texto {
    char* mensagem; // endereco do vetor que contem a mensagem
	int** matriz_resultado; // endereco da matriz que armazena o resultado
	int caracter_inicial; // indice do primeiro caracter que sera mapeado pela thread
	int caracter_final; // indice do ultimo caracter que sera mapeado pela thread
};    

struct parameters_transforma_codigo {

	char* texto; // endereco da string que vai armazenar o resultado
    int** matriz_codificada; // endereco da matriz codificada 
	int coluna_inicial; // indice da primeira coluna que sera mapeada pela thread;
	int coluna_final; // indice da ultima coluna que sera mapeada pela thread;
	int linha_inicial; // indice da primeira linha que sera mapeada pela thread;
	int linha_final; // indice da ultima linha que sera mapeada pela thread;
};

typedef struct parameters_transforma_texto parameters_transforma_texto; //parametros para a funcao transforma texto

typedef struct parameters_transforma_codigo parameters_transforma_codigo; //parametros para a funcao transforma codigo

// vetor com a mensagem recebida
char mensagem_original[TOTAL] = "Ola mundo!"; 

// funcao que transforma a mensagem de entrada em uma matriz numerica; realiza o maping entre as letras da mensagem e numeros
void* transforma_texto(void* texto){
    parameters_transforma_texto *p = (parameters_transforma_texto *) texto;
    for (int k = p->caracter_inicial; k <= p->caracter_final; k++){
        p->matriz_resultado[k/4][k%4] = (int) p->mensagem[k];   
    } 
}

// funcao que transforma o codigo criptografado de volta em texto; realiza o maping entre numeros do codigo e letras
void* transforma_codigo(void* codigo){
    parameters_transforma_texto *p = (parameters_transforma_texto *) codigo;
    for (int i= p->linha_inicial; i < p->linha_final; i++){
        for (int j = p->coluna_inicial; j < p->coluna_final; j++){
            p->texto[4*i+j] = (char) p->matriz_resultado[i][j]);   
        }
    }   
}
    

int main(){
    
    int tamanho_mensagem = strlen(mensagem_original);
    int n_linhas = tamanho_mensagem/4;

    int resto_tamanho = tamanho_mensagem % 4; 
	if (resto_tamanho!=0) { // verifica se o numero de caracteres no texto e divisivel por 4
		for (int i=0;i<4-resto_tamanho;i++) { // se nao for divisivel por 4 completa o texto com caracteres de escape
			mensagem_original[tamanho_mensagem] = ESCAPE;
			tamanho_mensagem++;
		}
	}

    // matriz com resultado
    int **mensagem_convertida;
    // aloca um vetor de "n_linhas" ponteiros para linhas
    mensagem_convertida = malloc (n_linhas * sizeof (int*));
    // aloca cada uma das linhas (vetores de COL inteiros)
    for (int i=0; i < n_linhas; i++){
        mensagem_convertida[i] = malloc (4 * sizeof (int));
    }

    parameters_transforma_texto *p;
    p->mensagem = mensagem_original; // endereco do vetor que contem a mensagem
	p->matriz_resultado = mensagem_convertida; // endereco da matriz que armazena o resultado

    for (int k=0; k < tamanho_mensagem; k++){
        if(k < 1*k/4){
            p->caracter_inicial = 0; // indice do primeiro caracter que sera mapeado pela thread
            p->caracter_final = 1*(k/4)-1; // indice do ultimo caracter que sera mapeado pela thread
        }
        if(k < 2*k/4 && k >= 1*k/4){
            p->caracter_inicial = 1*(k/4); // indice do primeiro caracter que sera mapeado pela thread
            p->caracter_final = 2*(k/4)-1; // indice do ultimo caracter que sera mapeado pela thread
        }
        if(k < 3*k/4 && k >= 2*k/4){
            p->caracter_inicial = 2*(k/4); // indice do primeiro caracter que sera mapeado pela thread
            p->caracter_final = 3*(k/4)-1; // indice do ultimo caracter que sera mapeado pela thread
        }
        if(k < 4*k/4 && k >= 3*k/4){
            p->caracter_inicial = 3*(k/4); // indice do primeiro caracter que sera mapeado pela thread
            p->caracter_final = 4*(k/4)-1; // indice do ultimo caracter que sera mapeado pela thread
        }
    }    
    
    transforma_texto(p);

    for (int i=0; i < tamanho_mensagem; i++){
        printf("%c ", mensagem_original[i]);
    } 

    printf("/n/n");

    for (int i=0; i < tamanho_mensagem; i++){
        printf("%d ", mensagem_original[i]);
    } 

    printf("/n/n");

    for (int i=0; i < n_linhas; i++){
        for (int j=0; j < 4; j++){
            printf("%d ", mensagem_convertida[i][j]);   
        }
        printf("/n");
    }    

    //LINHAS = ????;
    int n_elementos = 4*LINHAS; //FAZER ALGO QUE DESCUBRA O NUMERO DE "LINHAS" DA MATRIZ COM MENSAGEM CODIFICADA
    parameters_transforma_texto *t;
    char *mensagem_final = malloc (n_elementos *sizeof(char*));

    t->texto = mensagem_final; // endereco da string que vai armazenar o resultado
    t->matriz_codificada = mensagem_convertida;

    for(int i=0; i < LINHAS; i++){
        if(i <= 1*LINHAS/4 ){
            t->coluna_inicial = 0; 
            t->coluna_final = 3; 
            t->linha_inicial = 0; 
            t->linha_final = 1*(LINHAS/4)-1;
        }
        if(i < 2*LINHAS/4 && i >= 1*LINHAS/4){
            t->coluna_inicial = 0; 
            t->coluna_final = 3; 
            t->linha_inicial = 1*(LINHAS/4); 
            t->linha_final = 2*(LINHAS/4)-1;
        }
        if(i < 3*LINHAS/4 && i >= 2*LINHAS/4){
            t->coluna_inicial = 0; 
            t->coluna_final = 3; 
            t->linha_inicial = 2*(LINHAS/4); 
            t->linha_final = 3*(LINHAS/4)-1;
        }
        if(i < 4*LINHAS/4 && i >= 3*LINHAS/4){
            t->coluna_inicial = 0; 
            t->coluna_final = 3; 
            t->linha_inicial = 3*(LINHAS/4); 
            t->linha_final = 4*(LINHAS/4)-1;
        }
    }    

    transforma_codigo(t);

    for (int i=0; i < tamanho_mensagem; i++){
        printf("%c ", mensagem_final[i]);
    } 
    printf("/n/n");

    // libera a memória da matriz
    for (int i=0; i < n_linhas; i++)
        free (mensagem_convertida[i]) ;
    free (mensagem_convertida) ;

    return 1;
}




