#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include "menus.h"
int editUserPassword(nodoArbol * arbol, int id, char newPassword[]);

int main()
{
    char mainArchivo[] = {"user.dat"};
    char manderArchi[]= {"mensajeria.dat"};
    char namePostFile[]= {"post.dat"};
    int control,menu,validos=0;
    stUserNew arrayUser[30];
    char currentTIME [10];
    getTime(currentTIME);
    printf("\nEL tiempo es: %s\n",currentTIME);
    stUserNew aux;
    int valid=0;
    int i=0;
    int flag;
    int valor=0;
    valid=fileToArray(arrayUser,mainArchivo);
    nodoArbol * userArbol = inicArbol();

    do
    {
        printf("\n\t\t\t\t\t\t\t ==================== \n");
        printf("\n\t\t\t\t\t\t\t  [4] Punteros Remaster   \n");
        printf("\n\t\t\t\t\t\t\t ==================== \n\n\n");
        printf("\n\t\t\t\t\t[1] - Registrate!\n");
        printf("\n\t\t\t\t\t[2] - Inicia Sesion!\n");
        printf("\n\n\n\t\t\t\t\t");
        scanf("%d",&menu);
        switch(menu)
        {
        case 1:
            valid=createUser(arrayUser,valid,currentTIME);
            arrayToFile(arrayUser,valid,mainArchivo);
            break;
        case 2:
            userArbol=arrayToArbol(arrayUser,0,valid,valid);
            login(userArbol,arrayUser,valid,mainArchivo,manderArchi,namePostFile);
            break;
        }
        printf("\n Presione cualquier tecla volver al Inicio, ESC para salir... \n");
        fflush(stdin);
        control=getch();
        system("cls");
    }
    while(control!=27);

    return 0;
}

void login(nodoArbol * arbol, stUserNew arrayUser[], int validos, char mainArchivo[],char manderArchi[],char namePostFile[])
{
    int control;
    char username[30];
    char password[30];
    stUserNew aux;
    int status=0;
    int valor=0;
    int userStatus=0;
    int flag=0;
    do
    {
        do
        {
            printf("\n \t\t\t\t\t*************************************");
            printf("\n \t\t\t\t\t***                               ***");
            printf("\n \t\t\t\t\t*** Ingrese el nombre de Usuario: ***");
            printf("\n \t\t\t\t\t***                               ***");
            printf("\n \t\t\t\t\t*************************************");
            printf("\n \t\t\t\t\t--> ");
            fflush(stdin);
            gets(username);
            printf("\n\n\n");

            if(strlen(username)==0)
            {
                printf("\n\t  Usuario incorrecto, intente nuevamente...");
            }
            else
            {
                aux=buscarNombre(arbol,username,&userStatus);
                if(strcmpi(aux.userName,username)!=0)
                {
                    printf("\n\t  El Usuario ingresado no existe, intente nuevamente...\n");
                    valor=1;
                }
                else
                {
                    valor=0;
                }
            }
        }
        while(valor==1);

        do
        {
            printf("\n \t\t\t\t\t*************************************");
            printf("\n \t\t\t\t\t***                               ***");
            printf("\n \t\t\t\t\t*** Ingrese la contrasenia:       ***");
            printf("\n \t\t\t\t\t***                               ***");
            printf("\n \t\t\t\t\t*************************************");
            printf("\n \t\t\t\t\t--> ");
            fflush(stdin);
            gets(password);

            if(strcmpi(aux.password,password)==0)
            {
                mainMenu(aux.idUser,arbol,arrayUser,validos,mainArchivo,manderArchi,namePostFile);
                status=1;
                flag=1;
            }
            if(status==0)
            {
                printf("\n\t  El password ingresado es incorrecto...\n");
                printf("\n\t  Presione cualquier tecla para volver a intentar, ESC para salir.\n");
                fflush(stdin);
                control=getch();
            }
        }
        while(status==0 && control!=27);
    }
    while(status=0);
}

