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
    Ticket registro;
    FILE *pFile;
    int pos = id -1;

    pFile = fopen(_nombreArchivo.c_str(), "rb");

    if (pFile == nullptr)
    {
        return pos;
    }

    while (fread(&registro, sizeof(Ticket), 1, pFile))
    {
        if (registro.getIdTicket() == id)
        {
            pos = ftell(pFile) / sizeof(Ticket) - 1;
            break;
        }
    }
    fclose(pFile);
    return pos;
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
    Ticket reg;
    if (!leer(pos, reg)) return false;

    if (!reg.getActivo()) return true;
    reg.setActivo(false);
    return guardar(reg);
}
