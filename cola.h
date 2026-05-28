#include <iostream>
#include <string>

using namespace std;

struct NodoCola
{
    int idProceso;

    NodoCola *siguiente;

    NodoCola(int valor)
    {
        idProceso = valor;
        siguiente = NULL;
    }
};

struct Cola
{
    NodoCola *inicio;
    NodoCola *final;
};

void encolar(Cola*& head, int idProceso) {
    NodoCola* nuevo_nodo = new NodoCola(idProceso);

    if (head->final == NULL) {
        head->inicio = nuevo_nodo;
        head->final = nuevo_nodo;
    } else {
        head->final->siguiente = nuevo_nodo;
        head->final = nuevo_nodo;
    }
}

void desencolar(Cola*& head, int* idProceso) {
    if (head->inicio == NULL) {
        return;
    }

    NodoCola* temporal = head->inicio;
    *idProceso = temporal->idProceso;
    head->inicio = head->inicio->siguiente;

    if (head->inicio == NULL) {
        head->final = NULL;
    }

    delete temporal;
}