
#include "Recordatorios.h"
#include "Multas.h"
#include <stdio.h>

void EnviarRecordatoriosMultas(NodoUsuario **InicioUsuarios) {
    limpiarPantalla();
    printf("****ENVIAR RECORDATORIOS DE MULTAS****\n");

    NodoUsuario **auxUsuario = InicioUsuarios;
    int recordatoriosEnviados = 0;  // bandera para indicar si se enviaron recordatorios

    while (*auxUsuario) {
        if ((*auxUsuario)->Dato.multa) {
            // el usuario tiene una multa, enviar recordatorio
            printf("Enviando recordatorio al usuario %s %s por una multa pendiente.\n",
                   (*auxUsuario)->Dato.nombre, (*auxUsuario)->Dato.apellido);

            // puedes agregar aqui la logica especifica para enviar el recordatorio 

            recordatoriosEnviados = 1;  // se envio al menos un recordatorio
        }
        auxUsuario = &(*auxUsuario)->sgt;
    }

    if (!recordatoriosEnviados) {
        printf("No hay recordatorios para enviar.\n");
    }

    pausar();
}


void VisualizarNotificacionesEnviadas(NodoUsuario** InicioUsuarios) {
    limpiarPantalla();
    printf("****VISUALIZAR NOTIFICACIONES ENVIADAS****\n");

    NodoUsuario** auxUsuario = InicioUsuarios;
    int notificacionesVisualizadas = 0;  // bandera para indicar si se visualizaron notificaciones

    while (*auxUsuario) {
        if ((*auxUsuario)->Dato.ListaRecordatorios) {
            // el usuario tiene notificaciones, visualizarlas
            printf("Notificaciones para el usuario %s %s:\n",
                   (*auxUsuario)->Dato.nombre, (*auxUsuario)->Dato.apellido);

            // recorre la lista de recordatorios y visualizalos
            NodoRecordatorio* auxRecordatorio = (*auxUsuario)->Dato.ListaRecordatorios;
            while (auxRecordatorio) {
                printf("%s\n", auxRecordatorio->Dato.mensaje);
                auxRecordatorio = auxRecordatorio->sgt;
            }

            notificacionesVisualizadas = 1;  // se visualizó al menos una notificación
        }
        auxUsuario = &(*auxUsuario)->sgt;
    }

    if (!notificacionesVisualizadas) {
        printf("No hay notificaciones para visualizar.\n");
    }

    pausar();
}

