

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

void VerMultasRecordatorios(NodoTransaccion *InicioTransacciones);
void AgregarMultaRecordatorio(NodoUsuario *usuario, NodoLibro *libro, time_t fecha_devolucion, int dias_atraso);
void ProcesarMultasRecordatorios(NodoTransaccion **InicioTransacciones, NodoUsuario **InicioUsuarios, NodoLibro **InicioLibros);
int CalcularDiasAtraso(time_t fecha_devolucion);
void RealizarPrestamo(NodoUsuario **InicioUsuarios, NodoLibro **InicioLibros, NodoTransaccion **InicioTransacciones, int *IDUsuarios, int *IDLibros);



