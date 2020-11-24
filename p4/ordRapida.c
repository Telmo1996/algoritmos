/*Autores: Telmo Fernandez Corujo, Anna Taboada Pardiñas y Andrés Pérez Comesaña*/

#include <stdlib.h>
#include <stdio.h>
#include "time.h"

void inicializar_semilla(){
    srand(time(NULL));
}

int  aleatorio(int izq, int der){  //se generan números pseudoaleatorio entre -n y +n
    return izq + rand() / (RAND_MAX /(der-izq + 1) + 1);
}

void intercambiar(int v[], int n1, int n2){
	int aux = v[n1];
	v[n1]=v[n2];
	v[n2]=aux;
}

void ord_ins(int v[], int n){
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

void ord_aux(int v[], int izq, int der, int UMBRAL){
	int i, j, x, pivote;

	if(izq+UMBRAL <= der){
		x = aleatorio(izq, der);
		pivote = v[x];
		intercambiar(v, izq, x);
		i = izq + 1;
		j = der;
		while(i <= j){
			while(i <= der && v[i] < pivote)
				i++;
			while(v[j] > pivote)
				j--;
			if(i <= j){
				intercambiar(v, i, j);
				i++;
				j--;
			}
		}
		intercambiar(v, izq, j);
		ord_aux(v, izq, j-1, UMBRAL);
		ord_aux(v, j+1, der, UMBRAL);
	}
}

void ord_rapida(int v[], int n, int UMBRAL){
	ord_aux(v, 1, n, UMBRAL); //TODO esto fijo que peta
	if(UMBRAL > 1)
		ord_ins(v, n);
}
int main(){
    int a;
    inicializar_semilla();
	for(int i=0; i<30; i++){
		a=aleatorio(5,10);
		printf("%d\n",a);
	}
}
