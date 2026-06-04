#include <iostream>
#include <string>

using namespace std;

// Nodo de la cola que almacena el ID de un proceso
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

// Estructura de cola FIFO que mantiene referencias al inicio y final
struct Cola
{
    NodoCola *inicio;
    NodoCola *final;

    Cola()
    {
        inicio = NULL;
        final = NULL;
    }

    // Agrega un elemento al final de la cola
    void encolar(int idProceso)
    {
        NodoCola *nuevo_nodo = new NodoCola(idProceso);

        if (this->final == NULL)
        {
            this->inicio = nuevo_nodo;
            this->final = nuevo_nodo;
        }
        else
        {
            this->final->siguiente = nuevo_nodo;
            this->final = nuevo_nodo;
        }
    }

    // Extrae el elemento del inicio de la cola
    bool desencolar(int *idProceso)
    {
        if (this->inicio == NULL)
        {
            return false;
        }

        NodoCola *temporal = this->inicio;
        *idProceso = temporal->idProceso;
        this->inicio = this->inicio->siguiente;

        if (this->inicio == NULL)
        {
            this->final = NULL;
        }

        delete temporal;
        return true;
    }

    // Verifica si la cola está vacía
    bool estaVacia()
    {
        return this->inicio == NULL;
    }

    // Busca y elimina un nodo específico por ID de proceso
    bool eliminarNodo(int idProceso)
    {
        if (this->inicio == NULL)
        {
            return false;
        }

        NodoCola *temp = this->inicio;
        NodoCola *prev = NULL;

        while (temp != NULL && temp->idProceso != idProceso)
        {
            prev = temp;
            temp = temp->siguiente;
        }

        if (temp == NULL)
        {
            return false; // No se encontr� el nodo
        }

        if (prev == NULL)
        {
            this->inicio = temp->siguiente; // El nodo a eliminar es el primero
        }
        else
        {
            prev->siguiente = temp->siguiente; // El nodo a eliminar est� en medio o al final
        }

        if (temp == this->final)
        {
            this->final = prev; // Actualizar el final si se elimin� el �ltimo nodo
        }

        delete temp; // Liberar memoria del nodo eliminado
        return true;
    }

    // Libera toda la memoria de la cola
    void vaciar()
    {
        NodoCola *temp;
        while (this->inicio != NULL)
        {
            temp = this->inicio;
            this->inicio = this->inicio->siguiente;
            delete temp;
        }
        this->final = NULL;
        this->inicio = NULL;
    }

    // Muestra todos los IDs de procesos en la cola
    void mostrarCola()
    {
        NodoCola *temp = this->inicio;
        while (temp != NULL)
        {
            cout << temp->idProceso << ", ";
            temp = temp->siguiente;
        }
        cout << endl;
    }
}; // Fin de la estructura Cola
