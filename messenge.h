#ifndef MESSENGE_H_INCLUDED
#define MESSENGE_H_INCLUDED
#include "stUserMessenge.h"

typedef struct
{
    int idIssuing;
    int idReceiver;
    int idContent;
    char message [150];
    char timeSend[50];
    int read;
    int status;
} stMessenge;

typedef struct
{
    stMessenge messenge;
    struct nodoUserMessenge * following;
}nodoUserMessenge;
nodoUserMessenge * crearNodoUserMessenge (stMessenge mensaje);
nodoUserMessenge* agregarAlFinal(nodoUserMessenge * lista, nodoUserMessenge * nuevoNodo);
nodoUserMessenge * buscarUltimo(nodoUserMessenge * lista);
nodoUserMessenge * agregarAlPpio (nodoUserMessenge * lista, nodoUserMessenge * nuevo);

nodoUserMessenge * inicListaUserMessenge ();

stMessenge crearMensaje (int idIssuing, int idReceiver);
void mostrarNodo (nodoUserMessenge * lista);
void mostrarArchi(char manderArchi[]);
nodoUserMessenge * agregarAlfinalArchivo (nodoUserMessenge * lista,nodoUserMessenge * mensaje);
nodoUserMessenge* archivoMensajeALista (char manderArchi[],nodoUserMessenge* lista,int idUser);
nodoUserMessenge * buscarUltimo(nodoUserMessenge * lista);
nodoUserMessenge* agregarAlFinal(nodoUserMessenge * lista, nodoUserMessenge * nuevoNodo);
nodoUserMessenge * redactarMensaje (nodoUserMessenge * lista,int idUser, int idUserReceiver,nodoUserMessenge ** listaRecibe);
stMessenge crearMensajeRecibe (int idUser, int idReceiver,char mensaje[]);
nodoUserMessenge* archivoMensajeALista (char manderArchi[],nodoUserMessenge* lista,int idUser);
nodoUserMessenge * agregarAlfinalArchivo (nodoUserMessenge * lista,nodoUserMessenge * mensaje);


#endif // MESSENGE_H_INCLUDED
