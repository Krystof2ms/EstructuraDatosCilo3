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

bool desapilar(Pila *&inicio, int *idProceso)
{
    Pila *temporal;

    if (inicio == NULL)
    {
        return false;
    }

    temporal = inicio;
    *idProceso = temporal->idProceso;
    inicio = inicio->siguiente;

    return true;
}

bool tope(Pila *inicio, int *idProceso)
{
    if (inicio == NULL)
    {
        return false;
    }
    *idProceso = inicio->idProceso;
    return true;
}

void vaciarPila(Pila *&inicio)
{
    Pila *temp;
    while (inicio != NULL)
    {
        temp = inicio;
        inicio = inicio->siguiente;
        delete temp;
    }
}
