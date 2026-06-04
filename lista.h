#include <iostream>
#include <string>

using namespace std;

// Estructura que representa un proceso con ID, nombre y prioridad
struct Proceso
{
    int id;
    string nombre;
    int prioridad;
};

// Nodo de la lista enlazada que almacena un proceso
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

// Imprime los datos de un proceso en pantalla
void mostrarProceso(Proceso proceso)
{
    cout << "ID: " << proceso.id << ",\tNombre: " << proceso.nombre;
    cout << ",\tPrioridad: " << proceso.prioridad << endl;
}

// Inserta un proceso al inicio de la lista
void insertarInicio(Lista *&inicio, Proceso proceso)
{
    Lista *nuevoNodo = new Lista(proceso);
    nuevoNodo->siguiente = inicio;
    inicio = nuevoNodo;
}

// Inserta un proceso al final de la lista
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

// Inserta un proceso en orden ascendente por prioridad
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

// Busca y elimina un proceso por su ID
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

// Busca un proceso por ID y lo muestra en pantalla
bool buscarProceso(Lista *&inicio, int id)
{
    Lista *temp = inicio;
    while (temp != NULL)
    {
        if (temp->proceso.id == id)
        {
            mostrarProceso(temp->proceso);
            return true;
        }
        temp = temp->siguiente;
    }
    return false;
}

// Muestra todos los procesos en la lista
void mostrarLista(Lista *&inicio)
{
    Lista *temp = inicio;
    while (temp != NULL)
    {
        mostrarProceso(temp->proceso);
        temp = temp->siguiente;
    }
}

// Modifica un proceso eliminando el antiguo e insertando el nuevo ordenado
void modificarProceso(Lista *&inicio, int id, Proceso nuevoProceso)
{
    if (eliminarProceso(inicio, id))
    {
        insertarEnOrden(inicio, nuevoProceso);
        cout << "Proceso modificado exitosamente." << endl;
    }
    else
    {
        cout << "Proceso no encontrado." << endl;
    }
}

// Libera toda la memoria de la lista enlazada
void vaciarLista(Lista *&inicio)
{
    Lista *temp;
    while (inicio != NULL)
    {
        temp = inicio;
        inicio = inicio->siguiente;
        delete temp;
    }
}
