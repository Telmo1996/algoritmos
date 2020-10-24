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
            aleatorio(v,n);
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
    for(n=500; n<=32000; n*=2){
        int v[n];
        fun_init(v, n);
        t=tiempos(fun_init, fun_ord, v, n);

        printf("%10.4f\t", t);
        for (int i=0; i<3; i++)
            printf("%10.8f\t", t/pow(n, potencias[i]));
        printf("\n");
    }
}

int main (int argc, char **argv){
    double potencias[3]={1.8, 2, 2.2};
    inicializar_semilla();
    
    printf("INSERCION\n\n");
    printf("descendente\n");
    //cotas(ord_ins, descendente, potencias);
    printf("\naleatorio\n");
    //cotas(ord_ins, aleatorio, potencias);
    printf("\nascendente\n");
    //cotas(ord_ins, ascendente, potencias);

    printf("\n\nSHELL\n\n");
    printf("descendente\n");
    potencias[1]=1;
    potencias[0]=potencias[1]-0.1;
    potencias[2]=potencias[1]+0.1;
    cotas(ord_shell, descendente, potencias);

    printf("\naleatorio\n");
    potencias[1]=1.07;
    potencias[0]=potencias[1]-0.1;
    potencias[2]=potencias[1]+0.1;
    cotas(ord_shell, aleatorio, potencias);

    printf("\nascendente\n");
    potencias[1]=1.15;
    potencias[0]=potencias[1]-0.1;
    potencias[2]=potencias[1]+0.1;
    cotas(ord_shell, ascendente, potencias);
}
