
struct nodo{
	int elem;
	int num_repeticiones;
	struct nodo *izq, *der;	
};

typedef struct nodo *posición;
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