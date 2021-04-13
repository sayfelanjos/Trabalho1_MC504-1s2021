#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "criptografia.h"



int main() {
	int **matriz_entrada; // matriz de numeros inteiros obtida a partir do texto de entrada;
	int **matriz_criptografia; // matriz de criptografia
	int **matriz_criptografia_inv;
	int **matriz_saida;
	p_vetor vetor_texto = cria_vetor();
	int erro = 0;
	//-------------------------- Escolher se vai criptografar ou descriptografar
	
	FILE* arquivo_matriz; 
        int matriz_ent; 
	matriz_criptografia = (int**) malloc(4*sizeof(int*));
	matriz_criptografia_inv = (int**) malloc(4*sizeof(int*));
	for (int i=0;i<4;i++) {
		matriz_criptografia[i] = (int*) malloc(4*sizeof(int));
		matriz_criptografia_inv[i] = (int*) malloc(4*sizeof(int));
	}
        if ((arquivo_matriz=fopen("matriz.txt","r"))!=NULL) {
		for (int i=0;i<4;i++) {
			for (int j=0;j<4;j++) {
                		fscanf(arquivo_matriz,"%d",&matriz_ent);
                        	matriz_criptografia[i][j] = matriz_ent;
                	}
		}
        }
	fclose(arquivo_matriz);

	if ((arquivo_matriz=fopen("matriz_inversa.txt","r"))!=NULL) {
                for (int i=0;i<4;i++) {
                        for (int j=0;j<4;j++) {
                                fscanf(arquivo_matriz,"%d",&matriz_ent);
                                matriz_criptografia_inv[i][j] = matriz_ent;
                        }
                }
        }
        fclose(arquivo_matriz);
	
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

	//-------------------------- Parte responsavel pela leitura do arquivo
	FILE* arquivo_entrada; // ponteiro para o arquivo que contem a mensagem que sera criptografada
	char c; // caractere de entrada
	// int tamanho_mensagem = 0; // indice do vetor em que sera armazenado o caractere atual
	if ((arquivo_entrada=fopen("mensagem.txt","r"))!=NULL) { // tentativa de abrir o arquivo
		while((c=fgetc(arquivo_entrada))!=EOF) { // le o arquivo caractere por caractere ate encontrar o final
			inseri_dado(vetor_texto, c); // armazena o caractere atual no vetor de caracteres
			// tamanho_mensagem++; // incrementa o indice do proximo caractere que sera armazenado
		}
	}
	fclose(arquivo_entrada); // fecha o arquivo
	//------------------------- Parte responsavel pela leitura do arquivo
	
	
	//------------------------ Parte responsavel por obter uma matriz de inteiros a partir da matriz de texto

	int n_linhas = vetor_texto->size/4; // calcula o numero de colunas da matriz resultante da codificacao
	if (n_linhas%4!=0) {
		n_linhas++;
	}
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
	fclose(arquivo_saida);
	//-----------------------Parte responsavel por salvar a saida em um documento de texto
	} // fim da parte responsavel por criptografar


	else if (opcao==2) { //Se o usuario quiser descriptografar
		//-------------------------- Parte responsavel pela leitura do arquivo
		FILE* arquivo_entrada; // ponteiro para o arquivo que contem a mensagem criptografada
		int entrada; //inteiro que armazena o valor lido na entrada
		int n_linhas = 0; // linha da matriz em que sera armazenada o inteiro atual
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
					matriz_entrada[i][j] = entrada;
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
		

		// //------------------------ Parte responsavel por obter uma vetor de caracteres a partir da matriz de inteiros
		// pthread_t t_codificacao[4]; // threads responsaveis por transformar a matriz codigo em um vetor de caracteres


		//------------------------Parte responsavel por salvar a saida em um documento de texto
		FILE* arquivo_saida; // ponteiro para o arquivo que armazena o texto descriptografado
        	if ((arquivo_saida=fopen("texto.txt","w"))!=NULL) {
                	for (int i = 0; i < n_linhas; i++)
                        for (int j = 0; j < 4; j++)
							if (matriz_saida[i][j] != -1)
								fprintf(arquivo_saida,"%c", (char) matriz_saida[i][j]);

        	}
        	fclose(arquivo_saida);
        //-----------------------Parte responsavel por salvar a saida em um documento de texto

	}// fim da parte responsavel por descriptografar
	destroi_matriz(matriz_criptografia,4);
	destroi_matriz(matriz_criptografia_inv,4);
	return 0;
} // Fim do codigo
