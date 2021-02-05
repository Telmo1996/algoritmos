/*Telmo Fenánedz Corujo 77481943A*/

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

int  aleatorio(int izq, int der){
	//se generan números pseudoaleatorio entre -n y +n
	return izq + rand() / (RAND_MAX /(der-izq + 1) + 1);
}

void ordenar(int v[], int n){
	int incrementos[11];
	int i, j, x;
	int salto, temp;

	incrementos[0]=88573;
	incrementos[1]=29524;
	incrementos[2]=9841;
	incrementos[3]=3280;
	incrementos[4]=1093;
	incrementos[5]=364;
	incrementos[6]=121;
	incrementos[7]=40;
	incrementos[8]=13;
	incrementos[9]=4;
	incrementos[10]=1;

	for(x=0; x<11; x++){
		salto = incrementos[x];
		for(i=salto; i<n; i++){
			temp = v[i];
			j=i;
			while(j>= salto && (v[j-salto] > temp)){
				v[j] = v[j-salto];
				j = j-salto;
			}
			v[j] = temp;
		}
	}
}

void vec_aleatorio(int v[], int n){
	//se generan números pseudoaleatorio entre -n y +n
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
			printf("\nNO está ordenado.");
			return 0;
		}
	}
	printf("\nSI está ordenado.");
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
	void (*fun_ord)(int[],int),
	int v[], int n)
{

	int k=100, i;
	double t, ta, tb,t1,t2;

	printf("%d\t", n);

	ta = microsegundos();
	fun_ord(v,n);
	tb = microsegundos();

	t = tb - ta;

	if (t < 500.0){
		printf("*");

		ta = microsegundos();
		for (i=0; i<k; i++){
			fun_init(v,n);
			fun_ord(v,n);
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
	void (*fun_ord)(int[],int),
	void (*fun_init)(int[],int),
	double potencias[3])
{
	int n;
	double t;

	printf("n\tt(n)\t\tt(n)/n^%4.2f\tt(n)/n^%4.2f\tt(n)/n^%4.2f\n",
		potencias[0], potencias[1], potencias[2]);
	for(n=512; n<=pow(2, 16); n*=2){
		int v[n];
		fun_init(v, n);
		t=tiempos(fun_init, fun_ord, v, n);

		printf("%10.4f\t", t);
		for (int i=0; i<3; i++)
			printf("%10.8f\t", t/pow(n, potencias[i]));
		printf("\n");
	}
}

void test(){
	int n = 20;
	int v[n];
	
	printf("Test n=%d vector aleatorio\n", n);
	vec_aleatorio(v, n);
	print_array(v, n);
	ordenar(v, n);
	print_array(v, n);

	printf("\nTest n=%d vector ascendente\n", n);
	vec_ascendente(v, n);
	print_array(v, n);
	ordenar(v, n);
	print_array(v, n);

	printf("\nTest n=%d vector descendente\n", n);
	vec_descendente(v, n);
	print_array(v, n);
	ordenar(v, n);
	print_array(v, n);

}

int main(){
	double potencias[3];

	inicializar_semilla();
	test();

	printf("\n\nTiempos calculados en us.\n");

	printf("\t\t\tsubestimada\tajustada\tsobreestimada\n");

	printf("vector aleatorio\n");
	potencias[1]=1.11;
	potencias[0]=1;
	potencias[2]=potencias[1]+0.1;
	cotas(ordenar, vec_aleatorio, potencias);

	printf("\nvector ascendente\n");
	potencias[1]=1.11;
	potencias[0]=1;
	potencias[2]=potencias[1]+0.1;
	cotas(ordenar, vec_ascendente, potencias);

	printf("\nvector descendente\n");
	potencias[1]=1.11;
	potencias[0]=1;
	potencias[2]=potencias[1]+0.1;
	cotas(ordenar, vec_descendente, potencias);
}
