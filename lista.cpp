#include "Lista.h"
#include <iostream>
#include <algorithm>
#include <array>
#include <iomanip>

using namespace std;

NodoLista::NodoLista(Datos valor){
    buque = valor;
    next = nullptr;
}

NodoLista::~NodoLista() {}

Lista::Lista() {
    first = nullptr;
}

Lista::~Lista() {
    NodoLista* actual = first;
    while (actual != nullptr) {
        NodoLista* temp = actual;
        actual = actual->next;
        delete temp;
    }
}

NodoLista* Lista::obtenerPrimerNodo() {
    return first;
}

bool Lista::compararDatos(const Datos& a, const Datos& b) {
    if (a.ubi != b.ubi) return a.ubi < b.ubi;

    int dayA = stoi(a.fecha.substr(0, 2));
    int monthA = stoi(a.fecha.substr(3, 2));
    int yearA = stoi(a.fecha.substr(6, 4));

    int dayB = stoi(b.fecha.substr(0, 2));
    int monthB = stoi(b.fecha.substr(3, 2));
    int yearB = stoi(b.fecha.substr(6, 4));

    if (yearA != yearB) return yearA < yearB;
    if (monthA != monthB) return monthA < monthB;
    return dayA < dayB;
}

void Lista::insertarEnOrden(Datos buque) {
    NodoLista* nuevoNodo = new NodoLista(buque);

    if (first == nullptr || compararDatos(buque, first->buque)) {
        nuevoNodo->next = first;
        first = nuevoNodo;
    } else {
        NodoLista* actual = first;
        while (actual->next != nullptr && compararDatos(actual->next->buque, buque)) {
            actual = actual->next;
        }
        nuevoNodo->next = actual->next;
        actual->next = nuevoNodo;
    }
}

void Lista::ordenarMeses(NodoLista* serieM, NodoLista* serieR, const string& serie) {
    if (serieM == nullptr && serieR == nullptr) return;

    int mesesM[12] = {0};  // Conteo de buques en el Mediterráneo por mes
    int mesesR[12] = {0};  // Conteo de buques en el Rojo por mes
    const string meses[] = {"jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec"};

    int anioM = 0, anioR = 0;  // Para guardar el año de los registros

    // Recorremos la lista del Mediterráneo
    if (serieM != nullptr) {
        NodoLista* actualM = serieM;
        while (actualM != nullptr) {
            if (actualM->buque.ubi.substr(0, 3) == serie) {
                string fecha = actualM->buque.fecha;
                int mesIndex = stoi(fecha.substr(3, 2)) - 1;  // Obtener el índice del mes
                anioM = stoi(fecha.substr(6, 4));  // Guardamos el año
                mesesM[mesIndex]++;  // Aumentamos el conteo de buques para ese mes en Mediterráneo
            }
            actualM = actualM->next;
        }
    }

    // Recorremos la lista del Rojo
    if (serieR != nullptr) {
        NodoLista* actualR = serieR;
        while (actualR != nullptr) {
            if (actualR->buque.ubi.substr(0, 3) == serie) {
                string fecha = actualR->buque.fecha;
                int mesIndex = stoi(fecha.substr(3, 2)) - 1;  // Obtener el índice del mes
                anioR = stoi(fecha.substr(6, 4));  // Guardamos el año
                mesesR[mesIndex]++;  // Aumentamos el conteo de buques para ese mes en Rojo
            }
            actualR = actualR->next;
        }
    }

    // Encontrar el primer y último mes con datos
    int primerMes = 0, ultimoMes = 11;
    for (int i = 0; i < 12; ++i) {
        if (mesesM[i] > 0 || mesesR[i] > 0) {
            primerMes = i;
            break;
        }
    }
    for (int i = 11; i >= 0; --i) {
        if (mesesM[i] > 0 || mesesR[i] > 0) {
            ultimoMes = i;
            break;
        }
    }

    // Mostrar los resultados solo desde el primer mes con datos hasta el último mes con datos
    for (int i = primerMes; i <= ultimoMes; ++i) {
        cout << meses[i] << " " << (anioM != 0 ? anioM : anioR) << " " 
             << setw(2) << setfill(' ') << mesesM[i] << " " 
             << setw(2) << setfill(' ') << mesesR[i] << endl;
    }
}
