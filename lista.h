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
    Lista *temp = inicio;

    if (inicio == NULL)
    {
        inicio = nuevoNodo;
        return;
    }

    while (temp->siguiente != NULL)
    {
        temp = temp->siguiente;
    }
    temp->siguiente = nuevoNodo;
}

void insertarEnOrden(Lista *&inicio, Proceso proceso)
{
    Lista *nuevoNodo = new Lista(proceso);
    Lista *temp = inicio;

    if (inicio == NULL || inicio->proceso.prioridad > proceso.prioridad)
    {
        nuevoNodo->siguiente = inicio;
        inicio = nuevoNodo;
        return;
    }

    while (temp->siguiente != NULL && temp->siguiente->proceso.prioridad <= proceso.prioridad)
    {
        temp = temp->siguiente;
    }
    nuevoNodo->siguiente = temp->siguiente;
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

void buscarProceso(Lista *&inicio, int id)
{
    Lista *temp = inicio;
    while (temp != NULL)
    {
        if (temp->proceso.id == id)
        {
            mostrarProceso(temp->proceso);
            return;
        }
        temp = temp->siguiente;
    }
    cout << "Proceso no encontrado." << endl;
}

void mostrarLista(Lista *&inicio)
{
    Lista *temp = inicio;
    while (temp != NULL)
    {
        mostrarProceso(temp->proceso);
        temp = temp->siguiente;
    }
}

void modificarProceso(Lista *&inicio, int id, Proceso nuevoProceso)
{
    Lista *temp = inicio;
    while (temp != NULL)
    {
        if (temp->proceso.id == id)
        {
            temp->proceso = nuevoProceso;
            return;
        }
        temp = temp->siguiente;
    }
    cout << "Proceso no encontrado." << endl;
}
