#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

char minusculo () {
char ch = getche();
if ((ch >= 'A') && (ch <= 'Z')) return (ch + 32);
else return (ch);
}

int main() {
char letra = minusculo();
printf("\n%c", letra);
return 0;
}
