
#ifndef MultasYNotis_h
#define MultasYNotis_h

#include "LibreriaGeneral.h"
#include "Registro.h"
#include "Transacciones.h"

typedef struct {
    NodoUsuario *usuario;
    int monto;
    fecha fecha_generacion;
} multas;

typedef struct {
    NodoUsuario *usuario;
    char mensaje[100];
    fecha fecha_generacion;
} notificaciones;

void GenerarMultasYNotificaciones(NodoUsuario **InicioUsuarios, NodoTransaccion **InicioTransacciones);

void GenerarMultasYNotificaciones(NodoUsuario **InicioUsuarios, NodoTransaccion **InicioTransacciones) {
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

#endif
