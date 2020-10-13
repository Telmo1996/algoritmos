/* Inclusión de archivos */
#include <stdio.h>
#include <sys/time.h>
#include <math.h>

/* obtiene la hora actual en microsegundos */
double microsegundos() {
struct timeval t;
if (gettimeofday(&t, NULL) < 0 )
return 0.0;
return (t.tv_usec + t.tv_sec * 1000000.0);
}

int fib1 (int n){
	if (n < 2) {
		return n;
	}
	else {
		return (fib1(n - 1) + fib1(n - 2));
	}
}

int fib2(int n){
    int i=1;
    int j=0;
    int k; 
    
    for(k=1; k <= n; k++){
        j=i+j;
        i=j-i;
    }
    return j;
}

int fib3(int n){
	int i=1;
	int j=0;
	int k=0;
	int h=1;
	int t=0;
	
	while (n > 0){
		if (n % 2 != 0) {
			t = j*h;
			j = i*h + j*k + t;
			i = i*k + t;
		}
		t = h*h;
		h = 2*k*h + t;
		k = k*k + t;
		n = n/2;
	}
	return j;
}

//Esta funcion calcula el tiempo que tarda en ejecutarse una funcion
//que se pasa como argumento. Se contempla automaticamente el caso
//de t < 500us.
double tiempos(int (*fun_fib)(int), int n){
    
    int k=100, i;
    double t, ta, tb;

    ta = microsegundos();
    fun_fib(n);
    tb = microsegundos();

    t = tb - ta;

    if (t < 500.0){
        ta = microsegundos();
        for (i=0; i<k; i++){
            fun_fib(n);
        }
        tb = microsegundos();
        t = (tb-ta)/k;
        printf("*");
    }

    return t;
}

//Estas funciones calculan e imprimen por pantalla
//t(n), t(n)/f(n), t(n)/g(n) y t(n)/h(n) para fib 1, 2 y 3.
void cotasFib1(int nums[], size_t size, int (*fun_fib)(int)){
    double phi = (1 + sqrt(5)) / 2;
    int i;
    double t;

    printf("\tn\tt(n)\t\tt(n)/f(n)\tt(n)/g(n)\tt(n)/h(n)\n");
    for(i=0; i<size; i++){
        printf("\t%d\t",nums[i]);
        t = tiempos(fun_fib, nums[i]);
        printf("%f\t%f", t, t/pow(1.1, nums[i]));
        printf("\t%f", t/pow(phi, nums[i]));
        printf("\t%f", t/pow(2, nums[i]));

        printf("\n");
    }
}

void cotasFib2(int nums[], size_t size, int (*fun_fib)(int)){
    int i;
    double t;
    char letrero[][20] = {"10^3", "10^4", "10^5", "10^6", "10^7"};

    printf("\tn\tt(n)\t\tt(n)/f(n)\tt(n)/g(n)\tt(n)/h(n)\n");
    for(i=0; i<size; i++){
        printf("\t%s\t",letrero[i]);
        t = tiempos(fun_fib, nums[i]);
        printf("%f\t%f", t, t/pow(nums[i], 0.8));
        printf("\t%f", t/nums[i]);
        printf("\t%f", t/(nums[i]*log(nums[i])));

        printf("\n");
    }
}

void cotasFib3(int nums[], size_t size, int (*fun_fib)(int)){
    int i;
    double t;
    char letrero[][20] = {"10^3", "10^4", "10^5", "10^6", "10^7"};

    printf("\tn\tt(n)\t\tt(n)/f(n)\tt(n)/g(n)\tt(n)/h(n)\n");
    for(i=0; i<size; i++){
        printf("\t%s\t",letrero[i]);
        t = tiempos(fun_fib, nums[i]);
        printf("%f\t%f", t, t/sqrt(log(nums[i])));
        printf("\t%f", t/log(nums[i]));
        printf("\t%f", t/pow(nums[i], 0.5));

        printf("\n");
    }
}

void test(){
    printf("Test para cada algoritmo:\n");
    printf("Fib(5). Deberia dar 5\n");
    printf("Fib1: %d, Fib2: %d, Fib3: %d\n",fib1(5), fib2(5), fib3(5));
    printf("Fib(10). Deberia dar 55\n");
    printf("Fib1: %d, Fib2: %d, Fib3: %d\n",fib1(10), fib2(10), fib3(10));
    printf("Fib(15). Deberia dar 610\n");
    printf("Fib1: %d, Fib2: %d, Fib3: %d\n",fib1(15), fib2(15), fib3(15));

    printf("\n");
}

/* Función principal */
int main (int argc,char **argv)
{
    int (*fun_fib)(int);
    size_t tamano_n, tamano_n23;
    int arrayn_fib1[] = {2, 4, 8, 16, 32};
    int arrayn_fib23[] = {1000, 10000, 100000, 1000000, 10000000};

    test();
    printf("Tiempos expresados en us\n\n");
    printf("\t\t\t\tSubestimado\tAjustado\tSobrestimado\n");

    //Fib 1
    printf("Fib 1\n");
    fun_fib = &fib1;
    tamano_n = sizeof(arrayn_fib1)/sizeof(arrayn_fib1[0]);
    
    cotasFib1(arrayn_fib1, tamano_n, fun_fib);

    //Fib 2
    printf("\nFib 2\n");
    fun_fib = &fib2;
    tamano_n23 = sizeof(arrayn_fib23)/sizeof(arrayn_fib23[0]);

    cotasFib2(arrayn_fib23, tamano_n23, fun_fib);

    //Fib 3
    printf("\nFib 3\n");
    fun_fib = &fib3;

    cotasFib3(arrayn_fib23, tamano_n23, fun_fib);

    printf("\n(*) Tiempos medidos con la media de 100 ejecuciones.\n");

    return 0;

}
