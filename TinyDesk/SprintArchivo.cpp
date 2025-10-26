#include <iostream>
#include "SprintArchivo.h"

SprintArchivo::SprintArchivo(std::string nombreArchivo)
  : _nombreArchivo(nombreArchivo)
{
  /// validar
}

bool SprintArchivo::guardar(Sprint registro)
{
  bool result;
  FILE *pFile;

  pFile = fopen(_nombreArchivo.c_str(), "ab");

  if (pFile == nullptr)
  {
    return false;
  }

  result = fwrite(&registro, sizeof(Sprint), 1, pFile);

  fclose(pFile);

  return result;
}

Sprint SprintArchivo::leer(int pos)
{
  Sprint registro;
  FILE *pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if (pFile == nullptr)
  {
    registro.setIdSprint(-1);
    return registro;
  }

  fseek(pFile, sizeof(Sprint) * pos, SEEK_SET);
  fread(&registro, sizeof(Sprint), 1, pFile);

  fclose(pFile);

  return registro;
}

int SprintArchivo::leerTodos(Sprint sprints[], int cantidad)
{
  int result;
  FILE *pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if (pFile == nullptr)
  {
    return 0;
  }

  result = fread(sprints, sizeof(Sprint), cantidad, pFile);

  fclose(pFile);

  return result;
}

int SprintArchivo::getCantidadRegistros()
{
  int cantidad;
  FILE *pFile;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if (pFile == nullptr)
  {
    return 0;
  }

  fseek(pFile, 0, SEEK_END);
  cantidad = ftell(pFile) / sizeof(Sprint);

  fclose(pFile);

  return cantidad;
}

int SprintArchivo::getNuevoID()
{
  return getCantidadRegistros() + 1;
}

int SprintArchivo::buscarID(int id)
{
  Sprint registro;
  FILE *pFile;
  int pos = -1;

  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if (pFile == nullptr)
  {
    return pos;
  }

  while (fread(&registro, sizeof(Sprint), 1, pFile))
  {
    if (registro.getIdSprint() == id)
    {
      pos = ftell(pFile) / sizeof(Sprint) - 1;
      break;
    }
  }

  fclose(pFile);

  return pos;
}
