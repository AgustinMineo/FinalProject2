#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "time.h"
#include "stUserPost.h"
#include "user.h"

///*************************************************************************/// inicializa la lista de listas (estructura primaria)
nodePostLDL* inicLDL ()
{
    return NULL;
}
////************************************************************************///

///*************************************************************************/// CREA UN NODO
nodePostLDL* createNewNodoToLDL(stUserNew aux)
{
    nodePostLDL* newPostLDL=(nodePostLDL*)malloc(sizeof(nodePostLDL));

    newPostLDL->user.idUser=aux.idUser;
    strcpy(newPostLDL->user.userNamePost,aux.userName);
    newPostLDL->user.points=aux.points;
    newPostLDL->user.userStatus=aux.status;

    newPostLDL->listPost=inicList();
    newPostLDL->follow=inicLDL();

    return newPostLDL;
}
////************************************************************************///


///*************************************************************************/// agrega un nodo nuevo al principio de la lista de listas
nodePostLDL* addFirstLDL(nodePostLDL* listPostLDL,nodePostLDL* newNodeLDL)
{
    newNodeLDL->follow=listPostLDL;

    return newNodeLDL;
}
////************************************************************************///

///*************************************************************************/// agrega un nodo nuevo al final de la lista de listas
nodePostLDL* addLastLDL(nodePostLDL* listPostLDL,nodePostLDL* newNodeLD)
{
    if (listPostLDL==NULL)
    {
        listPostLDL=newNodeLD;
    }
    else
    {
        listPostLDL->follow=addLastLDL(listPostLDL->follow,newNodeLD);
    }
    return listPostLDL;
}
////************************************************************************///

///*************************************************************************///sub-programa que carga la lista de posteos
nodePostLDL* loadUserLDLpost(nodePostLDL* listPostLDL)
{
    if (listPostLDL)
    {
        nodePostLDL* aux=listPostLDL;
        while (aux!=NULL)
        {
            aux->listPost=filePostToListPost("post.dat",aux->listPost,aux->user.idUser);
            aux=aux->follow;
        }
    }
    return listPostLDL;
}
////************************************************************************///

///*************************************************************************///imprime por pantalla la estructura UserPost
void showUserPostLDL (stUserPost post)
{
    printf("ID_User_Contact.........: %d\n",post.idUser);
    printf("User_Name_Post..........: %s\n",post.userNamePost);
    printf("\nPuntos................: %d\n",post.points);
    printf("\nStatus................: %d\n",post.userStatus);
    printf("\n-----------------------------------\n");
}
////************************************************************************///

///*************************************************************************///imprime por pantalla un nodo de la lista de lista (estructura principal)
void showOneNodeLDL (nodePostLDL* nodeLDL)
{
    if (nodeLDL)
    {
        showUserPostLDL(nodeLDL->user);
    }
}
////************************************************************************///

///*************************************************************************///IMPRIME POR PANTALLA LA LISTA COMPLETA
void showListLDL (nodePostLDL* listPostLDL)
{
    if (listPostLDL)
    {
        while (listPostLDL!=NULL)
        {
            showOneNodeLDL(listPostLDL);
            listPostLDL=listPostLDL->follow;
        }
    }
}
////************************************************************************///

///*************************************************************************///
void showAllListPost (nodePostLDL* listPostLDL)
{
    if (listPostLDL)
    {
        showListPublish(listPostLDL->listPost);
        showAllListPost(listPostLDL->follow);
    }
}
////************************************************************************///

///************************************************************************/// CONTAR TAMAÑO DE LA LISTA DE LISTAS
int countLDL (nodePostLDL* listPostLDL)
{
    int count=0;

    if (listPostLDL==NULL)
    {
        count=0;
    }
    else
    {
        count=countListPost(listPostLDL->listPost);
        count=count+countLDL(listPostLDL->follow);
    }

    return count;
}
////************************************************************************///

///*************************************************************************/// BUSCA NODO DE USUARIO EN LDL, SI LO ENCUENTRA DEVUELVE EL NODO Y FLAG=1
nodePostLDL* searchNodeLDL (nodePostLDL* listPostLDL,int userID,int* flag)
{
    *flag=0;
    nodePostLDL* nodeToSearch=inicLDL();

    if (listPostLDL)
    {
        nodePostLDL* seg=listPostLDL;
        while (seg!=NULL && (*flag==0))
        {
            if (seg->user.idUser==userID)
            {
                *flag=1;
                nodeToSearch=seg;
            }
            seg=seg->follow;
        }
    }
    return nodeToSearch;
}
////************************************************************************///

///*************************************************************************/// MUESTRA UN USUARIO BUSCANDOLO POR ID
void showUserPostByUserId (nodePostLDL* listPostLDL,int currentId)
{
    if (listPostLDL->listPost==NULL)
    {
        printf("Lista vacia\n");
    }
    stUserNew user;
    int flag=0;

    nodePostLDL* searchUser=searchNodeLDL(listPostLDL,currentId,&flag);

    if (flag==1)
    {
        user.idUser=searchUser->user.idUser;
        user.points=searchUser->user.points;
        strcpy(user.userName,searchUser->user.userNamePost);
        user.status=searchUser->user.userStatus;
    }

    if (searchUser)
    {
        showListPublish(searchUser->listPost);
    }
}
////************************************************************************///

///*************************************************************************/// CARGA LA LDL (ESTRUCTURA PRINCIPAL) DESDE EL ARBOL
nodePostLDL * arbolUserToLDL (nodoArbol * arbol, nodePostLDL * lista)
{
    nodePostLDL * aux= inicLDL();

    if(arbol!=NULL)
    {
        lista= arbolUserToLDL(arbol->izq,lista);
        aux= createNewNodoToLDL(arbol->user);
        lista= addLastLDL(lista,aux);
        lista= arbolUserToLDL(arbol->der,lista);
    }
    return lista;
}
////************************************************************************///

////**********************************************************************************////
///**********************************MENU DE POSTEOS***********************************///
////**********************************************************************************////
void menuLDL (nodePostLDL* listPostLDL,int currentId,char namePostFile[])
{
    system("cls");
    int menu,control,deletepost;
    stPublish post;
    int flag=0;
    int lastId=searchMaxIdLDL(listPostLDL);

    ///-////////////////////////////////////////////////////// Current Time
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    char currentTIME[50];
    strftime(currentTIME,50,"%d/%m/%y a las %H:%M:%S",tlocal);
    ///-//////////////////////////////////////////////////////

    nodePostLDL* searchNode=searchNodeLDL(listPostLDL,currentId,&flag);

    do
    {
        printf("\n\t Seleccione una accion \n\n");
        printf("\n\t\t [1] - Mis posts \n");
        printf("\n\t\t [2] - Ver post \n");
        printf("\n\t\t [3] - Crear post \n");
        printf("\n\t\t [4] - Editar post \n");
        printf("\n\t\t [5] - Otros  \n");
        if(currentId==-1)
        {
            printf("\n\t\t [6] - Admin\n");
        }
        printf("\n\t\t [0] - Volver al Menu Principal \n");
        printf("\n\n\t\t  ");
        scanf("%d",&menu);

        switch(menu)
        {
        case 1:
            showListPublish(searchNode->listPost);
            break;
        case 2:
            showAllListPost(listPostLDL);
            break;
        case 3:
            post=publishPost(searchNode->listPost,searchNode->user.userNamePost,currentId,currentTIME,&lastId);
            showOnePublish(post);
            searchNode->listPost=addLast(searchNode->listPost,createNewPost(post));
            searchNode->user.points=(searchNode->user.points)+1;
            break;
        case 4:
            editPostMenu(searchNode->listPost,currentId);
            break;
        case 5:
            otherMenu(listPostLDL,currentId,currentTIME);
            break;
        case 6:
            if(currentId==-1)
            {
                adminMenuPost(listPostLDL,currentId);
            }
            else
            {
                printf("Opcion Incorrecta.");
            }
            break;
        }
        printf("\n\n  Cualquier tecla para volver, ESC para menu principal...\n");
        control=getch();
        system("cls");
    }
    while(control!=27);

}
////************************************************************************///

///*************************************************************************///
void adminMenuPost(nodePostLDL* listPostLDL, int currentID)
{
    int control,menu;
    int flag=0;
    int value;
    nodePost* searchNode;
    do
    {
        printf("\n\t Seleccione una accion \n\n");
        printf("\n\t\t [1] - Editar post \n");
        printf("\n\t\t [2] - Dar de baja un post \n");
        printf("\n\t\t [3] - Ver reportes \n");
        printf("\n\t\t [0] - Volver al Menu Principal \n");
        printf("\n\n\t\t  ");
        scanf("%d",&menu);

        switch(menu)
        {
        case 0:
            control=27;
            break;
        case 1:
            adminMenuEditPost(listPostLDL);
            break;
        case 2:
            printf("\n Ingrese la ID del post a dar de baja: \n");
            fflush(stdin);
            scanf("%d",&value);
            nodePostLDL* aux=listPostLDL;
            while(aux && flag==0)
            {
                searchNode=rightPost(aux->listPost,value,&flag);
                aux=aux->follow;
            }
            if(flag==0)
            {
                printf("\n Ingrese un ID de post correcto\n");
            }

            while(flag==0);
            showOneNodePost(searchNode);
            system("pause");
            disablePost(searchNode,value);
            break;
        case 3:
            showReportLDL(listPostLDL);
            break;
        }
        printf("\n\n  Cualquier tecla para volver, ESC para menu principal...\n");
        control=getch();
        system("cls");
    }
    while(control!=27);
}
////************************************************************************///

///*************************************************************************/// MENU DE EDICION DE ADMINISTRADOR
void adminMenuEditPost(nodePostLDL * listPostLDL)
{
    int control,menu,value=0;
    stPublish post;
    nodePost* searchNode;
    char newTitle[30];
    char newDescription[300];
    int newCost;
    char newTime[20];
    char newTopics[30];
    int flag=0;
    showAllListPost(listPostLDL);
    do
    {
        printf("\n\t Seleccione una accion: \n\n");
        printf("\n\t\t[1] - Editar Titulo \n");
        printf("\n\t\t[2] - Editar Descripcion \n");
        printf("\n\t\t[3] - Editar Categoria \n");
        printf("\n\t\t[4] - Editar Valor \n");
        printf("\n\t\t[5] - Editar Horario \n");
        printf("\n\t\t[6] - Editar Lugar \n");
        printf("\n\t\t[7] - Dar de baja una publicacion \n");
        printf("\n\t\t[0] - Volver al Menu Principal \n");
        printf("\n\t\t  ");

        scanf("%d",&menu);

        switch(menu)
        {
        case 0:
            control=27;
            break;
        case 1:
            do
            {
                printf("\n Ingrese la ID del post a modificar: \n");
                fflush(stdin);
                scanf("%d",&value);
                nodePostLDL* aux=listPostLDL;
                while(aux&& flag==0)
                {
                    searchNode=rightPost(aux->listPost,value,&flag);
                    aux=aux->follow;
                }
                if(flag==0)
                {
                    printf("\n Ingrese un ID de post correcto\n");
                }
            }
            while(flag==0);
            showOneNodePost(searchNode);
            system("pause");
            printf("\n  Ingrese el nuevo titulo: \n");
            fflush(stdin);
            gets(newTitle);
            editPostTitle(searchNode,value,newTitle);
            break;
        case 2:
            do
            {
                printf("\n Ingrese la ID del post a modificar: \n");
                scanf("%d",&value);
                nodePostLDL* aux=listPostLDL;
                while(aux&& flag==0)
                {
                    searchNode=rightPost(aux->listPost,value,&flag);
                    aux=aux->follow;
                }
                if(flag==0)
                {
                    printf("\n Ingrese un ID de post correcto\n");
                }
            }
            while(flag==0);
            printf("\n  Ingrese la nueva descripcion: \n");
            fflush(stdin);
            gets(newDescription);
            editPostDescription(searchNode,value,newDescription);
            break;
        case 3:
            do
            {
                printf("\n Ingrese la ID del post a modificar: \n");
                scanf("%d",&value);
                nodePostLDL* aux=listPostLDL;
                while(aux&& flag==0)
                {
                    searchNode=rightPost(aux->listPost,value,&flag);
                    aux=aux->follow;
                }
                if(flag==0)
                {
                    printf("\n Ingrese un ID de post correcto\n");
                }
            }
            while(flag==0);
            printf("\n  Ingrese los nuevos topicos a hablar: \n");
            fflush(stdin);
            gets(newTopics);
            editPostTopics(searchNode,value,newTopics);
            break;
        case 4:
            do
            {
                printf("\n Ingrese la ID del post a modificar: \n");
                scanf("%d",&value);
                nodePostLDL* aux=listPostLDL;
                while(aux&& flag==0)
                {
                    searchNode=rightPost(aux->listPost,value,&flag);
                    aux=aux->follow;
                }
                if(flag==0)
                {
                    printf("\n Ingrese un ID de post correcto\n");
                }
            }
            while(flag==0);
            printf("\n  Ingrese el nuevo valor: \n");
            scanf("%d",&newCost);
            editPostCost(searchNode,value,newCost);
            break;
        case 5:
            do
            {
                printf("\n Ingrese la ID del post a modificar: \n");
                scanf("%d",&value);
                nodePostLDL* aux=listPostLDL;
                while(aux&& flag==0)
                {
                    searchNode=rightPost(aux->listPost,value,&flag);
                    aux=aux->follow;
                }
                if(flag==0)
                {
                    printf("\n Ingrese un ID de post correcto\n");
                }
            }
            while(flag==0);
            printf("\n  Ingrese el nuevo horario: \n");
            fflush(stdin);
            gets(newTime);
            editPostTime(searchNode,value,newTime);
            break;
        case 6:
            do
            {
                printf("\n Ingrese la ID del post a modificar: \n");
                scanf("%d",&value);
                nodePostLDL* aux=listPostLDL;
                while(aux&& flag==0)
                {
                    searchNode=rightPost(aux->listPost,value,&flag);
                    aux=aux->follow;
                }
                if(flag==0)
                {
                    printf("\n Ingrese un ID de post correcto\n");
                }
            }
            while(flag==0);
            editSelectPlace(searchNode,post,value);
            break;
        case 7:
            do
            {
                printf("\n Ingrese la ID del post a modificar: \n");
                scanf("%d",&value);
                nodePostLDL* aux=listPostLDL;
                while(aux&& flag==0)
                {
                    searchNode=rightPost(aux->listPost,value,&flag);
                    aux=aux->follow;
                }
                if(flag==0)
                {
                    printf("\n Ingrese un ID de post correcto\n");
                }
            }
            while(flag==0);
            disablePost(searchNode,value);
            break;
        }
        printf("\n\n  Cualquier tecla para volver, ESC para Menu Principal...\n");
        fflush(stdin);
        control=getch();
        system("cls");
    }
    while(control!=27);
}
////************************************************************************///

///*************************************************************************///OTHER MENU
void otherMenu(nodePostLDL* listPostLDL,int currentID,char currentTIME[])
{
    int menu,control;
    int like;
    int valids;
    int auxIdUser;
    int reportID;
    valids=countLDL(listPostLDL);
    stPublish allPostArray[valids];
    valids=allPostToArray(listPostLDL,allPostArray,valids);

    int flag=0;

    do
    {
        printf("\n\t Seleccione que accion quiere realizar \n\n");
        printf("\n\t\t [1] - Ver 5 post aleatorios \n");
        printf("\n\t\t [2] - Dar like a post \n");
        printf("\n\t\t [3] - Feedback de post \n");
        printf("\n\t\t [4] - Reportar post \n");
        printf("\n\t\t [6] - Salir\n");
        printf("\n\t\t  ");
        scanf("%d",&menu);

        switch(menu)
        {
        case 1:
            randomPost(allPostArray,currentID,valids,5);
            break;
        case 2:
            showAllListPost(listPostLDL);
            printf("Ingrese el post a dar me gusta\n");
            scanf("%d",&like);
            auxIdUser=postLike(allPostArray,like,valids);
            nodePostLDL* searchNode=searchNodeLDL(listPostLDL,auxIdUser,&flag);
            if (searchNode)
            {
                flag=0;
                nodePost* searchPost=searchNodePost(searchNode->listPost,like,&flag);
                if (searchPost)
                {
                    searchPost->post.likes=(searchPost->post.likes+1);
                }
                searchNode->user.points++;
            }
            break;
        case 3:
            feedbackMenu(listPostLDL,currentID,currentTIME);
            break;
        case 4:
            showAllListPost(listPostLDL);
            printf("\n Ingrese el ID del post a reportar\n");
            scanf("%d",&reportID);
            reportPost(listPostLDL,reportID);
            break;
        case 5:
            printf("\n  Saliendo... Presione ESC\n");
            control=27;
            break;
        }
        printf("\nEnter para continuar, ESC para salir.\n");
        fflush(stdin);
        control=getch();
        system("cls");
    }
    while(control!=27);

}
////************************************************************************///

///*************************************************************************/// IdContentToArray
int allPostToArray(nodePostLDL* listPostLDL,stPublish allPostArray[],int dim)
{
    int valids=0;

    if (listPostLDL)
    {
        nodePostLDL* aux=listPostLDL;
        while(aux)
        {
            valids=listToArray(aux->listPost,allPostArray,valids,dim);
            aux=aux->follow;
        }
    }
    return valids;
}
////************************************************************************///


///*************************************************************************/// PERSISTE TODA LA LISTA DE LISTA DE POSTEOS EN EL ARCHIVO "post.dat"
void allListToFile (nodePostLDL* listPostLDL,char nameFile[])
{
    FILE* pFile=fopen(nameFile,"wb");
    if (pFile)
        fclose(pFile);

    if (listPostLDL)
    {
        nodePostLDL* aux=listPostLDL;
        while(aux)
        {
            listToFile(aux->listPost,nameFile);
            aux=aux->follow;
        }
    }
}
////************************************************************************///

///*************************************************************************/// BUSCA EL ULTIMO ID DE LA LISTA COMPLETA
int searchMaxIdLDL (nodePostLDL* listPostLDL)
{
    int maxLDL=0;
    int auxMax;
    if (listPostLDL)
    {
        maxLDL=searchMaxID(listPostLDL->listPost);
        nodePostLDL* aux=listPostLDL->follow;
        while(aux)
        {
            auxMax=searchMaxID(aux->listPost);
            if (auxMax>maxLDL)
            {
                maxLDL=auxMax;
            }
            aux=aux->follow;
        }
    }
    return maxLDL;
}
////************************************************************************///

///*************************************************************************/// FEEDBACK MENU
void feedbackMenu(nodePostLDL* listPostLDL,int currentID,char currentTIME[])
{
    int menu,control;
    int flag=0;
    int value;
    nodePostLDL* userNode=NULL;
    do
    {
        printf("\n\t Seleccione que accion quiere realizar \n\n");
        printf("\n\t\t [1] - Dar feedback \n");
        printf("\n\t\t [2] - Ver feedbacks \n");
        printf("\n\t\t [3] - Salir\n");
        printf("\n\t\t  ");
        scanf("%d",&menu);

        switch(menu)
        {
        case 1:
            system("cls");
            showAllListPost(listPostLDL);
            printf("\n Ingrese el post a cual quiere dar un feedback\n");
            scanf("%d",&value);
            feedback(listPostLDL,currentID,value);
            userNode=searchNodeLDL(listPostLDL,currentID,&flag);
            userNode->user.points=(userNode->user.points)+1;
            break;
        case 2:
            system("cls");
            showAllFeedbackPosts(listPostLDL);
            break;
        case 3:
            printf("\nEnter para continuar, ESC para salir.\n");
            fflush(stdin);
            control=getch();
            system("cls");
            break;
        }
    }
    while(control!=27);
}
////************************************************************************///

///*************************************************************************/// FEEDBACK
void feedback(nodePostLDL* listPostLDL,int currentID,int value)
{
    int flag=0;
    nodePost* nodeToSearch=NULL;

    if (listPostLDL)
    {
        nodePostLDL* aux=listPostLDL;
        while(aux && flag==0)
        {
            nodeToSearch=searchNodePost(aux->listPost,value,&flag);
            aux=aux->follow;
        }
    }
    if (flag)
    {
        printf("\nIngrese su feedback\n");
        fflush(stdin);
        gets(nodeToSearch->post.feedback);
        nodeToSearch->post.idFeedback=currentID;
    }
}

////************************************************************************///

///*************************************************************************/// SHOW FEEDBACK POST
void showAllFeedbackPosts (nodePostLDL* listPostLDL)
{
    if (listPostLDL)
    {
        nodePostLDL* aux=listPostLDL;
        while(aux)
        {
            showFeedbackPosts(aux->listPost);
            aux=aux->follow;
        }
    }
}
////************************************************************************///

///*************************************************************************/// REPORTAR POSTEO
void reportPost (nodePostLDL* listPostLDL,int idContent)
{
    int flag=0;
    nodePost* nodeToSearch=NULL;

    if (listPostLDL)
    {
        nodePostLDL* aux=listPostLDL;
        while(aux && flag==0)
        {
            nodeToSearch=searchNodePost(aux->listPost,idContent,&flag);
            aux=aux->follow;
        }
    }
    if (flag)
    {
        disablePost(nodeToSearch,idContent);
        printf("\nIngrese la razon por el reporte\n");
        fflush(stdin);
        gets(nodeToSearch->post.report);
    }
}
////************************************************************************///

///*************************************************************************/// MOSTRAR REPORTE
void showReportLDL(nodePostLDL* listPostLDL)
{
    if (listPostLDL)
    {
        nodePostLDL* aux=listPostLDL;

        while(aux)
        {
            showReport(aux->listPost);
            aux=aux->follow;
        }
    }
}
////************************************************************************///


