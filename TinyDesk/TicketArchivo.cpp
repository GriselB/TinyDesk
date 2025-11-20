#include <iostream>
#include "TicketManager.h"

using namespace std;

TicketArchivo::TicketArchivo(std::string nombreArchivo)
: _nombreArchivo(nombreArchivo) {}

bool TicketArchivo::leer(int pos, Ticket &ticket)
{
FILE *pFile;
bool result;
    pFile=fopen(_nombreArchivo.c_str(),"rb");
    if(pFile==nullptr)
    {
        ticket.setIdTicket(-1);
        return false;
    }
        fseek(pFile,pos*sizeof(Ticket),SEEK_SET);
        result=fread(&ticket,sizeof(Ticket),1,pFile);
        fclose(pFile);
        return true;
}

int TicketArchivo::leerTodos(Ticket tickets[], int cantidad)
{
int result;
FILE *pFile;
  pFile = fopen(_nombreArchivo.c_str(), "rb");

  if (pFile == nullptr){
    return 0;
  }

  result = fread(tickets, sizeof(Ticket), cantidad, pFile);

  fclose(pFile);

  return result;
}

int TicketArchivo::getCantidadRegistros(){
FILE *pFile = fopen(_nombreArchivo.c_str(), "rb");
    if (pFile == nullptr) return 0;

    if (fseek(pFile, 0, SEEK_END) != 0) { fclose(pFile); return 0; }

    long bytes = ftell(pFile);
    fclose(pFile);
    if (bytes < 0) return 0;

    return (int)(bytes / (long)sizeof(Ticket));
}

int TicketArchivo::buscarID(int id){
FILE* pFile = fopen(_nombreArchivo.c_str(), "rb");
    if (pFile == nullptr) {
        return -1;
    }
    Ticket registro;
    int index = 0;

    while (fread(&registro, sizeof(Ticket), 1, pFile) == 1) {
        if (registro.getIdTicket() == id) {
            fclose(pFile);
            return index;
        }
        index++;
    }

    fclose(pFile);
    return -1;
}

int TicketArchivo::getNuevoIdTicket(int idProyecto, int idSprint){
    FILE* f = fopen(_nombreArchivo.c_str(), "rb");
    if (!f) return 1;

    Ticket ticket;
    int maxId = 0;

    while (fread(&ticket, sizeof(Ticket), 1, f) == 1) {
        if (ticket.getIdProyecto() == idProyecto && ticket.getIdSprint() == idSprint){
            if (ticket.getIdTicket() > maxId) maxId = ticket.getIdTicket();
        }
    }

    fclose(f);
    return maxId + 1;

}

int TicketArchivo::buscarIDTicketSprintProyecto(int idTicket, int idProyecto, int idSprint){
    FILE* pFile = fopen(_nombreArchivo.c_str(), "rb");
    if (pFile == nullptr){
        return -1;
    }
    Ticket t;
    int index = 0;

    while (fread(&t, sizeof(Ticket), 1, pFile) == 1) {
        if (t.getIdTicket() == idTicket && t.getIdSprint() == idSprint && t.getIdProyecto() == idProyecto){
            fclose(pFile);
            return index;
        }
        index++;
    }

    fclose(pFile);
    return -1;
}

bool TicketArchivo::guardar(int pos, Ticket &t) {
    FILE* f = fopen(_nombreArchivo.c_str(), "rb+");
    if (!f) return false;

    fseek(f, pos * sizeof(Ticket), SEEK_SET);
    bool ok = fwrite(&t, sizeof(Ticket), 1, f);
    fclose(f);
    return ok;
}

bool TicketArchivo::guardarNuevo(Ticket &ticket){
bool existe = false;
    FILE *pFile = fopen(_nombreArchivo.c_str(), "ab");
    if (pFile == nullptr) return existe;
    size_t escritos = fwrite(&ticket, sizeof(Ticket), 1, pFile);
    fclose(pFile);
    return (escritos == 1);
}


bool TicketArchivo::darDeBaja(int idTicket, int idProyecto, int idSprint){
int pos = buscarIDTicketSprintProyecto(idTicket, idProyecto, idSprint);

 if (pos != -1){
    Ticket ticket;

    bool pudoLeer = leer(pos, ticket);

    return guardar(pos, ticket);
  }
  return false;
}

