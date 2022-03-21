#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "user.h"
#include "arbolUser.h"
#include "stUserPost.h"


nodoArbol* arrayToArbol (stUserNew a[], int base, int tope, int valid)
{
    int medio;
    nodoArbol* arbol=inicArbol();
    if(!(base>tope))
    {
        medio=(base+tope)/2;

        arbol=crearNodoArbol(a[medio]);
        arbol->izq=arrayToArbol(a,base,medio-1,valid);
        if(medio+1<valid)
            arbol->der=arrayToArbol(a,medio+1,tope,valid);

    }
    return arbol;
}

nodoArbol * inicArbol()
{
    return NULL;
}

nodoArbol * crearNodoArbol(stUserNew user)
{
    nodoArbol * aux = (nodoArbol *) malloc(sizeof( nodoArbol ));
    aux->user=user;
    aux->der=NULL;
    aux->izq=NULL;
    return aux;
}

nodoArbol * insertar(nodoArbol * arbol, stUserNew user)
{
    if(arbol==NULL)
        arbol = crearNodoArbol(user);
    else
    {
        if(arbol->user.idUser>user.idUser)
        {
            arbol->der = insertar(arbol->der, user);
        }
        else
        {
            arbol->izq = insertar(arbol->izq, user);
        }
    }
    return arbol;
}

///-///////////////////////////////////////////// Devuelve el nodo del usuario buscado.


stUserNew buscarNombre(nodoArbol * arbol, char nombre[],int *userStatus)
{
    stUserNew aux;
    if(arbol)
    {
        if(strcmpi(arbol->user.userName,nombre)==0)
        {
            aux=arbol->user;
            (*userStatus)=1;
        }
        else
        {
            (*userStatus)=0;

            aux=buscarNombre(arbol->izq,nombre,userStatus);
            if((*userStatus)==0)
            {
                aux=buscarNombre(arbol->der,nombre,userStatus);
            }
        }
    }
    return aux;
}
///-/////////////////////////////////////////////
stUserNew getUsuario(nodoArbol * arbol, int idUser)
{
    stUserNew aux;
    if(arbol!=NULL)
    {
        if(arbol->user.idUser==idUser)
        {
            aux=arbol->user;

        }
        else if (idUser>arbol->user.idUser)
        {
            aux=getUsuario(arbol->der,idUser);
        }
        else
        {
            aux=getUsuario(arbol->izq,idUser);
        }
    }
    return aux;
}

void preorder(nodoArbol * arbol)
{
    if(arbol != NULL)
    {
        preorder(arbol->izq);
        showOneUser(arbol->user);
        preorder(arbol->der);
    }
}

void postorder(nodoArbol * arbol)
{
    if(arbol != NULL)
    {
        postorder(arbol->izq);
        postorder(arbol->der);
        showOneUser(arbol->user);
    }
}

void inorder (nodoArbol * arbol)
{
    if(arbol!=NULL)
    {
        inorder(arbol->izq);
        showOneUser(arbol->user);
        inorder(arbol->der);
    }
}
int editUserPassword(nodoArbol * arbol, int id, char newPassword[])
{
    int flag=0;

    if(arbol!=NULL)
    {
        if(id == arbol->user.idUser)
        {
            strcpy(arbol->user.password,newPassword);
            flag=1;
        }
        else if(id>arbol->user.idUser)
        {
            flag = editUserPassword(arbol->der, id,newPassword);
        }
        else
        {
            flag = editUserPassword(arbol->izq, id,newPassword);
        }
    }
    return flag;
}

int editUserCity(nodoArbol * arbol, int id, char newCity[])
{
    int flag=0;
    if(arbol!=NULL)
    {
        if(id == arbol->user.idUser)
        {
            strcpy(arbol->user.city,newCity);
            flag=1;
        }
        else if(id>arbol->user.idUser)
            flag = editUserCity(arbol->der, id,newCity);
        else
            flag = editUserCity(arbol->izq, id,newCity);
    }
    return flag;
}

int editUserAge(nodoArbol * arbol, int id)
{
    int flag=0;
    if(arbol!=NULL)
    {
        if(id == arbol->user.idUser)
        {
            arbol->user.age++;
            flag=1;
        }
        else if(id>arbol->user.idUser)
            flag = editUserAge(arbol->der, id);
        else
            flag = editUserAge(arbol->izq, id);
    }
    return flag;
}

int editUserEmail(nodoArbol * arbol, int id, char newEmail[])
{
    int flag=0;
    if(arbol!=NULL)
    {
        if(id == arbol->user.idUser)
        {
            strcpy(arbol->user.email,newEmail);
            flag=1;
        }
        else if(id>arbol->user.idUser)
            flag = editUserEmail(arbol->der, id,newEmail);
        else
            flag = editUserEmail(arbol->izq, id,newEmail);
    }
    return flag;
}

int editUserGender(nodoArbol * arbol, int id, char newGender[])
{
    int flag=0;
    if(arbol!=NULL)
    {
        if(id == arbol->user.idUser)
        {
            strcpy(arbol->user.gender,newGender);
            flag=1;
        }
        else if(id>arbol->user.idUser)
            flag = editUserGender(arbol->der, id,newGender);
        else
            flag = editUserGender(arbol->izq, id,newGender);
    }
    return flag;
}

int editUserStatus(nodoArbol * arbol, int id, int status)
{
    int flag=0;
    if(arbol!=NULL)
    {
        if(id == arbol->user.idUser)
        {
            arbol->user.status=status;
            flag=1;
        }
        else if(id>arbol->user.idUser)
            flag = editUserStatus(arbol->der, id,status);
        else
            flag = editUserStatus(arbol->izq, id,status);
    }
    return flag;
}


void editPlaceholder(int flag, char valor[])
{
    if(flag==1)
    {
        printf("\n El cambio de la %s fue realizado correctamente\n",valor);
    }
    else
    {
        printf("\n El cambio de la %s fallo\n",valor);
    }
}

int validateEmailArbol(nodoArbol *arbol,char newEmail[])
{
    int flag=0;
    if(arbol!=NULL && flag==0)
    {
        if(strcmp(arbol->user.email,newEmail)!=0)
        {
            flag=1;
        }
        else
        {
            if(arbol->izq!=NULL)
            {

                flag=validateEmailArbol(arbol->izq,newEmail);
            }
            else
            {
                flag=validateEmailArbol(arbol->der,newEmail);
            }
        }

    }
    return flag;
}

int cargarArregloDelArbol (nodoArbol * arbol, userListMessages arrayUser[],int validos)
{
    if(arbol!=NULL)
    {
        validos=cargarArregloDelArbol(arbol->izq,arrayUser,validos);///0 - 1
        validos=cargarArreglo(arbol,arrayUser,validos,arbol->user);
        validos=cargarArregloDelArbol(arbol->der,arrayUser,validos);/// 3 - 4
    }
    return validos;
}

///*****/// menssaje
int arbolToArregloUser(nodoArbol *arbol,stUserNew arrayUser[],int validos)
{
    if(arbol!=NULL)
    {
        validos=arbolToArregloUser(arbol->der,arrayUser,validos++);
        arrayUser[validos++]=arbol->user;
        validos=arbolToArregloUser(arbol->izq,arrayUser,validos++);
    }
    return validos;
}
void rotateArray(stUserNew arrayUser[], int validos)
{
    stUserNew aux;
    int j=validos;
    int p=(validos/2);
    for(int i=0; i<p; i++)
    {
        aux=arrayUser[i];
        arrayUser[i]=arrayUser[j-1];
        arrayUser[j-1]=aux;
        j--;
    }
}

void arrayToFileLast(stUserNew arrayUser [], int valid, char mainArchivo [])
{
    stUserNew auxFile;
    FILE *pArch = fopen(mainArchivo,"r+b");
    if(pArch)
    {
        for(int i=0; i<valid; i++)
        {

            if(fread(&auxFile,sizeof(stUserNew),1,pArch)>0)
            {
                fseek(pArch,(i)*sizeof(stUserNew),SEEK_SET);
                fread(&auxFile,sizeof(stUserNew),1,pArch);
                strcpy(auxFile.lastName,arrayUser[i].lastName);
                strcpy(auxFile.firstName,arrayUser[i].firstName);
                strcpy(auxFile.userName,arrayUser[i].userName);
                auxFile.dni=arrayUser[i].dni;
                strcpy(auxFile.password,arrayUser[i].password);
                strcpy(auxFile.city,arrayUser[i].city);
                auxFile.age=arrayUser[i].age;
                strcpy(auxFile.email,arrayUser[i].email);
                strcpy(auxFile.gender,arrayUser[i].gender);
                auxFile.points=arrayUser[i].points;
                auxFile.level=arrayUser[i].level;
                strcpy(auxFile.ranki,arrayUser[i].ranki);
                auxFile.status=arrayUser[i].status;
                fseek(pArch,(i)*sizeof(stUserNew),SEEK_SET);
                fwrite(&auxFile,sizeof(stUserNew),1,pArch);
            }
        }
    }
    fclose(pArch);
}

int editUserPoints(nodoArbol * arbol, int id, int points)
{
    int flag=0;
    if(arbol!=NULL)
    {
        if(id == arbol->user.idUser)
        {
            arbol->user.points=points;
            flag=1;
        }
        else if(id>arbol->user.idUser)
            flag = editUserPoints(arbol->der, id,points);
        else
            flag = editUserPoints(arbol->izq, id,points);
    }
    return flag;
}

int editUserDNI(nodoArbol * arbol, int id, int dni)
{
    int flag=0;
    if(arbol!=NULL)
    {
        if(id == arbol->user.idUser)
        {
            arbol->user.dni=dni;
            flag=1;
        }
        else if(id>arbol->user.idUser)
            flag = editUserDNI(arbol->der, id,dni);
        else
            flag = editUserDNI(arbol->izq, id,dni);
    }
    return flag;
}

int editUserUsername(nodoArbol * arbol, int id, char nombreUsuario[])
{
    int flag=0;
    if(arbol!=NULL)
    {
        if(id == arbol->user.idUser)
        {
            strcpy(arbol->user.userName,nombreUsuario);
            flag=1;
        }
        else if(id>arbol->user.idUser)
            flag = editUserUsername(arbol->der, id,nombreUsuario);
        else
            flag = editUserUsername(arbol->izq, id,nombreUsuario);
    }
    return flag;
}

int editarNameUser(nodoArbol * arbol, int id, char nombre[])
{
    int flag=0;
    if(arbol!=NULL)
    {
        if(id == arbol->user.idUser)
        {
            strcpy(arbol->user.firstName,nombre);
            flag=1;
        }
        else if(id>arbol->user.idUser)
            flag = editarNameUser(arbol->der, id,nombre);
        else
            flag = editarNameUser(arbol->izq, id,nombre);
    }
    return flag;
}

int editUserApellido(nodoArbol * arbol, int id, char apellido[])
{
    int flag=0;
    if(arbol!=NULL)
    {
        if(id == arbol->user.idUser)
        {
            strcpy(arbol->user.lastName,apellido);
            flag=1;
        }
        else if(id>arbol->user.idUser)
            flag = editUserApellido(arbol->der, id,apellido);
        else
            flag = editUserApellido(arbol->izq, id,apellido);
    }
    return flag;
}

int editUserEdad(nodoArbol * arbol, int id, int edad)
{
    int flag=0;
    if(arbol!=NULL)
    {
        if(id == arbol->user.idUser)
        {
            arbol->user.age=edad;
            flag=1;
        }
        else if(id>arbol->user.idUser)
            flag = editUserEdad(arbol->der, id,edad);
        else
            flag = editUserEdad(arbol->izq, id,edad);
    }
    return flag;
}

stUserNew searchID(nodoArbol* arbol, int idUser)
{
    stUserNew aux;
    if(arbol!=NULL)
    {
        if(idUser==arbol->user.idUser)
        {
            aux=arbol->user;
        }
        else if(idUser>arbol->user.idUser)
            aux=searchID(arbol->der,idUser);
        else
            aux=searchID(arbol->izq,idUser);
    }
    return aux;
}


///********* Mensajeria

stUserMessenge searchIDMessange(nodoArbol* arbol, int idUser)
{
    stUserMessenge aux;
    if(arbol!=NULL)
    {
        if(idUser==arbol->user.idUser)
        {
            aux.idUser=arbol->user.idUser;
            strcpy(aux.userName,arbol->user.userName);
            aux.points=arbol->user.points;
            aux.status=arbol->user.status;
        }
        else if(idUser>arbol->user.idUser)
            aux=searchIDMessange(arbol->der,idUser);
        else
            aux=searchIDMessange(arbol->izq,idUser);
    }
    return aux;
}


void mostrarInfoUser(nodoArbol * arbol)
{
    if(arbol != NULL)
    {
        mostrarInfoUser(arbol->izq);
        if(arbol->user.idUser!=-1)
            mostrarNombreyID(arbol->user);

        mostrarInfoUser(arbol->der);
    }
}

void mostrarNombreyID(stUserNew user)
{

    printf("\n\t\t\t Id.......................: %15d", user.idUser);
    printf("\n\t\t\t Usuario..................: %15s", user.userName);
    printf("\n\t\t\t Status usuario...........: %15d", user.status);
    printf("\n");
}
///-//////////////////////////////////////////////////
///   actualizar el Rank de usuario
///-//////////////////////////////////////////////////

void actualizarRanki(nodoArbol * arbol, int id)
{
    if(arbol!=NULL)
    {
        if(id == arbol->user.idUser)
        {
            arbol->user.level=rankUser(arbol->user,arbol->user.ranki);
        }
        else if(id>arbol->user.idUser)
        {
            actualizarRanki(arbol->der, id);
        }
        else
        {
            actualizarRanki(arbol->izq, id);
        }
    }
}

///-//////////////////////////////////////////////////
///   Rank de usuario
///-//////////////////////////////////////////////////
int rankUser(stUserNew user,char ranki[])
{
    if(user.points<10)
    {
        strcpy(ranki,"Bronce");
        user.level=0;
    }
    else if(user.points>10 && user.points<20)
    {
        strcpy(ranki,"Plata");
        user.level=1;
    }
    else if(user.points>20 && user.points<30)
    {
        strcpy(ranki,"Oro");
        user.level=2;
    }
    else
    {
        strcpy(ranki,"Diamante");
        user.level=3;
    }
    return user.level;
}
