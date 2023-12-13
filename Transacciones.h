#ifndef Transacciones_h
#define Transacciones_h
#define NUM_CHARS 256

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "LibreriaGeneral.h"
#include "Registro.h"
#include "ArbolTrie.h"
#include "Reserva.h"
#include "Multas.h"
//-----------------------------PROTOTIPOS DE FUNCIONES-----------------------------------------

int obtenerIDUsuario();
char* obtenerIDLibro();
void realizarPrestamo(NodoUsuario **InicioUsuarios, NodoTrie **InicioLibros, NodoTransaccion **InicioTransacciones);
void realizarTransaccion(NodoTransaccion **InicioTransacciones, NodoUsuario **usuario, NodoTrie **libro, time_t fechaActual, time_t fechaVencimiento);
void RealizarDevolucion(NodoUsuario **InicioUsuarios, NodoTrie **InicioLibros, NodoTransaccion **InicioTransacciones);
void MostrarUsuariosConLibrosPrestados(NodoUsuario **InicioUsuarios, NodoTrie **InicioLibros, NodoTransaccion **InicioTransacciones);
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


int obtenerIDUsuario() {
    int idUsuario;
    printf("Ingrese el ID del usuario que realizara el prestamo: \n");
    scanf("%d", &idUsuario);
    return idUsuario;
}

char* obtenerIDLibro() {
    static char idLibro[41];
    fflush(stdin);
    printf("Ingrese el nombre del libro que se prestara: ");
    puts("");
    scanf("%40[^\n]", idLibro);
    return idLibro;
}

void realizarPrestamo(NodoUsuario **InicioUsuarios, NodoTrie **InicioLibros, NodoTransaccion **InicioTransacciones) {
    limpiarPantalla();

    printf("****REALIZAR PRESTAMO****\n");

    int idUsuario = obtenerIDUsuario();
    NodoUsuario **usuario = Buscar_NodoUsuario(InicioUsuarios, idUsuario);
    if (!usuario) {
        printf("Usuario no encontrado. Verifique el ID.\n");
        return;
    }
    if ((*usuario)->Dato.Multa > 0){
        printf("Usuario con Multa vigente favor de pagar\n");
        return;
    }

    char idLibro[41];
    fflush(stdin);
    printf("Ingrese el nombre del libro que se devolvera: ");
    scanf("%40[^\n]", idLibro);
    NodoTrie **libro = Buscar_NodoLibro(InicioLibros, idLibro);
    if (!libro) {
        printf("Libro no encontrado. Verifique el ID.\n");
        return;
    }

    if ((*libro)->InfoLibro.numero_ejemplares == 0){
        puts("Existencias agotadas, reservando");
        agregarReserva((*libro)->InfoLibro.Reservas, idUsuario);
        return;
    }

    time_t fechaActual = time(NULL);
    struct tm *local = localtime(&fechaActual);
    local->tm_mday += 15; // Se establece la fecha de vencimiento a 15 días desde la fecha actual
    time_t fechaVencimiento = mktime(local);

    realizarTransaccion(InicioTransacciones, usuario, libro, fechaActual, fechaVencimiento);
}

void realizarTransaccion(NodoTransaccion **InicioTransacciones, NodoUsuario **usuario, NodoTrie **libro, time_t fechaActual, time_t fechaVencimiento) {
    prestamos_devoluciones nuevaTransaccion = {
        .libro_prestado = &(*libro)->InfoLibro,
        .usuario = &(*usuario)->Dato,
        .fecha_prestamo = fechaActual,
        .fecha_devolucion = fechaVencimiento
    };

    NodoTransaccion *nuevoNodoTransaccion = (NodoTransaccion *)malloc(sizeof(NodoTransaccion));
    if (!nuevoNodoTransaccion) {
        printf("Error al asignar memoria para la transaccion.\n");
        return;
    }

    nuevoNodoTransaccion->Dato = nuevaTransaccion;
    nuevoNodoTransaccion->sgt = *InicioTransacciones;
    *InicioTransacciones = nuevoNodoTransaccion;

    (*usuario)->Dato.libros_prestados++; // Incrementar el contador de libros prestados del usuario
    (*libro)->InfoLibro.numero_ejemplares--;  // Decrementar el número de ejemplares disponibles del libro
    printf("_____________________________________________\n");
    printf("\nPrestamo realizado con exito. \nFecha a devolver: %s", ctime(&fechaVencimiento));
    printf("_____________________________________________\n");
}

void RealizarDevolucion(NodoUsuario **InicioUsuarios, NodoTrie **InicioLibros, NodoTransaccion **InicioTransacciones){
    limpiarPantalla();
    printf("****REALIZAR DEVOLUCION****\n");

    int idUsuario;
    char NombreLibro[41];
    printf("Ingrese el ID del usuario que realizara la devolucion: ");
    scanf("%d", &idUsuario);

    NodoUsuario **usuario = Buscar_NodoUsuario(InicioUsuarios, idUsuario);
    if (!usuario)
    {
        printf("Usuario no encontrado. Verifique el ID.\n");
        return; 
    }

    fflush(stdin);
    printf("Ingrese el nombre del libro que se devolvera: ");
    scanf("%40[^\n]", NombreLibro);

    NodoTrie **libro = Buscar_NodoLibro(InicioLibros, NombreLibro);
    if (!libro)
    {
        printf("Libro no encontrado. Verifique el ID.\n");
        return;
    }
    puts("Libro encontrado");
    NodoTransaccion **transaccion = Buscar_NodoTransaccion(InicioTransacciones, (prestamos_devoluciones){.usuario = &(*usuario)->Dato, .libro_prestado = &(*libro)->InfoLibro});
    puts("Transaccion encontrada");
    if (!transaccion)
    {
        printf("No se encontro una transaccion para este usuario y libro. Verifique los datos.\n");
        return;
    }

    time_t fechaActual = time(NULL);
    if (fechaActual > (*transaccion)->Dato.fecha_devolucion)
    {
        printf("El libro esta devuelto con retraso. Se aplicaran multas.\n");
        Multar(*usuario, (fechaActual-(*transaccion)->Dato.fecha_devolucion));
    }

    (*usuario)->Dato.libros_prestados--; // Decrementar el contador de libros prestados del usuario
    (*libro)->InfoLibro.numero_ejemplares++;  // Incrementar el número de ejemplares disponibles del libro

    NodoTransaccion *temp = *transaccion;
    *transaccion = temp->sgt;
    free(temp);

    if ((*libro)->InfoLibro.numero_ejemplares == 1){
        
        notificarDisponibilidad((*libro)->InfoLibro.Reservas, NombreLibro, InicioUsuarios);
    }


    printf("Devolucion realizada con exito.\n");
}


void MostrarUsuariosConLibrosPrestados(NodoUsuario **InicioUsuarios, NodoTrie **InicioLibros, NodoTransaccion **InicioTransacciones){
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

void RecordarLibrosVencidos(NodoUsuario **InicioUsuarios, NodoTrie **InicioLibros, NodoTransaccion **InicioTransacciones){
    limpiarPantalla();
    printf("****USUARIOS CON PRESTAMOS VENCIDOS****\n");

    NodoUsuario **auxUsuario = InicioUsuarios;
    time_t fechaActual = time(NULL);
    int transaccionesEncontradas = 0;  // Bandera para indicar si se encontraron transacciones

    while (*auxUsuario)
    {
        if ((*auxUsuario)->Dato.libros_prestados > 0)
        {
            ImprimirUsuario((*auxUsuario)->Dato);
            printf("Libros Prestados:\n");

            NodoTransaccion **auxTransaccion = InicioTransacciones;

            while (*auxTransaccion)
            {
                if (((*auxTransaccion)->Dato.usuario == &(*auxUsuario)->Dato) && (fechaActual > (*auxTransaccion)->Dato.fecha_devolucion ))
                {
                    transaccionesEncontradas = 1;  // Se encontró al menos una transacción
                    // Imprimir información del libro
                    printf("ID del Usuario: %d\n", (*auxUsuario)->Dato.id_usuario);
                    printf("Titulo del Libro: %s\n", (*auxTransaccion)->Dato.libro_prestado->titulo);
                    printf("Dias vencido: %d", fechaActual-(*auxTransaccion)->Dato.fecha_devolucion);
                    printf("NotificandoUsuario\n");
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

void iterarTrieDisponibilidad(NodoTrie *nodo, unsigned char *prefijo, int tam, NodoUsuario** InicioUsuarios){
    unsigned char newPrefix[tam+2];
    //printf("%s", prefijo); //Debug
    memcpy(newPrefix, prefijo, tam);
    newPrefix[tam+1] = 0;
    
    if (nodo->terminal){
        if (nodo->InfoLibro.Reservas->cabeza != NULL)
            notificarDisponibilidad(nodo->InfoLibro.Reservas, nodo->InfoLibro.titulo, InicioUsuarios);
    }

    for (int i=0; i < NUM_CHARS; i++){
        if (nodo->hijos[i]){
            newPrefix[tam] = i;
            iterarTrieDisponibilidad(nodo->hijos[i], newPrefix, tam+1, InicioUsuarios); 
        }
    }
}

void notificarDisponibilidadTotal(NodoTrie* root, NodoUsuario** InicioUsuarios){
    if (root == NULL){
        printf("No hay libros en el catalogo");
    }
    iterarTrieDisponibilidad(root, NULL, 0, InicioUsuarios);
}
#endif

