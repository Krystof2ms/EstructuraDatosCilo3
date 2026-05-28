#include <iostream>
#include <string>

using namespace std;

struct Pila
{
    int idProceso;

    Pila *siguiente;

    Pila(int idProceso)
    {
        this->idProceso = idProceso;
        siguiente = NULL;
    }
};

void apilar(Pila *&inicio, int idProceso)
{
    Pila *nueva_pila = new Pila(idProceso);

    nueva_pila->siguiente = inicio;
    inicio = nueva_pila;
}

void desapilar(Pila *&inicio, int *idProceso)
{
    Pila *temporal;

    if (inicio == NULL)
    {
        return;
    }

    temporal = inicio;
    *idProceso = temporal->idProceso;
    inicio = inicio->siguiente;

    return;
}

bool estaVacia(Pila *inicio)
{
    return inicio == NULL;
}

int *tope(Pila *inicio)
{
    if (inicio == NULL)
    {
        return NULL;
    }
    return &inicio->idProceso;
}