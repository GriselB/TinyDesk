#include<iostream>
#include "Proyecto.h"
#include "ProyectoArchivo.h"


ProyectoArchivo::ProyectoArchivo(std::string nombreArchivo)
: _nombreArchivo(nombreArchivo){
}
bool ProyectoArchivo::guardar(Proyecto registro)
{
    FILE *pFile;
    bool result;
    pFile = fopen(_nombreArchivo.c_str(),"ab");
    if(pFile==nullptr)
    {
        return false;
    }
    result =fwrite(&registro,sizeof(Proyecto),1,pFile);
    fclose(pFile);
    return result;
}
Proyecto ProyectoArchivo::leer(int pos)
{
    FILE *pFile;
    bool result;
    Proyecto registro;
    pFile=fopen(_nombreArchivo.c_str(),"rb");
    if(pFile==nullptr)
    {
        registro.setIdProyecto(-1);
        return registro;
    }
        fseek(pFile,pos*sizeof(Proyecto),SEEK_SET);
        result=fread(&registro,sizeof(Proyecto),1,pFile);
        fclose(pFile);
        return registro;
}
int ProyectoArchivo::leerTodos(Proyecto registros[], int cantidad)
{
    int result;
    FILE *pFile;

    pFile = fopen(_nombreArchivo.c_str(), "rb");

    if (pFile == nullptr)
    {
        return 0;
    }

    result = fread(registros, sizeof(Proyecto), cantidad, pFile);  ////////////////////
    fclose(pFile);

    return result;
}
int ProyectoArchivo::getCantidadRegistros()
{
    FILE *pFile;
    bool result;
    int cantidad;
    pFile=fopen(_nombreArchivo.c_str(),"rb");
    if(pFile==nullptr)
    {
        return 0;
    }
    fseek(pFile,0,SEEK_END);
    cantidad=ftell(pFile)/sizeof(Proyecto);
    fclose(pFile);
    return cantidad;

}
int ProyectoArchivo::getNuevoID()
{
    if(getCantidadRegistros()==0)
    {
        return 1;
    }
return leer(getCantidadRegistros()-1).getIdProyecto()+1;
}
int ProyectoArchivo::buscarID(int id)
{
    Proyecto registro;
    FILE *pFile;
    int pos = -1;

    pFile = fopen(_nombreArchivo.c_str(), "rb");

    if (pFile == nullptr)
    {
        return pos;
    }

    while (fread(&registro, sizeof(Proyecto), 1, pFile))
    {
        if (registro.getIdProyecto() == id)
        {
            pos = ftell(pFile) / sizeof(Proyecto) - 1;
            break;
        }
    }
    fclose(pFile);
    return pos;
}
