#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <malloc.h>
#include "stUserMessenge.h"
#include "menus.h"

int cargarArreglo (nodoArbol * arbol,userListMessages arreglo[], int validos,stUserNew user)
{
    stUserMessenge userNuevosDatos = searchIDMessange(arbol,user.idUser);
    int pos;
    userListMessages * aux = crearNodoArregloLista(userNuevosDatos);
    pos = buscarUsuarioMensajes(arreglo, validos, aux->userMessenger.userName);
    if (pos==-1)
   {
        validos = agregarUsuarioMensajes(arreglo, validos, aux->userMessenger);
        pos = validos-1;
    }
    arreglo[pos].lista = agregarAlFinal(arreglo[pos].lista, aux);
    return validos;
}

int agregarUsuarioMensajes (userListMessages arreglo[], int validos, stUserMessenge userMensajes)
{
    arreglo[validos].userMessenger.idUser = userMensajes.idUser;
    strcpy(arreglo[validos].userMessenger.userName, userMensajes.userName);
    arreglo[validos].userMessenger.points = userMensajes.points;
    arreglo[validos].userMessenger.status = userMensajes.status;
    arreglo[validos].lista = inicLisMessenge();
    validos++;
    return validos;
}

int buscarUsuarioMensajes (userListMessages arreglo[], int validos, char userMensajes[])
{
    int pos = -1;
    int i=0;
    while (i<validos && pos == -1)
    {
        if (strcmp(arreglo[i].userMessenger.userName, userMensajes)==0)
        {
            pos=i;
        }
        i++;
    }
    return pos;
}

nodoUserMessenge* agregarAlFinal(nodoUserMessenge * lista, nodoUserMessenge * nuevoNodo)
{

    if(lista==NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        nodoUserMessenge* ultimo = buscarUltimo(lista);
        ultimo->following = nuevoNodo;
    }
    return lista;
}

nodoUserMessenge * buscarUltimo(nodoUserMessenge * lista)
{
    nodoUserMessenge * seg = lista;
    while(seg->following!=NULL)
    {
        seg = seg->following;
    }
    return seg;
}

userListMessages * crearNodoArregloLista(stUserMessenge userMessenge)
{
    userListMessages * aux = (userListMessages*) malloc(sizeof(userListMessages));
    aux->userMessenger=userMessenge;
    aux->lista=inicListaUserMessenge();//inicLisMessenge();
    return aux;
}



int buscarPosMenssenge(userListMessages arreglo[],int validosMessages,int idUser)
{
    int pos=-1;
    int i=0;
    int flag=0;
    while(flag==0 && i<validosMessages)
    {
        if(arreglo[i].userMessenger.idUser==idUser)
        {
            flag=1;

            pos=i;
        }

        i++;
    }
    return pos;
}

void inicUserMenssange (userListMessages arreglo[],int validos)
{
    for(int j=0;j<validos;j++)
            {
            arreglo[j].lista=inicListaUserMessenge();
            }
}


nodoUserMessenge* loadUserMessange(userListMessages* lista, char manderArchi[])
{
        nodoUserMessenge * seg=lista;
    if (lista)
    {
        while (seg!=NULL)
        {
            seg=archivoMensajeALista(manderArchi,seg,seg->messenge.idReceiver);
            seg=seg->following;
        }
    }
    return seg;
}

nodoUserMessenge* archivoMensajeALista (char manderArchi[],nodoUserMessenge* lista,int idUser)
{
    FILE * pFile=fopen(manderArchi,"rb");
    stMessenge sms;


    if(pFile)
    {
        while (fread(&sms,sizeof(stMessenge),1,pFile)>0)
        {
            if (sms.idIssuing==idUser || sms.idReceiver==idUser)
            {
                lista=agregarAlfinalArchivo(lista,crearNodoUserMessenge(sms));
            }
        }
    }
    fclose(pFile);

    return lista;
}

nodoUserMessenge * agregarAlfinalArchivo (nodoUserMessenge * lista,nodoUserMessenge * mensaje)
{
    if (lista==NULL)
    {
        lista=mensaje;
    }
    else
    {
        lista->following=agregarAlfinalArchivo(lista->following,mensaje);
    }
    return lista;
}
