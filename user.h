#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED
#include "messenge.h"
#include "stUserMessenge.h"
typedef struct _stUserNew
{
    int idUser;
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
    int level;
    char ranki[20];
    int status;
    char time[10];
    char lastCon[10];
}stUserNew;


int createUser(stUserNew arrayUser[],int valid, char currentTIME[]);
int ageOver(int age);
void showOneUser(stUserNew user);
void showMyUser(stUserNew user);
int getUser(stUserNew aux, stUserNew arreglo[]);
int dniValidation(stUserNew arreglo[],int validos, int dni);
int emailValidation(stUserNew arreglo[],int validos, char email[]);
int userValidation(stUserNew arreglo[],int validos, char user[]);
void showArray(stUserNew arreglo[], int validos);
int addUserFix (stUserNew arrayUser[], int valid, char firstName[]);
int searchPosition (stUserNew arrayUser[], int valid, char firstName[]);
int altaArreglo (stUserNew arrayUser[], int valid, stUserNew auxUser);
int fileToArray(stUserNew arrayUser[], char mainArchivo []);
void mostrarArreglobase (stUserNew arrayUser[],int valid);
void mostrarCabeza(stUserNew cabecera);
void mostrarArchivo(char mainArchivo[]);
void cargarArchivo (char mainArchivo[]);
void mostrarIndividual(stUserNew a);
void arrayToFile (stUserNew arrayUser [], int valid, char mainArchivo []);
void arrayLoadsFile (stUserNew arrayUser,char mainArchivo[],stUserNew auxFile);



#endif // USER_H_INCLUDED
