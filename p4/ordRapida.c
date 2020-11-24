/*Autores: Telmo Fernandez Corujo, Anna Taboada Pardiñas y Andrés Pérez Comesaña*/

#include <stdlib.h>
#include <stdio.h>
#include "time.h"

void inicializar_semilla(){
    srand(time(NULL));
}

int  aleatorio(int izq, int der){  //se generan números pseudoaleatorio entre -n y +n
    int i, n;
    return izq + rand() / (RAND_MAX /der-izq)+izq;
}
/*
void ord_ins(int v[], int n, int UMBRAL){
    int i, x, j;

    for (i=1; i<n; i++){
        x = v[i];
        j = i-1;
        while(j>-1 && v[j]>=x){
            v[j+1] = v[j];
            j = j-1;
        }
        v[j+1] = x;
    }
}
*/
/*
void ord_aux(int v[], int izq, int der){
	if(izq+UMBRAL <= der){
		x = aleatorio() 
	}
}
*/
int main(){
    int a;
    inicializar_semilla();
    a=aleatorio(1,5);
    printf("%d\n",a);
}