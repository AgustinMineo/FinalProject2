#ifndef STUSERMESSENGE_H_INCLUDED
#define STUSERMESSENGE_H_INCLUDED
#include "user.h"
#include "messenge.h"
typedef struct
{
    int idUser;
    char userName[30];
    int points;
    int status;
} stUserMessenge;

typedef struct
{
    stUserMessenge userMessenger;
   struct nodoUserMessenge *lista;
} userListMessages;


int addMessengeCell (stUserMessenge arrayMessenge[], int validMessenge, char userName[]);
int searchUserMessenge (stUserMessenge arrayMessenge[], int validMessenge, char userName[]);

userListMessages * crearNodoArregloLista(stUserMessenge userMessenge);
stUserMessenge buscarUser(userListMessages arreglo[],int validos,int idUser);
int enviarMensaje(userListMessages arreglo[],int validosMessages,char userEnviar[], int idUser);

int buscarPosMenssenge(userListMessages arreglo[],int validosMessages,int idUser);



#endif // STUSERMESSENGE_H_INCLUDED
