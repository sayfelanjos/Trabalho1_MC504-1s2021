structure parameters_multiplicacao {

	int linha_inicial; // numero da primeira linha da matriz resultante da entrada que sera multiplicada pela thread
	int linha_final; // numero da ultima linha da matriz resultante da entrada que sera multiplicada pela thread
	int coluna_inicial; // numero da coluna da primeira coluna da matriz de criptografia que sera multiplicada pela thread
	int coluna_final; //numero da ultima coluna da matriz de criptografia que sera multiplicada pela thread
	int *** matriz_codigo; // endereco da matriz que sera usada para armazenar o resultado final da multiplicacao
};

structure parameters_transforma_texto {

	int*** matriz_resultado; // endereco da matriz que armazena o resultado
	int caracter_inicial; // indice do primeiro caracter que sera mapeado pela thread
	int caracter_final; // indice do ultimo caracter que sera mapeado pela thread
};

structure parameters_transforma_codigo {

	char** texto; // endereco da string que vai armazenar o resultado
	int coluna_inicial; // indice da primeira coluna que sera mapeada pela thread;
	int coluna_final; // indice da ultima coluna que sera mapeada pela thread;
	int linha_inicial; // indice da primeira linha que sera mapeada pela thread;
	int linha_final; // indice da ultima linha que sera mapeada pela thread;
};

typedef structure parameters_multiplicacao parameters_multiplicacao; //parametros para a funcao multiplicacao

typedef structure parameters_transforma_texto parameters_transforma_texto; //parametros para a funcao transforma texto

typedef structure parameters_transforma_codigo parameters_transforma_codigo; //parametros para a funcao transforma codigo

void* multiplicacao(void* parametros); //funcao usada pela thread pra multiplicar a matriz de entrada pela matriz de criptografia

void* transforma_texto(void* texto); // funcao que transforma a mensagem de entrada em uma matriz numerica; realiza o maping entre as letras da mensagem e numeros

void* transforma_codigo(void* codigo); // funcao que transforma o codigo criptografado de volta em texto; realiza o maping entre numeros do codigo e letras
