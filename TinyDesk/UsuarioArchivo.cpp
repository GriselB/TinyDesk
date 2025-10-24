//
//  UsuarioArchivo.cpp
//  TinyDesk
//
//  Created by Sebastian Yanni on 18/10/2025.
//

#include <iostream>
#include "UsuarioArchivo.h"

UsuarioArchivo::UsuarioArchivo(std::string nombreArchivo)
  : _nombreArchivo(nombreArchivo)
{
  /// validar
}

bool UsuarioArchivo::guardar(Usuario registro)
{
  bool result;
  FILE *pFile;

  pFile = fopen(_nombreArchivo.c_str(), "ab");

  if (pFile == nullptr)
  {
    return false;
  }

  result = fwrite(&registro, sizeof(Usuario), 1, pFile);

  fclose(pFile);

  return result;
}

Usuario UsuarioArchivo::leer(int pos)
{
  Usuario registro;
  FILE *pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if (pFile == nullptr)
  {
    registro.setIdUsuario(-1);
    return registro;
  }

  fseek(pFile, sizeof(Usuario) * pos, SEEK_SET);
  fread(&registro, sizeof(Usuario), 1, pFile);

  fclose(pFile);

  return registro;
}

int UsuarioArchivo::leerTodos(Usuario usuarios[], int cantidad)
{
  int result;
  FILE *pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if (pFile == nullptr)
  {
    return 0;
  }

  result = fread(usuarios, sizeof(Usuario), cantidad, pFile);

  fclose(pFile);

  return result;
}

int UsuarioArchivo::getCantidadRegistros()
{
  int cantidad;
  FILE *pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if (pFile == nullptr)
  {
    return 0;
  }

  fseek(pFile, 0, SEEK_END);
  cantidad = ftell(pFile) / sizeof(Usuario);

  fclose(pFile);

  return cantidad;
}

int UsuarioArchivo::getNuevoID()
{
  return getCantidadRegistros() + 1;
}

int UsuarioArchivo::buscarID(int idUsuario)
{
  Usuario registro;
  FILE *pFile;
  int pos = -1;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if (pFile == nullptr)
  {
    return pos;
  }

  while (fread(&registro, sizeof(Usuario), 1, pFile))
  {
    if (registro.getIdUsuario() == idUsuario)
    {
      pos = ftell(pFile) / sizeof(Usuario) - 1;
      break;
    }
  }

  fclose(pFile);

  return pos;
}
