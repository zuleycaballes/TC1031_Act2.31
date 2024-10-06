#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Lista.h"
using namespace std;

int main(){
    string nomArchivo;
    cout << "Ingresa el nombre del archivo de entrada: ";
    cin >> nomArchivo;

    ifstream inFile(nomArchivo);

    if (!inFile) {
        cerr << "Error al abrir el archivo de entrada" << endl;
        return 1;
    }

    Lista listaMediterraneo;
    Lista listaRojo;

    string linea;
    while (getline(inFile, linea)) {
        istringstream iss(linea);
        Datos buque;
        iss >> buque.fecha >> buque.hora >> buque.entrada >> buque.ubi;

        if (buque.entrada == 'M') {
            listaMediterraneo.insertarEnOrden(buque);
        } else if (buque.entrada == 'R') {
            listaRojo.insertarEnOrden(buque);
        }
    }

    inFile.close();

    string serieElegida;
    cout << "Ingresa los primeros 3 caracteres del UBI a buscar: ";
    cin >> serieElegida;
   
    listaMediterraneo.ordenarMeses(listaMediterraneo.obtenerPrimerNodo(), listaRojo.obtenerPrimerNodo(), serieElegida);

    return 0;
}
