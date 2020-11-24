/*Autores: Telmo Fernandez Corujo, Anna Taboada Pardiñas y Andrés Pérez Comesaña*/

#include <stdlib.h>
#include <stdio.h>


void inicializar_semilla(){
    srand(time(NULL));
}

void aleatorio(int n1, int n2){  //se generan números pseudoaleatorio entre -n y +n
    int i, m=2*n+1;
    for(i=0;i<n;i++){
        v[i]=(rand() %m)-n;
    }
}

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

void ord_aux(int v[], int izq, int der){
	if(izq+UMBRAL <= der){
		x = aleatorio() 
	}
}
