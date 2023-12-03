#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "LibreriaGeneral.h"
#include "Registro.h"

int main(void) {
    NodoUsuario* Inicio = NULL;     // Inicialización lista usuarios
    int ID = 1;                     // Inicialización ID

    int opcion;
    do {
        printf("\nOpciones:\n");
        printf("1. Registrar nuevo usuario\n");
        printf("2. Ver lista de usuarios registrados\n");
        printf("3. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                RegistroManualUsuario(&Inicio, &ID);
                break;
            case 2:
                Imprimir_Lista_Usuarios(&Inicio);
                break;
            case 3:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción no válida. Intente de nuevo.\n");
        }
    } while (opcion != 3);

    return 0;
}

