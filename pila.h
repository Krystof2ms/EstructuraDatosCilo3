#include <iostream>
#include <string>

using namespace std;

// Nodo de la pila que almacena el ID de un proceso
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

// Agrega un elemento al tope de la pila
void apilar(Pila *&inicio, int idProceso)
{
    Pila *nueva_pila = new Pila(idProceso);

    nueva_pila->siguiente = inicio;
    inicio = nueva_pila;
}

// Extrae el elemento del tope de la pila
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

// Obtiene el ID del proceso en el tope sin extraerlo
bool tope(Pila *inicio, int *idProceso)
{
    if (inicio == NULL)
    {
        return false;
    }
    *idProceso = inicio->idProceso;
    return true;
}

// Libera toda la memoria de la pila
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

// Muestra todos los IDs de procesos almacenados en la pila
void mostrarPila(Pila *inicio)
{
    Pila *temp = inicio;
    while (temp != NULL)
    {
        cout << "ID del proceso con memoria en la pila: " << temp->idProceso << endl;
        temp = temp->siguiente;
    }
}
