#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

double microsegundos() {
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
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

void ord_shell(int v[], int n){
    int i, tmp, j, seguir;
    int incremento = n;
    while(1){
        incremento = incremento / 2;
        for (i=incremento; i<n; i++){
            tmp = v[i];
            j = i;
            seguir = 1;
            while (j-incremento > -1 && seguir){
                if (tmp < v[j-incremento]){
                    v[j] = v[j-incremento];
                    j = j-incremento;
                }else{
                    seguir = 0;
                }
            }
            v[j] = tmp;
        }
    
        if(incremento == 1) break;
    }
}

void inicializar_semilla(){
    srand(time(NULL));
}

void aleatorio(int v[], int n){  //se generan números pseudoaleatorio entre -n y +n
    int i, m=2*n+1;
    for(i=0;i<n;i++){
        v[i]=(rand() %m)-n;
    }
}

void ascendente(int v[],int n){
    int i;
    for(i=0;i<n;i++){
        v[i]=i;
    }
}

void descendente(int v[], int n){
    int i;
    for(i=0;i<n;i++){
        v[n-i-1]=i;
    }
}

void print_array(int v[], int n){
    printf("{%d", v[0]);
    for (int i=1; i<n; i++){
        printf(", %d", v[i]);
    }
    printf("}\n");
}

int test(int v[], int n){
    for (int i=1; i<n; i++){
        if(v[i-1] > v[i])
            return 0;
    }
    return 1;
}

double tiempos(void (*fun_ord)(int[],int), int v[], int n){

    int k=100, i;
    double t, ta, tb,t1,t2;

    ta = microsegundos();
    fun_ord(v,n);
    tb = microsegundos();

    t = tb - ta;

    if (t < 500.0){
        ta = microsegundos();
        for (i=0; i<k; i++){
            aleatorio(v,n);
            fun_ord(v,n);
        }
        tb = microsegundos();
        t1 = tb-ta;
        ta=microsegundos();
        for(i=0;i<k;i++){
            aleatorio(v,n);
        }
        tb=microsegundos();
        t2=tb-ta;
        t=(t1-t2)/k;
    }

    return t;
}

void cotas(void (*fun_ord)(int[],int), void (*init)(int[],int)){
    int n;
    double t;

    printf("n\tt(n)\t\tt(n)/n^1.8\tt(n)/n^2\tt(n)/n^2.2\n");
    for(n=500; n<=32000; n*=2){
        int v[n];
        init(v, n);
        t=tiempos(fun_ord, v, n);

        printf("%d\t", n);
        printf("%f\t", t);
        printf("%f\t", t/pow(n,1.8));
        printf("%f\t", t/pow(n,2));
        printf("%f\t", t/pow(n,2.2));
        printf("\n");
    }
}

int main (int argc, char **argv){
    inicializar_semilla();
    
    printf("INSERCION\n\n");
    printf("descendente\n");
    cotas(ord_ins, descendente);
    printf("aleatorio\n");
    cotas(ord_ins, aleatorio);
    printf("ascendente\n");
    cotas(ord_ins, ascendente);

    printf("\nSHELL\n\n");
    printf("descendente\n");
    cotas(ord_shell, descendente);
    printf("aleatorio\n");
    cotas(ord_shell, aleatorio);
    printf("ascendente\n");
    cotas(ord_shell, ascendente);
}
