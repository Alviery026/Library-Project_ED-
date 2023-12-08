#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "LibreriaGeneral.h"
#include "Registro.h"
#include "DatosPredeterminados.h"

// Declaración de  de menús del programa
void menuPrincipal(NodoUsuario **InicioUsuarios, NodoLibro **InicioLibros, int *IDUsuarios, int *IDLibros);
void menuUsuarios(NodoUsuario **InicioUsuarios, NodoLibro **InicioLibros, int *IDUsuarios, int *IDLibros);
void menuLibros(NodoUsuario **InicioUsuarios, NodoLibro **InicioLibros, int *IDUsuarios, int *IDLibros);
void limpiarPantalla();

int main(void)
{
    NodoUsuario *InicioUsuarios = NULL; // Inicialización lista usuarios
    NodoLibro *InicioLibros = NULL;     // Inicialización lista libros
    int IDUsuarios = 1;                 // Inicialización ID para usuarios
    int IDLibros = 1;                   // Inicialización ID para libros

    // Llamar a la función para cargar datos predeterminados
    CargarDatosPredeterminados(&InicioUsuarios, &InicioLibros, &IDUsuarios, &IDLibros);

    menuPrincipal(&InicioUsuarios, &InicioLibros, &IDUsuarios, &IDLibros);

    return 0;
}

void menuPrincipal(NodoUsuario **InicioUsuarios, NodoLibro **InicioLibros, int *IDUsuarios, int *IDLibros) {
    int opcion;
    do {
        limpiarPantalla(); // Limpia la pantalla antes de mostrar el menú principal
        printf("****MENU DE LA BIBLIOTECA FIEE****\n");
        printf("1.- Usuarios\n");
        printf("2.- Catalogo de Libros\n");
        printf("3.- Transaccion\n");
        printf("4.- Multas y recordatorios\n");
        printf("5.- Notificaciones\n");
        printf("6. Salir del programa\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                menuUsuarios(InicioUsuarios, InicioLibros, IDUsuarios, IDLibros);
                break;
            case 2:
                menuLibros(InicioUsuarios, InicioLibros, IDUsuarios, IDLibros);
                break;
            case 3:
                // Agrega la lógica para transacciones
                break;
            case 4:
                // Agrega la lógica para multas y recordatorios
                break;
            case 5:
                // Agrega la lógica para notificaciones
                break;
            case 6:
                printf("Saliendo del programa...\n");
                return;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
        }
    } while (opcion != 6);
}

void menuUsuarios(NodoUsuario **InicioUsuarios, NodoLibro **InicioLibros, int *IDUsuarios, int *IDLibros) {
    int opcion;
    do {
        limpiarPantalla();
        printf("\n****MENU DE USUARIO****\n");
        printf("1. Registrar nuevo usuario\n");
        printf("2. Ver lista de usuarios registrados\n");
        printf("3. Salir al menu principal\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
        case 1:
            RegistroManualUsuario(InicioUsuarios, IDUsuarios);
            break;
        case 2:
            Imprimir_Lista_Usuarios(InicioUsuarios);
            break;
        case 3:
            // Salir al menú principal
            menuPrincipal(InicioUsuarios, InicioLibros, IDUsuarios, IDLibros);
            break;
        default:
            printf("Opción no válida. Intente de nuevo.\n");
        }
    } while (opcion != 3);
}

void menuLibros(NodoUsuario **InicioUsuarios, NodoLibro **InicioLibros, int *IDUsuarios, int *IDLibros) {
    int opcion;
    do {
        printf("\n****MENU DE LIBROS****\n");
        printf("1. Registrar nuevo libro\n");
        printf("2. Ver lista de libros registrados\n");
        printf("3. Volver al menú principal\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
        case 1:
            RegistroManualLibro(InicioLibros, IDLibros);
            break;
        case 2:
            Imprimir_Lista_Libros(InicioLibros);
            break;
        case 3:
            // Volver al menú principal
            return;
        default:
            printf("Opción no válida. Intente de nuevo:\n");
        }
    } while (opcion != 3);
}

void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}