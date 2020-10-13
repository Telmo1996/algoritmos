#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>

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

double tiempos(int (*fun_ord)(int[],int), int n){

    int k=100, i;
    double t, ta, tb,t1,t2;
    int v[n];
    aleatorio(v,n);

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
int main (int argc, char **argv){
    inicializar_semilla();
    int n=10;
    int v[n];
    void(*fun_ord)(int,int);

    aleatorio(v, n);
    printf("aleatorio");
    print_array(v, n);
    printf("%d\n", test(v, n));

    ord_ins(v, n);
    printf("insercion");
    print_array(v, n);
    printf("%d\n", test(v, n));

    aleatorio(v, n);
    printf("aleatorio");
    print_array(v, n);
    printf("%d\n", test(v, n));

    ord_shell(v, n);
    printf("shell");
    print_array(v, n);
    printf("%d\n", test(v, n));

    fun_ord=ord_ins;
    tiempos(ord_ins,n);
}
