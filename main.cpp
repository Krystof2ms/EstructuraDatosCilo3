#include <iostream>
#include <string>
#include "Pila.h"
#include "validacion.h"

using namespace std;

Pila *inicio = NULL;

void agregarLibro()
{
    string titulo, autor;
    int stock, isbn;
    float precio;
    Libro libro;

    cout << "Ingrese el titulo del libro: ";
    getline(cin, titulo);
    cout << "Ingrese el autor del libro: ";
    getline(cin, autor);
    isbn = validarIsnb();
    precio = validarPrecio();
    stock = validarStock();

    libro = crearLibro(isbn, titulo, autor, precio, stock);
    apilar(inicio, libro);
}

void menuOrdenarPrecio()
{
    ordenarPrecio(inicio);
}

void menuBusquedaIsbn()
{
    int isnb = validarIsnb();
    busquedaIsbn(inicio, isnb);
}

void menuActualizarDescuento()
{
    int isnb;
    float descuento;

    isnb = validarIsnb();
    descuento = validarDescuento();

    actualizarDescueto(inicio, isnb, descuento);
}

void menuEliminarStockCero()
{
    eliminarStockCero(inicio);
}

void menuDescontarStock()
{
    int cantidad, isnb;

    isnb = validarIsnb();
    cantidad = validarStock();

    descontarStock(inicio, isnb, cantidad);
}

void menuMostrarLibros()
{
    mostrarLibros(inicio);
}

void menu()
{
    int opcion;
    do
    {
        cout << "===== Menu de opciones =====\n";
        cout << "1. Agregar libro\n";
        cout << "2. Ordenar libros por precio\n";
        cout << "3. Buscar libro por ISNB\n";
        cout << "4. Actualizar descuento de un libro\n";
        cout << "5. Eliminar libros con stock cero\n";
        cout << "6. Descontar stock de un libro\n";
        cout << "7. Mostrar libros\n";
        cout << "8. Salir" << endl;

        opcion = validarOpcion(1, 8);

        switch (opcion)
        {
        case 1:
            agregarLibro();
            break;
        case 2:
            menuOrdenarPrecio();
            break;
        case 3:
            menuBusquedaIsbn();
            break;
        case 4:
            menuActualizarDescuento();
            break;
        case 5:
            menuEliminarStockCero();
            break;
        case 6:
            menuDescontarStock();
            break;
        case 7:
            menuMostrarLibros();
            break;
        case 8:
            cout << "Saliendo del programa..." << endl;
            break;
        }
    } while (opcion != 8);
}

int main()
{
    menu();
    return 0;
}