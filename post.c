#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include "gotoxy.h"
#include "post.h"
#include "stUserPost.h"

///*************************************************************************/// inicializa la lista simplemente enlazada (estructura secundaria)
nodePost* inicList()
{
    return NULL;
}
////************************************************************************///

///*************************************************************************/// crea un nuevo nodo de la lista simplemente enlazada
nodePost* createNewPost (stPublish post)
{
    nodePost* newPost= (nodePost*)malloc(sizeof(nodePost));
    newPost->post=post;
    newPost->follow=inicList();
    return newPost;
}
////************************************************************************///

///*************************************************************************/// agrega un nodo al principio de la lista
nodePost* addFirst (nodePost* listPost, nodePost* newPost)
{
    newPost->follow=listPost;
    return newPost;
}
////************************************************************************///

///*************************************************************************/// agrega un nodo al final de la lista (recursiva)
nodePost* addLast (nodePost* listPost,nodePost* newPost)
{
    if (listPost==NULL)
    {
        listPost=newPost;
    }
    else
    {
        listPost->follow=addLast(listPost->follow,newPost);
    }
    return listPost;
}
////************************************************************************///

///*************************************************************************/// imprime por pantalla la estructura Publish
void showOnePublish(stPublish post)
{
    printf("\n\t\t **\n");
    printf("\n\t\t -----------------------------------------------------------------------------------------\n");
    printf("\n\t\t El post se publico: %s\n",post.currentTIME);
    printf("\n\t\t\t\t\t\t\t\t\t\t\t  %s\n",post.userNamePost);
    printf("\n\t\t ID post: %d\n", post.idContent);
    printf("\n\t\t\t\t\t\t\t %s \n",post.title);
    printf("\n\t\t--------------------------------------------------------------------------------------------");
    printf("\n\t\t Descripcion: %s \n", post.description);
    printf("\n\t\t--------------------------------------------------------------------------------------------");
    printf("\n\t\t Las tematicas a tratar seran: %s \n",post.categoria);
    printf("\n\t\t--------------------------------------------------------------------------------------------");
    printf("\n\t\t Localizacion : %s \n",post.places);
    printf("\n\t\t--------------------------------------------------------------------------------------------");
    printf("\n\t\t El horario de la reunion sera: %s",post.time);
    printf("\n \t\t Likes de la publicacion: %d",post.likes);
    printf("\n\t\t\t\t\t\t\t\t\t\t  El valor es: $%d\n",post.cost);
    printf("\n\t\t -----------------------------------------------------------------------------------------\n");
    printf("\n\t\t **\n");
}
////************************************************************************///

///*************************************************************************/// imprime por pantalla un nodo
void showOneNodePost (nodePost* onePost)
{
    if (onePost && onePost->post.active!=0)
        showOnePublish(onePost->post);
}
////************************************************************************///

///*************************************************************************/// imprime por pantalla la lista
void showListPublish (nodePost* listPost)
{
    if(listPost)
    {
        showOneNodePost(listPost);
        showListPublish(listPost->follow);
    }
}
////************************************************************************///

///*************************************************************************/// funcion que levanta del archivo "publish.dat" los posteos
nodePost* filePostToListPost (char nameFile[],nodePost* listPost,int currentID)
{
    FILE * pFile=fopen(nameFile,"rb");
    stPublish post;

    if(pFile)
    {
        while (fread(&post,sizeof(stPublish),1,pFile)>0)
        {
            if (post.idUserContact==currentID)
            {
                listPost=addLast(listPost,createNewPost(post));
            }
        }
    }
    fclose(pFile);

    return listPost;
}
////************************************************************************///

////************************************************************************////
///******************************MENU DE POSTEOS****************************////
////************************************************************************////

///*************************************************************************/// CREAR UN NUEVO POSTEO
stPublish publishPost(nodePost* listPost,char userName[],int currentID,char currentTime[],int* lastId)
{
    int postStatus=0;
    int iDpost=(*lastId);
    stPublish post;

    strcpy(post.currentTIME,currentTime);

    system("cls");
    gotoxy(5,6);
    printf("Titulo del posteo: \n\n");
    gotoxy(5,8);
    printf("Ingrese una breve descripcion de su persona: \n\n");
    gotoxy(5,10);
    printf("Ingrese el valor requerido: \n\n");
    gotoxy(5,12);
    printf("Hora del encuentro: \n\n");
    gotoxy(5,14);
    printf("Ingrese tematica a charlar: \n\n");
    gotoxy(5,16);
    printf("Ingrese lugar del encuentro: \n\n");

    iDpost++;
    strcpy(post.userNamePost,userName);
    post.idContent=iDpost;
    post.idUserContact=currentID;
    post.active=1;
    postStatus=1;
    post.likes=0;

    gotoxy(30,6);
    fflush(stdin);
    gets(post.title);
    gotoxy(50,8);
    fflush(stdin);
    gets(post.description);
    gotoxy(50,10);
    fflush(stdin);
    scanf("%d",&post.cost);
    gotoxy(50,12);
    fflush(stdin);
    scanf("%s",post.time);
    gotoxy(50,14);
    fflush(stdin);
    gets(post.categoria);

    selectPlace(&post);

    strcpy(post.report,"NULL");
    strcpy(post.feedback,"NULL");
    strcpy(post.report,"NULL");
    post.idFeedback=0;
    (*lastId)+=1;
    statusPublisPost(postStatus);
    return post;
}
////************************************************************************///

///*************************************************************************/// ELEGIR EL LUGAR DE ENCUENTRO
void selectPlace(stPublish *post)
{
    int menu;
    printf("\n\n\n\t  Seleccione un sitio: \n\n");
    printf("\n [1]  - La Fonte D큀ro || Colon y Buenos Aires \n");
    printf("\n [2]  - La Fonte D큀ro || Constitucion y Tejedor \n");
    printf("\n [3]  - La Fonte D큀ro || Luro y 180 \n");
    printf("\n [4]  - La Fonte D큀ro || Urquiza y la Costa \n");
    printf("\n [5]  - Cafe Martinez  || Colon 3651 - 7 a 22 \n");
    printf("\n [6]  - Di Mero Espresso Cafeteria || Martin Miguel de Guemes 2483 - 7 a 20 \n");
    printf("\n [7]  - ADORADO Cafe & Bar || Paseo Aldrey - 8 a 20 \n");
    printf("\n [8]  - De Postres || Carlos Alvear 2889 \n");
    printf("\n [9]  - Croissant Cafe || Cordoba 2361 \n");
    printf("\n [10] - Adorado Cafe || Independencia 2546 \n");
    do
    {
        scanf("%d",&menu);
        switch(menu)
        {
        case 1:
            strcpy((*post).places,"La Fonte D큀ro - Colon y Buenos Aires");
            break;
        case 2:
            strcpy((*post).places,"La Fonte D큀ro - Constitucion y Tejedor");
            break;
        case 3:
            strcpy((*post).places,"La Fonte D큀ro - Luro y 180");
            break;
        case 4:
            strcpy((*post).places,"La Fonte D큀ro - Urquiza y la Costa");
            break;
        case 5:
            strcpy((*post).places,"Cafe Martinez - Colon 3651 - 7 a 22");
            break;
        case 6:
            strcpy((*post).places,"Di Mero Espresso Cafeteria - Martin Miguel de Guemes 2483 - 7 a 20");
            break;
        case 7:
            strcpy((*post).places,"ADORADO Cafe & Bar - Paseo Aldrey - 8 a 20");
            break;
        case 8:
            strcpy((*post).places,"De Postres - Carlos Alvear 2889");
            break;
        case 9:
            strcpy((*post).places,"Croissant Cafe - Cordoba 2361");
            break;
        case 10:
            strcpy((*post).places,"Adorado Cafe - Independencia 2546");
            break;
        }
        if(menu<0 && menu>=11)
        {
            printf("\n  La opcion ingresada no se encuentra, intente nuevamente...\n");
        }
    }
    while(menu>0 && menu>=11);
}
////************************************************************************///

///*************************************************************************/// RETORNA EL ESTATUS DE LA PUBLICACION
void statusPublisPost (int postStatus)
{
    if (postStatus==1)
    {
        printf("\n\t\t El post se ha publicado exitosamente!\n\n");
    }
    else
    {
        printf("\n\t\t El post no pudo publicarse, intente nuevamente...\n\n");
    }
}
////************************************************************************///

///************************************************************************/// MENU SECUNDARIO DE LA ESTRUCTURA DE POSTS - MENU DE EDICION
void editPostMenu(nodePost* listPost,int currentID)
{
    stPublish post;
    int menu;
    int control;
    int value=0;
    char newTitle[30];
    char newDescription[300];
    int newCost;
    char newTime[20];
    char newTopics[30];
    int flag=0;
    nodePost* searchNode;

    showListPublish(listPost);
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
        case 1:
            do
            {
                printf("\n Ingrese la ID del post a modificar: \n");
                fflush(stdin);
                scanf("%d",&value);
                searchNode=rightPost(listPost,value,&flag);
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
                searchNode=rightPost(listPost,value,&flag);
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
                searchNode=rightPost(listPost,value,&flag);
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
                searchNode=rightPost(listPost,value,&flag);
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
                searchNode=rightPost(listPost,value,&flag);
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
                searchNode=rightPost(listPost,value,&flag);
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
                searchNode=rightPost(listPost,value,&flag);
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

///************************************************************************/// DEVUELVE UNA BANDERA EN 1 SI EL ID INGRESADO ES VALIDO
nodePost* rightPost(nodePost* listPost,int value,int* flag)
{
    *flag=0;
    nodePost* searchNode;

    if(listPost)
    {
        nodePost* aux=listPost;
        while(aux!=NULL && (*flag)==0)
        {
            if (aux->post.idContent==value)
            {
                *flag=1;
                searchNode=aux;
            }
            aux=aux->follow;
        }
    }
    return searchNode;
}
////************************************************************************///

///*************************************************************************/// EDITAR TITULO
void editPostTitle(nodePost* node,int value, char newTitle[30])
{
    if (node)
        strcpy(node->post.title,newTitle);
}
////************************************************************************///

///*************************************************************************/// EDITAR DESCRIPCION
void editPostDescription(nodePost* node,int value,char newDescription[300])
{
    if (node && (node->post.idContent==value))
    {
        strcpy(node->post.description,newDescription);
    }
}
////************************************************************************///

///*************************************************************************/// EDITAR CATEGORIA
void editPostTopics(nodePost* node,int value,char newTopics[30])
{
    if (node && (node->post.idContent==value))
    {
        strcpy(node->post.categoria,newTopics);
    }
}
////************************************************************************///

///*************************************************************************/// EDITAR HORARIO
void editPostTime(nodePost* node,int value,char newTime[])
{
    if (node && (node->post.idContent==value))
    {
        strcpy(node->post.time,newTime);
    }
}
////************************************************************************///

///*************************************************************************/// BAJA PUBLICACIO
void disablePost(nodePost* node, int value)
{
    if (node && (node->post.idContent==value))
    {
        node->post.active=0;
        strcpy(node->post.report,"Baja");
    }
}
////************************************************************************///

///*************************************************************************/// EDITAR VALOR
void editPostCost(nodePost* node,int value, int newCost)
{
    if (node && (node->post.idContent==value))
    {
        node->post.cost=newCost;
    }
}
////************************************************************************///

///*************************************************************************/// EDITAR LUGAR
void editSelectPlace(nodePost* node,stPublish post, int value)
{
    int menu;

    printf("\n\t  Seleccione un sitio: \n\n");
    printf("\n [1]  - La Fonte D큀ro || Colon y Buenos Aires \n");
    printf("\n [2]  - La Fonte D큀ro || Constitucion y Tejedor \n");
    printf("\n [3]  - La Fonte D큀ro || Luro y 180 \n");
    printf("\n [4]  - La Fonte D큀ro || Urquiza y la Costa \n");
    printf("\n [5]  - Cafe Martinez  || Colon 3651 - 7 a 22 \n");
    printf("\n [6]  - Di Mero Espresso Cafeteria || Martin Miguel de Guemes 2483 - 7 a 20 \n");
    printf("\n [7]  - ADORADO Cafe & Bar || Paseo Aldrey - 8 a 20 \n");
    printf("\n [8]  - De Postres || Carlos Alvear 2889 \n");
    printf("\n [9]  - Croissant Cafe || Cordoba 2361 \n");
    printf("\n [10] - Adorado Cafe || Independencia 2546 \n");
    do
    {
        scanf("%d",&menu);
        switch(menu)
        {
        case 1:
            strcpy(post.places,"La Fonte D큀ro - Colon y Buenos Aires");
            break;
        case 2:
            strcpy(post.places,"La Fonte D큀ro - Constitucion y Tejedor");
            break;
        case 3:
            strcpy(post.places,"La Fonte D큀ro - Luro y 180");
            break;
        case 4:
            strcpy(post.places,"La Fonte D큀ro - Urquiza y la Costa");
            break;
        case 5:
            strcpy(post.places,"Cafe Martinez - Colon 3651 - 7 a 22");
            break;
        case 6:
            strcpy(post.places,"Di Mero Espresso Cafeteria - Martin Miguel de Guemes 2483 - 7 a 20");
            break;
        case 7:
            strcpy(post.places,"ADORADO Cafe & Bar - Paseo Aldrey - 8 a 20");
            break;
        case 8:
            strcpy(post.places,"De Postres - Carlos Alvear 2889");
            break;
        case 9:
            strcpy(post.places,"Croissant Cafe - Cordoba 2361");
            break;
        case 10:
            strcpy(post.places,"Adorado Cafe - Independencia 2546");
            break;
        }
        if(menu>0 && menu>=11)
        {
            printf("\n  La opcion ingresada no se encuentra, intente nuevamente...\n");
        }
    }
    while(menu>0 && menu>=11);

    if (node && (node->post.idContent==value))
    {
        strcpy(node->post.places,post.places);
    }
}
////************************************************************************///

///************************************************************************/// DEVUELVE LA CANTIDAD DE ELEMENTOS QUE TIENE LA LISTA
int countListPost (nodePost* listPost)
{
    int count=0;
    if (listPost==NULL)
    {
        count=0;
    }
    else
    {
        count=1+countListPost(listPost->follow);
    }
    return count;
}
////************************************************************************///

///*************************************************************************/// PASAR LOS POSTEOS A UN ARREGLO
int listToArray (nodePost* listPost,stPublish array[],int valids,int dim)
{
    if (listPost)
    {
        nodePost* aux=listPost;
        while (aux!=NULL && valids<dim)
        {
            if (valids==0)
            {
                array[0]=aux->post;
            }
            else if(aux->post.idContent<array[valids-1].idContent)
            {
                array[valids]=array[valids-1];
                array[valids-1]=aux->post;
            }
            else
            {
                array[valids+1]=aux->post;
            }
            valids++;
            aux=aux->follow;
        }
    }

    return valids;
}
////************************************************************************///

///************************************************************************/// RANDOM POST
void randomPost(stPublish allPostArray[],int currentID,int valids,int cant)
{
    srand (time(NULL));
    int i=0;
    int flag=0;
    int random;
    while(i<cant && i<valids)
    {
        do
        {
            random=rand()%valids;
            if (allPostArray[random].active==1)
            {
                showOnePublish(allPostArray[random]);
                flag=1;
            }
        }
        while(flag==0);
        i++;
    }
}
////************************************************************************///

///*************************************************************************/// POST LIKE
int postLike(stPublish allPostArray[],int like,int valids)
{
    int i=0;
    int flag=0;
    int idUser;

    while (i<valids && flag==0)
    {
        if (allPostArray[i].idContent==like)
        {
            idUser=allPostArray[i].idUserContact;
            flag=1;
        }
        i++;
    }
    return idUser;
}
////************************************************************************///

///*************************************************************************/// PASA LOS DATOS DE UNA LISTA DE POST AL ARCHIVO
void listToFile (nodePost* listPost,char nameFile[])
{
    FILE* pFile=fopen(nameFile,"ab");
    stPublish post;
    if (pFile)
    {
        while(listPost)
        {
            post=listPost->post;
            fwrite(&post,sizeof(stPublish),1,pFile);
            listPost=listPost->follow;
        }
    }
    fclose(pFile);
}
////************************************************************************///

///*************************************************************************/// GET LAST ID_POST
int getLastId (char nameFile[])
{
    FILE *pFile = fopen(nameFile,"rb");
    stPublish post;
    int lastId=0;
    if (pFile && fread(&post,sizeof(stPublish),1,pFile)>0)
    {
        fseek(pFile,-1*sizeof(stPublish),SEEK_END);
        fread(&post,sizeof(stPublish),1,pFile);
        lastId=post.idContent;
    }
    fclose(pFile);

    return lastId;
}
////************************************************************************///

///*************************************************************************/// DEVUELVE EL MAXIMO VALOR DE ID DEL CURRENT USUARIO
int searchMaxID (nodePost* listPost)
{
    int max=0;
    if (listPost)
    {
        max=listPost->post.idContent;
        nodePost* aux=listPost->follow;
        while (aux)
        {
            if (aux->post.idContent>max)
            {
                max=aux->post.idContent;
            }
            aux=aux->follow;
        }
    }
    return max;
}
////************************************************************************///

///*************************************************************************/// BUSCA UN POSTEO POR ID
nodePost* searchNodePost(nodePost* listPost,int idContent,int* flag)
{
    nodePost* searchNode=NULL;
    *flag=0;
    if (listPost)
    {
        nodePost* aux=listPost;
        while(aux && *flag==0)
        {
            if (aux->post.idContent==idContent)
            {
                searchNode=aux;
                *flag=1;
            }
            aux=aux->follow;
        }
    }
    return searchNode;
}
////************************************************************************///

///*************************************************************************/// MUESTRA EL FEEDBACK DE LOS POSTEOS DEL USUARIO
void showFeedbackPosts(nodePost* listPost)
{
    if (listPost)
    {
        nodePost* aux=listPost;
        if(aux && aux->post.active==1 && strlen(aux->post.feedback)>5)
        {
            printf("\n\t\t********************************************************************\n");
            printf("\n\t\t Feedback realizado por: %s \n",listPost->post.userNamePost);
            printf("\n\t\t ID del post: %d \n",listPost->post.idContent);
            printf("\n\t\t Titulo del post: %s \n",listPost->post.title);
            printf("\n\t\t Descripcion: %s \n",listPost->post.description);
            printf("\n\t\t Feedback: %s \n",listPost->post.feedback);
            printf("\n\t\t********************************************************************\n");
        }
    }
}
////************************************************************************///

///*************************************************************************/// MUESTRA POSTEOS REPORTADOS
void showReport(nodePost* listPost)
{
    if (listPost)
    {
        nodePost* aux=listPost;
        while (aux)
        {
            if (aux->post.active!=1 && strlen(aux->post.report)>4)
            {
                printf("\n\t\t**********************************************************\n");
                showOnePublish(aux->post);
                printf("\n\t\t Razon del reporte: %s\n",aux->post.report);
                printf("\n\t\t**********************************************************\n");
            }
            aux=aux->follow;
        }
    }
}
////************************************************************************///
