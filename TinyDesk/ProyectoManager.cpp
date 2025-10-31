#include<iostream>
#include "ProyectoManager.h"
#include "Proyecto.h"


ProyectoManager::ProyectoManager()
{

}
void ProyectoManager::crearProyecto()
{
    system("cls");

    std::cout << "---- CREAR NUEVO PROYECTO ----" << std::endl;
    Proyecto proyecto;
    proyecto.cargar();
    proyecto.setIdProyecto(_repo.getNuevoID());
    if(_repo.guardar(proyecto))

    {
        std::cout<<"Proyecto agregado correctamente"<<std::endl;
        system("pause");
    }
    else
    {
        std::cout<<"No se pudo crear el proyecto "<<std::endl;
        system("pause");
    }
}
void ProyectoManager::listarProyectos()
{
    int cant = _repo.getCantidadRegistros();
    if(cant<=0)
    {
        std::cout<<"No hay proyectos cargados"<<std::endl;
        system("pause");
        return;
    }
    Proyecto *vecProyectos = new Proyecto[cant];
    if(vecProyectos==nullptr)
    {
        std::cout << "No se pudo asignar memoria" << std::endl;
        system("pause");
        exit(-1);
    }
    _repo.leerTodos(vecProyectos,cant);
    std::cout<<" ------- Lista de Proyectos ------- "<<std::endl;
    for(int i=0;i<cant;i++)
    {
        vecProyectos[i].mostrar();
    }
    system("pause");
    delete [] vecProyectos;
}
void ProyectoManager::mostrarProyectoPorId()
{
    int id,pos;
    std::cout<<"Ingrese numero Id del Proyecto a buscar: "<<std::endl;
    std::cin>>id;
    pos= _repo.buscarID(id);
    if(pos<0)
    {
        std::cout<<"No existe un Proyecto con dicho ID"<<std::endl;
        system("pause");
        return;
    }
    Proyecto proyecto=_repo.leer(pos);
    system("pause");
}
void ProyectoManager::finalizarProyecto()
{
    int id,pos;
    std::cout<<"Ingrese numero Id del Proyecto a finalizar: "<<std::endl;
    std::cin>>id;
    pos= _repo.buscarID(id);
    if(pos<0)
    {
        std::cout<<"No existe un Proyecto con dicho ID"<<std::endl;
        system("pause");
        return;
    }
    Proyecto proyecto=_repo.leer(pos);
    proyecto.getFechaFinalizada();
    FILE *pFile=fopen("proyectos.dat","rb+");
    if(pFile != nullptr)
    {
        fseek(pFile,sizeof(Proyecto)*pos,SEEK_SET);
        fwrite(&proyecto,sizeof(Proyecto),1,pFile);
        fclose(pFile);
        std::cout<<"Proyecto finalizado correctamente"<<std::endl;
    }
    else
    {
        std::cout<<"No se pudo cargar el archivo"<<std::endl;
    }
    system("pause");
}
void ProyectoManager::bajaLogicaProyecto()
{
    int id,pos;
    std::cout<<"Ingrese numero Id del Proyecto a finalizar: "<<std::endl;
    std::cin>>id;
    pos= _repo.buscarID(id);
    if(pos<0)
    {
        std::cout<<"No existe un Proyecto con dicho ID"<<std::endl;
        system("pause");
        return;
    }
    Proyecto proyecto=_repo.leer(pos);
    proyecto.setIdEstado(0);
    FILE *pFile=fopen("proyectos.dat","rb+");
    if(pFile != nullptr)
    {
        fseek(pFile,sizeof(Proyecto)*pos,SEEK_SET);
        fwrite(&proyecto,sizeof(Proyecto),1,pFile);
        fclose(pFile);
        std::cout<<"Proyecto finalizado correctamente"<<std::endl;
    }
    else
    {
        std::cout<<"No se pudo cargar el archivo"<<std::endl;
    }
    system("pause");
}
