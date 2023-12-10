#ifndef MultasYNotis_h
#define MultasYNotis_h

#include "LibreriaGeneral.h"
#include "Registro.h"
#include "Transacciones.h"

// struct para representar multas y recordatorios
typedef struct {
    NodoUsuario *usuario;
    NodoLibro *libro;
    time_t fecha_devolucion;
    int dias_atraso;
} MultaRecordatorio;

void VerMultasRecordatorios(NodoTransaccion **InicioTransacciones);
void AgregarMultaRecordatorio(NodoUsuario *usuario, NodoLibro *libro, time_t fecha_devolucion, int dias_atraso);
void ProcesarMultasRecordatorios(NodoTransaccion **InicioTransacciones, NodoUsuario **InicioUsuarios, NodoLibro **InicioLibros);
void RealizarPrestamo(NodoUsuario** InicioUsuarios, NodoLibro** InicioLibros, NodoTransaccion** InicioTransacciones, int* IDUsuarios, int* IDLibros);
// calcular días de atraso
static inline int CalcularDiasAtraso(time_t fecha_devolucion) {
    time_t ahora;
    time(&ahora);

    //  calcula la diferencia en segundos entre las dos fechas
    double diferencia = difftime(ahora, fecha_devolucion);

    // convierte la diferencia de segundos a días
    int dias_atraso = diferencia / (24 * 60 * 60);  // 24 horas, 60 minutos, 60 segundos

    return dias_atraso;
}

#endif
