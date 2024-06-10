#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidades.h"

// Função para inicializar a estrada a partir do arquivo
Estrada* getEstrada(const char *nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    Estrada* estrada = (Estrada*)malloc(sizeof(Estrada));
    if (fscanf(arquivo, "%d", &estrada->T) != 1 || estrada->T < 3 || estrada->T > 1000000) {
        fclose(arquivo);
        free(estrada);
        return NULL;
    }

    if (fscanf(arquivo, "%d", &estrada->N) != 1 || estrada->N < 2 || estrada->N > 10000) {
        fclose(arquivo);
        free(estrada);
        return NULL;
    }

    estrada->C = (Cidade*)malloc(estrada->N * sizeof(Cidade));

    for (int i = 0; i < estrada->N; i++) {
        int posicao;
        char nome[256];
        if (fscanf(arquivo, "%d %s", &posicao, nome) != 2 || posicao <= 0 || posicao >= estrada->T) {
            fclose(arquivo);
            free(estrada->C);
            free(estrada);
            return NULL;
        }
        for (int j = 0; j < i; j++) {
            if (estrada->C[j].Posicao == posicao) {
                fclose(arquivo);
                free(estrada->C);
                free(estrada);
                return NULL;
            }
        }
        estrada->C[i].Posicao = posicao;
        strcpy(estrada->C[i].Nome, nome);
        printf("Posição da cidade %s: %d\n", estrada->C[i].Nome, estrada->C[i].Posicao);
    }

    fclose(arquivo);
    return estrada;
}


// Função para calcular a menor vizinhança
double calcularMenorVizinhanca(const char *nomeArquivo) {
    Estrada* estrada = getEstrada(nomeArquivo);
    if (estrada == NULL) {
        printf("Erro ao abrir o arquivo ou ler os dados.\n");
        return -1.0;
    }

    printf("Comprimento total da estrada: %d\n", estrada->T);
    printf("Número de cidades: %d\n", estrada->N);

    double menorVizinhanca = estrada->T;
    for (int i = 0; i < estrada->N; i++) {
        double vizinhanca;
        if (i == 0) {
            // Primeira cidade
            vizinhanca = (double)(estrada->C[i + 1].Posicao - estrada->C[i].Posicao) / 2.0;
        } else if (i == estrada->N - 1) {
            // Última cidade
            vizinhanca = (double)(estrada->C[i].Posicao - estrada->C[i - 1].Posicao) / 2.0;
        } else {
            // Cidade no meio
            vizinhanca = (double)((estrada->C[i + 1].Posicao - estrada->C[i - 1].Posicao) / 2.0);
        }
        printf("Vizinhança da cidade %s: %.2f\n", estrada->C[i].Nome, vizinhanca);
        if (vizinhanca < menorVizinhanca) {
            menorVizinhanca = vizinhanca;
        }
    }

    free(estrada->C);
    free(estrada);

    return menorVizinhanca;
}





// Função para retornar o nome da cidade com a menor vizinhança
char* cidadeMenorVizinhanca(const char *nomeArquivo) {
    Estrada* estrada = getEstrada(nomeArquivo);
    if (estrada == NULL) {
        return NULL;
    }

    double menorVizinhanca = estrada->T;
    char* nomeCidadeMenor = NULL;
    for (int i = 0; i < estrada->N; i++) {
        double vizinhanca;
        if (i == 0) {
            // Primeira cidade
            vizinhanca = (estrada->C[i + 1].Posicao - estrada->C[i].Posicao) / 2.0;
        } else if (i == estrada->N - 1) {
            // Última cidade
            vizinhanca = (estrada->C[i].Posicao - estrada->C[i - 1].Posicao) / 2.0;
        } else {
            // Cidade no meio
            vizinhanca = (estrada->C[i + 1].Posicao - estrada->C[i - 1].Posicao) / 2.0;
        }
        if (vizinhanca < menorVizinhanca) {
            menorVizinhanca = vizinhanca;
            if (nomeCidadeMenor) {
                free(nomeCidadeMenor);
            }
            nomeCidadeMenor = (char*)malloc((strlen(estrada->C[i].Nome) + 1) * sizeof(char));
            strcpy(nomeCidadeMenor, estrada->C[i].Nome);
        }
    }

    free(estrada->C);
    free(estrada);

    return nomeCidadeMenor;
}

// Função main
int main() {
    char *nomeArquivo = "teste01.txt";

    double menorVizinhanca = calcularMenorVizinhanca(nomeArquivo);
    char *cidadeMenor = cidadeMenorVizinhanca(nomeArquivo);

    if (menorVizinhanca < 0) {
        printf("Erro ao calcular a menor vizinhança.\n");
    } else {
        printf("Menor vizinhança: %.2f\n", menorVizinhanca);
        printf("Cidade com menor vizinhança: %s\n", cidadeMenor);
    }

    // Libera a memória alocada para o nome da cidade
    free(cidadeMenor);

    return 0;
}
