#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define ERRO -12345

int g(intX);

void main (){
    system("cls");
    int X = g(3);
    printf ("Resposta:%d\n", X);
}
 int f(int X){
    if(X == 0) return (-1);
    else if (X > 0) return (4 * g (X-1) + 6 );
    else return (ERRO);
    
}