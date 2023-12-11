#ifndef LibreriaGeneral_h
#define LibreriaGeneral_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Declaración de avance
struct NodoMulta;

typedef struct fecha
{
    int dia;
    int mes;
    int anio;
} fecha;

typedef struct libros
{
    int id_libro;
    char titulo[50];
    char autor[50];
    char editorial[50];
    int numero_ejemplares;
    fecha anio_publicacion;
} libros;

typedef struct usuarios
{
    char nombre[40];
    char apellido[40];
    int id_usuario;
    int libros_prestados;
    fecha fecha_nac;
    struct NodoMulta* multa; // cambiado a "struct NodoMulta*"
    struct NodoRecordatorio* ListaRecordatorios; // agregado para manejar recordatorios
} usuarios;


typedef struct NodoUsuario{
    usuarios Dato;
    struct NodoUsuario* sgt;
} NodoUsuario;

typedef struct prestamos_devoluciones
{
    struct libros *libro_prestado;
    struct usuarios *usuario;
    time_t fecha_prestamo;
    time_t fecha_devolucion;
} prestamos_devoluciones;

typedef struct NodoLibro
{
    libros Dato;
    struct NodoLibro *sgt;
} NodoLibro;

typedef struct NodoTransaccion
{
    prestamos_devoluciones Dato;
    struct NodoTransaccion *sgt;
} NodoTransaccion;


#endif
