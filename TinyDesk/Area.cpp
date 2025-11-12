#include <iostream>
#include <cstring>
#include "area.h"

using namespace std;

//getter
int Area::getIdArea()
{
    return _idArea;
}

string Area::getNombreArea() {
    return string(_nombre);
}

//setter
void Area::setIdArea(int idArea)
{
    _idArea=idArea;
}
void Area::setNombreArea(string nombre)
{
    strncpy(_nombre, nombre.c_str(), sizeof(_nombre) - 1);
    _nombre[sizeof(_nombre) - 1] = '\0';
}



void Area::mostrarOpciones() {
    cout << "\n--- ÁREAS DISPONIBLES ---\n";
    cout << "1: Administración"<<endl;
    cout << "2: Backend"<<endl;
    cout << "3: Frontend"<<endl;
    cout << "4: QA"<<endl;
    cout << "5: UX/UI"<<endl;
}


void Area::seleccionar() {
    int idArea;
    string nombres[5] = {"Administración", "Backend", "Frontend", "QA", "UX/UI"};

    do {
        mostrarOpciones();
        cout << "Ingrese el ID del área: ";
        cin >> idArea;
    } while (idArea < 1 || idArea > 5);

    setIdArea(idArea);
    setNombreArea(nombres[idArea - 1]);

}
