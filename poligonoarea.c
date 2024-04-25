#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    float X;
    float Y;
} Ponto;

// area triangulo
float AreaTriangulo(Ponto A, Ponto B, Ponto C) {
    return 0.5 * ((B.X - A.X) * (C.Y - A.Y) - (C.X - A.X) * (B.Y - A.Y));
}

// calculo da area
float AreaPoligono(Ponto vertices[], int n) {
    float area = 0.0;
    Ponto pontoBase = vertices[0];

    for (int i = 1; i < n - 1; i++) {
        area += AreaTriangulo(pontoBase, vertices[i], vertices[i + 1]);
    }

    return fabs(area); //valor absoluto
}

void LerVertices(FILE *file, Ponto vertices[], int n_vertices) {
    for (int i = 0; i < n_vertices; i++) {
        fscanf(file, "%f %f", &vertices[i].X, &vertices[i].Y);
    }
}


void EscreverVertices(FILE *file, Ponto vertices[], int n_vertices) {
    
    fprintf(file, "%d\n", n_vertices);


    for (int i = 0; i < n_vertices; i++) {
        fprintf(file, "%.2f %.2f\n", vertices[i].X, vertices[i].Y);
    }
}

int main() {
    FILE *file;
    int n_vertices = 3; 
    char filename[] = "vertices.txt"; 

    Ponto vertices[] = {{1.0, 2.0}, {3.0, 8.0}, {5.0, 1.0}};

    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erro ao criar o arquivo.\n");
        exit(1);
    }
    EscreverVertices(file, vertices, n_vertices);

    fclose(file);

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    fscanf(file, "%d", &n_vertices);
    Ponto *verticesFromFile = (Ponto *)malloc(n_vertices * sizeof(Ponto));
    LerVertices(file, verticesFromFile, n_vertices);
    fclose(file);

    //calculo de area
    float area = AreaPoligono(verticesFromFile, n_vertices);

    // resultado
    printf("A area do poligono e %.f\n", area);
    free(verticesFromFile);

    return 0;
}
