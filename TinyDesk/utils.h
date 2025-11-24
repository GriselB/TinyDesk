#pragma once
#include <string>
#include "Fecha.h"
#include <cmath>
std::string cargarCadena();
int buscarMaximo(int vec[], int cant);
void cleanBuffer();
void pause();
void clear();
std::string evaluarCV(double cv);
bool fechaMenorOIgual(Fecha esMenor, Fecha esMayor);
void compararRendimientoUsuario(std::string titulo,
                                double diferenciaCumplimiento,
                                double diferenciaCumplimientoATiempo,
                                double cvUsuario,
                                double cvBase,
                                double cvUsuarioATiempo,
                                double cvBaseATiempo);
void cuentaBinomanial(float &media, double &porcentaje, double &CV, int finalizados, int total);
