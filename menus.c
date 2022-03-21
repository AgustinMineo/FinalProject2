#include "menus.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stUserPost.h"
#include "messenge.h"
#include "stUserMessenge.h"
#include "arbolUser.h"


void mainMenu(int idUser,nodoArbol * arbol, stUserNew arrayUser[], int validos,char mainArchivo[],char manderArchi[],char namePostFile[])
{
    int statusArray=0;
    int idContent;
    int pos=0;
    int menu,control;
    int validosMessages=0;
    userListMessages arreglo[30];
    stUserNew arrayAlter[50];
    nodePostLDL * listaUsers=inicLDL();
    /// Actualizamos el ranking
    actualizarRanki(arbol,idUser);
    /// Actualizamos el ranking
    listaUsers= arbolUserToLDL(arbol,listaUsers);
    listaUsers=loadUserLDLpost(listaUsers);
    system("cls");
    do
    {
        printf("\n\t Bienvenido, que desea consultar? \n\n");
        printf("\n\t\t [1] - Casilla de Mensajes \n");
        printf("\n\t\t [2] - Posts \n");
        printf("\n\t\t [3] - Editar perfil \n");
        printf("\n\t\t [4] - Cerrar sesion \n");
        printf("\n\t\t  ");
        scanf("%d",&menu);

        switch(menu)
        {
        case 1:

            validosMessages=cargarArregloDelArbol(arbol,arreglo,0);
            inicUserMenssange (arreglo,validos);
            pos=buscarPosMenssenge(arreglo,validosMessages,idUser);
            arreglo[pos].lista=archivoAListaMensaje(arreglo,validos,manderArchi,idUser);
            inbox (arreglo,validosMessages,idUser,manderArchi);
            break;
        case 2:

            menuLDL(listaUsers,idUser,namePostFile);
            allListToFile(listaUsers,"post.dat");
            break;
        case 3:
            statusArray=1;
            editUserMenu(idUser,arbol,arrayUser,validos,arrayAlter,mainArchivo);
            break;
        case 4:
            if(statusArray==1)
            {
                arrayToFileLast(arrayAlter,validos,mainArchivo);
            }
            todoArregloAlArchivo (arreglo,validosMessages,manderArchi);

            printf("\n  Saliendo... Presione ESC\n");
            control=27;
            exit(0);
            break;
        }

        system("cls");
    }
    while(control!=27);
}

void editUserMenu(int idUser,nodoArbol * arbol, stUserNew arrayUser[],int validos,stUserNew arrayAlter[],char mainArchivo[])
{
    stUserNew aux;
    system("cls");
    int menu,control,flag=0;
    char newGender[30];
    char newPassword[30];
    char newCity[50];
    char newPlaces[150];
    char newEmail[50];
    int validosAlter=0;

    do
    {
        printf("\n\t Editar Perfil: \n\n\n");
        printf("\n\t\t[1] - Cambiar Password \n");
        printf("\n\t\t[2] - Cambiar Ciudad \n");
        printf("\n\t\t[3] - Cambiar Edad \n");
        printf("\n\t\t[4] - Cambiar E-mail\n");
        printf("\n\t\t[5] - Cambiar Percepcion de genero\n");
        printf("\n\t\t[6] - Mostrar Perfil\n");
        printf("\n\t\t[7] - Dar de baja la cuenta\n");
        if(idUser==-1)
        {
            printf("\n\t\t[8] - User Admin\n");
        }
        printf("\n\t\t[0] - Volver al Menu Principal\n");
        printf("\n\n\t\t  ");

        scanf("%d",&menu);
        switch(menu)
        {
        case 0:
            if(validosAlter>0)
            {
                arrayAlter=NULL;
                validosAlter=0;
            }
            validosAlter=arbolToArregloUser(arbol,arrayAlter,validosAlter);
            rotateArray(arrayAlter,validosAlter);
            control=27;
            break;
        case 1:
            printf("\n\t  Ingrese el nuevo Password: \n");
            printf("\n\n\t  ");
            fflush(stdin);
            gets(newPassword);
            flag=editUserPassword(arbol,idUser,newPassword);
            editPlaceholder(flag,"Password");
            break;
        case 2:
            printf("\n\t  Ingrese su nueva locacion: \n");
            printf("\n\n\t  ");
            fflush(stdin);
            gets(newCity);
            flag=editUserCity(arbol,idUser,newCity);
            editPlaceholder(flag,"Localizacion");
            break;
        case 3:
            flag=editUserAge(arbol,idUser);
            editPlaceholder(flag,"Edad");
            break;
        case 4:
            do
            {
                printf("\n\t  Ingrese el nuevo correo electronico: \n");
                printf("\n\n\t  ");
                fflush(stdin);
                gets(newEmail);
                flag=validateEmailArbol(arbol,newEmail);
                if(flag==1)
                {
                    flag=editUserEmail(arbol,idUser,newEmail);
                    editPlaceholder(flag,"Correo Electronico");
                }
                else
                {
                    printf("\n El correo ya esta registrado\n");
                }
            }
            while(flag==0);
            break;
        case 5:
            printf("\n\t  Ingrese su percepcion de genero: \n");
            printf("\n\n\t  ");
            fflush(stdin);
            gets(newGender);
            flag=editUserGender(arbol,idUser,newGender);
            editPlaceholder(flag,"Genero");
            break;
        case 6:
            aux=getUsuario(arbol,idUser);
            showMyUser(aux);
            break;
        case 7:
            if(idUser!=-1)
            {
                while(control!=27 && flag==0)
                {
                    printf("\n\t  Esta seguro que quiere darse de baja? \n\n");
                    printf("\n\t  Intro para confirmar, ESC para volver.\n");
                    fflush(stdin);
                    control=getch();
                    flag=editUserStatus(arbol,idUser,0);
                    if(flag==1)
                    {
                        validosAlter=arbolToArregloUser(arbol,arrayAlter,validosAlter);
                        rotateArray(arrayAlter,validosAlter);
                        arrayToFileLast(arrayAlter,validos,mainArchivo);
                        printf("\n Usuario dado de baja correctamente.\n");
                        exit(0);
                    }
                }
            }
            else
            {
                printf("\n Error, no se puede dar de baja un administrador.\n");
            }
            break;
            if(idUser==-1)
            {
            case 8:
                adminEditMenu(arbol);
                break;
            }
        }
        printf("\n\n  Cualquier tecla para volver, ESC para Menu Principal...\n");
        fflush(stdin);
        control=getch();
        system("cls");
    }
    while(control!=27);
}

void adminEditMenu(nodoArbol * arbol)
{
    system("cls");
    int menu,control;
    int idUserEditar;
    stUserNew aux;
    int status;
    int flag,searchUser;
    int statusActivo;
    do
    {
        printf("\n\t Seleccione una accion \n\n");
        printf("\n\t\t [1] - Editar usuario \n");
        printf("\n\t\t [2] - Cambiar status de usuario \n");
        printf("\n\t\t [3] - Mostrar usuarios \n");
        printf("\n\t\t [4] - Buscar usuario por ID \n");
        printf("\n\t\t [0] - Volver al Menu Principal \n");
        printf("\n\n\t\t  ");
        scanf("%d",&menu);

        switch(menu)
        {
        case 0:
            control=27;
            break;
        case 1:
            mostrarInfoUser(arbol);
            printf("\n Ingrese el id del usuario a editar\n");
            scanf("%d",&idUserEditar);
            aux=searchID(arbol,idUserEditar);
            showOneUser(aux);
            system("pause");
            editUserAdmin(arbol,idUserEditar);
            break;
        case 2:
            printf("\n Usuarios disponibles:\n");
            mostrarInfoUser(arbol);
            printf("\n\t  Ingrese el ID del usuario a dar de alta/baja : \n");
            printf("\n\n\t  ");
            scanf("%d",&status);
            printf("\n Desea activar o desactivar la cuenta?\n");
            printf("\n [0] - Desactivar\n");
            printf("\n [1] - Activar\n");
            scanf("%d",&statusActivo);
            flag=editUserStatus(arbol,status,statusActivo);
            editPlaceholder(flag,"Status");
            break;
        case 3:
            preorder(arbol);
            break;
        case 4:
            mostrarInfoUser(arbol);
            printf("\n Ingrese el id del usuario a buscar\n");
            scanf("%d",&searchUser);
            aux=searchID(arbol,searchUser);
            showOneUser(aux);
            break;
        }
        printf("\n\n  Cualquier tecla para volver, ESC para menu principal...\n");
        control=getch();
        system("cls");
    }
    while(control!=27);
}
void editUserAdmin(nodoArbol * arbol, int idUserEditar)
{
    system("cls");
    int menu,control,deletepost;
    int like;
    int validos;
    int idContent;
    int flag=0;
    stUserNew aux;

    char lastName[50];
    char firstName[50];
    char userName[30];
    int dni;
    char password[30];
    char city[50];
    int age;
    char email[50];
    char gender[30];
    int points;


    do
    {
        printf("\n\t Seleccione una accion \n\n");
        printf("\n\t\t [1]  - Apellido del usuario\n");
        printf("\n\t\t [2]  - Nombre del usuario \n");
        printf("\n\t\t [3]  - Username del usuario \n");
        printf("\n\t\t [4]  - DNI del usuario \n");
        printf("\n\t\t [5]  - Password del usuario \n");
        printf("\n\t\t [6]  - Ciudad del usuario \n");
        printf("\n\t\t [7]  - Edad del usuario \n");
        printf("\n\t\t [8]  - Correo del usuario \n");
        printf("\n\t\t [9]  - Genero del usuario \n");
        printf("\n\t\t [10] - Puntos del usuario \n");
        printf("\n\t\t [0]  - Volver al Menu de edicion \n");
        printf("\n\n\t\t  ");
        scanf("%d",&menu);

        switch(menu)
        {
        case 0:
            aux=searchID(arbol,idUserEditar);
            showOneUser(aux);
            system("pause");
            control=27;
            break;
        case 1:
            printf("\n\t  Ingrese el nuevo Apellido: \n");
            printf("\n\n\t  ");
            fflush(stdin);
            gets(lastName);
            flag=editUserApellido(arbol,idUserEditar,lastName);
            editPlaceholder(flag,"Apellido");
            break;
        case 2:
            printf("\n\t  Ingrese el nuevo nombre: \n");
            printf("\n\n\t  ");
            fflush(stdin);
            gets(firstName);
            flag=editarNameUser(arbol,idUserEditar,firstName);
            editPlaceholder(flag,"Nombre");
            break;
        case 3:
            printf("\n\t  Ingrese el nuevo nombre de usuario : \n");
            printf("\n\n\t  ");
            fflush(stdin);
            gets(userName);
            flag=editUserUsername(arbol,idUserEditar,userName);
            editPlaceholder(flag,"Nombre de usuario");
            break;
        case 4:
            printf("\n\t  Ingrese el nuevo DNI : \n");
            printf("\n\n\t  ");
            scanf("%d",&dni);
            flag=editUserDNI(arbol,idUserEditar,dni);
            editPlaceholder(flag,"DNI");
            break;
        case 5:
            printf("\n\t  Ingrese el nuevo Password: \n");
            printf("\n\n\t  ");
            fflush(stdin);
            gets(password);
            flag=editUserPassword(arbol,idUserEditar,password);
            editPlaceholder(flag,"Password");
            break;
        case 6:
            printf("\n\t  Ingrese la nueva ciudad: \n");
            printf("\n\n\t  ");
            fflush(stdin);
            gets(city);
            flag=editUserCity(arbol,idUserEditar,city);
            editPlaceholder(flag,"Ciudad");
            break;
        case 7:
            printf("\n\t  Ingrese la edad : \n");
            printf("\n\n\t  ");
            scanf("%d",&age);
            flag=editUserEdad(arbol,idUserEditar,age);
            editPlaceholder(flag,"Edad");
            break;
        case 8:
            printf("\n\t  Ingrese el nuevo Email: \n");
            printf("\n\n\t  ");
            fflush(stdin);
            gets(email);
            flag=editUserEmail(arbol,idUserEditar,email);
            editPlaceholder(flag,"Correo electronico");
            break;
        case 9:
            printf("\n\t  Ingrese el nuevo Genero : \n");
            printf("\n\n\t  ");
            fflush(stdin);
            gets(gender);
            flag=editUserGender(arbol,idUserEditar,gender);
            editPlaceholder(flag,"Genero");
            break;
        case 10:
            printf("\n\t  Ingrese los nuevos puntos: \n");
            printf("\n\n\t  ");
            scanf("%d",&points);
            flag=editUserPoints(arbol,idUserEditar,points);
            editPlaceholder(flag,"Puntos");
            break;
        }
        printf("\n\n  Cualquier tecla para volver, ESC para menu principal...\n");
        control=getch();
        system("cls");
    }
    while(control!=27);
}
void getTime(char currentTIME[])
{
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    strftime(currentTIME,50,"%d/%m/%y a las %H:%M:%S",tlocal);
}
void inbox (userListMessages arreglo[],int validosMessages, int idUser,char manderArchi[])
{
    int menu,control;
    int pos;
    char userEnviar[30];
    int arregloUsuariosMensajes[20];
    int validosArregloMensajes=0;
    system("cls");
    int variableBusqueda;
    int validosCargados;
    int arregloComparar [20];
    int validosArreglo=0;
    int valor,valorIf;
    char userName[30];

    do
    {
        printf("\n\t Casilla de mensajes de \n\n" );
        printf("\n\t\t [1] - Chats \n");
        printf("\n\t\t [2] - Nuevo chat \n");
        printf("\n\t\t [3] - Ayuda administrador \n");
        printf("\n\t\t [4] - Salir \n");
        printf("\n\t\t  ");
        scanf("%d",&menu);

        switch(menu)
        {
        case 1:
            levantaMensajes (arreglo,validosMessages,idUser);
            printf("\n Seleccione que chat quiere ver\n");
            scanf("%d",&valor);
            mostrarNodo(arreglo[valor-1].lista);
            break;
        case 2:
            do
            {
                showUserConectingMessenge(arreglo,validosMessages);
                printf("Ingrese el usuario a enviar el mensaje: ");
                fflush(stdin);
                gets(userEnviar);
                if(enviarMensaje(arreglo,validosMessages,userEnviar,idUser))
                    printf("Se envio correctamente\n");
                else
                    printf("Hubo error al enviar el mensaje\n");

                printf("\n Desea enviar otro mensaje?\n");
                printf("\n [0] - No\n");
                printf("\n [1] - Si\n");
                scanf("%d",&valorIf);
                if(valorIf==0)
                {
                    control=27;
                }
            }
            while(control!=27);
            break;
        case 3:
            enviarMensajeAdmin(idUser,validosMessages,arreglo);
            break;
        case 4:
            printf("\nESC para salir\n");
            break;
        }
        printf("\n\n  Cualquier tecla para volver, ESC para menu principal...\n");
        control=getch();
        system("cls");
    }
    while(control!=27);
}

