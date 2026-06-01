#include <iostream>
#include <string>

using namespace std;

struct Proceso
{
    int id;
    string nombre;
    int prioridad;
};

struct Lista
{
    Proceso proceso;
    Lista *siguiente;

    Lista(Proceso p)
    {
        proceso = p;
        siguiente = NULL;
    }
};

void mostrarProceso(Proceso proceso)
{
    cout << "ID: " << proceso.id << ",\tNombre: " << proceso.nombre;
    cout << ",\tPrioridad: " << proceso.prioridad << endl;
}

void insertarInicio(Lista *&inicio, Proceso proceso)
{
    Lista *nuevoNodo = new Lista(proceso);
    nuevoNodo->siguiente = inicio;
    inicio = nuevoNodo;
}

void insertarFinal(Lista *&inicio, Proceso proceso)
{
    Lista *nuevoNodo = new Lista(proceso);
    nuevoNodo->siguiente = NULL;

    if (inicio == NULL)
    {
        inicio = nuevoNodo;
        return;
    }

    Lista *temp = inicio;
    while (temp->siguiente != NULL)
    {
        temp = temp->siguiente;
    }
    temp->siguiente = nuevoNodo;
}

bool eliminarProceso(Lista *&inicio, int id)
{
    Lista *temp = inicio;
    Lista *nodoAEliminar;

    if (inicio == NULL)
    {
        return false;
    }

    if (inicio->proceso.id == id)
    {
        inicio = inicio->siguiente;
        delete temp;
        return true;
    }

    while (temp->siguiente != NULL && temp->siguiente->proceso.id != id)
    {
        temp = temp->siguiente;
    }

    if (temp->siguiente != NULL)
    {
        nodoAEliminar = temp->siguiente;
        temp->siguiente = nodoAEliminar->siguiente;
        delete nodoAEliminar;
        return true;
    }

    return false;
}
