#include<iostream>
#include "ProyectoManager.h"
#include "Proyecto.h"
#include "utils.h"

using namespace std;

ProyectoManager::ProyectoManager()
{

}

void ProyectoManager::crearProyecto()
{
    system("cls");

    cout << "---- CREAR NUEVO PROYECTO ----" << endl;
    Proyecto proyecto;
    proyecto.setIdProyecto(_repo.getNuevoID());
    proyecto.cargar();
    if(_repo.guardar(proyecto))

    {
        cout<<"Proyecto agregado correctamente"<<endl;
        pause();
    }
    else
    {
        cout<<"No se pudo crear el proyecto "<<endl;
        pause();
    }
}
void ProyectoManager::listarProyectos()
{
    int cant = _repo.getCantidadRegistros();
    if(cant<=0)
    {
        cout<<"No hay proyectos cargados"<<endl;
        pause();
        return;
    }
    Proyecto *vecProyectos = new Proyecto[cant];
    if(vecProyectos==nullptr)
    {
        cout << "No se pudo asignar memoria" <<endl;
        pause();
        exit(-1);
    }
    _repo.leerTodos(vecProyectos,cant);
    cout << "                   ----- PROYECTOS -----" << endl;
    for(int i=0;i<cant;i++)
    {
        vecProyectos[i].mostrar();
    }
    pause();

    delete [] vecProyectos;
}

void ProyectoManager::listarProyectosNombreID()
{
    int cant = _repo.getCantidadRegistros();
    if(cant<=0)
    {
        cout<<"No hay proyectos cargados"<<endl;
        pause();
        return;
    }
    Proyecto *vecProyectos = new Proyecto[cant];
    if(vecProyectos==nullptr)
    {
        cout << "No se pudo asignar memoria" <<endl;
        pause();
        exit(-1);
    }
    _repo.leerTodos(vecProyectos,cant);
    cout<<" ------- Lista de Proyectos ------- "<<endl;
    for(int i=0;i<cant;i++)
    {
        cout<<"Id del proyecto: "<<vecProyectos[i].getIdProyecto()<<endl;
        cout<<"Nombre del proyecto: "<<vecProyectos[i].getNombre()<<endl;
        cout<<" ----------------------------------- "<<endl;
    }
    pause();

    delete [] vecProyectos;
}
void ProyectoManager::mostrarProyectoPorId()
{
    int id,pos;
    cout<<"Ingrese numero Id del Proyecto a buscar: "<<endl;
    cin>>id;
    pos= _repo.buscarID(id);
    if(pos<0)
    {
        cout<<"No existe un Proyecto con dicho ID"<<endl;
        pause();
        return;
    }
    Proyecto proyecto=_repo.leer(pos);
    pause();
}
void ProyectoManager::finalizarProyecto()
{
    int id,pos;
    cout<<"Ingrese numero Id del Proyecto a finalizar: "<<endl;
    cin>>id;
    pos= _repo.buscarID(id);
    if(pos<0)
    {
        cout<<"No existe un Proyecto con dicho ID"<<endl;
        pause();
        return;
    }
    Proyecto proyecto=_repo.leer(pos);
    if(proyecto.getIdEstado()==2)
    {
        cout<<"El proyecto ya fue finalizado anteriormente"<<endl;
        pause();
        return;
    }
    if(proyecto.getIdEstado()==0)
    {
        cout<<"El proyecto no se encuentra disponible"<<endl;
        pause();
        return;
    }
    proyecto.setFechaFinalizada();
    Fecha a =  proyecto.getFechaFinTipoFecha();
    Fecha b = proyecto.getFechaFinalizadaTipoFecha();
    cout<<a.getAnio();
    while(!fechaMenorOIgual(a,b))
    {
        cout<<"Fecha de finalizacion anterior a fecha de fin, fecha invalida"<<endl;
        proyecto.setFechaFinalizada();
        b = proyecto.getFechaFinalizadaTipoFecha();
    }
    proyecto.setIdEstado(2);
    FILE *pFile=fopen("proyectos.dat","rb+");
    if(pFile != nullptr)
    {
        fseek(pFile,sizeof(Proyecto)*pos,SEEK_SET);
        fwrite(&proyecto,sizeof(Proyecto),1,pFile);
        fclose(pFile);
        cout<<"Proyecto finalizado correctamente"<<endl;
    }
    else
    {
        cout<<"No se pudo cargar el archivo"<<endl;
    }
    pause();
}
void ProyectoManager::bajaLogicaProyecto()
{
    int id,pos;
    cout<<"Ingrese numero Id del Proyecto a finalizar: "<<endl;
    cin>>id;
    pos= _repo.buscarID(id);
    if(pos<0)
    {
        cout<<"No existe un Proyecto con dicho ID"<<endl;
        pause();
        return;
    }
    Proyecto proyecto=_repo.leer(pos);
    if(proyecto.getIdEstado()==2)
    {
        cout<<"El proyecto ya fue finalizado anteriormente"<<endl;
        pause();
        return;
    }
    if(proyecto.getIdEstado()==0)
    {
        cout<<"El proyecto ya se encuentra dado de baja"<<endl;
        pause();
        return;
    }
    proyecto.setIdEstado(0);
    FILE *pFile=fopen("proyectos.dat","rb+");
    if(pFile != nullptr)
    {
        fseek(pFile,sizeof(Proyecto)*pos,SEEK_SET);
        fwrite(&proyecto,sizeof(Proyecto),1,pFile);
        fclose(pFile);
        cout<<"Proyecto dado de baja correctamente"<<endl;
    }
    else
    {
        cout<<"No se pudo cargar el archivo"<<endl;
    }
    pause();
}

void ProyectoManager::altaLogicaProyecto()
{
    int id,pos;
    cout<<"Ingrese numero Id del Proyecto a finalizar: "<<endl;
    cin>>id;
    pos= _repo.buscarID(id);
    if(pos<0)
    {
        cout<<"No existe un Proyecto con dicho ID"<<endl;
        pause();
        return;
    }
    Proyecto proyecto=_repo.leer(pos);
    if(proyecto.getIdEstado()==2)
    {
        cout<<"El proyecto ya fue finalizado anteriormente"<<endl;
        pause();
        return;
    }
    if(proyecto.getIdEstado()==1)
    {
        cout<<"El proyecto ya se encuentra dado de alta"<<endl;
        pause();
        return;
    }
    proyecto.setIdEstado(1);
    FILE *pFile=fopen("proyectos.dat","rb+");
    if(pFile != nullptr)
    {
        fseek(pFile,sizeof(Proyecto)*pos,SEEK_SET);
        fwrite(&proyecto,sizeof(Proyecto),1,pFile);
        fclose(pFile);
        cout<<"Proyecto dado de alta correctamente"<<endl;
    }
    else
    {
        cout<<"No se pudo cargar el archivo"<<endl;
    }
    pause();
}
