#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef LibreriaGeneral_h
#define LibreriaGeneral_h



typedef struct fecha
{
    int dia;
    int mes;
    int anio;
}fecha;

typedef struct usuarios
{
    char nombre[40];
    char apellido[40];
    int id_usuario;
    int libros_prestados;
    fecha fecha_nac;
    int Multa;
} usuarios;

// Estructura para representar un nodo de reserva
typedef struct ReservaNodo {
    int UsuarioReserva;
    struct ReservaNodo* siguiente;
} ReservaNodo;

// Estructura para representar una lista enlazada de reservas
typedef struct {
    ReservaNodo* cabeza;
    ReservaNodo* cola;
} ListaReservas;

typedef struct libros
{
    int id_libro;
    char titulo[50];
    char autor[50];
    char editorial[50];
    int numero_ejemplares;
    fecha anio_publicacion;
    ListaReservas* Reservas;
} libros;





typedef struct NodoUsuario{
    usuarios Dato;
    struct NodoUsuario* sgt;
}NodoUsuario;

typedef struct prestamos_devoluciones
{
    struct libros *libro_prestado; // puntero al libro prestado
    struct usuarios *usuario;     // puntero al usuario que tiene el libro prestado
    time_t fecha_prestamo;        
    time_t fecha_devolucion;      
} prestamos_devoluciones;


typedef struct NodoTransaccion
{
    prestamos_devoluciones Dato;
    struct NodoTransaccion *sgt;
} NodoTransaccion;



void limpiarPantalla() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void pausar() {
  printf("\nPresione Enter para continuar...");
  while (getchar() != '\n')
    ;
  getchar(); // Espera la pulsacion del ENTER
}

//Funcion para crear Colas Usada en struct libros
ListaReservas* CrearCola(){
    ListaReservas* Cola = (ListaReservas*) malloc(sizeof (ListaReservas));
    Cola->cabeza = NULL;
    Cola->cola = NULL;
    return Cola;
}
#endif
