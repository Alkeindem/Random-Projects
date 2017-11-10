#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct NodoArbol
{
	struct NodoArbol* padre;
	struct NodoArbol* izquierdo;
	struct NodoArbol* derecho;
	char valor;
};

typedef struct NodoArbol NodoArbol;

struct Arbol
{
	NodoArbol* raiz;
};

typedef struct Arbol Arbol;
NodoArbol* crearNodoArbol(char valor)
{
	NodoArbol* r;
	r = (NodoArbol*)malloc(sizeof(NodoArbol));
	if (r == NULL)
	{
		printf("Error asignando memoria al nodo\n");
		exit(1);
	}
	r->valor = valor;
	r->izquierdo = NULL;
	r->derecho = NULL;
	r->padre = NULL;
	return r;
}

Arbol* crearArbol()
{
	Arbol* t;
	t = (Arbol*)malloc(sizeof(Arbol));
	if (t == NULL)
	{
		printf("Error asignando memoria al nodo\n");
		exit(1);
	}
	t->raiz = NULL;
	return t;
}

void imprimirString(char v1)
{
	printf("%c", v1);
}

void inorden(NodoArbol* t, void(*procesar)(char))
{
	if(t != NULL)
	{
		inorden(t->izquierdo, procesar);
		(*procesar)(t->valor);
		inorden(t->derecho, procesar);
	}
}

void inorden_inverso(NodoArbol* t, void(*procesar)(char))
{
	if (t != NULL)
	{
		inorden_inverso(t->derecho, procesar);
		(*procesar)(t->valor);
		inorden_inverso(t->izquierdo, procesar);
	}
}

void preorden(NodoArbol* t, void(*procesar)(char))
{
	if (t != NULL)
	{
		(*procesar)(t->valor);
		preorden(t->izquierdo, procesar);
		preorden(t->derecho, procesar);
	}
}

void postorden(NodoArbol* t, void(*procesar)(char))
{
	if (t != NULL)
	{
		postorden(t->izquierdo, procesar);
		postorden(t->derecho, procesar);
		(*procesar)(t->valor);
	}
}

void insertar(Arbol* t, char valor)
{
	NodoArbol* p;
	NodoArbol* a;
	NodoArbol* nuevo = crearNodoArbol(valor);
	if (t->raiz == NULL)
	{
		t->raiz = nuevo;
		return;
	}
	else
		a = t->raiz;
	while (a != NULL)
	{
		p = a;
		if (valor < a->valor)
			a = a->izquierdo;
		else
			a = a->derecho;
	}
	if (valor < p->valor)
		p->izquierdo = nuevo;
	else
		p->derecho = nuevo;
	nuevo->padre = p;
}

NodoArbol* rotarDerecha(NodoArbol* t)
{
	NodoArbol* raiz;
	raiz = t->izquierdo;
	raiz->padre = t->padre;
	t->izquierdo = raiz->derecho;
	t->izquierdo->padre = t;
	raiz->derecho = t;
	raiz->derecho->padre = raiz;
	return raiz;
}

NodoArbol* rotarIzquierda(NodoArbol* t)
{
	NodoArbol* raiz;
	raiz = t->derecho;
	raiz->padre = t->padre;
	t->derecho = raiz->izquierdo;
	t->derecho->padre = t;
	raiz->izquierdo = t;
	raiz->izquierdo->padre = raiz;
	return raiz;
}

int altura(NodoArbol* t)
{
	int hizq, hder;
	if (t == NULL)
		return -1;
	if (t->derecho == NULL && t->izquierdo == NULL)
		return 0;
	hizq = altura(t->izquierdo);
	hder = altura(t->derecho);
	if (hizq > hder)
		return hizq + 1;
	else
		return hder + 1;
}

int isLeftHeavy(NodoArbol *raiz)
{
    int a;
    int b;
    
    if ((raiz-> izquierdo) == NULL)
        a = 0;
    else
        a = altura(raiz->izquierdo) + 1;
        
    if ((raiz-> derecho) == NULL)
        b = 0;
    else
        b = altura(raiz->derecho) + 1;

    if ((b-a) <= -2)
    {
        return 1;
    }
    
    return 0;
}

int isRightHeavy(NodoArbol *raiz)
{
    int a;
    int b;
    
    if ((raiz-> izquierdo) == NULL)
        a = 0;
    else
        a = altura(raiz->izquierdo) + 1;
        
    if ((raiz-> derecho) == NULL)
        b = 0;
    else
        b = altura(raiz->derecho) + 1;
    
    if ((b-a) >= 2)
    {
        return 1;
    }
    
    return 0;
}

NodoArbol* balance(NodoArbol* t)
{
    if (isLeftHeavy(t))
    {
        if(isRightHeavy(t->izquierdo))
        {
            t->izquierdo = rotarIzquierda(t->izquierdo);
            t = rotarDerecha(t);
        }
        
        else
            t = rotarIzquierda(t);
    }
    
    if (isRightHeavy(t))
    {
        if (isLeftHeavy(t->derecho))
        {
            t->derecho = rotarDerecha(t->derecho);
            t = rotarIzquierda(t);
        }
        
        else
            t = rotarDerecha(t);
    }
    return t;
}

NodoArbol* callBackBalance(NodoArbol* t)
{
	if(t != NULL)
	{
		t = callBackBalance(t->izquierdo);
		t = balance(t);
		t = callBackBalance(t->derecho);
	}
	return (t)
}

int main(int argc, char** argv)
{
	Arbol* t = crearArbol();
	char* patron = "ABCDEFG";
	unsigned int i;
	for (i = 0; i < strlen(patron); i++)
		insertar(t, patron[i]);
	t = callBackBalance(t);
	printf("La altura del arbol es %d\n", altura(t->raiz));
}
