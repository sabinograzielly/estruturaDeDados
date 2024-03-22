#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define ERRO_FATORIALNEGATIVO -1234

int Fatorial(int N);

void main(){
    system("cls");
    int N;
    int F;
    printf("Digite um valor:");
    scanf("%d", &N);
    F = Fatorial(N);
    if (F!= ERRO_FATORIALNEGATIVO) 
        printf("Resultado:%d\n", Fatorial(N));
    else 
        printf("Nao existe esse fatorial.");
}

int Fatorial(int N){
    int R = 1;{
    if (N >=0){
    for (int i = N; i>0; i--) R = R *i;
    return(R);
    } else {
        return(ERRO_FATORIALNEGATIVO);
    }
}



}