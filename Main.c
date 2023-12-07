#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "LibreriaGeneral.h"
#include "Registro.h"
#include "DatosPredeterminados.h"

int main(void)
{
    NodoUsuario *InicioUsuarios = NULL; // Inicialización lista usuarios
    NodoLibro *InicioLibros = NULL;     // Inicialización lista libros
    int IDUsuarios = 1;                 // Inicialización ID para usuarios
    int IDLibros = 1;                   // Inicialización ID para libros

    // Llamar a la función para cargar datos predeterminados
    CargarDatosPredeterminados(&InicioUsuarios, &InicioLibros, &IDUsuarios, &IDLibros);


    int opcion;
    do
    {
        printf("\n****BIENVENIDO A LA BIBLIOTECA FIEE**** \n");
        printf("1. Registrar nuevo usuario\n");
        printf("2. Ver lista de usuarios registrados\n");
        printf("3. Registrar libros\n");
        printf("4. Ver lista de libros registrados\n");
        printf("5. Realizar prestamo\n");
        printf("6. Realizar una devolucion\n");
        printf("7. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            RegistroManualUsuario(&InicioUsuarios, &IDUsuarios);
            break;
        case 2:
            Imprimir_Lista_Usuarios(&InicioUsuarios);
            break;
        case 3:
            RegistroManualLibro(&InicioLibros, &IDLibros);
            break;
        case 4:
            Imprimir_Lista_Libros(&InicioLibros);
            break;
        case 5:

            break;
        case 6:

            break;
        case 7:
            printf("Saliendo del programa...\n");
            break;
        default:
            printf("Opcion no valida. Intente de nuevo.\n");
        }
    } while (opcion != 7);

    return 0;
}