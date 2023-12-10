

#include "LibreriaGeneral.h"
#include "Registro.h"

// struct para representar recordatorios
typedef struct {
    NodoUsuario *usuario;
    NodoLibro *libro;
    time_t fecha_devolucion;
} Recordatorio;

static void EnviarRecordatorio(NodoUsuario *usuario, NodoLibro *libro, time_t fecha_devolucion);
void VerRecordatorios(NodoUsuario *InicioUsuarios, NodoTransaccion *InicioTransacciones);

