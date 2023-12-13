#include "DatosPredeterminados.h"
#include "LibreriaGeneral.h"
#include "Registro.h"
#include "Transacciones.h"
#include "ArbolTrie.h"
#include "Multas.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Declaración de  de menús del programa
void menuPrincipal(NodoUsuario **InicioUsuarios, NodoTrie **InicioLibros,NodoTransaccion **InicioTransacciones, int *IDUsuarios, int *IDLibros);
void menuUsuarios(NodoUsuario **InicioUsuarios, NodoTrie **InicioLibros,int *IDUsuarios, int *IDLibros);
void menuLibros(NodoUsuario **InicioUsuarios, NodoTrie **InicioLibros, int *IDUsuarios, int *IDLibros);
void menuMultas(NodoUsuario** InicioUsuarios);
void menuNotificaciones(NodoUsuario** InicioUsuarios, NodoTrie** InicioLibros, NodoTransaccion** InicioTransaccion);
void menuTransacciones(NodoUsuario **InicioUsuarios, NodoTrie **InicioLibros,NodoTransaccion **InicioTransacciones,int *IDUsuarios, int *IDLibros);

int main(void) {
  NodoUsuario *InicioUsuarios = NULL; // Inicialización lista usuarios
  NodoTrie *InicioLibros = NULL;     // Inicialización lista libros
  NodoTransaccion *InicioTransacciones = NULL; // Inicialización lista Transaccion
  int IDUsuarios = 1;                 // Inicialización ID para usuarios
  int IDLibros = 1;                   // Inicialización ID para libros


  // Llamada de la función para cargar datos predeterminados
  CargarDatosPredeterminados(&InicioUsuarios, &InicioLibros, &IDUsuarios, &IDLibros, &InicioTransacciones);

  menuPrincipal(&InicioUsuarios, &InicioLibros, &InicioTransacciones, &IDUsuarios, &IDLibros);



  return 0;
}




//FUNCIONES DE MENÚS:

void menuPrincipal(NodoUsuario **InicioUsuarios, NodoTrie **InicioLibros,NodoTransaccion **InicioTransacciones, int *IDUsuarios, int *IDLibros) {
  
  int opcion;
  do {
    limpiarPantalla(); // Limpia la pantalla antes de mostrar el menú principal
    printf("----------------------------------\n");
    printf("****MENU DE LA BIBLIOTECA FIEE****\n");
    printf("----------------------------------\n");
    printf("1.- Usuarios\n");
    printf("2.- Catalogo de Libros\n");
    printf("3.- Transaccion\n");
    printf("4.- Multas\n");
    printf("5.- Notificaciones\n");
    printf("6. Salir del programa\n");
    printf("Seleccione una opcion: ");
    scanf("%d", &opcion);

    switch (opcion) {
    case 1:
      menuUsuarios(InicioUsuarios, InicioLibros, IDUsuarios, IDLibros);
      break;
    case 2:
      limpiarPantalla();
      menuLibros(InicioUsuarios, InicioLibros, IDUsuarios, IDLibros);
      limpiarPantalla();
      break;
    case 3:
      menuTransacciones(InicioUsuarios, InicioLibros, InicioTransacciones, IDUsuarios, IDLibros);
      break;
    case 4:
      menuMultas(InicioUsuarios);

      break;
    case 5:
      menuNotificaciones(InicioUsuarios, InicioLibros, InicioTransacciones);
      break;
    case 6:
      printf("Saliendo del programa...\n");
      return;
    default:
      printf("Opcion no valida. Intente de nuevo.\n");
    }
  } while (opcion != 6);
}

void menuUsuarios(NodoUsuario **InicioUsuarios, NodoTrie **InicioLibros,int *IDUsuarios, int *IDLibros) {
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
      limpiarPantalla();
      Imprimir_Lista_Usuarios(InicioUsuarios);
      pausar();
      break;
    case 3:
      // Salir al menú principal
      break;
    default:
      printf("Opción no válida. Intente de nuevo.\n");
    }
  } while (opcion != 3);
}

void menuLibros(NodoUsuario **InicioUsuarios, NodoTrie **InicioLibros,int *IDUsuarios, int *IDLibros) {
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
      Insertar_ManualLibro(InicioLibros, IDLibros);
      break;
    case 2:
      Imprimir_Trie(*InicioLibros);
      pausar();
      break;
    case 3:
      // Volver al menú principal
      return;
    default:
      printf("Opción no válida. Intente de nuevo:\n");
    }
  } while (opcion != 3);
}

void menuTransacciones(NodoUsuario **InicioUsuarios, NodoTrie **InicioLibros,NodoTransaccion **InicioTransacciones, int *IDUsuarios, int *IDLibros) {
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
      pausar();
      break;
    case 2:
      RealizarDevolucion(InicioUsuarios, InicioLibros, InicioTransacciones);
      pausar();
      break;
    case 3:
      limpiarPantalla();
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

void menuMultas(NodoUsuario** InicioUsuarios){
  int opcion;
  do{
    limpiarPantalla();
    printf("\n****MENU DE MULTAS****\n");
    printf("1. Pagar Multas\n");
    printf("2. Regresar al menu principal\n");
    scanf("%d", &opcion);
    switch (opcion)
    {
    case 1:
      PagarMultas(InicioUsuarios);
      break;
    case 2:
      return;
    default:
      printf("Opcion no valida. Intente de nuevo:\n");
      break;
    }
  }while (opcion != 2);
}

void menuNotificaciones(NodoUsuario** InicioUsuarios, NodoTrie** InicioLibros, NodoTransaccion** InicioTransaccion){
  int opcion;
  do{
    limpiarPantalla();
    printf("\n****MENU DE NOTIFICACIONES****\n");
    printf("1. Notificar usuarios con libros atrasados\n");
    printf("2. Notificar disponibilidad de libros\n");
    printf("3. Regresar al menu principal\n");
    scanf("%d", &opcion);
    switch (opcion)
    {
    case 1:
      RecordarLibrosVencidos(InicioUsuarios, InicioLibros, InicioTransaccion);
      break;
    case 2:
      notificarDisponibilidadTotal(*InicioLibros, InicioUsuarios);
      break;
    case 3:
      return;
    default:
      printf("Opcion no valida. Intente de nuevo:\n");
      break;
    }
  }while (opcion != 2);
}
