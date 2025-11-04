
#include "EstadoArchivo.h"
#include "Estado.h"

EstadoArchivo::EstadoArchivo(){
this->_nombreArchivo = "estados.dat";
}

EstadoArchivo::EstadoArchivo(std::string nombreArchivo)
: _nombreArchivo(nombreArchivo){
}
bool EstadoArchivo::guardar(Estado registro)
{
    FILE *pFile;
    bool result;
    pFile = fopen(_nombreArchivo.c_str(),"ab");
    if(pFile==nullptr)
    {
        return false;
    }
    result =fwrite(&registro,sizeof(Estado),1,pFile);
    fclose(pFile);
    return result;
}
Estado EstadoArchivo::leer(int pos)
{
    FILE *pFile;
    bool result;
    Estado registro;
    pFile=fopen(_nombreArchivo.c_str(),"rb");
    if(pFile==nullptr)
    {
        registro.setIdEstado(-1);
        return registro;
    }
        fseek(pFile,pos*sizeof(Estado),SEEK_SET);
        result=fread(&registro,sizeof(Estado),1,pFile);
        fclose(pFile);
        return registro;
}
int EstadoArchivo::getCantidadRegistros()
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
    cantidad=ftell(pFile)/sizeof(Estado);
    fclose(pFile);
    return cantidad;
}

int EstadoArchivo::leerTodos(Estado registros[], int cantidad)
{
    int result;
    FILE *pFile;

    pFile = fopen(_nombreArchivo.c_str(), "rb");

    if (pFile == nullptr)
    {
        return 0;
    }

    result = fread(registros, sizeof(Estado), cantidad, pFile);
    fclose(pFile);

    return result;
}

