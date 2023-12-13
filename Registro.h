#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "LibreriaGeneral.h"

#ifndef Registro_h
#define Registro_h

//-----------------------------PROTOTIPOS DE FUNCIONES-----------------------------------------

void RegistrarUsuario(usuarios UsuarioIngresar, NodoUsuario** Inicio);
NodoUsuario** Buscar_NodoUsuario(NodoUsuario** Inicio, int dato);
void RegistroManualUsuario(NodoUsuario**, int*);
usuarios IngresoManualUsuario(int* ID);
NodoUsuario* Crear_NodoUsuario(usuarios dato);
void Insertar_NodoUsuario(NodoUsuario** Inicio, usuarios dato);
void Eliminar_Nodo(NodoUsuario** Inicio, usuarios datoEl);
void Imprimir_Lista_Usuarios(NodoUsuario** Inicio);
void ImprimirUsuario(usuarios User);
void limpiarPantalla();
void pausar();


//Funciones de registro, creaccion, impresion y mas de usuario

void RegistrarUsuario(usuarios UsuarioIngresar, NodoUsuario** Inicio) {
    if (Buscar_NodoUsuario(Inicio, UsuarioIngresar.id_usuario) == NULL) {
        Insertar_NodoUsuario(Inicio, UsuarioIngresar);
    } else {
        printf("El usuario con ID %d ya existe.\n", UsuarioIngresar.id_usuario);
    }
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
    NuevoUsuario.Multa = 0;

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

NodoUsuario** Buscar_NodoUsuario(NodoUsuario** Inicio, int dato){
    while (*Inicio){//Mientras inicio no sea NULL (Se acabe la lista)
    if((*Inicio)->Dato.id_usuario == dato) //Comparar si el nodo actual contiene el dato
        return Inicio;// Si sí, retornar conexión al nodo
    Inicio = &((*Inicio))->sgt;//Recorrer lista
    }
    return NULL;
}

void Eliminar_Nodo(NodoUsuario** Inicio, usuarios datoEl) {
    NodoUsuario* temp = *Inicio;
    NodoUsuario* prev = NULL;

    while (temp != NULL && temp->Dato.id_usuario != datoEl.id_usuario) {
        prev = temp;
        temp = temp->sgt;
    }

    if (temp == NULL) {
        printf("Usuario no encontrado.\n");
        return;
    }

    if (prev == NULL) {
        // El nodo a eliminar es el primero
        *Inicio = temp->sgt;
    } else {
        // El nodo a eliminar no es el primero
        prev->sgt = temp->sgt;
    }

    free(temp);
    printf("Usuario eliminado con éxito.\n");
}

void Imprimir_Lista_Usuarios(NodoUsuario** Inicio){
  int i = 0;
  while ((*Inicio)) {                              
    ImprimirUsuario((*Inicio)->Dato);
    Inicio = &((*Inicio)->sgt);
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
    if (User.Multa > 0){
        printf("Multas por pagar $%d", User.Multa);
        puts("");
    }
    puts("");
    return;
}



#endif
