#include "messenge.h"
#include "stUserMessenge.h"
#include "user.h"
#include <stdio.h>
#include <string.h>

userListMessages * inicLisMessenge()
{
    return NULL;
}

int fileToArrayMessenge (char mainArchivoMessange [], stUserMessenge arrayMessenge[], int validMessenge)
{
    FILE * archi = fopen(mainArchivoMessange, "rb");
    if (archi)
    {
        stUserMessenge auxMessenge;
        stUserNew auxUser;
        while (fread(&auxMessenge, sizeof(stUserMessenge), 1, archi)>0)
        {
            auxMessenge.idUser = auxUser.idUser;
            auxMessenge.status= auxUser.status;
            strcpy(auxMessenge.userName, auxUser.userName);
        }
        fclose(archi);
    }
    return validMessenge;
}
void showUserConectingMessenge(userListMessages arrayMessenge[],int validMessenge)
{
    int i=0;
    while(i<validMessenge)
    {
        if(arrayMessenge[i].userMessenger.idUser!=-1)
        {
            printf("Usuarios disponibles ->>> %s\n",arrayMessenge[i].userMessenger.userName);
            printf("\n\n");
        }
        i++;
    }
}
int enviarMensaje(userListMessages arreglo[],int validosMessages,char userEnviar[], int idUser)
{
    int i=1;
    int pos1=0;
    int pos2=0;
    pos1=buscarUsuarioMensajes (arreglo,validosMessages,userEnviar);
    pos2=buscarPosMenssenge(arreglo,validosMessages,idUser);

    arreglo[pos2].lista=redactarMensaje(arreglo[pos2].lista,idUser,arreglo[pos1].userMessenger.idUser,&arreglo[pos1].lista);
    return i;
}

nodoUserMessenge * redactarMensaje (nodoUserMessenge * lista,int idUser, int idUserReceiver,nodoUserMessenge ** listaRecibe)
{
    stMessenge aux;
    stMessenge auxRecibe;
    aux= crearMensaje(idUser,idUserReceiver);
    nodoUserMessenge * nuevoMsn= crearNodoUserMessenge(aux);

    lista= agregarAlFinal(lista,nuevoMsn);

    return lista;
}

stMessenge crearMensajeRecibe (int idUser, int idReceiver,char mensaje[])
{
    stMessenge aux;
    aux.idIssuing=idUser;
    aux.idReceiver=idReceiver;
    aux.idContent=1;

    strcpy(aux.message,mensaje);
    aux.read=0;

    aux.status=1;

    return aux;
}

stMessenge crearMensaje (int idUser, int idReceiver)
{
    stMessenge aux;

    aux.idIssuing=idUser;
    aux.idReceiver=idReceiver;
    aux.idContent=1;

    printf("Escribe tu mensaje: ");
    fflush(stdin);
    gets(aux.message);

    getTime(aux.timeSend);

    aux.read=0;

    aux.status=1;

    return aux;
}

nodoUserMessenge * inicListaUserMessenge ()
{
    return NULL;
}

nodoUserMessenge * crearNodoUserMessenge (stMessenge mensaje)
{
    nodoUserMessenge * nuevoNodo = (nodoUserMessenge*) malloc(sizeof(nodoUserMessenge));
    nuevoNodo->messenge=mensaje;
    nuevoNodo->following=NULL;
    return nuevoNodo;
}

nodoUserMessenge * agregarAlPpio (nodoUserMessenge * lista, nodoUserMessenge * nuevo)
{
    nuevo->following=lista;
    return nuevo;
}
void mostrarArregloDeMensajesPendientes (stUserMessenge arregloMensajes[],int validos)
{
    for(int j=0; j<validos; j++)
    {
        printf("User ---> %s \n",arregloMensajes[j].userName);
    }
}

int buscarUsuarioMensajeArreglo (char nombre[], stUserMessenge arregloMensajes[], int validos)
{
    int rta;
    int flag=0;
    int i=0;
    while(i<validos && flag==0)
    {
        if(strcmpi(nombre,arregloMensajes[i].userName)==0)
        {
            rta=i;
            flag=1;
        }
        i++;
    }
    return rta;
}

void mostrarNodo (nodoUserMessenge * lista)
{
    nodoUserMessenge * seg=lista;

    while(seg!=NULL)
    {

        printf("\nMENSAJE --> %s\n",seg->messenge.message);
        printf("\nTIME %s\n",seg->messenge.timeSend);
        seg=seg->following;
    }
}
void enviarMensajeAdmin(int idUser,int validosMessages,userListMessages arreglo[])
{
    int admin=-1;
    int pos;
    pos=buscarPosMenssenge(arreglo,validosMessages,idUser);
    arreglo[pos].lista=redactarMensaje(arreglo[pos].lista,idUser,admin,&arreglo[admin].lista);
}

void ingresarChat(nodoUserMessenge * lista,userListMessages arreglo[], int validos,char userEnviar[],int idUser)
{
    int aux;
    int op=0;
    aux=buscarUsuarioMensajes(arreglo,validos,userEnviar);
    nodoUserMessenge * seg = lista;
    while (seg!=NULL)
    {
        if(arreglo[aux].userMessenger.idUser == seg->messenge.idReceiver)
        {
            printf("chat: %s\n",seg->messenge.message);
            seg->messenge.read=1;
        }
        seg=seg->following;
    }
    printf("¿Desea contestar?\n 1. SI\n 2. NO\n");
    fflush(stdin);
    scanf("%d",&op);
    if(op==1)
    {
        enviarMensaje(arreglo,validos,userEnviar,idUser);
    }
}
void todoArregloAlArchivo (userListMessages arreglo[],int validos, char manderArchi[])
{
    FILE* pFile=fopen(manderArchi,"wb");
    if (pFile)
        fclose(pFile);
    int i;
    for(i=0; i<validos; i++)
    {
        if(arreglo[i].lista!=NULL)
        {
            arregloCompletoArchivo(arreglo[i].lista,manderArchi,validos,arreglo);
        }
    }
}

void arregloCompletoArchivo (nodoUserMessenge * lista,char manderArchi[],int validos, userListMessages arreglo[])
{
    FILE* pFile=fopen(manderArchi,"ab");
    stMessenge sms;
    nodoUserMessenge * seg=lista;
    if (pFile)
    {
        if(seg!=NULL)
        {
            while(seg!=NULL)
            {
                sms=seg->messenge;
                fwrite(&sms,sizeof(stMessenge),1,pFile);
                seg=seg->following;
            }
        }
    }
    fclose(pFile);
}
nodoUserMessenge * archivoAListaMensaje (userListMessages arreglo[],int validos,char manderArchi[],int idUser)
{
    FILE* pFile=fopen(manderArchi,"rb");
    stMessenge sms;
    int i=0;
    int pos1=0;
    if(pFile)
    {
        while(fread(&sms,sizeof(stMessenge),1,pFile)>0)
        {
            if(sms.idReceiver==idUser || sms.idIssuing==idUser)
            {
                nodoUserMessenge * aux=crearNodoUserMessenge(sms);
                if(idUser!=sms.idIssuing)
                {
                    pos1=buscarPosMenssenge(arreglo,validos,aux->messenge.idIssuing);
                    arreglo[pos1].lista=agregarAlFinal(arreglo[aux->messenge.idIssuing].lista,aux);
                }
                else if(sms.idReceiver!=idUser)
                {
                    pos1=buscarPosMenssenge(arreglo,validos,aux->messenge.idIssuing);
                    arreglo[pos1].lista=agregarAlFinal(arreglo[sms.idReceiver].lista,aux);
                }
                else if(sms.idReceiver==idUser && sms.idIssuing==idUser)
                {
                    arreglo[idUser].lista=agregarAlFinal(arreglo[idUser].lista,aux);
                }
            }
        }
        fclose(pFile);

    }
    return arreglo[pos1].lista;
}

void mostrarArchi(char manderArchi[])
{
    FILE* pFile=fopen(manderArchi,"r");
    stMessenge sms;
    if(pFile)
    {

    while(fread(&sms,sizeof(stMessenge),1,pFile)>0)
    {
        printf("\nID CONTENT %d\n",sms.idContent);
        printf("\nID ISSU %d\n",sms.idIssuing);
        printf("\nID RECEIVER %d\n",sms.idReceiver);
        printf("\n MENSAJE %s\n",sms.message);
    }
    fclose(pFile);
    }
}

void levantaMensajes (userListMessages arreglo[], int validos, int idUser)
{
    int pos=buscarPosMenssenge(arreglo,validos,idUser);
    int pos1;
    int i=0;
    nodoUserMessenge * seg=arreglo[pos].lista;
    int arreglocargado[50];
    int validosArreglo=0;
    while(seg!=NULL)
    {
        if(seg->messenge.idIssuing==idUser)
        {
            pos1=buscarPosMenssenge(arreglo,validos,seg->messenge.idReceiver);
            arreglocargado[validosArreglo]=arreglo[pos1].userMessenger.idUser;
        }
        else if(seg->messenge.idReceiver==idUser)
        {
            pos1=buscarPosMenssenge(arreglo,validos,seg->messenge.idIssuing);
            arreglocargado[validosArreglo]=arreglo[pos1].userMessenger.idUser;
        }
        seg=seg->following;
        validosArreglo++;
    }
    for(int j=0; j<validosArreglo; j++)
    {
        int prueba=-1;
        int posi=arreglocargado[j]-1;
        printf("\nMensajes de... %s\n",arreglo[posi].userMessenger.userName);
        if(prueba!=arreglocargado[j])
            printf("Pos %d\n",arreglocargado[j]);
        prueba=arreglocargado[j];
    }
}




