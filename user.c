#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "user.h"
#include "arbolUser.h"

const int ESC=27;


int createUser(stUserNew arrayUser[], int valid,char currentTIME[])
{
    int i=0;
    int flag=0;
    stUserNew user;
    if(valid==0)
    {
        printf("\n \t\t\t\t\tCargando un usuario ADMINISTRADOR:\n");
    }
    fflush(stdin);
    printf("\n  Ingrese su Apellido: \n");
    printf("\n --->  ");
    gets(user.lastName);

    fflush(stdin);
    printf("\n  Ingrese su Nombre:  \n");
    printf("\n --->  ");
    gets(user.firstName);
    do
    {
        printf("\n  Ingrese su edad: \n");
        printf("\n --->  ");
        scanf("%d",&user.age);
        flag=ageOver(user.age);
    }
    while(flag==0);
    do
    {
        printf("\n  Ingrese su DNI: \n");
        printf("\n --->  ");
        fflush(stdin);
        scanf("%d",&user.dni);
        flag=dniValidation(arrayUser,valid,user.dni);
        if(flag==1)
        {
            printf("\n  DNI ya registrado, ingrese un nuevo DNI\n");
        }
    }
    while(flag==1);

    do
    {
        fflush(stdin);
        printf("\n Ingrese su nombre de Usuario: \n");
        printf("\n --->  ");
        fflush(stdin);
        gets(user.userName);
        flag=userValidation(arrayUser,valid,user.userName);
        if(flag==1)
        {
            printf("\n  El nombre de usuario %s ya existe. Por favor ingrese otro\n",user.userName);
        }

    }
    while(flag==1);


    fflush(stdin);
    printf("\n  Ingrese su password: \n");
    printf("\n --->  ");
    scanf("%s",&user.password);

    do
    {

        printf("\n  Ingrese su correo electronico \n");
        printf("\n --->  ");
        fflush(stdin);
        gets(user.email);
        flag=emailValidation(arrayUser,valid,user.email);
        if(flag==1)
        {
            printf("\n El correo %s ya esta registrado\n",user.email);
        }
    }
    while(flag==1);

    fflush(stdin);
    printf("\n  Ingrese su ciudad actual: \n");
    printf("\n --->  ");
    gets(user.city);

    fflush(stdin);
    printf("\n  Ingrese su percepcion de genero: \n");
    printf("\n --->  ");
    scanf("%s",&user.gender);
    i++;
    if(valid==0)
    {
        user.idUser=-1;
    }
    else
    {
        user.idUser=valid+1;
    }
    user.status=1;
    user.points=0;
    user.level=rankUser(user,user.ranki);
    strcpy(user.time,currentTIME);
    strcpy(user.lastCon,currentTIME);


    valid = altaArreglo(arrayUser, valid, user);

    system("cls");
    return valid;
}

int ageOver(int age)
{
    int flag;
    if(age>16 && age<105)
    {
        flag=1;
    }
    else
    {
        if(age<16)
        {
            printf("Usted debe tener mas de 16 anios para registrarse");
        }
        else
        {
            printf("\nIngrese una edad correcta\n");
        }
    }

    return flag;
}

void showOneUser(stUserNew user)
{
    printf("\n\t\t\t <------------------------------------------------->\n");
    printf("\n\t\t\t <------------------------------------------------->\n");
    printf("\n\t\t\t Informacion de Usuario: \n\n");
    printf("\n\t\t\t Id.......................: %15d", user.idUser);
    printf("\n\t\t\t Usuario..................: %15s", user.userName);
    printf("\n\t\t\t Password.................: %15s", user.password);
    printf("\n\t\t\t Informacion Personal.....: \n\n");
    printf("\n\t\t\t Nombre...................: %15s",user.firstName);
    printf("\n\t\t\t Apellido.................: %15s", user.lastName);
    printf("\n\t\t\t Edad.....................: %15d", user.age);
    printf("\n\t\t\t DNI......................: %15d", user.dni);
    printf("\n\t\t\t Genero...................: %15s \n", user.gender);
    printf("\n\t\t\t Ciudad...................: %15s\n",user.city);
    printf("\n\t\t\t Nivel....................: %15d\n", user.level);
    printf("\n\t\t\t Puntos...................: %15d\n", user.points);
    printf("\n\t\t\t Ranking..................: %15s\n", user.ranki);

    printf("\n\t\t\t Informacion de Contacto..: \n\n");
    printf("\n\t\t\t Correo electronico.......: %15s\n\n", user.email);
    printf("\n\t\t\t User Status..............: %15d\n",user.status);
    printf("\n\t\t\t First Login..............: %15s\n",user.time);
    printf("\n\t\t\t Last conection...........: %15s\n",user.lastCon);
    printf("\n\t\t\t <------------------------------------------------->\n");
    printf("\n\t\t\t <------------------------------------------------->\n");
}

void showMyUser(stUserNew user)
{
    printf("\t\t\t------------------------------------------------------------------\n");
    printf("\n\t\t\t***  Usuario.............. : %25s         ***\n", user.userName);
    printf("\n\t\t\t***  Password............. : %25s         ***\n", user.password);
    printf("\n\t\t\t***  Nombre............... : %25s         ***\n", user.firstName);
    printf("\n\t\t\t***  Apellido............. : %25s         ***\n", user.lastName);
    printf("\n\t\t\t***  Edad................. : %25d         ***\n", user.age);
    printf("\n\t\t\t***  DNI.................. : %25d         ***\n", user.dni);
    printf("\n\t\t\t***  Genero............... : %25s         ***\n", user.gender);
    printf("\n\t\t\t***  Ciudad............... : %25s         ***\n", user.city);
    printf("\n\t\t\t***  Email................ : %25s         ***\n", user.email);
    printf("\n\t\t\t***  Ranking.............. : %25s         ***\n", user.ranki);
    printf("\n\t\t\t***  Nivel................ : %25d         ***\n", user.level);
    printf("\n\t\t\t***  Puntos............... : %25d         ***\n", user.points);
    printf("\n\t\t\t Ultima conexion ......... : %25s         ***\n", user.lastCon);
    printf("\n\t\t\t------------------------------------------------------------------");
}

int getUser(stUserNew aux, stUserNew arreglo[])
{
    int validos=1;
    arreglo=(stUserNew*)malloc(1*sizeof(stUserNew));
    return validos;
}

int dniValidation(stUserNew arreglo[],int validos, int dni)
{
    int i=0;
    int flag=0;
    while(i<validos && flag==0)
    {
        if(arreglo[i].dni==dni)
        {
            flag=1;
        }
        else
        {
            i++;
        }
    }
    return flag;
}


int emailValidation(stUserNew arreglo[],int validos, char email[])
{
    int i=0;
    int flag=0;
    while(i<validos && flag==0)
    {
        if(strcmp(arreglo[i].email,email)==0)
        {
            flag=1;
        }
        else
        {
            i++;
        }
    }
    return flag;
}
int userValidation(stUserNew arreglo[],int validos, char user[])
{
    int i=0;
    int flag=0;
    while(i<validos && flag==0)
    {
        if(strcmp(arreglo[i].userName,user)==0)
        {
            flag=1;
        }
        else
        {
            i++;
        }
    }
    return flag;
}

void showArray(stUserNew arreglo[], int validos)
{
    int i;
    for(i=0; i<validos; i++)
    {
        showOneUser(arreglo[i]);
    }
}


int altaArreglo (stUserNew arrayUser[], int valid, stUserNew auxUser)
{
    arrayUser[valid]=auxUser;
    valid++;
    return valid;
}

int searchPosition (stUserNew arrayUser[], int valid, char userName[])
{
    int pos = -1;
    int i=0;
    while (i<valid && pos == -1)
    {
        if (strcmp(arrayUser[i].userName, userName)==0)
        {
            pos=i;
        }
        i++;
    }
    return pos;
}

int addUserFix (stUserNew arrayUser[], int valid, char userName[])
{

    arrayUser[valid].idUser = valid;
    return valid;
}

int fileToArray(stUserNew arrayUser[], char mainArchivo [])
{
    int i=0;
    FILE * archi = fopen(mainArchivo, "rb");
    if (archi)
    {
        stUserNew auxUser;
        while (fread(&auxUser, sizeof(stUserNew), 1, archi)>0)
        {

            arrayUser[i]=auxUser;
            i++;

        }
        fclose(archi);
    }
    return i;
}

void mostrarArreglobase (stUserNew arrayUser[],int valid)
{
    for(int i=0; i<valid; i++)
    {
        mostrarCabeza(arrayUser[i]);
    }
}

void mostrarCabeza(stUserNew cabecera)
{
    printf("Nombre de usuario --> %s\n\n",cabecera.firstName);
    printf("Apellido de usuario --> %s\n\n",cabecera.lastName);
    printf("Usuario --> %s\n\n",cabecera.userName);
    printf("Dni --> %d\n\n",cabecera.dni);
}

void mostrarArchivo(char mainArchivo[])
{
    stUserNew usuario;
    FILE * archi =fopen(mainArchivo,"rb");
    if(archi)
    {
        system("Pause");
        while(fread(&usuario,sizeof(stUserNew),1,archi)>0)
        {
            printf("Usuario :%s\n",usuario.userName);
        }
        fclose(archi);
    }

}

void mostrarIndividual(stUserNew a)
{
    printf("Usuario ---> %s",a.userName);
}

void arrayToFile (stUserNew arrayUser [], int valid, char mainArchivo [])
{
    stUserNew auxFile;
    FILE * archi = fopen(mainArchivo,"ab");
    if(archi)
    {
        fwrite(&arrayUser[valid-1],sizeof(stUserNew),1,archi);
        fclose(archi);
    }
}
