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