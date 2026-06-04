#include <iostream>
#include <string>
#include <locale.h>
#include "pila.h"
#include "lista.h"
#include "cola.h"
#include "validador.h"

using namespace std;

// Cola para almacenar procesos listos para ejecutar
Cola *colaListos = new Cola();
// Lista enlazada de procesos registrados
Lista *inicioLista = NULL;
// Pila para gestionar memoria asignada a procesos
Pila *inicioPila = NULL;

// Valida que el ID ingresado sea único en la lista de procesos
int validarId()
{
    int id;
    bool valido = false;

    do
    {
        id = validarPositivo("Ingrese el ID del proceso: ", "El ID debe ser un número positivo.");
        valido = buscarProceso(inicioLista, id);
        if (valido)
        {
            cout << "El ID ya existe. Por favor, ingrese un ID único." << endl;
        }
    } while (valido);
    return id;
}

// Menú para gestionar la asignación y liberación de memoria mediante una pila
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
            // Asigna memoria apilando el ID del proceso
            idProceso = validarId();
            apilar(inicio, idProceso);
            cout << "Memoria asignada al proceso con ID " << idProceso << "." << endl;
            break;
        case 2:
            // Libera memoria desapilando el proceso más recientemente asignado
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
            // Muestra todos los procesos con memoria asignada
            mostrarPila(inicio);
            break;
        case 4:
            // Libera toda la memoria de una vez
            vaciarPila(inicio);
            cout << "Memoria vaciada." << endl;
            break;
        case 5:
            cout << "Volver seleccionado." << endl;
            break;
        }
    } while (op != 5);
}

// Menú para encolar, desencolar y ejecutar procesos usando la cola
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
            // Verifica que haya procesos registrados antes de encolar
            if (inicioLista == NULL)
            {
                cout << "No hay procesos registrados para encolar." << endl;
                break;
            }

            id = validarPositivo("Ingresa ID a encolar: ", "Id invalido");
            if (buscarProceso(inicioLista, id))
			{
            	// Añade el proceso a la cola FIFO
            	colaListos->encolar(id);
            	cout << "Proceso con ID " << id << " encolado exitosamente." << endl;
            	break;
			} else 
			{
				cout << "No hay proceso con ese Id\n";
			}
            
        case 2:
            // Extrae el primer proceso de la cola
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
            // Muestra todos los procesos en la cola
            if (colaListos->estaVacia())
            {
                cout << "No hay procesos en la cola." << endl;
                break;
            }

            cout << "Procesos en la cola: ";
            colaListos->mostrarCola();
            break;
        case 4:
            // Ejecuta todos los procesos en cola en orden FIFO
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

// Registra un nuevo proceso en la lista enlazada ordenada por prioridad
void registrarProceso(Lista *&inicio)
{
    int id;
    string nombre;
    int prioridad;
    Proceso nuevoProceso;

    id = validarId();
    nombre = validarNombre("Ingrese el nombre del proceso: ");
    prioridad = validarRango("Ingrese la prioridad del proceso (1-10): ", 1, 10);

    nuevoProceso.id = id;
    nuevoProceso.nombre = nombre;
    nuevoProceso.prioridad = prioridad;

    // Inserta el proceso en la lista manteniéndola ordenada por prioridad
    insertarEnOrden(inicio, nuevoProceso);
    cout << "Proceso registrado exitosamente." << endl;
}

// Menú para gestionar procesos (registrar, buscar, modificar, eliminar, mostrar)
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
            // Registra un nuevo proceso con ID, nombre y prioridad
            registrarProceso(inicio);
            break;
        case 2:
            cout << "Buscar proceso por ID seleccionado." << endl;
            // Búsqueda simple de un proceso en la lista
            {
                id = validarPositivo("Ingrese el ID del proceso a buscar: ", "El ID debe ser un número positivo.");
                if (buscarProceso(inicio, id))
                {
                    cout << "Proceso encontrado." << endl;
                }
                else
                {
                    cout << "Proceso no encontrado." << endl;
                }
            }
            break;
        case 3:
            cout << "Modificar proceso por ID seleccionado." << endl;
            // Modifica los datos de un proceso existente
            {
                id = validarPositivo("Ingrese el nuevo ID del proceso: ", "El ID debe ser un número positivo.");

                nuevoProceso.id = validarId();
                nuevoProceso.nombre = validarNombre("Ingrese el nuevo nombre del proceso: ");
                nuevoProceso.prioridad = validarRango("Ingrese la nueva prioridad del proceso (1-10): ", 1, 10);
                modificarProceso(inicio, id, nuevoProceso);
            }
            break;
        case 4:
            cout << "Eliminar proceso por ID seleccionado." << endl;
            // Elimina un proceso de la lista
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
            // Muestra toda la lista de procesos ordenada por prioridad
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

// Menú principal que coordina todas las funcionalidades del gestor de procesos
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
            // Accede al menú de gestión de procesos
            menuProcesos(inicioLista);
            break;
        case 2:
            // Accede al menú del planificador de procesos
            menuPlanificador(inicioLista, colaListos);
            break;
        case 3:
            // Accede al menú de gestión de memoria
            menuMemoria(inicioPila);
            break;
        case 4:
            cout << "Saliendo del programa." << endl;
            break;
        }
    } while (op != 4);
}

// Función principal: inicia el programa y libera la memoria al finalizar
int main()
{
    setlocale(LC_CTYPE, "Spanish"); // Configura idioma español
    menu();

    // Libera la memoria de todas las estructuras
    vaciarLista(inicioLista);
    vaciarPila(inicioPila);
    colaListos->vaciar();
    delete colaListos;
    return 0;
}
