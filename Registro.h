#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "LibreriaGeneral.h"

//-----------------------------------PROTOTIPOS DE FUNCIONES--------------------------------------------------------

#ifndef Registro_h
#define Registro_h

typedef struct NodoUsuario{
    usuarios Dato;
    struct NodoUsuario* sgt;
}NodoUsuario;


void RegistrarUsuario(usuarios, NodoUsuario**);
void RegistroManualUsuario(NodoUsuario**, int*);
usuarios IngresoManualUsuario(int* ID);
NodoUsuario* Crear_NodoUsuario(usuarios dato);
void Insertar_NodoUsuario(NodoUsuario** Inicio, usuarios dato);
void Eliminar_Nodo(NodoUsuario** Inicio, usuarios datoEl);
void Imprimir_Lista_Usuarios(NodoUsuario** Inicio);
void ImprimirUsuario(usuarios User);


void RegistrarUsuario(usuarios UsuarioIngresar, NodoUsuario** Inicio){//Esta funcion en caso de hacer cosas posterior al Inserte
    Insertar_NodoUsuario(Inicio, UsuarioIngresar);
    return;
}

void RegistroManualUsuario(NodoUsuario** Inicio, int* ID){
    usuarios NuevoUsuario = IngresoManualUsuario(ID);
    RegistrarUsuario(NuevoUsuario, Inicio);
    return;
}

usuarios IngresoManualUsuario(int* ID){
    usuarios NuevoUsuario;
    NuevoUsuario.id_usuario = *ID;
    NuevoUsuario.libros_prestados = 0;

    fflush(stdin);
    printf("Ingrese el nombre del usuario: ");
    scanf("%40[^\n]", NuevoUsuario.nombre);
    fflush(stdin);
    printf("Ingrese el apellido del usuario: ");
    scanf("%40[^\n]", NuevoUsuario.apellido);
    fflush(stdin);
    printf("Ingrese la fecha de nacimiento del usuario(DD/MM/AAAA): ");
    scanf("%02d/%02d/%04d", &NuevoUsuario.fecha_nac.dia, &NuevoUsuario.fecha_nac.mes, &NuevoUsuario.fecha_nac.anio);
    fflush(stdin);
    *ID += 1;
    return NuevoUsuario;
}

NodoUsuario* Crear_NodoUsuario(usuarios dato){
    NodoUsuario* NewNode = (NodoUsuario *)malloc(sizeof(NodoUsuario));//Crear Nodo
    if (!NewNode)                                //Verificar si se creo correctamente
        return NULL;
    NewNode->Dato = dato;                       //Instanciar datos, sgt es NULL
    NewNode->sgt = NULL;
    return NewNode;
}

void Insertar_NodoUsuario(NodoUsuario** Inicio, usuarios dato){
    NodoUsuario* NodoInsert = Crear_NodoUsuario(dato);        //Crear Nodo con funcion
    NodoInsert->sgt = *Inicio;                  //Nuevo nodo será el inicio de la lista
    *Inicio = NodoInsert;                       //Cambiar puntero a inicio
    return;
}

NodoUsuario** Buscar_NodoUsuario(NodoUsuario** Inicio, usuarios dato){
    while (*Inicio){//Mientras inicio no sea NULL (Se acabe la lista)
    if((*Inicio)->Dato.id_usuario == dato.id_usuario) //Comparar si el nodo actual contiene el dato
        return Inicio;// Si sí, retornar conexión al nodo
    Inicio = &((*Inicio))->sgt;//Recorrer lista
    }
    return NULL;
}

void Eliminar_Nodo(NodoUsuario** Inicio, usuarios datoEl){
    NodoUsuario** temp; //Crear temporal para no mover inicio
    if (!(temp = Buscar_NodoUsuario(Inicio, datoEl))) //Buscar elemento, si no existe salir
        return;
    NodoUsuario *temp2 = *temp; //Crear segundo temporal en dirección del nodo
    *temp = temp2->sgt;  //Modificar conexion, Nodo
    free(temp2);         //Liberar Nodo
    return;
}

void Imprimir_Lista_Usuarios(NodoUsuario** Inicio){
    if ((*Inicio)->sgt == *Inicio){
        ImprimirUsuario((*Inicio)->Dato);
        return;
    }
    NodoUsuario** aux = Inicio;
    while (((*aux)->sgt != *Inicio)) {
        ImprimirUsuario((*aux)->Dato);
        aux = &(*aux)->sgt;           
    }
    return;
}

void ImprimirUsuario(usuarios User){
    printf("ID\t\t %d", User.id_usuario);
    puts("");
    printf("Nombre(s)\t %s", User.nombre);
    puts("");
    printf("Apellido(s)\t %s", User.apellido);
    puts("");
    printf("Fecha Nacimiento %d/%d/%d", User.fecha_nac.dia, User.fecha_nac.mes, User.fecha_nac.anio);
    puts("");
    printf("Libros Prestados  %d", User.libros_prestados);
    puts("");
    puts("");
    return;
}

#endif
