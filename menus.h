#ifndef MENUS_H_INCLUDED
#define MENUS_H_INCLUDED
#include <stdint.h>
#include "arbolUser.h"
#include "user.h"
#include "stUserPost.h"
#include "stUserMessenge.h"


void mainMenu(int idUser,nodoArbol * arbol, stUserNew arrayUser[], int validos,char mainArchivo[],char manderArchi[],char namePostFile[]);
void editUserMenu(int idUser,nodoArbol * arbol, stUserNew arrayUser[],int validos,stUserNew arrayAlter[],char mainArchivo[]);
void getTime(char currentTIME[]);
void adminEditMenu(nodoArbol * arbol);
void editUserAdmin(nodoArbol * arbol, int idUserEditar);
void inbox (userListMessages arreglo[],int validosMessages, int idUser,char manderArchi[]);

#endif // MENUS_H_INCLUDED
