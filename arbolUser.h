#ifndef ARBOLUSER_H_INCLUDED
#define ARBOLUSER_H_INCLUDED

#include "stUserMessenge.h"
#include "user.h"
typedef struct _nodoArbol
{
    stUserNew user;
    struct _nodoArbol *izq;
    struct _nodoArbol *der;
}nodoArbol;

int editUserPassword(nodoArbol * arbol, int id, char newPassword[]);
int validateEmailArbol(nodoArbol *arbol,char newEmail[]);
int editUserCity(nodoArbol * arbol, int id, char newCity[]);
int editUserAge(nodoArbol * arbol, int id);
int editUserEmail(nodoArbol * arbol, int id, char newEmail[]);
int editUserGender(nodoArbol * arbol, int id, char newGender[]);
int editUserStatus(nodoArbol * arbol, int id, int status);
void editPlaceholder(int flag, char valor[]);
int arbolToArreglo(nodoArbol * arbol, stUserNew arrayUser[],int validos);
int arbolToArregloM(nodoArbol * arbol, userListMessages arrayUserm[],int validos);
int rankUser(stUserNew user,char ranki[]);
void actualizarRanki(nodoArbol * arbol, int id);
void mostrarNombreyID(stUserNew user);
void mostrarInfoUser(nodoArbol * arbol);
void arrayToFileLast(stUserNew arrayUser [], int valid, char mainArchivo []);
void rotateArray(stUserNew arrayUser[], int validos);
int arbolToArregloUser(nodoArbol *arbol,stUserNew arrayUser[],int validos);
int cargarArregloDelArbol (nodoArbol * arbol, userListMessages arrayUser[],int validos);
///-//////////////////////////////////////////////////-EDIT USER-/////////////////////////////////////////////-///
void editPlaceholder(int flag, char valor[]);
int editUserStatus(nodoArbol * arbol, int id, int status);
int editUserGender(nodoArbol * arbol, int id, char newGender[]);
int editUserEmail(nodoArbol * arbol, int id, char newEmail[]);
int editUserAge(nodoArbol * arbol, int id);
int editUserCity(nodoArbol * arbol, int id, char newCity[]);
int editUserPassword(nodoArbol * arbol, int id, char newPassword[]);
///-//////////////////////////////////////////////////-MOSTRAR ARBOL-/////////////////////////////////////////-///
void inorder (nodoArbol * arbol);
void postorder(nodoArbol * arbol);
void preorder(nodoArbol * arbol);
///-//////////////////////////////////////////////////-MOSTRAR ARBOL-/////////////////////////////////////////-///
///-//////////////////////////////////////////////////-EDIT USER-/////////////////////////////////////////////-///
stUserMessenge searchIDMessange(nodoArbol* arbol, int idUser);
stUserNew searchID(nodoArbol* arbol, int idUser);
stUserNew getUsuario(nodoArbol * arbol, int idUser);
stUserNew buscarNombre(nodoArbol * arbol, char nombre[],int *userStatus);
nodoArbol * insertar(nodoArbol * arbol, stUserNew user);
nodoArbol * inicArbol();
nodoArbol * crearNodoArbol(stUserNew user);
nodoArbol * buscar(nodoArbol * arbol, char userName[]);
nodoArbol* arrayToArbol (stUserNew a[], int base, int tope, int valid);
///-/////////////////////////////////////- ADMIN -///////////////////////////////////////////////////////-///
int editUserApellido(nodoArbol * arbol, int id, char apellido[]);
int editUserEdad(nodoArbol * arbol, int id, int edad);
int editarNameUser(nodoArbol * arbol, int id, char nombre[]);
int editUserUsername(nodoArbol * arbol, int id, char nombreUsuario[]);
int editUserDNI(nodoArbol * arbol, int id, int dni);
int editUserPoints(nodoArbol * arbol, int id, int points);
///-/////////////////////////////////////- ADMIN -///////////////////////////////////////////////////////-///
userListMessages * inicLisMessenge();
int fileToArrayMessenge (char mainArchivoMessange [], stUserMessenge arrayMessenge[], int validMessenge);
void showUserConectingMessenge(userListMessages arrayMessenge[],int validMessenge);
int enviarMensaje(userListMessages arreglo[],int validosMessages,char userEnviar[], int idUser);
void mostrarArregloDeMensajesPendientes (stUserMessenge arregloMensajes[],int validos);
int buscarUsuarioMensajeArreglo (char nombre[], stUserMessenge arregloMensajes[], int validos);
void enviarMensajeAdmin(int idUser,int validosMessages,userListMessages arreglo[]);
void ingresarChat(nodoUserMessenge * lista,userListMessages arreglo[], int validos,char userEnviar[],int idUser);
void todoArregloAlArchivo (userListMessages arreglo[],int validos, char manderArchi[]);
void arregloCompletoArchivo (nodoUserMessenge * lista,char manderArchi[],int validos, userListMessages arreglo[]);
void levantaMensajes (userListMessages arreglo[], int validos, int idUser);
nodoUserMessenge* loadUserMessange(userListMessages* lista, char manderArchi[]);
void inicUserMenssange (userListMessages arreglo[],int validos);
int buscarPosMenssenge(userListMessages arreglo[],int validosMessages,int idUser);
userListMessages * crearNodoArregloLista(stUserMessenge userMessenge);
int buscarUsuarioMensajes (userListMessages arreglo[], int validos, char userMensajes[]);
int agregarUsuarioMensajes (userListMessages arreglo[], int validos, stUserMessenge userMensajes);
int cargarArreglo (nodoArbol * arbol,userListMessages arreglo[], int validos,stUserNew user);
#endif // ARBOLUSER_H_INCLUDED
