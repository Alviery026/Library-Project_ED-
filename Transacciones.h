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

//DECLARACION DE PROTOTIPOS DE FUNCIONES
int obtenerIDUsuario();
char* obtenerIDLibro();
void realizarPrestamo(NodoUsuario **InicioUsuarios, NodoTrie **InicioLibros, NodoTransaccion **InicioTransacciones);
void realizarTransaccion(NodoTransaccion **InicioTransacciones, NodoUsuario **usuario, NodoTrie **libro, time_t fechaActual, time_t fechaVencimiento);
void RealizarDevolucion(NodoUsuario **InicioUsuarios, NodoTrie **InicioLibros, NodoTransaccion **InicioTransacciones);
void MostrarUsuariosConLibrosPrestados(NodoUsuario **InicioUsuarios, NodoTrie **InicioLibros, NodoTransaccion **InicioTransacciones);
NodoTransaccion **Buscar_NodoTransaccion(NodoTransaccion **Inicio, prestamos_devoluciones dato);
void ImprimirTransaccionesConMultas(NodoTransaccion **InicioTransacciones);

// Función para buscar una transacción por usuario y libro
NodoTransaccion **Buscar_NodoTransaccion(NodoTransaccion **Inicio, prestamos_devoluciones dato){
    while (*Inicio)
    {
        if ((*Inicio)->Dato.usuario == dato.usuario && (*Inicio)->Dato.libro_prestado == dato.libro_prestado)
            return Inicio;
        Inicio = &((*Inicio))->sgt;
    }
    return NULL;
}

// Función para obtener el ID del usuario
int obtenerIDUsuario() {
    int idUsuario;
    printf("Ingrese el ID del usuario que realizara el prestamo: \n");
    scanf("%d", &idUsuario);
    return idUsuario;
}

// Función para obtener el ID del libro
char* obtenerIDLibro() {
    static char idLibro[41];
    fflush(stdin);
    printf("Ingrese el nombre del libro que se prestara: ");
    puts("");
    scanf("%40[^\n]", idLibro);
    return idLibro;
}

// Función para realizar un préstamo
void realizarPrestamo(NodoUsuario **InicioUsuarios, NodoTrie **InicioLibros, NodoTransaccion **InicioTransacciones) {
    limpiarPantalla();

    printf("****REALIZAR PRESTAMO****\n");

    // Obtener el ID del usuario
    int idUsuario = obtenerIDUsuario();
    NodoUsuario **usuario = Buscar_NodoUsuario(InicioUsuarios, idUsuario);

    // Verificar si el usuario existe y no tiene multas
    if (!usuario) {
        printf("Usuario no encontrado. Verifique el ID.\n");
        return;
    }
    if ((*usuario)->Dato.Multa > 0){
        printf("Usuario con Multa vigente favor de pagar\n");
        return;
    }
 
    // Obtener el nombre del libro
    char idLibro[41];
    fflush(stdin);
    printf("Ingrese el nombre del libro que se solicita: \n");
    
    // Utilizando fgets para leer el nombre del libro
    fgets(idLibro, sizeof(idLibro), stdin);
    idLibro[strcspn(idLibro, "\n")] = '\0';  // Eliminar el carácter de nueva línea

    // Buscar el libro en el catálogo
    NodoTrie **libro = Buscar_NodoLibro(InicioLibros, idLibro);
    if (!libro) {
        printf("\n-------------------------------------------------\n");
        printf("Libro no encontrado. Verifique el nombre del libro \n(respetando mayusculas y minusculas del titulo.).\n");
        printf("\n-------------------------------------------------\n");
        return;
    }

    // Verificar existencias y realizar el préstamo
    if ((*libro)->InfoLibro.numero_ejemplares == 0){
        printf("\n\n--------------------------------\n");
        puts("Existencias agotadas, reservando...");
        printf("\n----------------------------------\n");
        agregarReserva((*libro)->InfoLibro.Reservas, idUsuario);
        return;
    }

    // Obtener la fecha actual y calcular la fecha de vencimiento (15 días después)
    time_t fechaActual = time(NULL);
    struct tm *local = localtime(&fechaActual);
    local->tm_mday += 15; // Se establece la fecha de vencimiento a 15 días desde la fecha actual
    time_t fechaVencimiento = mktime(local);

    // Realizar la transacción
    realizarTransaccion(InicioTransacciones, usuario, libro, fechaActual, fechaVencimiento);
}

// Función para realizar una transacción (préstamo)
void realizarTransaccion(NodoTransaccion **InicioTransacciones, NodoUsuario **usuario, NodoTrie **libro, time_t fechaActual, time_t fechaVencimiento) {
    prestamos_devoluciones nuevaTransaccion = {
        // Crear la estructura de la transacción
        .libro_prestado = &(*libro)->InfoLibro,
        .usuario = &(*usuario)->Dato,
        .fecha_prestamo = fechaActual,
        .fecha_devolucion = fechaVencimiento
    };

    // Crear un nuevo nodo de transacción
    NodoTransaccion *nuevoNodoTransaccion = (NodoTransaccion *)malloc(sizeof(NodoTransaccion));
    if (!nuevoNodoTransaccion) {
        printf("Error al asignar memoria para la transaccion.\n");
        return;
    }

    // Asignar los datos de la transacción al nodo
    nuevoNodoTransaccion->Dato = nuevaTransaccion;
    nuevoNodoTransaccion->sgt = *InicioTransacciones;
    *InicioTransacciones = nuevoNodoTransaccion;

    (*usuario)->Dato.libros_prestados++; // Incrementar el contador de libros prestados del usuario
    (*libro)->InfoLibro.numero_ejemplares--;  // Decrementar el número de ejemplares disponibles del libro
    printf("_____________________________________________\n");
    printf("\nPrestamo realizado con exito. \nFecha a devolver: %s", ctime(&fechaVencimiento));
    printf("_____________________________________________\n");
}

// Función para realizar una devolución
void RealizarDevolucion(NodoUsuario **InicioUsuarios, NodoTrie **InicioLibros, NodoTransaccion **InicioTransacciones){
    limpiarPantalla();
    printf("****REALIZAR DEVOLUCION****\n");

    // Obtener el ID del usuario
    int idUsuario;
    char NombreLibro[41];
    printf("Ingrese el ID del usuario que realizara la devolucion: \n");
    scanf("%d", &idUsuario);

    // Buscar al usuario en la lista
    NodoUsuario **usuario = Buscar_NodoUsuario(InicioUsuarios, idUsuario);
    if (!usuario)
    {
        printf("Usuario no encontrado. Verifique el ID.\n");
        return; 
    }

    // Obtener el nombre del libro
    fflush(stdin);
    printf("Ingrese el nombre del libro que se devolvera: \n");
    scanf("%40[^\n]", NombreLibro);

    // Buscar el libro en el catálogo
    NodoTrie **libro = Buscar_NodoLibro(InicioLibros, NombreLibro);
    if (!libro)
    {
        printf("\n---------------------------------------------------\n");
        printf("Libro no encontrado. Verifique el nombre del libro \n(respetando mayusculas y minusculas del titulo.).\n");
        printf("\n---------------------------------------------------\n");
        return;
    }
    printf("\n---------------------------------\n");
    puts("->Libro encontrado");

    // Buscar la transacción correspondiente
    NodoTransaccion **transaccion = Buscar_NodoTransaccion(InicioTransacciones, (prestamos_devoluciones){.usuario = &(*usuario)->Dato, .libro_prestado = &(*libro)->InfoLibro});
    if (!transaccion)
    {
            printf("\n---------------------------------\n");
        printf("No se encontro alguna transaccion \npara este usuario y libro. \n\n->Verifique los datos.\n");
            printf("---------------------------------\n");
        return;
    }


    // Obtener la fecha actual
    time_t fechaActual = time(NULL);

    // Verificar si la devolución está atrasada y aplicar multas
    if (fechaActual > (*transaccion)->Dato.fecha_devolucion)
    {
        printf("El libro esta devuelto con retraso. Se aplicaran multas.\n");
        Multar(*usuario, (fechaActual-(*transaccion)->Dato.fecha_devolucion));
    }

    (*usuario)->Dato.libros_prestados--;     // Decrementar el contador de libros prestados del usuario
    (*libro)->InfoLibro.numero_ejemplares++; // Incrementar el número de ejemplares disponibles del libro

    // Eliminar la transacción de la lista
    NodoTransaccion *temp = *transaccion;
    *transaccion = temp->sgt;
    free(temp);


    // Verificar si quedaba solo un ejemplar y notificar disponibilidad a reservas
    if ((*libro)->InfoLibro.numero_ejemplares == 1){
        
        notificarDisponibilidad((*libro)->InfoLibro.Reservas, NombreLibro, InicioUsuarios);
    }

    // Imprimir mensaje de éxito
    printf("->Devolucion realizada con exito.\n");
    printf("---------------------------------\n");
}

// Función para mostrar usuarios con libros prestados
void MostrarUsuariosConLibrosPrestados(NodoUsuario **InicioUsuarios, NodoTrie **InicioLibros, NodoTransaccion **InicioTransacciones){
    limpiarPantalla();
    printf("****USUARIOS CON LIBROS PRESTADOS****\n");
 
    // Inicializar puntero a la lista de usuarios
    NodoUsuario **auxUsuario = InicioUsuarios;
    int transaccionesEncontradas = 0;  // Bandera para indicar si se encontraron transacciones
  

    // Iterar sobre la lista de usuarios
    while (*auxUsuario)
    {
        if ((*auxUsuario)->Dato.libros_prestados > 0)
        {
            transaccionesEncontradas = 1;  // Se encontró al menos una transacción
            ImprimirUsuario((*auxUsuario)->Dato);

            // Inicializar puntero a la lista de transacciones
            NodoTransaccion **auxTransaccion = InicioTransacciones;
            
            // Iterar sobre la lista de transacciones
            while (*auxTransaccion)
            {
                if ((*auxTransaccion)->Dato.usuario == &(*auxUsuario)->Dato)
                {
                    // Imprimir información del libro
                    printf("----------------------------\n");
                    printf("ID del Usuario: %d\n", (*auxUsuario)->Dato.id_usuario);
                    printf("ID del Libro: %d\n", (*auxTransaccion)->Dato.libro_prestado->id_libro);
                    printf("Titulo del Libro: %s\n", (*auxTransaccion)->Dato.libro_prestado->titulo);
                    printf("Fecha de Prestamo: %s", ctime(&(*auxTransaccion)->Dato.fecha_prestamo));
                }

                auxTransaccion = &(*auxTransaccion)->sgt;
            }
        }
        auxUsuario = &(*auxUsuario)->sgt;
    }


    // Imprimir mensaje si no se encontraron transacciones
    if (!transaccionesEncontradas) {
        printf("\n------------------------------------\n");
        printf("No hay transacciones vigentes...\n");
        printf("------------------------------------\n");
    }

    // Pausar la ejecución para visualizar resultados
    pausar();
}

// Función para recordar libros con préstamos vencidos
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

// Función para recordar libros vencidos y aplicar multas
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

// Función para iterar sobre el Trie y notificar disponibilidad de libros reservados
void notificarDisponibilidadTotal(NodoTrie* root, NodoUsuario** InicioUsuarios){
    if (root == NULL){
        printf("No hay libros en el catalogo");
    }
    iterarTrieDisponibilidad(root, NULL, 0, InicioUsuarios);
}
#endif
