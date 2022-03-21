#ifndef STUSERPOST_H_INCLUDED
#define STUSERPOST_H_INCLUDED
#include "post.h"
#include "user.h"
#include "arbolUser.h"
typedef struct
{
   int idUser;            /// id usuario actual.
   char userNamePost[30]; /// nombre del usuario actual.
   int points;            /// variable de puntos.
   int userStatus;        /// status del usuario activo o desactivado.
} stUserPost;


///ESTRUCTURA DEL NODO DE LA LISTA DE LISTAS (ESTRUCTURA PRIMARIA)
typedef struct _NodePostLDL
{
    stUserPost user;
    nodePost * listPost;
    struct _NodePostLDL* follow;
} nodePostLDL;


///DECLARACION DE FUNCIONES:
///FUNCIONES BASICAS PARA EL MANEJO DE LA LISTA DE lISTA DE POSTS (EST. PRIMARIA)
nodePostLDL* inicLDL ();
nodePostLDL* addFirstLDL(nodePostLDL*,nodePostLDL*);
nodePostLDL* addLastLDL(nodePostLDL*,nodePostLDL*);
void showListLDL (nodePostLDL* listPost);
void allListToFile (nodePostLDL* listPostLDL,char nameFile[]);
nodePostLDL* createNewPostLDL(stUserPost);///HACE USO DE LA ESTRUCTURA,PERO ES UNA FUNCION BASICA DE LA LISTA DE LISTA
void feedbackMenu(nodePostLDL* listPostLDL,int currentID,char currentTIME[]);
void showAllFeedbackPosts (nodePostLDL* listPostLDL);

///FUNCIONES QUE HACEN USO DE LA ESTRUCTURA
nodePostLDL* fileUserToLDL (char[],nodePostLDL*);
nodePostLDL* loadUserLDLuser(nodePostLDL* listPostLDL,stUserPost userPost);
nodePostLDL* loadUserLDLpost(nodePostLDL* listPostLDL);
nodePostLDL* searchNodeLDL (nodePostLDL* listPostLDL,int userID,int* flag);
void showOneNodeLDL (nodePostLDL* post);
void showUserPostByUserId (nodePostLDL* listPostLDL,int userId);
void menuLDL (nodePostLDL* listPostLDL,int currentId,char namePostFile[]);
void otherMenu(nodePostLDL* listPostLDL,int currentID,char currentTIME[]);
void feedback(nodePostLDL* listPostLDL,int currentID,int value);
void reportPost (nodePostLDL* listPostLDL,int idContent);
void showReportLDL(nodePostLDL* listPostLDL);
nodePostLDL* createNewNodoToLDL(stUserNew aux);
nodePostLDL * arbolUserToLDL (nodoArbol * arbol, nodePostLDL * lista);
void adminMenuEditPost(nodePostLDL*listPostLDL);

///FUNCIONES DE LA ESTRUCTURA
void showUserPostLDL (stUserPost post);
stUserPost loadUserPost(stPublish);
int searhMaxIdLDL (nodePostLDL* listPostLDL);
int searchMaxIdLDL (nodePostLDL* listPostLDL);
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

#endif // STUSERPOST_H_INCLUDED
