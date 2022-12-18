#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

void bubble_sort (double *matriz, int tam) {
    int i, j; 
    double aux;

    for(i = tam - 1; i > 0; i--) {
        for(j = 0; j < i; j++) {
            if(matriz[j] > matriz[j + 1]) {
                aux = matriz[j];
                matriz[j] = matriz[j + 1];
                matriz[j + 1] = aux;
            }
        }
    }
}

void ordena_colunas(double *matriz, int lin, int col) {
    int i;
    
    for(i = 0; i < col; i++) {    
        //manda o endereco do primeiro elemento da coluna, limites inf e sup e a largura da matriz
        bubble_sort(&matriz[i * lin], lin);
    }
} 

void calcula_media(double *matriz, double *vet, int lin, int col) {
    int i, j;
    double soma;

    for(i = 0; i < col; i++) {
        soma = 0;
        for(j = 0; j < lin; j++) {
            soma += matriz[i * lin + j];
        }
        vet[i] = soma / lin; 
    }   
}

void calcula_media_harmonica(double *matriz, double *vet,int lin, int col) {
    int i, j;
    double soma;
    for(i = 0; i < col; i++) {
        soma = 0;
        for(j = 0; j < lin; j++) {
            soma += (1 / (matriz[i * lin + j]));
        }
        vet[i] = lin / soma; 
    }   
}

void calcula_mediana(double *matriz, double *vet, int lin, int col) {  
    int i = 0;
    if((lin - 1) % 2) { //Quantidade par de elementos
        for(i = 0; i < col; i++) {
            vet[i] = (matriz[(((i * lin) + (i + 1) * lin) - 1) / 2] + matriz[((((i * lin) + (i + 1) * lin) - 1) / 2) + 1]);
            vet[i] *= 0.5;  
        }
    } else { //Quantidade ímpar de elementos
        for(i = 0; i < col; i++) {
            vet[i] = matriz[(((i * lin) + (i + 1) * lin) - 1) / 2];
        }
    }    
} 

// Adaptado de https://www.clubedohardware.com.br/forums/topic/1291570-programa-em-c-que-calcula-moda-media-e-mediana/
double moda_aux(double *matriz, int lin) {
    int i, j; 
    double *cont;
    cont = (double*)malloc(lin * sizeof(double));
	float conta = 0, moda = 0;
	
    //#pragma omp parallel for private(i, j) 
	for(i = 0; i < lin; i++) {
        for(j = i + 1; j < lin; j++) {
		    if(matriz[i] == matriz[j]) {
			    cont[i]++;
				if(cont[i] > conta) {
				    conta = cont[i];
					moda = matriz[i];
				}
			}
        }
        
        cont[i] = 0;
    }

    free(cont);
    
    if(conta == 0) {
    	return -1;
	} else {
		return moda;
	}
}

void calcula_moda(double *matriz, double *moda, int lin, int col) {
    int i;
    #pragma omp parallel for private(i)
    for(i = 0; i < col; i++) {
        moda[i] = moda_aux(matriz + (i * lin), lin);
    }
}

void calcula_variancia(double *matriz, double *media,double *variancia, int lin, int col) {
    int i, j;
    double soma;
    for(i = 0; i < col; i++) {
        soma = 0;
        for(j = 0; j < lin; j++) {
            soma += pow((matriz[i * lin + j] - media[i]), 2);
        }
        variancia[i] = soma / (lin - 1); 
    } 
}

void calcula_desvio_padrao(double *variancia, double *dp, int col) {
    int i;
    for(i=0; i < col; i++) {
        dp[i] = sqrt(variancia[i]);
    }  
}

void calcula_coeficiente_variacao(double *media, double *dp, double *cv, int col) {
    int i;
    for(i = 0; i < col; i++) {
        cv[i] = dp[i] / media[i];
    }  
}

int main(int argc,char **argv){
    int lin, col, i, j; // Define as variáveis de índices e dimensões
    double *matriz, *mediana, *media, *media_har, *moda, *variancia, *dp, *cv; // Define a matriz (forma linear), vetores de medidas estatísticas

    fscanf(stdin, "%d ", &lin); // Lê a quantidade de linhas da matriz
    fscanf(stdin, "%d\n", &col); // Lê a quantidade de colunas da matriz
    
    // Alocações
    matriz = (double *)malloc(lin * col * sizeof(double)); // Aloca a matriz
    media = (double *)malloc(col * sizeof(double)); // Aloca o vetor de media
    media_har = (double *)malloc(col * sizeof(double)); // Aloca o vetor de media harmônica
    mediana = (double *)malloc(col * sizeof(double)); // Aloca o vetor de mediana
    moda = (double *)malloc(col * sizeof(double)); // Aloca o vetor de moda
    variancia = (double *)malloc(col * sizeof(double)); // Aloca o vetor de variância
    cv = (double *)malloc(col * sizeof(double)); // Aloca o vetor de coeficiente de variação
    dp = (double *)malloc(col * sizeof(double)); // Aloca o vetor de desvio padrão

    for(i = 0; i < lin; i++) {
        for(j = 0; j < col; j++) {
            fscanf(stdin, "%lf ", &(matriz[j * lin + i])); // Lê os dados transpostos em uma matriz de entrada
        }
    }

    double t0 = omp_get_wtime();
    calcula_media(matriz, media, lin,col);
    calcula_media_harmonica(matriz, media_har, lin, col);
    ordena_colunas(matriz, lin, col);
    calcula_mediana(matriz, mediana, lin, col);
    calcula_moda(matriz, moda, lin, col);
    calcula_variancia(matriz, media, variancia, lin, col);
    calcula_desvio_padrao(variancia, dp, col);
    calcula_coeficiente_variacao(media, dp, cv, col);
    double tf = omp_get_wtime();

    for(i = 0; i < col; i++)
        printf("%.1lf\t", media[i]); // Imprime as médias aritméticas de cada coluna
    printf("\n");

    for(i = 0; i < col; i++)
        printf("%.1lf\t", media_har[i]); // Imprime as médias harmônicas de cada coluna
    printf("\n");

    for(i = 0; i < col; i++)
        printf("%.1lf\t", mediana[i]); // Imprime as medianas de cada coluna
    printf("\n");

    for(i = 0; i < col; i++)
        printf("%.1lf\t", moda[i]); // Imprime as modas de cada coluna
    printf("\n");

    for(i = 0; i < col; i++)
        printf("%.1lf\t", variancia[i]); // Imprime as variâncias amostrais de cada coluna
    printf("\n");

    for(i = 0; i < col; i++)
        printf("%.1lf\t", dp[i]); // Imprime os desvios padrão de cada coluna
    printf("\n");

    for(i = 0; i < col; i++)
        printf("%.1lf\t", cv[i]); // Imprime os coeficientes de variação de cada coluna
    printf("\n");

    printf("Tempo de exec: %lf\n", tf-t0);

    // Desaloca memória
    free(matriz);
    free(media);
    free(media_har);
    free(mediana);
    free(moda);
    free(variancia);
    free(dp);
    free(cv);
}
