#include "DatosPredeterminados.h"
#include "LibreriaGeneral.h"
#include "Registro.h"
#include "Transacciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Declaración de  de menús del programa
void menuPrincipal(NodoUsuario **InicioUsuarios, NodoLibro **InicioLibros,NodoTransaccion **InicioTransacciones, int *IDUsuarios, int *IDLibros);
void menuUsuarios(NodoUsuario **InicioUsuarios, NodoLibro **InicioLibros,int *IDUsuarios, int *IDLibros);
void menuLibros(NodoUsuario **InicioUsuarios, NodoLibro **InicioLibros, int *IDUsuarios, int *IDLibros);
void menuTransacciones(NodoUsuario **InicioUsuarios, NodoLibro **InicioLibros,NodoTransaccion **InicioTransacciones,int *IDUsuarios, int *IDLibros);

int main(void) {
  NodoUsuario *InicioUsuarios = NULL; // Inicialización lista usuarios
  NodoLibro *InicioLibros = NULL;     // Inicialización lista libros
  NodoTransaccion *InicioTransacciones = NULL; // Inicialización lista Transaccion
  int IDUsuarios = 1;                 // Inicialización ID para usuarios
  int IDLibros = 1;                   // Inicialización ID para libros


  // Llamada de la función para cargar datos predeterminados
  CargarDatosPredeterminados(&InicioUsuarios, &InicioLibros, &IDUsuarios, &IDLibros, &InicioTransacciones);

  menuPrincipal(&InicioUsuarios, &InicioLibros, &InicioTransacciones, &IDUsuarios, &IDLibros);



  return 0;
}




//FUNCIONES DE MENÚS:

void menuPrincipal(NodoUsuario **InicioUsuarios, NodoLibro **InicioLibros,NodoTransaccion **InicioTransacciones, int *IDUsuarios, int *IDLibros) {
  
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
      menuTransacciones(InicioUsuarios, InicioLibros, InicioTransacciones, IDUsuarios, IDLibros);
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

void menuUsuarios(NodoUsuario **InicioUsuarios, NodoLibro **InicioLibros,int *IDUsuarios, int *IDLibros) {
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
      break;
    default:
      printf("Opción no válida. Intente de nuevo.\n");
    }
  } while (opcion != 3);
}

void menuLibros(NodoUsuario **InicioUsuarios, NodoLibro **InicioLibros,int *IDUsuarios, int *IDLibros) {
  int opcion;
  do {
    limpiarPantalla();
    printf("\n****MENU DE LIBROS****\n");
    printf("1. Registrar nuevo libro\n");
    printf("2. Ver lista de libros registrados\n");
    printf("3. Volver al menu principal\n");
    printf("Seleccione una opcion: ");
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

void menuTransacciones(NodoUsuario **InicioUsuarios, NodoLibro **InicioLibros,NodoTransaccion **InicioTransacciones, int *IDUsuarios, int *IDLibros) {
  int opcion;
  do {
    limpiarPantalla();
    printf("\n****MENU DE TRANSACCIONES****\n");
    printf("1. Realizar prestamo\n");
    printf("2. Realizar devolucion\n");
    printf("3. Mostrar transacciones vigentes\n");
    printf("4. Volver al menu principal\n");
    printf("Seleccione una opcion: ");
    scanf("%d", &opcion);

    switch (opcion) {
    case 1:
      realizarPrestamo(InicioUsuarios, InicioLibros, InicioTransacciones);
      break;
    case 2:
      RealizarDevolucion(InicioUsuarios, InicioLibros, InicioTransacciones);
      break;
    case 3:
      MostrarUsuariosConLibrosPrestados(InicioUsuarios, InicioLibros, InicioTransacciones);
      break;
    case 4: 
      //Volver al menu principal
      return;
    default:
      printf("Opcion no valida. Intente de nuevo:\n");
    }
  } while (opcion != 4);
}
