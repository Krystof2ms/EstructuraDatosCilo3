#include <iostream>
#include <string>

using namespace std;

int validarRango(string msg, int min, int max) {
    int valor;

    do {
        cout << msg;
        cin >> valor;

        if (valor < min || valor > max) {
            cout << "Valor fuera de rango. Por favor, ingrese un valor entre (" << min << " - " << max << ")" << endl;
        }
    } while (valor < min || valor > max);

    return valor;
}

int validarPositivo(string msg, string errorMsg) {
    int id;

    do {
        cout << msg;
        cin >> id;

        if (id < 0) {
            cout << errorMsg << endl;
        }
    } while (id < 0);

    return id;
}

string validarNombre(string msg) {
    string nombre;

    do {
        cout << msg;
        cin >> nombre;

        if (nombre == "") {
            cout << "El nombre no puede estar vacio. Por favor, ingrese un nombre vlido." << endl;
        }
    } while (nombre == "");

    return nombre;
}

bool validarConfirmacion(string msg) {
    char respuesta;

    do {
        cout << msg << " (s/n): ";
        cin >> respuesta;

        respuesta = tolower(respuesta);

        if (respuesta != 's' && respuesta != 'n') {
            cout << "Respuesta invalida. Por favor, ingrese 's' para si o 'n' para no." << endl;
        }
    } while (respuesta != 's' && respuesta != 'n');

    return respuesta == 's';
}
