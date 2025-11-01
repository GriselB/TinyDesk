#include <iostream>
#include "TicketManager.h"

using namespace std;

TicketArchivo::TicketArchivo(std::string nombreArchivo)
: _nombreArchivo(nombreArchivo) {}

//Nota mental: va a recibir el ticket vacío por referencia, y luego lo llena para devolverlo
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

  if (pFile == nullptr)
  {
    return 0;
  }

  result = fread(tickets, sizeof(Ticket), cantidad, pFile);

  fclose(pFile);

  return result;
}

int TicketArchivo::getCantidadRegistros()
{
    FILE *pFile = fopen(_nombreArchivo.c_str(), "rb");
    if (pFile == nullptr) return 0;

    if (fseek(pFile, 0, SEEK_END) != 0) { fclose(pFile); return 0; }

    long bytes = ftell(pFile);
    fclose(pFile);
    if (bytes < 0) return 0;

    return (int)(bytes / (long)sizeof(Ticket));
}
int TicketArchivo::buscarID(int id)
{
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


int TicketArchivo::getNuevoID()
{

int cantidad = getCantidadRegistros();
    if(cantidad == 0)
    {
        return 1;
    }
Ticket ultimoTicket;

bool ticketAnteriorExiste = leer(cantidad - 1, ultimoTicket);
    if (ticketAnteriorExiste){
        return ultimoTicket.getIdTicket()+1;
    }
    else{
        return 1;
    }
}

bool TicketArchivo::guardar(Ticket ticket) {
bool existe = false;
    FILE *pFile = fopen(_nombreArchivo.c_str(), "ab");
    if (pFile == nullptr) return existe;
    size_t escritos = fwrite(&ticket, sizeof(Ticket), 1, pFile);
    fclose(pFile);
    return (escritos == 1);
}

bool TicketArchivo::eliminar(int pos) {
    if (pos < 0) return false;

    FILE* f = fopen(_nombreArchivo.c_str(), "rb+");
    if (!f) return false;

    Ticket r;
    bool ok = (fseek(f, pos * (int)sizeof(Ticket), SEEK_SET) == 0) &&
              (fread(&r, sizeof(Ticket), 1, f) == 1);

    if (!ok) { fclose(f); return false; }
    if (!r.getActivo()) { fclose(f); return true; }   // ya estaba dado de baja

    r.setActivo(false);

    ok = (fseek(f, pos * (int)sizeof(Ticket), SEEK_SET) == 0) &&
         (fwrite(&r, sizeof(Ticket), 1, f) == 1);

    fclose(f);
    return ok;
}

bool TicketArchivo::yaExisteTicketEmpleadoSprint(Ticket &ticket)
{
    FILE* pFile = fopen(_nombreArchivo.c_str(), "rb");
    if (pFile == nullptr) {
        return -1;
    }
    Ticket registro;
    int index = 0;

    while (fread(&registro, sizeof(Ticket), 1, pFile) == 1) {
        if (registro.getIdEmpleado() == ticket.getIdEmpleado() &&
            registro.getIdSprint() == ticket.getIdSprint() &&
            registro.getActivo()
           ) {
            fclose(pFile);
            return true;
        }
        index++;
    }

    fclose(pFile);
    return false;
}

