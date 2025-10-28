#include <iostream>
#include <cstring>
#include "area.h"

using namespace std;

//getter
int Area::getIdArea()
{
    return _idArea;
}
std::string Area::getNombre()
{
    return _nombre;
}

//setter
void Area::setIdArea(int idArea)
{
    _idArea=idArea;
}
void Area::setNombreArea(std::string nombre)
{
    strncpy(_nombre, nombre.c_str(), 19);
    _nombre[19] = '\0';
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
    string nombres[] = {"Administración", "Backend", "Frontend", "QA", "UX/UI"};

    Area area;

    do {
        mostrarOpciones();
        cout << "Ingrese el ID del área: ";
        cin >> idArea;
    } while (idArea < 1 || idArea > 5);

    area.setIdArea(idArea);
    area.setNombreArea(nombres[idArea - 1]);

}
