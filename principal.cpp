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

void menuPlanificador(Lista *&inicioLista, Cola *&colaListos)
{
    int op, id, idProceso;
    bool procesoEjecutado = false;

    do
    {
        procesoEjecutado = false;
        cout << "====== Menú del Planificador ======\n";
        cout << "1. Encolar proceso\n";
        cout << "2. Desencolar proceso\n";
        cout << "3. Mostrar procesos en cola\n";
        cout << "4. Ejecutar procesos\n";
        cout << "5. Volver\n";

        op = validarRango("Seleccione una opción: ", 1, 5);

        switch (op)
        {
        case 1:
            if (inicioLista == NULL)
            {
                cout << "No hay procesos registrados para encolar." << endl;
                break;
            }

            id = validarPositivo("Ingrese el ID del proceso a encolar: ", "El ID debe ser un número positivo.");

            colaListos->encolar(id);
            cout << "Proceso con ID " << id << " encolado exitosamente." << endl;
            break;
        case 2:
            if (colaListos->desencolar(&idProceso))
            {
                cout << "Proceso desencolado con ID " << idProceso << "." << endl;
            }
            else
            {
                cout << "La cola está vacía. No hay procesos para desencolar." << endl;
            }
            break;
        case 3:
            if (colaListos->estaVacia())
            {
                cout << "No hay procesos en la cola." << endl;
                break;
            }

            cout << "Procesos en la cola: ";
            colaListos->mostrarCola();
            break;
        case 4:
            while (colaListos->desencolar(&idProceso))
            {
                procesoEjecutado = true;
                cout << "Ejecutando proceso con ID " << idProceso << ":" << endl;
                buscarProceso(inicioLista, idProceso);
            }

            if (!procesoEjecutado)
            {
                cout << "No hay procesos en cola para ejecutar." << endl;
            }
            break;
        case 5:
            cout << "Volver seleccionado." << endl;
            break;
        }
    } while (op != 5);
}

void registrarProceso(Lista *&inicio)
{
    int id;
    string nombre;
    int prioridad;
    Proceso nuevoProceso;

    id = validarPositivo("Ingrese el ID del proceso: ", "El ID debe ser un número positivo.");
    nombre = validarNombre("Ingrese el nombre del proceso: ");
    prioridad = validarRango("Ingrese la prioridad del proceso (1-10): ", 1, 10);

    nuevoProceso.id = id;
    nuevoProceso.nombre = nombre;
    nuevoProceso.prioridad = prioridad;

    insertarFinal(inicio, nuevoProceso);
    cout << "Proceso registrado exitosamente." << endl;
}

void menuProcesos(Lista *&inicio)
{
    int op;
    int id;
    Proceso nuevoProceso;

    do
    {
        cout << "====== Menú de Procesos ======" << endl;
        cout << "1. Registrar proceso\n";
        cout << "2. Buscar proceso por ID\n";
        cout << "3. Modificar proceso por ID\n";
        cout << "4. Eliminar proceso por ID\n";
        cout << "5. Mostrar procesos\n";
        cout << "6. Volver\n";

        op = validarRango("Seleccione una opción: ", 1, 6);

        switch (op)
        {
        case 1:
            cout << "Registrar proceso seleccionado." << endl;
            registrarProceso(inicio);
            break;
        case 2:
            cout << "Buscar proceso por ID seleccionado." << endl;
            {
                id = validarPositivo("Ingrese el ID del proceso a buscar: ", "El ID debe ser un número positivo.");
                buscarProceso(inicio, id);
            }
            break;
        case 3:
            cout << "Modificar proceso por ID seleccionado." << endl;
            {
                id = validarPositivo("Ingrese el ID del proceso a modificar: ", "El ID debe ser un número positivo.");
                nuevoProceso.id = validarPositivo("Ingrese el nuevo ID del proceso: ", "El ID debe ser un número positivo.");
                nuevoProceso.nombre = validarNombre("Ingrese el nuevo nombre del proceso: ");
                nuevoProceso.prioridad = validarRango("Ingrese la nueva prioridad del proceso (1-10): ", 1, 10);
                modificarProceso(inicio, id, nuevoProceso);
            }
            break;
        case 4:
            cout << "Eliminar proceso por ID seleccionado." << endl;
            {
                id = validarPositivo("Ingrese el ID del proceso a eliminar: ", "El ID debe ser un número positivo.");
                if (eliminarProceso(inicio, id))
                {
                    cout << "Proceso eliminado exitosamente." << endl;
                }
                else
                {
                    cout << "No se encontró un proceso con ese ID." << endl;
                }
            }
            break;
        case 5:
            cout << "Mostrar procesos seleccionado." << endl;
            if (inicio == NULL)
            {
                cout << "No hay procesos registrados." << endl;
            }
            else
            {
                mostrarLista(inicio);
            }
            break;
        case 6:
            cout << "Volver seleccionado." << endl;
            break;
        }
    } while (op != 6);
}

void menu()
{
    int op;

    do
    {
        cout << "====== Menú Principal ======" << endl;
        cout << "1. Gestión de Procesos\n";
        cout << "2. Planificador de Procesos\n";
        cout << "3. Gestión de Memoria\n";
        cout << "4. Salir\n";

        op = validarRango("Seleccione una opción: ", 1, 4);

        switch (op)
        {
        case 1:
            menuProcesos(inicioLista);
            break;
        case 2:
            menuPlanificador(inicioLista, colaListos);
            break;
        case 3:
            menuMemoria(inicioPila);
            break;
        case 4:
            cout << "Saliendo del programa." << endl;
            break;
        }
    } while (op != 4);
}

int main()
{
    setlocale(LC_CTYPE, "Spanish");
    menu();

    vaciarLista(inicioLista);
    vaciarPila(inicioPila);
    colaListos->vaciar();
    delete colaListos;
    return 0;
}
