#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura para representar un libro
typedef struct {
    char titulo[100];
    int prestado; // 0 si no está prestado, 1 si está prestado
    int reservable; // 1 si se puede reservar, 0 si no se puede reservar
} Libro;

// Estructura para representar un nodo de reserva
typedef struct ReservaNodo {
    char nombreUsuario[50];
    struct ReservaNodo* siguiente;
} ReservaNodo;

// Estructura para representar una lista enlazada de reservas
typedef struct {
    ReservaNodo* cabeza;
} ListaReservas;

// Estructura para representar un usuario
typedef struct {
    char nombre[50];
    ListaReservas reservas;
} Usuario;

// Función para agregar una reserva a la lista
void agregarReserva(ListaReservas* listaReservas, char nombreUsuario[]) {
    ReservaNodo* nuevoNodo = (ReservaNodo*)malloc(sizeof(ReservaNodo));
    strcpy(nuevoNodo->nombreUsuario, nombreUsuario);
    nuevoNodo->siguiente = NULL;

    // Si la lista está vacía, el nuevo nodo se convierte en la cabeza
    if (listaReservas->cabeza == NULL) {
        listaReservas->cabeza = nuevoNodo;
    } else {
        // Si no, se agrega al final de la lista
        ReservaNodo* actual = listaReservas->cabeza;
        while (actual->siguiente != NULL) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevoNodo;
    }
}

// Función para notificar a los usuarios cuando un libro está disponible
void notificarDisponibilidad(ListaReservas* listaReservas, Libro* libro) {
    if (listaReservas->cabeza != NULL) {
        ReservaNodo* liberarNodo = listaReservas->cabeza;
        listaReservas->cabeza = liberarNodo->siguiente;

        printf("Libro '%s' ahora disponible. Reserva para %s notificada.\n", libro->titulo, liberarNodo->nombreUsuario);

        free(liberarNodo);
    }
}

// Función para notificar a los usuarios cuando no se puede reservar un libro
void notificarNoReservable(Usuario* usuario, Libro* libro) {
    printf("Libro '%s' no se puede reservar por el usuario %s.\n", libro->titulo, usuario->nombre);
}

int main() {
    // Ejemplo de datos de varios libros
    Libro libros[] = {
        {"Libro1", 0, 1}, // Inicialmente no prestado y reservable
        {"Libro2", 1, 0}, // Inicialmente prestado y no reservable
        // Puedes agregar más libros según sea necesario
    };

    // Ejemplo de datos de varios usuarios
    Usuario usuarios[] = {
        {"Usuario1", {NULL}},
        {"Usuario2", {NULL}},
        // Puedes agregar más usuarios según sea necesario
    };

    // Usuarios reservan libros
    if (libros[1].reservable) {
        agregarReserva(&usuarios[0].reservas, "Usuario1");
    } else {
        notificarNoReservable(&usuarios[0], &libros[0]);
    }

    if (libros[0].reservable) {
        agregarReserva(&usuarios[1].reservas, "Usuario2");
    } else {
        notificarNoReservable(&usuarios[1], &libros[1]);
    }

    // Simulación: si un libro se devuelve, notificar a los usuarios en la lista de reservas
    if (libros[1].prestado == 0) {
        notificarDisponibilidad(&usuarios[0].reservas, &libros[0]);
    }

    if (libros[0].prestado == 0) {
        notificarDisponibilidad(&usuarios[1].reservas, &libros[1]);
    }

    return 0;
}
