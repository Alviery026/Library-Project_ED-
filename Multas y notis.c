#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// Estructura para representar multas
typedef struct {
    struct NodoUsuario *usuario;
    int monto;
    fecha fecha_generacion;
} multas;

// Estructura para representar notificaciones
typedef struct {
    struct NodoUsuario *usuario;
    char mensaje[100];
    fecha fecha_generacion;
} notificaciones;

// Estructura para representar usuarios
typedef struct usuarios {
    char nombre[40];
    char apellido[40];
    int id_usuario;
    int libros_prestados;
    fecha fecha_nac;
    multas MultasUsuario;  // Campo para multas
    notificaciones NotificacionesUsuario;  // Campo para notificaciones
} usuarios;

// Definicion de nodos para listas enlazadas
typedef struct NodoUsuario {
    usuarios Dato;
    struct NodoUsuario *sgt;
} NodoUsuario;

// Estructura para representar libros
typedef struct libros {
    int id_libro;
    char titulo[50];
    char autor[50];
    char editorial[50];
    int numero_ejemplares;
    fecha anio_publicacion;
} libros;

// Definición de nodos para listas enlazadas
typedef struct NodoUsuario {
    usuarios Dato;
    struct NodoUsuario *sgt;
} NodoUsuario;

typedef struct NodoLibro {
    libros Dato;
    struct NodoLibro *sgt;
} NodoLibro;

// funciones
void CargarDatosPredeterminados(NodoUsuario **InicioUsuarios, NodoLibro **InicioLibros, int *IDUsuarios, int *IDLibros);
void GenerarMultas(NodoUsuario **InicioUsuarios);
void GenerarNotificaciones(NodoUsuario **InicioUsuarios);
void menuPrincipal(NodoUsuario **InicioUsuarios, NodoLibro **InicioLibros, int *IDUsuarios, int *IDLibros);
int CalcularDiasRetraso(fecha fecha_generacion, fecha fecha_actual);
int CalcularMontoMulta(int diasRetraso);



int main(void) {
    NodoUsuario *InicioUsuarios = NULL;
    NodoLibro *InicioLibros = NULL;
    int IDUsuarios = 1;
    int IDLibros = 1;

    //  cargar datos predeterminados
    CargarDatosPredeterminados(&InicioUsuarios, &InicioLibros, &IDUsuarios, &IDLibros);


    menuPrincipal(&InicioUsuarios, &InicioLibros, &IDUsuarios, &IDLibros);

    return 0;
}



// generar multas y notificaciones
void GenerarMultas(NodoUsuario **InicioUsuarios) {
    time_t ahora = time(NULL);
    struct tm *tm_actual = localtime(&ahora);
    fecha fecha_actual = {tm_actual->tm_mday, tm_actual->tm_mon + 1, tm_actual->tm_year + 1900};

    NodoUsuario **aux = InicioUsuarios;
    while (*aux) {
        int diasRetraso = CalcularDiasRetraso((*aux)->MultasUsuario.fecha_generacion, fecha_actual);

        if (diasRetraso > 0) {
            int montoMulta = CalcularMontoMulta(diasRetraso);
            // Actualizar multa y notificación
            (*aux)->MultasUsuario.monto = montoMulta;
            strcpy((*aux)->NotificacionesUsuario.mensaje, "Tiene una multa pendiente. Por favor, regularice su situación.");
        }

        aux = &(*aux)->sgt;
    }
}

//  calcular días de retraso
int CalcularDiasRetraso(fecha fecha_generacion, fecha fecha_actual) {
   
    int diasRetraso = 0;

    if (fecha_actual.mes == fecha_generacion.mes) {
        diasRetraso = fecha_actual.dia - fecha_generacion.dia;
    } else if (fecha_actual.mes > fecha_generacion.mes) {
        diasRetraso = 30 - fecha_generacion.dia + fecha_actual.dia;
    }

    return diasRetraso;
}

//  calcular el monto de la multa
int CalcularMontoMulta(int diasRetraso) {
    //  $100 por el primer día y $50 adicionales por cada día subsiguiente
    if (diasRetraso > 0) {
        int montoMulta = 100 + (diasRetraso - 1) * 50;
        return montoMulta;
    } else {
        return 0;  // no hay retraso, sin multa
    }
}

// generar notificaciones
void GenerarNotificaciones(NodoUsuario **InicioUsuarios) {
    time_t ahora = time(NULL);
    struct tm *tm_actual = localtime(&ahora);
    fecha fecha_actual = {tm_actual->tm_mday, tm_actual->tm_mon + 1, tm_actual->tm_year + 1900};

    NodoUsuario **aux = InicioUsuarios;
    while (*aux) {
        int diasRetraso = CalcularDiasRetraso((*aux)->MultasUsuario.fecha_generacion, fecha_actual);

        if (diasRetraso > 0) {
            // notificación
            sprintf((*aux)->NotificacionesUsuario.mensaje, "Recordatorio: Tiene una multa de $%d pendiente. Por favor, regularice su situación.", (*aux)->MultasUsuario.monto);
        }

        aux = &(*aux)->sgt;
    }
}


