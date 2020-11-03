#include <stdlib.h>
#include <stdio.h>


struct nodo{
	int elem;
	int num_repeticiones;
	struct nodo *izq, *der;	
};

typedef struct nodo *posicion;
typedef struct nodo *arbol;


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
	while(i != a->elem){
		if(i < a->elem){
			return buscar(i, a->izq);
		}else if(i > a->elem){
			return buscar(i, a->der);
		}else{
			return a;
		}
	}

	return NULL;
}

void imprimir(arbol a){
	char *i, *d;

	if(!esarbolvacio){
		if(a->izq != NULL)
			i=a->izq;
		else
			i="";
		if(a->der != NULL)
			d=a->der;
		else
			d="";

		printf("(");
	}
}

int main(int argc, char **argv){
	arbol a;

	a=creararbol();

	a=insertar(1, a);
	a=insertar(2, a);
	a=insertar(4, a);
	a=insertar(3, a);
	a=insertar(7, a);
	a=insertar(4, a);
	
}
