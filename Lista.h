#ifndef LISTA_H
#define LISTA_H

#include <iostream>
#include <string> 

using namespace std;

struct Datos {
    string fecha;
    string hora;
    char entrada;
    string ubi;
};

class NodoLista {
public:
    Datos buque;
    NodoLista *next;
    NodoLista(Datos buque);
    ~NodoLista();
};

class Lista {
private:
    NodoLista *first;
public:
    Lista();
    bool compararDatos(const Datos& a, const Datos& b);
    void insertarEnOrden(Datos buque);
    void ordenarMeses(NodoLista* listaM, NodoLista* listaR, const string& serie);
    NodoLista* obtenerPrimerNodo(); // Método getter para obtener el puntero 'first'
    ~Lista();
};

#endif
