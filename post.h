#ifndef POST_H_INCLUDED
#define POST_H_INCLUDED
#include <string.h>
#include "user.h"
#include "gotoxy.h"

typedef struct
{
    int idUserContact;
    int idContent;
    char userNamePost[30];
    char title [30];
    char description[300];
    char categoria[30];
    int likes;
    int active;
    char report[100];
    int cost;
    char time[30];
    char places[100];
    char feedback[60];
    char currentTIME[50];
    int idFeedback;
}stPublish;


///ESTRUCTURA DEL NODO DE LA LISTA SIMPLEMENTE ENLAZADA (ESTRUCTURA SECUNDARIA DE POSTEOS)
typedef struct _nodePost
{
    stPublish post;
    struct _nodePost * follow;
}nodePost;


///DECLARACION DE FUNCIONES:
///FUNCIONES BASICAS PARA EL MANEJO DE LA LISTA DE POSTS (EST. SECUNDARIA)
nodePost* inicList();
nodePost* addFirst(nodePost* listPost, nodePost* newPost);
nodePost* addLast (nodePost* listPost, nodePost* newPost);
void showOneNodePost (nodePost* onePost);
void showListPublish (nodePost* listPost);
int countListPost (nodePost* listPost);
nodePost*createNewPost (stPublish post);///HACE USO DE LA ESTRUCTURA,PERO ES UNA FUNCION BASICA DE LA LISTA
int countListPost (nodePost* listPost);


///FUNCIONES QUE HACEN USO DE LA ESTRUCTURA
nodePost* filePostToListPost (char nameFile[],nodePost* listPost,int currentID);
void selectPlace(stPublish *post);
void statusPublisPost (int postStatus);
stPublish publishPost(nodePost* listPost,char userName[],int currentID,char currentTime[],int* lastId);
nodePost* rightPost(nodePost* listPost,int value,int* flag);
void editPostMenu(nodePost* listPost,int currentID);
void editPostTitle(nodePost* listPost,int value, char newTitle[30]);
void editPostDescription(nodePost* listPost,int value,char newDescription[300]);
void editPostTopics(nodePost* listPost,int value,char newTopics[30]);
void editPostCost(nodePost* listPost,int value,int newCost);
void editPostTime(nodePost* listPost,int value,char newTime[]);
void disablePost(nodePost* listPost, int value);
void editSelectPlace(nodePost* node,stPublish post, int value);
int listToArray (nodePost* listPost,stPublish [],int valids,int dim);
void listToFile (nodePost* listPost,char nameFile[]);
nodePost* searchNodePost(nodePost* listPost,int idContent,int* flag);
void showFeedbackPosts(nodePost* listPost);
void showReport(nodePost* listPost);


///FUNCIONES DE LA ESTRUCTURA
void showOnePublish(stPublish);
void getTime(char currentTIME[]);
void randomPost(stPublish allPostArray[],int currentID,int valids,int cant);
int postLike(stPublish allPostArray[],int like,int valids);
int getLastId (char nameFile[]);
//int publishPost(nodePostLDL* listPostLDL,int currentID);


#endif // POST_H_INCLUDED
