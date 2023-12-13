#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LibreriaGeneral.h"
#include "Registro.h"
#include "ArbolTrie.h"

#ifndef Reserva_h
#define Reserva_h



// Función para agregar una reserva a la lista
void agregarReserva(ListaReservas* ListaReservas, int id_usuario) {
    ReservaNodo* nuevoNodo = (ReservaNodo*)malloc(sizeof(ReservaNodo));
    if (nuevoNodo == NULL)
        return;
    nuevoNodo->UsuarioReserva = id_usuario;
    nuevoNodo->siguiente = NULL;
    // Si la lista está vacía, el nuevo nodo se convierte en la cabeza
    if (ListaReservas->cola == NULL) {
        ListaReservas->cabeza = nuevoNodo;
        ListaReservas->cola = nuevoNodo;
    } else {
        ListaReservas->cola->siguiente = nuevoNodo;
        ListaReservas->cola = nuevoNodo;
    }
}

// Función para notificar a los usuarios cuando un libro está disponible
void notificarDisponibilidad(ListaReservas* Reservas, char* NombreLibro, NodoUsuario** InicioUsuarios) {
    if (Reservas == NULL || Reservas->cabeza == NULL){
        puts("No hay reservas");
        return;
    }
    NodoUsuario** Usuario = Buscar_NodoUsuario(InicioUsuarios, Reservas->cabeza->UsuarioReserva);
    ReservaNodo* liberarNodo = Reservas->cabeza;
    Reservas->cabeza = Reservas->cabeza->siguiente;
    free(liberarNodo);

    if (Reservas->cabeza = NULL){
        Reservas->cola = NULL;
    }

    printf("Libro %s disponible, notificando usuario %s (Id %d)", NombreLibro, (*Usuario)->Dato.nombre, (*Usuario)->Dato.id_usuario);
}


// Función para notificar a los usuarios cuando no se puede reservar un libro
void notificarNoReservable(usuarios* usuario, libros* libro) {
    printf("Libro '%s' no se puede reservar por el usuario %s.\n", libro->titulo, usuario->nombre);
}


#endif
