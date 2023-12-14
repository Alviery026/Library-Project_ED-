#include "DatosPredeterminados.h"
#include "LibreriaGeneral.h"
#include "Registro.h"
#include "Transacciones.h"
#include "ArbolTrie.h"
#include "Multas.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Declaración de prototipos de función de los multiples menús del programa
void menuPrincipal(NodoUsuario **InicioUsuarios, NodoTrie **InicioLibros,NodoTransaccion **InicioTransacciones, int *IDUsuarios, int *IDLibros);
void menuUsuarios(NodoUsuario **InicioUsuarios, NodoTrie **InicioLibros,int *IDUsuarios, int *IDLibros);
void menuLibros(NodoUsuario **InicioUsuarios, NodoTrie **InicioLibros, int *IDUsuarios, int *IDLibros);
void menuMultas(NodoUsuario** InicioUsuarios);
void menuNotificaciones(NodoUsuario** InicioUsuarios, NodoTrie** InicioLibros, NodoTransaccion** InicioTransaccion);
void menuTransacciones(NodoUsuario **InicioUsuarios, NodoTrie **InicioLibros,NodoTransaccion **InicioTransacciones,int *IDUsuarios, int *IDLibros);
void acercaDeNosotros();

// Función principal del programa
int main(void) {
  NodoUsuario *InicioUsuarios = NULL;            // Inicialización lista usuarios
  NodoTrie *InicioLibros = NULL;                // Inicialización lista libros
  NodoTransaccion *InicioTransacciones = NULL; // Inicialización lista Transaccion
  int IDUsuarios = 1;                         // Inicialización ID para usuarios
  int IDLibros = 1;                          // Inicialización ID para libros


  // Llamada de la función para cargar datos predeterminados
  CargarDatosPredeterminados(&InicioUsuarios, &InicioLibros, &IDUsuarios, &IDLibros, &InicioTransacciones);

  // Llamada de la funcion de el menú principal del programa
  menuPrincipal(&InicioUsuarios, &InicioLibros, &InicioTransacciones, &IDUsuarios, &IDLibros);



  return 0;
}




// FUNCIONES DE MENÚS:
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
    printf("6.- Acerca de nosotros\n");
    printf("7. Salir del programa\n");
    printf("Seleccione una opcion: ");
    scanf("%d", &opcion);

    switch (opcion) {
    case 1:
      // Ir al menú de usuarios
      menuUsuarios(InicioUsuarios, InicioLibros, IDUsuarios, IDLibros);
      break;
    case 2:
      limpiarPantalla();
      // Ir al menú de libros
      menuLibros(InicioUsuarios, InicioLibros, IDUsuarios, IDLibros);
      limpiarPantalla();
      break;
    case 3:
      // Ir al menú de transacciones
      menuTransacciones(InicioUsuarios, InicioLibros, InicioTransacciones, IDUsuarios, IDLibros);
      break;
    case 4:
      // Ir al menú de multas
      menuMultas(InicioUsuarios);
      break;
    case 5:
      // Ir al menú de notificaciones
      menuNotificaciones(InicioUsuarios, InicioLibros, InicioTransacciones);
      break;
    case 6:
      // Ir a la funcion de informacion del equipo
      acercaDeNosotros();
      break;
    case 7:
      // Salir del programa
      printf("\n->Saliendo del programa...\n");
      return;
    default:
      printf("Opcion no valida. Intente de nuevo.\n");
    }
  } while (opcion != 7);
}

// Menú de usuarios
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
      // Registrar nuevo usuario
      RegistroManualUsuario(InicioUsuarios, IDUsuarios);
      break;
    case 2:
      limpiarPantalla();
      // Ver lista de usuarios registrados
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

// Menú de libros
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

// Menú de transacciones
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
      // Realizar préstamo
      realizarPrestamo(InicioUsuarios, InicioLibros, InicioTransacciones);
      pausar();
      break;
    case 2:
      // Realizar devolución
      RealizarDevolucion(InicioUsuarios, InicioLibros, InicioTransacciones);
      pausar();
      break;
    case 3:
      // Mostrar transacciones vigentes
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

// Menú de multas
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
      // Pagar multas
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

// Menú de notificaciones
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
      // Notificar usuarios con libros atrasados
      RecordarLibrosVencidos(InicioUsuarios, InicioLibros, InicioTransaccion);
      break;
    case 2:
      // Notificar disponibilidad de libros
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

// Función para mostrar la información del equipo
void acercaDeNosotros() {
    limpiarPantalla();
    printf("----------------------------------------\n");
    printf("****ACERCA DE NOSOTROS - EQUIPO 7****\n");
    printf("----------------------------------------\n");

    printf("\nMIEMBROS:\n");
    printf("-> Policarpio Moran Michell Alexis - zs21002379\n");
    printf("-> Villar Caparroso Jose Antonio - zs21002440\n");
    printf("-> Rios Valtierra Bryant Alviery - zs20004637\n");
    printf("-> Valdes Palmero Jair de Jesus - zs19022211\n");

    printf("\nDOCENTE: Fleitas Toranzo Yadira\n");
    printf("\nMATERIA: Estructura de Datos - NRC: 21602 \n");
    printf("\nPROYECTO: Biblioteca\n");
    printf("\nFacultad de Ingenieria Electrica y Electronica (FIEE) \n\nUniversidad Veracruzana (UV)\n");

    // Pausa para que el usuario pueda ver la información
    pausar();
}