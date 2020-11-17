/*Autores: Telmo Fernandez Corujo, Anna Taboada Pardiñas y Andrés Pérez Comesaña*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>


struct nodo{
	int elem;
	int num_repeticiones;
	struct nodo *izq, *der;	
};

typedef struct nodo *posicion;
typedef struct nodo *arbol;


double microsegundos() {
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

int max(int a, int b){
	if(a>b) return a;
	else return b;
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

static struct nodo *crearnodo(int e){
	struct nodo *p = malloc(sizeof(struct nodo));
	if(p == NULL){
		printf("memoria agotada\n");
		exit(EXIT_FAILURE);
	}
	p->elem=e;
	p->num_repeticiones = 1;
	p->izq = NULL;
	p->der = NULL;
	return p;
}

arbol insertar(int e, arbol a){
	if (a == NULL)
		return crearnodo(e);
	else if (e < a->elem)
		a->izq = insertar (e, a->izq);
	else if (e> a->elem)
		a->der = insertar (e, a->der);
	else
		a->num_repeticiones++;
	return a;
}

arbol creararbol(){
	return NULL;
}

int esarbolvacio(arbol a){
	return a == NULL;
}

posicion buscar(int i, arbol a){
	if(a != NULL){
		if(i < a->elem){
			return buscar(i, a->izq);
		}else if(i > a->elem){
			return buscar(i, a->der);
		}else{
			return a;
		}
	}else{
		return NULL;
	}
}

arbol eliminararbol(arbol a){
	if(a != NULL){
		if(a->izq != NULL){
			eliminararbol(a->izq);
			a->izq = NULL;
		}
		if(a->der != NULL){
			eliminararbol(a->der);
			a->der = NULL;
		}
		free(a);
	}
	return NULL;
}

posicion hijoderecho(arbol a){
	return a->der;
}

posicion hijoizquierdo(arbol a){
	return a->izq;
}

int elemento(posicion a){
	return a->elem;
}

int numerorepeticiones(posicion a){
	return a->num_repeticiones;
}

int alturaRec(arbol a, int buffAltura){
	if(a->izq == NULL && a->der ==NULL){
		return ++buffAltura;
	}
	if(a->izq != NULL && a->der != NULL){
		buffAltura++;
		return max(
			alturaRec(a->izq, buffAltura),
			alturaRec(a->der, buffAltura));
	}
	if(a->izq != NULL && a->der == NULL){
		buffAltura++;
		return alturaRec(a->izq, buffAltura);
	}
	if(a->izq == NULL && a->der != NULL){
		buffAltura++;
		return alturaRec(a->der, buffAltura);
	}
	return buffAltura; //Nunca se va a dar este caso
}

int altura(arbol a){
	if(esarbolvacio(a))
		return -1;
	return alturaRec(a, -1);
}

char* visualizar(arbol a){
	char i[256], e[256], d[256];
	static char buff[256] = "";
	
	strcpy(buff, "");
	if(!esarbolvacio(a)){
		sprintf(e, "%d", a->elem);
		if(a->izq != NULL)
			sprintf(i, "(%s)", visualizar(a->izq));
		else
			sprintf(i, " ");
		if(a->der != NULL)
			sprintf(d, "(%s)", visualizar(a->der));
		else
			sprintf(d, " ");
		
		sprintf(buff, "%s %s %s", i, e,d);
	}
	return buff;
}


void test(){
	arbol a;

	a=creararbol();
	if(esarbolvacio(a)) printf("Está vacio\n"); else printf("No está vacio\n");

	a=insertar(3, a);
	a=insertar(1, a);
	a=insertar(2, a);
	a=insertar(4, a);
	a=insertar(3, a);
	a=insertar(7, a);
	a=insertar(4, a);
	printf("Inserto: 3, 1, 2, 4, 3, 7, 4\n");
	if(esarbolvacio(a)) printf("Está vacio\n"); else printf("No está vacio\n");
	printf("%s\n", visualizar(a));

	printf("Busco el 4.\n");
	printf("%s\n", visualizar(buscar(4, a)));
	printf("Visualizo el hijo derecho.\n");
	printf("%s\n", visualizar(hijoderecho(a)));
	printf("Visualizo el hijo izquierdo.\n");
	printf("%s\n", visualizar(hijoizquierdo(a)));
	printf("Elemento: %d\n", elemento(a));
	printf("Numero de repeticiones: %d\n", numerorepeticiones(a));
	printf("Altura: %d\n", altura(a));
	printf("Elimino el arbol\n");
	a=eliminararbol(a);
	if(esarbolvacio(a)) printf("Está vacio\n"); else printf("No está vacio\n");

}

double tiemposInsercion(arbol a, int n)
{

    int k=100, i, j;
    double t, ta, tb,t1,t2;
	int v[n];

	aleatorio(v, n);

    printf("%d\t", n);

    ta = microsegundos();
	for(i=0; i<n; i++){
		a=insertar(v[i], a);
	}
    tb = microsegundos();
	a=eliminararbol(a);

    t = tb - ta;

    if (t < 500.0){
        printf("*");

        ta = microsegundos();
        for (i=0; i<k; i++){
			aleatorio(v, n);
			for(j=0; j<n; j++){
				a=insertar(v[j], a);
			}
			a=eliminararbol(a);
        }
        tb = microsegundos();
        t1 = tb-ta;
        ta=microsegundos();
        for(i=0;i<k;i++){
			aleatorio(v, n);
        }
        tb=microsegundos();
        t2=tb-ta;
        t=(t1-t2)/k;
    }else{
        printf(" ");
    }

    return t;
}

double tiemposBusqueda(arbol a, int n){

    int k=100, i, j;
    double t, ta, tb;
	int v[n];

	aleatorio(v, n);
	for(i=0; i<n; i++){
		a=insertar(v[i], a);
	}
	aleatorio(v, n);

    printf("%d\t", n);

    ta = microsegundos();
	for(i=0; i<n; i++){
		buscar(v[i], a);
	}
    tb = microsegundos();

    t = tb - ta;

    if (t < 500.0){
        ta = microsegundos();
        for (i=0; i<k; i++){
			for(j=0; j<n; j++){
				buscar(v[k], a);	
			}
        }
        tb = microsegundos();
        t = (tb-ta)/k;
        printf("*");
    }

    return t;
}

void cotas(
    double (*fun_tiempos)(arbol, int),
    double potencias[3])
{
    int n;
    double t;
	arbol a=creararbol();

    printf("n\tt(n)\t\tt(n)/n^%4.2f\tt(n)/n^%4.2f\tt(n)/n^%4.2f\n",
        potencias[0], potencias[1], potencias[2]);
    for(n=8000; n<=1024000; n*=2){
        t=fun_tiempos(a, n);

        printf("%10.4f\t", t);
        for (int i=0; i<3; i++)
            printf("%10.8f\t", t/pow(n, potencias[i]));
        printf("\n");
    }
}

int main(int argc, char **argv){
	double potencias[3];
	test();

	inicializar_semilla();
	
	printf("Insercion:\n");
    potencias[1]=1;
    potencias[0]=potencias[1]-0.1;
    potencias[2]=potencias[1]+0.1;
    cotas(tiemposInsercion, potencias);

	printf("\n\n");
	printf("Busqueda:\n");
    potencias[1]=1;
    potencias[0]=potencias[1]-0.1;
    potencias[2]=potencias[1]+0.1;
    cotas(tiemposBusqueda, potencias);
	
}
