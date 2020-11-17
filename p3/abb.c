#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct nodo{
	int elem;
	int num_repeticiones;
	struct nodo *izq, *der;	
};

typedef struct nodo *posicion;
typedef struct nodo *arbol;


int max(int a, int b){
	if(a>b) return a;
	else return b;
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
	if(i < a->elem){
		return buscar(i, a->izq);
	}else if(i > a->elem){
		return buscar(i, a->der);
	}else{
		return a;
	}
}

arbol eliminararbol(arbol a){
	if(a->izq != NULL){
		eliminararbol(a->izq);
		a->izq = NULL;
	}
	if(a->der != NULL){
		eliminararbol(a->der);
		a->der = NULL;
	}
	free(a);
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

int main(int argc, char **argv){
	test();

	
}
