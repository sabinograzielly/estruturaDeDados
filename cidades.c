#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para armazenar informações sobre a cidade
typedef struct {
    char Nome[100];
    double Posicao;
} Cidade;

// Estrutura para armazenar informações sobre a estrada
typedef struct {
    int T;
    int N;
    Cidade *C;
} Estrada;

// Função para ler as informações da estrada a partir de um arquivo
Estrada *getEstrada(const char *nomeArquivo) {
    FILE *file = fopen(nomeArquivo, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    Estrada *estrada = (Estrada *)malloc(sizeof(Estrada));
    if (estrada == NULL) {
        perror("Erro ao alocar memoria");
        fclose(file);
        return NULL;
    }

    if (fscanf(file, "%d %d", &(estrada->T), &(estrada->N)) != 2) {
        perror("Erro ao ler o comprimento da estrada e/ou o numero de cidades");
        fclose(file);
        free(estrada);
        return NULL;
    }

    // Verificar restrições
    if (estrada->T < 3 || estrada->T > 1000000 || estrada->N < 2 || estrada->N > 10000) {
        perror("Restricoes nao atendidas: 3 ≤ T ≤ 10^6 e 2 ≤ N ≤ 10^4");
        fclose(file);
        free(estrada);
        return NULL;
    }

    estrada->C = (Cidade *)malloc(estrada->N * sizeof(Cidade));
    if (estrada->C == NULL) {
        perror("Erro ao alocar memoria");
        fclose(file);
        free(estrada);
        return NULL;
    }

    for (int i = 0; i < estrada->N; i++) {
        if (fscanf(file, "%lf %s", &(estrada->C[i].Posicao), estrada->C[i].Nome) != 2) {
            perror("Erro ao ler informacoes da cidade");
            fclose(file);
            free(estrada->C);
            free(estrada);
            return NULL;
        }
        // Verificar se as posições das cidades estão dentro das restrições
        if (estrada->C[i].Posicao <= 0 || estrada->C[i].Posicao >= estrada->T) {
            perror("Erro: As posicoes das cidades devem ser 0 < Xi < T");
            fclose(file);
            free(estrada->C);
            free(estrada);
            return NULL;
        }
        // Verificar se as posições das cidades são únicas
        for (int j = 0; j < i; j++) {
            if (estrada->C[i].Posicao == estrada->C[j].Posicao) {
                perror("Erro: As posicoes das cidades devem ser distintas");
                fclose(file);
                free(estrada->C);
                free(estrada);
                return NULL;
            }
        }
    }

    fclose(file);
    return estrada;
}

// Função para calcular a menor vizinhança entre cidades
double calcularMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (estrada == NULL) {
        fprintf(stderr, "Erro ao obter a estrada.\n");
        return -1;
    }

    double menorVizinhanca = estrada->T + 1; // Inicializando com um valor maior que qualquer possível vizinhança
    for (int i = 0; i < estrada->N - 1; i++) {
        double vizinhanca = estrada->C[i].Posicao - estrada->C[i + 1].Posicao;
        if (vizinhanca < 0) {
            vizinhanca = -vizinhanca; // Obter valor absoluto
        }
        if (vizinhanca < menorVizinhanca) {
            menorVizinhanca = vizinhanca;
        }
    }

    free(estrada->C);
    free(estrada);
    return menorVizinhanca;
}

// Função para encontrar a cidade com a menor vizinhança
char *cidadeMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (estrada == NULL) {
        fprintf(stderr, "Erro ao obter a estrada.\n");
        return NULL;
    }

    double menorVizinhanca = estrada->T + 1; // Inicializando com um valor maior que qualquer possível vizinhança
    char *nomeCidadeMenor = NULL;
    for (int i = 0; i < estrada->N - 1; i++) {
        double vizinhanca = estrada->C[i].Posicao - estrada->C[i + 1].Posicao;
        if (vizinhanca < 0) {
            vizinhanca = -vizinhanca; // Obter valor absoluto
        }
        if (vizinhanca < menorVizinhanca) {
            menorVizinhanca = vizinhanca;
            if (nomeCidadeMenor) {
                free(nomeCidadeMenor);
            }
            nomeCidadeMenor = (char *)malloc((strlen(estrada->C[i + 1].Nome) + 1) * sizeof(char));
            strcpy(nomeCidadeMenor, estrada->C[i + 1].Nome);
        }
    }

    free(estrada->C);
    free(estrada);
    return nomeCidadeMenor;
}

int main() {
    // Exemplo de uso das funções
    const char *nomeArquivo = "C:\\Users\\grazi\\Desktop\\estruturaDeDados\\teste01.txt";
    
    Estrada *estrada = getEstrada(nomeArquivo);
    if (estrada != NULL) {
        printf("Comprimento da estrada (T): %d\n", estrada->T);
        printf("Numero de cidades (N): %d\n", estrada->N);

        double menorVizinhanca = calcularMenorVizinhanca(nomeArquivo);
        printf("Menor vizinhanca: %.2f\n", menorVizinhanca);

        char *cidadeMenor = cidadeMenorVizinhanca(nomeArquivo);
        if (cidadeMenor != NULL) {
            printf("Cidade com menor vizinhanca: %s\n", cidadeMenor);
            free(cidadeMenor);
        } else {
            printf("Erro ao obter a cidade com menor vizinhanca.\n");
        }

        free(estrada->C);
        free(estrada);
    } else {
        printf("Erro ao obter a estrada.\n");
    }

    return 0;
}
