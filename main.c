#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "criptografia.h"

int n_linhas;

int main(void) {
	int **matriz_entrada; // matriz que armazena a entrada da operacao de multiplicacao
	int **matriz_criptografia; // matriz de criptografia
	int **matriz_criptografia_inv; // matriz inversa
	int **matriz_saida; //matriz que armazena o resultado da operacao de multiplicacao
	p_vetor vetor_texto = cria_vetor(); // lista ligada que armazena o texto que sera criptografado
	int erro = 0;
	
	//-------------------------- Aloca memoria e realiza a leitura das matrizes de criptografia 

	FILE* arquivo_matriz; 
	matriz_criptografia = (int**) malloc(4*sizeof(int*));
	matriz_criptografia_inv = (int**) malloc(4*sizeof(int*));
	for (int i=0;i<4;i++) {
		matriz_criptografia[i] = (int*) malloc(4*sizeof(int));
		matriz_criptografia_inv[i] = (int*) malloc(4*sizeof(int));
	}
        if ((arquivo_matriz=fopen("matriz.txt","r"))!=NULL) {
		for (int i=0;i<4;i++) {
			for (int j=0;j<4;j++) {
                		fscanf(arquivo_matriz,"%d",&matriz_criptografia[i][j]);
                	}
		}
        }
	fclose(arquivo_matriz);

	if ((arquivo_matriz=fopen("matriz_inversa.txt","r"))!=NULL) {
                for (int i=0;i<4;i++) {
                        for (int j=0;j<4;j++) {
                                fscanf(arquivo_matriz,"%d",&matriz_criptografia_inv[i][j]);
                        }
                }
        }
        fclose(arquivo_matriz);
	//-------------------------- Aloca memoria e realiza a leitura das matrizes de criptografia 


	//-------------------------- Escolher se vai criptografar ou descriptografar

	int opcao = 0;

	while (1) {
		printf("Digite (1) para criptografar uma mensagem.\nDigite (2) para descriptografar uma mensagem.\n");
		scanf("%d", &opcao);
		if (opcao==1||opcao==2) {
			break;
		}
	}
	//------------------------- Escolher se vai criptografar ou descriptografar

	if (opcao==1) { // Se o usuario quiser criptografar

	printf("Mensagem sendo criptografada. \n");

	//-------------------------- Parte responsavel pela leitura do arquivo
	FILE* arquivo_entrada; // mensagem que sera criptografada
	char c; // caractere de entrada
	if ((arquivo_entrada=fopen("mensagem.txt","r"))!=NULL) {
		while((c=fgetc(arquivo_entrada))!=EOF) { // le o arquivo caractere por caractere ate encontrar o final
			inseri_dado(vetor_texto, c); // armazena o caractere atual no vetor de caracteres

		//-------------------------- Parte responsavel pela leitura do arquivo
		FILE* arquivo_entrada; // mensagem que sera criptografada
		char c; // caractere de entrada
		if ((arquivo_entrada=fopen("mensagem.txt","r"))!=NULL) {
			while((c=fgetc(arquivo_entrada))!=EOF) { // le o arquivo caractere por caractere ate encontrar o final
				inseri_dado(vetor_texto, c); // armazena o caractere atual no vetor de caracteres
			}
		}
		fclose(arquivo_entrada); // fecha o arquivo
		//------------------------- Parte responsavel pela leitura do arquivo


		
		//------------------------ Parte responsavel por obter uma matriz de inteiros a partir da matriz de texto

		n_linhas = vetor_texto->size/4; // calcula o numero de linhas da matriz resultante da codificacao
		if (vetor_texto->size%4!=0) {
			n_linhas++;
		} // adiciona uma linha caso o tamanho do texto nao seja divisel por 4
		matriz_entrada = cria_matriz(n_linhas); // inicializa a matriz de entrada;
		matriz_saida = cria_matriz(n_linhas); // inicializa a matriz que receberá a mensagem criptografada.
		pthread_t t_codificacao[4]; // threads responsaveis pela codificacao

		parameters_transforma_texto parametros_cria_matriz[4]; // parametros para as threads
		
		
		for (int i=0;i<4;i++) { // atribui valores para os parametros de cada thread
			parametros_cria_matriz[i].mensagem = vetor_texto;
			parametros_cria_matriz[i].matriz_resultado = matriz_entrada;
			parametros_cria_matriz[i].caracter_inicial = i*vetor_texto->size/4;
			parametros_cria_matriz[i].caracter_final = (i+1)*vetor_texto->size/4;
		}
		for (int i=0;i<4;i++) { // cria as threads responsaveis pela codificacao
			if (!erro) {
				erro = pthread_create(&t_codificacao[i],NULL,transforma_texto,&parametros_cria_matriz[i]);
			}
			else {
				printf("Erro ocorrido na criacao de threads.\n");
				return 1;
			}
		}
		for (int i=0;i<4;i++) { // espera as threads responsaveis pela codificacao terminarem a tarefa
			if (!erro) {
				erro = pthread_join(t_codificacao[i],NULL);
			}
			else {
				printf("Erro ocorrido na tentativa de juntar threads.\n");
				return 1;
			}
		}
		//------------------------Parte responsavel por obter uma matriz de inteiros a partir da matriz de texto
		
		
		//------------------------Parte responsavel por realizar a multiplicacao de matrizes
		pthread_t t_multiplicacao[4]; // threads responsaveis pela multiplicacao
		Parameters_multiplicacao parametros_multiplicacao[4]; // parametros para as threads responsaveis pela multiplicacao
		for (int i=0;i<4;i++) { // atribui valores para os parametros de cada thread
			parametros_multiplicacao[i].criptografia = matriz_criptografia;
			parametros_multiplicacao[i].matriz_texto = matriz_entrada;
			parametros_multiplicacao[i].num_linhas = n_linhas;
			parametros_multiplicacao[i].coluna = i;
			parametros_multiplicacao[i].matriz_codigo = matriz_saida;
		}
		for (int i=0;i<4;i++) { //cria as threads responsaveis pela multiplicacao
			if (!erro) {
				erro = pthread_create(&t_multiplicacao[i],NULL,multiplicacao,&parametros_multiplicacao[i]);
			}
			else {
				printf("Erro ocorrido na criacao de threads.\n");
				return 1;
			}
		}
		for (int i=0;i<4;i++) { // espera as threads responsaveis pela multiplicacao terminarem a tarefa
			if (!erro) {
				erro = pthread_join(t_multiplicacao[i],NULL);
			}
			else {
				printf("Erro ocorrido na tentiva de juntar threads");
				return 1;
			}
		}
		//------------------------Parte responsavel por realizar a multiplicacao de matrizes
		

		//------------------------Parte responsavel por salvar a saida em um documento de texto
		FILE* arquivo_saida;
		if ((arquivo_saida=fopen("codigo.txt","w"))!=NULL) {
			for (int i=0;i<n_linhas;i++) {
				for (int j=0;j<4;j++) {
					fprintf(arquivo_saida,"%d ", matriz_saida[i][j]);
				}
				fprintf(arquivo_saida,"\n");
			}
		}
<<<<<<< HEAD
	}
	fclose(arquivo_saida);
	//-----------------------Parte responsavel por salvar a saida em um documento de texto
	
	printf("A mensagem criptografada se encontra no arquivo codigo.txt .\n");

		fclose(arquivo_saida);
		//-----------------------Parte responsavel por salvar a saida em um documento de texto
	} // fim da parte responsavel por criptografar


	else if (opcao==2) { //Se o usuario quiser descriptografar

		printf ("Mensagem sendo descriptografada. \n");
		//-------------------------- Parte responsavel pela leitura do arquivo
		FILE* arquivo_entrada; // ponteiro para o arquivo que contem a mensagem criptografada
		int n_linhas = 0; // linha da matriz em que sera armazenada o inteiro atual
		int entrada;
		if ((arquivo_entrada=fopen("codigo.txt","r"))!=NULL) {
			while((fscanf(arquivo_entrada,"%d",&entrada))!=EOF) {
				n_linhas++;
			}
		}
		fclose(arquivo_entrada);
		n_linhas/= 4;
		matriz_entrada = cria_matriz(n_linhas); // inicializa a matriz de entrada;
		matriz_saida = cria_matriz(n_linhas); // inicializa a matriz que receberá a mensagem criptografada.		
		
		if ((arquivo_entrada=fopen("codigo.txt","r"))!=NULL) {
			for(int i = 0; i < n_linhas; i++) {
				for(int j = 0; j < 4; j++){
					fscanf(arquivo_entrada,"%d ", &matriz_entrada[i][j]);
				}
			}
		}
		fclose(arquivo_entrada);
		//-------------------------- Parte responsavel pela leitura do arquivo


		//------------------------Parte responsavel por realizar a multiplicacao de matrizes
		pthread_t t_multiplicacao[4]; // threads responsaveis pela multiplicacao
		Parameters_multiplicacao parametros_multiplicacao[4]; // parametros para as threads que realizam a multiplicacao
	        for (int i=0;i<4;i++) { // atribui valores para os parametros de cada threads
        	        parametros_multiplicacao[i].criptografia = matriz_criptografia_inv;
               		parametros_multiplicacao[i].matriz_texto = matriz_entrada;
                	parametros_multiplicacao[i].num_linhas = n_linhas;
                	parametros_multiplicacao[i].coluna = i;
                	parametros_multiplicacao[i].matriz_codigo = matriz_saida;
        	}
        	for (int i=0;i<4;i++) { // cria as threads responsaveis pela multiplicacao
			if (!erro) {
        	        	erro = pthread_create(&t_multiplicacao[i],NULL,multiplicacao,&parametros_multiplicacao[i]);
			}
			else {
				printf("Erro ocorrido na criacao de threads.\n");
				return 1;
			}
        	}
        	for (int i=0;i<4;i++) { // espera as threads responsaveis pela multiplicacao terminarem a tarefa
			if (!erro) {
        	        	erro = pthread_join(t_multiplicacao[i],NULL);
			}
			else {
				printf("Erro ocorrido na tentativa de juntar threads");
				return 1;
			}
        	}
		//------------------------Parte responsavel por realizar a multiplicacao de matrizes


		//------------------------Parte responsavel por salvar a saida em um documento de texto
		FILE* arquivo_saida; // ponteiro para o arquivo que armazena o texto descriptografado
        	if ((arquivo_saida=fopen("texto.txt","w"))!=NULL) {
                	for (int i = 0; i < n_linhas; i++)
                        	for (int j = 0; j < 4; j++)
					if (matriz_saida[i][j] != 0)
						fprintf(arquivo_saida,"%c", (char) matriz_saida[i][j]);

        	}
        	fclose(arquivo_saida);
        //-----------------------Parte responsavel por salvar a saida em um documento de texto

	printf("A mensagem descriptografada se encontra no arquivo texto.txt .\n");
		
	}// fim da parte responsavel por descriptografar

	destroi_vetor(vetor_texto);
	destroi_matriz(matriz_saida, n_linhas); // libera a memoria alocada para a matriz original
	destroi_matriz(matriz_entrada, 	n_linhas); // libera a memoria alocada para a matriz original
	destroi_matriz(matriz_criptografia,4); // libera a memoria alocada para a matriz original
	destroi_matriz(matriz_criptografia_inv,4); // libera a memoria alocada para a matriz inversa
	return 0;
} // Fim do codigo
