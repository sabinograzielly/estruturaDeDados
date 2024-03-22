#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define ERRO -1234

int f(intN);

void main (){
    system("cls");
    int X = f(4);
    printf ("Resposta:%d\n", X);
}
 int f(int N){
    if(N == 0) return (3);
    else if (N > 0) return (2 * f (N-1) + 5 );
}