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
} usuarios;

typedef struct prestamos_devoluciones
{
    struct libros *libro_prestado; // puntero al libro prestado
    struct usuarios *usuario;     // puntero al usuario que tiene el libro prestado
    time_t fecha_prestamo;        
    time_t fecha_devolucion;      
} prestamos_devoluciones;

#endif
