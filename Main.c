#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "LibreriaGeneral.h"
#include "Registro.h"

int main(void) {
    NodoUsuario* Inicio = NULL;     // Inicializaci�n lista usuarios
    int ID = 1;                     // Inicializaci�n ID

    int opcion;
    do {
        printf("\nOpciones:\n");
        printf("1. Registrar nuevo usuario\n");
        printf("2. Ver lista de usuarios registrados\n");
        printf("3. Salir\n");
        printf("Seleccione una opci�n: ");
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
                printf("Opci�n no v�lida. Intente de nuevo.\n");
        }
    } while (opcion != 3);

    return 0;
}

