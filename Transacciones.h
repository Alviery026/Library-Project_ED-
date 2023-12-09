#ifndef Transacciones_h
#define Transacciones_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "LibreriaGeneral.h"
#include "Registro.h"

//-----------------------------PROTOTIPOS DE FUNCIONES-----------------------------------------

void RealizarPrestamo(NodoUsuario **InicioUsuarios, NodoLibro **InicioLibros, NodoTransaccion **InicioTransacciones, int *IDUsuarios, int *IDLibros);
void RealizarDevolucion(NodoUsuario **InicioUsuarios, NodoLibro **InicioLibros, NodoTransaccion **InicioTransacciones);
void MostrarUsuariosConLibrosPrestados(NodoUsuario **InicioUsuarios, NodoLibro **InicioLibros, NodoTransaccion **InicioTransacciones);
NodoTransaccion **Buscar_NodoTransaccion(NodoTransaccion **Inicio, prestamos_devoluciones dato);

NodoTransaccion **Buscar_NodoTransaccion(NodoTransaccion **Inicio, prestamos_devoluciones dato){
    while (*Inicio)
    {
        if ((*Inicio)->Dato.usuario == dato.usuario && (*Inicio)->Dato.libro_prestado == dato.libro_prestado)
            return Inicio;
        Inicio = &((*Inicio))->sgt;
    }
    return NULL;
}

void RealizarPrestamo(NodoUsuario **InicioUsuarios, NodoLibro **InicioLibros, NodoTransaccion **InicioTransacciones, int *IDUsuarios, int *IDLibros){
    limpiarPantalla();
    printf("****REALIZAR PRESTAMO****\n");

    int idUsuario, idLibro;
    printf("Ingrese el ID del usuario que realizara el prestamo: ");
    scanf("%d", &idUsuario);

    NodoUsuario **usuario = Buscar_NodoUsuario(InicioUsuarios, (usuarios){.id_usuario = idUsuario});
    if (!usuario)
    {
        printf("Usuario no encontrado. Verifique el ID.\n");
        return;
    }

    printf("Ingrese el ID del libro que se prestara: ");
    scanf("%d", &idLibro);

    NodoLibro **libro = Buscar_NodoLibro(InicioLibros, (libros){.id_libro = idLibro});
    if (!libro)
    {
        printf("Libro no encontrado. Verifique el ID.\n");
        return;
    }

    time_t fechaActual = time(NULL);
    struct tm *local = localtime(&fechaActual);
    local->tm_mday += 15; // Se establece la fecha de vencimiento a 15 días desde la fecha actual
    time_t fechaVencimiento = mktime(local);

     prestamos_devoluciones nuevaTransaccion = {
        .libro_prestado = &(*libro)->Dato,
        .usuario = &(*usuario)->Dato,
        .fecha_prestamo = fechaActual,
        .fecha_devolucion = fechaVencimiento
    };

    NodoTransaccion *nuevoNodoTransaccion = (NodoTransaccion *)malloc(sizeof(NodoTransaccion));
    if (!nuevoNodoTransaccion)
    {
        printf("Error al asignar memoria para la transaccion.\n");
        return;
    }

    nuevoNodoTransaccion->Dato = nuevaTransaccion;
    nuevoNodoTransaccion->sgt = *InicioTransacciones;
    *InicioTransacciones = nuevoNodoTransaccion;

    (*usuario)->Dato.libros_prestados++; // Incrementar el contador de libros prestados del usuario
    (*libro)->Dato.numero_ejemplares--;  // Decrementar el número de ejemplares disponibles del libro

    printf("Prestamo realizado con exito. Fecha de devolución: %s", ctime(&fechaVencimiento));
}

void RealizarDevolucion(NodoUsuario **InicioUsuarios, NodoLibro **InicioLibros, NodoTransaccion **InicioTransacciones){
    limpiarPantalla();
    printf("****REALIZAR DEVOLUCION****\n");

    int idUsuario, idLibro;
    printf("Ingrese el ID del usuario que realizara la devolucion: ");
    scanf("%d", &idUsuario);

    NodoUsuario **usuario = Buscar_NodoUsuario(InicioUsuarios, (usuarios){.id_usuario = idUsuario});
    if (!usuario)
    {
        printf("Usuario no encontrado. Verifique el ID.\n");
        return;
    }

    printf("Ingrese el ID del libro que se devolvera: ");
    scanf("%d", &idLibro);

    NodoLibro **libro = Buscar_NodoLibro(InicioLibros, (libros){.id_libro = idLibro});
    if (!libro)
    {
        printf("Libro no encontrado. Verifique el ID.\n");
        return;
    }

    NodoTransaccion **transaccion = Buscar_NodoTransaccion(InicioTransacciones, (prestamos_devoluciones){.usuario = &(*usuario)->Dato, .libro_prestado = &(*libro)->Dato});

    if (!transaccion)
    {
        printf("No se encontro una transaccion para este usuario y libro. Verifique los datos.\n");
        return;
    }

    time_t fechaActual = time(NULL);
    if (fechaActual > (*transaccion)->Dato.fecha_devolucion)
    {
        printf("El libro esta devuelto con retraso. Se aplicaran multas.\n");
        // Aquí puedes agregar la lógica para aplicar multas.
    }

    (*usuario)->Dato.libros_prestados--; // Decrementar el contador de libros prestados del usuario
    (*libro)->Dato.numero_ejemplares++;  // Incrementar el número de ejemplares disponibles del libro

    NodoTransaccion *temp = *transaccion;
    *transaccion = temp->sgt;
    free(temp);

    printf("Devolucion realizada con exito.\n");
}


void MostrarUsuariosConLibrosPrestados(NodoUsuario **InicioUsuarios, NodoLibro **InicioLibros, NodoTransaccion **InicioTransacciones){
    limpiarPantalla();
    printf("****USUARIOS CON LIBROS PRESTADOS****\n");

    NodoUsuario **auxUsuario = InicioUsuarios;
    int transaccionesEncontradas = 0;  // Bandera para indicar si se encontraron transacciones

    while (*auxUsuario)
    {
        if ((*auxUsuario)->Dato.libros_prestados > 0)
        {
            transaccionesEncontradas = 1;  // Se encontró al menos una transacción
            ImprimirUsuario((*auxUsuario)->Dato);
            printf("Libros Prestados:\n");

            NodoTransaccion **auxTransaccion = InicioTransacciones;

            while (*auxTransaccion)
            {
                if ((*auxTransaccion)->Dato.usuario == &(*auxUsuario)->Dato)
                {
                    // Imprimir información del libro
                    printf("ID del Usuario: %d\n", (*auxUsuario)->Dato.id_usuario);
                    printf("ID del Libro: %d\n", (*auxTransaccion)->Dato.libro_prestado->id_libro);
                    printf("Titulo del Libro: %s\n", (*auxTransaccion)->Dato.libro_prestado->titulo);
                    printf("Fecha de Prestamo: %s", ctime(&(*auxTransaccion)->Dato.fecha_prestamo));
                    printf("----------------------\n");
                }

                auxTransaccion = &(*auxTransaccion)->sgt;
            }
        }
        auxUsuario = &(*auxUsuario)->sgt;
    }

    if (!transaccionesEncontradas) {
        printf("No hay transacciones vigentes.\n");
    }

    pausar();
}

#endif
