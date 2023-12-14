#ifndef DatosPredeterminados_h
#define DatosPredeterminados_h

#include "LibreriaGeneral.h"
#include "Registro.h"
#include "Transacciones.h"
#include "ArbolTrie.h"

// Función para cargar datos predeterminados al programa
void CargarDatosPredeterminados(NodoUsuario **InicioUsuarios, NodoTrie **InicioLibros, int *IDUsuarios, int *IDLibros, NodoTransaccion **InicioTransacciones)
{
    // Usuarios predefinidos
    usuarios usuario1 = {"Michell", "Policarpio", *IDUsuarios, 0, {07, 01, 2002},0};
    usuarios usuario2 = {"Antonio", "Villar", *IDUsuarios + 1, 0, {8, 07, 2002},0};
    usuarios usuario3 = {"Alviery", "Rios", *IDUsuarios + 2, 0, {1, 01, 2000},0};
    usuarios usuario4 = {"Jair", "Valdes", *IDUsuarios + 3, 0, {31, 12, 2001}, 120};
    usuarios usuario5 = {"Yadira", "Fleitas", *IDUsuarios + 4, 0, {24, 02, 1994}, 0};

    // Registrar usuarios predefinidos
    RegistrarUsuario(usuario1, InicioUsuarios);
    RegistrarUsuario(usuario2, InicioUsuarios);
    RegistrarUsuario(usuario3, InicioUsuarios);
    RegistrarUsuario(usuario4, InicioUsuarios);
    RegistrarUsuario(usuario5, InicioUsuarios);

    *IDUsuarios = 6; // Ajustar el ID de usuarios

    // Libros predefinidos
    libros libro1 = { *IDLibros, "Programacion en C", "Luis Joyanes", "Pearson", 10, {2020, 1, 1}, };
    libros libro2 = { *IDLibros + 1, "Codigo Limpio", "Robert C. Martin", "Prentice Hall", 1, {2008, 8, 11} };
    libros libro3 = { *IDLibros + 2, "Liberalismo", "Juan Ramon Rallo", "Deusto", 2, {2019, 4, 19} };
    libros libro4 = { *IDLibros + 3, "Estructura de Datos", "Luis Joyanes Aguilar", "Pearson", 1, {1998, 01, 31} };

    // Insertar libros predefinidos en el Trie
    Insertar_Trie(InicioLibros, libro1);
    Insertar_Trie(InicioLibros, libro2);
    Insertar_Trie(InicioLibros, libro3);
    Insertar_Trie(InicioLibros, libro4);

    *IDLibros += 4; // Ajustar el ID de libros


    // GENERANDO UN PRESTAMO YA PREDEFINIDO:
    // Obtener nodos de usuario y libro
    NodoUsuario **nodoUsuario1 = Buscar_NodoUsuario(InicioUsuarios, 1);
    NodoTrie **nodoLibro1 = Buscar_NodoLibro(InicioLibros, "Programacion Avanzada");

    if (nodoUsuario1 && nodoLibro1)
    {
        // Configurar fechas para simular un préstamo pasado
        time_t fechaActual = time(NULL);
        struct tm *fechaPrestamo = localtime(&fechaActual);
        fechaPrestamo->tm_mday -= 30; // Retroceder 30 días para simular un préstamo pasado
        time_t fechaPrestamo30dias = mktime(fechaPrestamo);

        // Crear y agregar el préstamo predefinido
        prestamos_devoluciones prestamoPredefinido = {
            .libro_prestado = &(*nodoLibro1)->InfoLibro,
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
            (*nodoLibro1)->InfoLibro.numero_ejemplares--;  // Decrementar el número de ejemplares disponibles del libro
        }
        else
        {
            printf("Error al asignar memoria para el préstamo predefinido.\n");
        }
    }
}

#endif
