#include <iostream>
#include <string>
#include <locale.h>
#include "pila.h"
#include "lista.h"
#include "cola.h"
#include "validador.h"

using namespace std;

Cola *colaListos = new Cola();
Lista *inicioLista = NULL;
Pila *inicioPila = NULL;

int main() {
    return 0;
}

void menuMemoria(Pila *&inicio)
{
    int op;
    int idProceso;

    do
    {
        cout << "====== Menú de la Memoria ======" << endl;
        cout << "1. Asignar memoria a proceso\n";
        cout << "2. Liberar memoria de proceso\n";
        cout << "3. Mostrar procesos con memoria asignada\n";
        cout << "4. Vaciar memoria\n";
        cout << "5. Volver\n";

        op = validarRango("Seleccione una opción: ", 1, 5);

        switch (op)
        {
        case 1:
            idProceso = validarPositivo("Ingrese el ID del proceso a asignar memoria: ", "El ID debe ser un número positivo.");
            apilar(inicio, idProceso);
            cout << "Memoria asignada al proceso con ID " << idProceso << "." << endl;
            break;
        case 2:
            if (desapilar(inicio, &idProceso))
            {
                cout << "Memoria liberada del proceso con ID " << idProceso << "." << endl;
            }
            else
            {
                cout << "No hay procesos con memoria para liberar." << endl;
            }
            break;
        case 3:
            mostrarPila(inicio);
            break;
        case 4:
            vaciarPila(inicio);
            cout << "Memoria vaciada." << endl;
            break;
        case 5:
            cout << "Volver seleccionado." << endl;
            break;
        }
    } while (op != 5);
}
