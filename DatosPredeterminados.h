#ifndef DatosPredeterminados_h
#define DatosPredeterminados_h

#include "LibreriaGeneral.h"
#include "Registro.h"
#include "Transacciones.h"

void CargarDatosPredeterminados(NodoUsuario **InicioUsuarios, NodoLibro **InicioLibros, int *IDUsuarios, int *IDLibros, NodoTransaccion **InicioTransacciones);


void CargarDatosPredeterminados(NodoUsuario **InicioUsuarios, NodoLibro **InicioLibros, int *IDUsuarios, int *IDLibros, NodoTransaccion **InicioTransacciones)
{
    // Usuarios predefinidos
    usuarios usuario1 = {"Michell", "Policarpio", *IDUsuarios, 0, {07, 01, 2002}};
    usuarios usuario2 = {"Antonio", "Villar", *IDUsuarios + 1, 0, {8, 07, 2002}};
    usuarios usuario3 = {"Alviery", "Rios", *IDUsuarios + 2, 0, {1, 01, 2000}};
    usuarios usuario4 = {"Jair", "Valdes", *IDUsuarios + 3, 0, {31, 12, 2001}};
    usuarios usuario5 = {"Yadira", "Fleitas", *IDUsuarios + 4, 0, {24, 02, 1994}};

    RegistrarUsuario(usuario1, InicioUsuarios);
    RegistrarUsuario(usuario2, InicioUsuarios);
    RegistrarUsuario(usuario3, InicioUsuarios);
    RegistrarUsuario(usuario4, InicioUsuarios);
    RegistrarUsuario(usuario5, InicioUsuarios);

    *IDUsuarios += 3; // Ajustar el ID de usuarios

    // Libros predefinidos
    libros libro1 = { *IDLibros, "Introduccion a la Programacion", "John Smith", "Editorial A", 10, {2020, 1, 1} };
    libros libro2 = { *IDLibros + 1, "Programacion Avanzada", "Jane Doe", "Editorial B", 8, {2018, 3, 15} };
    libros libro3 = { *IDLibros + 2, "Liberalismo", "Juan Ramon Rallo", "Editorial c", 2, {2019, 4, 19} };
    libros libro4 = { *IDLibros + 3, "Estructura de Datos", "Luis Joyanes Aguilar", "Editorial D", 1, {1998, 01, 31} };

    RegistrarLibro(libro1, InicioLibros);
    RegistrarLibro(libro2, InicioLibros);
    RegistrarLibro(libro3, InicioLibros);
    RegistrarLibro(libro4, InicioLibros);

    *IDLibros += 4; // Ajustar el ID de libros


    // GENERANDO UN PRESTAMO YA PREDEFINIDO:
    // Obtener nodos de usuario y libro
    NodoUsuario **nodoUsuario1 = Buscar_NodoUsuario(InicioUsuarios, (usuarios){.id_usuario = 1});
    NodoLibro **nodoLibro1 = Buscar_NodoLibro(InicioLibros, (libros){.id_libro = 1});

    if (nodoUsuario1 && nodoLibro1)
    {
        time_t fechaActual = time(NULL);
        struct tm *fechaPrestamo = localtime(&fechaActual);
        fechaPrestamo->tm_mday -= 30; // Retroceder 30 días para simular un préstamo pasado
        time_t fechaPrestamo30dias = mktime(fechaPrestamo);

        prestamos_devoluciones prestamoPredefinido = {
            .libro_prestado = &(*nodoLibro1)->Dato,
            .usuario = &(*nodoUsuario1)->Dato,
            .fecha_prestamo = fechaPrestamo30dias,
            .fecha_devolucion = fechaActual
        };

        NodoTransaccion *nodoTransaccionPredefinido = (NodoTransaccion *)malloc(sizeof(NodoTransaccion));
        if (nodoTransaccionPredefinido)
        {
            nodoTransaccionPredefinido->Dato = prestamoPredefinido;
            nodoTransaccionPredefinido->sgt = *InicioTransacciones;
            *InicioTransacciones = nodoTransaccionPredefinido;

            (*nodoUsuario1)->Dato.libros_prestados++; // Incrementar el contador de libros prestados del usuario
            (*nodoLibro1)->Dato.numero_ejemplares--;  // Decrementar el número de ejemplares disponibles del libro
        }
        else
        {
            printf("Error al asignar memoria para el préstamo predefinido.\n");
        }
    }
}

#endif
