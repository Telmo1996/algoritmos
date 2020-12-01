/*Autores: Telmo Fernandez Corujo, Anna Taboada Pardiñas y Andrés Pérez Comesaña*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

double microsegundos() {
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

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
	ord_aux(v, 0, n-1, UMBRAL);
	if(UMBRAL > 1)
		ord_ins(v, n);
}

void vec_aleatorio(int v[], int n){  //se generan números pseudoaleatorio entre -n y +n
    int i, m=2*n+1;
    for(i=0;i<n;i++){
        v[i]=(rand() %m)-n;
    }
}

void vec_ascendente(int v[],int n){
    int i;
    for(i=0;i<n;i++){
        v[i]=i;
    }
}

void vec_descendente(int v[], int n){
    int i;
    for(i=0;i<n;i++){
        v[n-i-1]=i;
    }
}

int esta_ordenado(int v[], int n){
    for (int i=1; i<n; i++){
        if(v[i-1] > v[i]){
            printf("NO está ordenado.");
            return 0;
        }
    }
    printf("SI está ordenado.");
    return 1;
}

void print_array(int v[], int n){
    printf("{%d", v[0]);
    for (int i=1; i<n; i++){
        printf(", %d", v[i]);
    }
    printf("} ");
    esta_ordenado(v, n);
    printf("\n");
}

double tiempos(
    void (*fun_init)(int[],int),
    void (*fun_ord)(int[],int,int),
    int v[], int n, int UMBRAL)
{

    int k=100, i;
    double t, ta, tb,t1,t2;

    printf("%d\t", n);

    ta = microsegundos();
    fun_ord(v,n,UMBRAL);
    tb = microsegundos();

    t = tb - ta;

    if (t < 500.0){
        printf("*");

        ta = microsegundos();
        for (i=0; i<k; i++){
            fun_init(v,n);
            fun_ord(v,n,UMBRAL);
        }
        tb = microsegundos();
        t1 = tb-ta;
        ta=microsegundos();
        for(i=0;i<k;i++){
            fun_init(v,n);
        }
        tb=microsegundos();
        t2=tb-ta;
        t=(t1-t2)/k;
    }else{
        printf(" ");
    }

    return t;
}

void cotas(
    void (*fun_ord)(int[],int,int),
    void (*fun_init)(int[],int),
    double potencias[3],
	int UMBRAL)
{
    int n;
    double t;

    printf("n\tt(n)\t\tt(n)/n^%4.2f\tt(n)/n^%4.2f\tt(n)/n^%4.2f\n",
        potencias[0], potencias[1], potencias[2]);
    for(n=512; n<=pow(2, 16); n*=2){
        int v[n];
        fun_init(v, n);
        t=tiempos(fun_init, fun_ord, v, n, UMBRAL);

        printf("%10.4f\t", t);
        for (int i=0; i<3; i++)
            printf("%10.8f\t", t/pow(n, potencias[i]));
        printf("\n");
    }
}

void test(){
	int n=15;
	int v[n];

	printf("test quicksort con umbral = 1 y vector aleatorio\n");
	vec_aleatorio(v, n);
	print_array(v, n);
	ord_rapida(v, n, 1);
	print_array(v, n);

	printf("\ntest quicksort con umbral = 5 y vector aleatorio\n");
	vec_aleatorio(v, n);
	print_array(v, n);
	ord_rapida(v, n, 5);
	print_array(v, n);

	printf("\ntest quicksort con umbral = 1 y vector ascendente\n");
	vec_ascendente(v, n);
	print_array(v, n);
	ord_rapida(v, n, 1);
	print_array(v, n);

	printf("\ntest quicksort con umbral = 5 y vector ascendente\n");
	vec_ascendente(v, n);
	print_array(v, n);
	ord_rapida(v, n, 5);
	print_array(v, n);

	printf("\ntest quicksort con umbral = 1 y vector descendente\n");
	vec_descendente(v, n);
	print_array(v, n);
	ord_rapida(v, n, 1);
	print_array(v, n);

	printf("\ntest quicksort con umbral = 5 y vector descendente\n");
	vec_descendente(v, n);
	print_array(v, n);
	ord_rapida(v, n, 5);
	print_array(v, n);
}

int main(){
	double potencias[3];
	int UMBRAL;

    inicializar_semilla();
	test();

	printf("\n\nTiempos calculados en us.\n");


	printf("\nUMBRAL = 1\n");
	printf("\t\t\tsubestimada\tajustada\tsobreestimada\n");
	UMBRAL=1;

	printf("vector aleatorio\n");
	potencias[1]=1.08;
	potencias[0]=1;
	potencias[2]=potencias[1]+0.1;
	cotas(ord_rapida, vec_aleatorio, potencias, UMBRAL);

	printf("\nvector ascendente\n");
	potencias[1]=1.08;
	potencias[0]=1;
	potencias[2]=potencias[1]+0.1;
	cotas(ord_rapida, vec_ascendente, potencias, UMBRAL);

	printf("\nvector descendente\n");
	potencias[1]=1.08;
	potencias[0]=1;
	potencias[2]=potencias[1]+0.1;
	cotas(ord_rapida, vec_descendente, potencias, UMBRAL);


	printf("\nUMBRAL = 10\n");
	printf("\t\t\tsubestimada\tajustada\tsobreestimada\n");
	UMBRAL=10;

	printf("vector aleatorio\n");
	potencias[1]=1.1;
	potencias[0]=potencias[1]-0.1;
	potencias[2]=potencias[1]+0.1;
	cotas(ord_rapida, vec_aleatorio, potencias, UMBRAL);

	printf("\nvector ascendente\n");
	potencias[1]=1.1;
	potencias[0]=potencias[1]-0.1;
	potencias[2]=potencias[1]+0.1;
	cotas(ord_rapida, vec_ascendente, potencias, UMBRAL);

	printf("\nvector descendente\n");
	potencias[1]=1.1;
	potencias[0]=potencias[1]-0.1;
	potencias[2]=potencias[1]+0.1;
	cotas(ord_rapida, vec_descendente, potencias, UMBRAL);

	
	printf("\nUMBRAL = 100\n");
	printf("\t\t\tsubestimada\tajustada\tsobreestimada\n");
	UMBRAL=100;

	printf("vector aleatorio\n");
	potencias[1]=1.11;
	potencias[0]=1;
	potencias[2]=potencias[1]+0.1;
	cotas(ord_rapida, vec_aleatorio, potencias, UMBRAL);

	printf("\nvector ascendente\n");
	potencias[1]=1.11;
	potencias[0]=1;
	potencias[2]=potencias[1]+0.1;
	cotas(ord_rapida, vec_ascendente, potencias, UMBRAL);

	printf("\nvector descendente\n");
	potencias[1]=1.11;
	potencias[0]=1;
	potencias[2]=potencias[1]+0.1;
	cotas(ord_rapida, vec_descendente, potencias, UMBRAL);

}
