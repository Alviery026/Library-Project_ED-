
#ifndef Recordatorios_h
#define Recordatorios_h

#include "LibreriaGeneral.h"
#include "Registro.h"
#include "Multas.h"


typedef struct recordatorios
{
    NodoTransaccion* transaccion; // puntero a la transacción asociada al recordatorio
    char mensaje[100];            // mensaje del recordatorio
} recordatorios;

typedef struct NodoRecordatorio
{
    recordatorios Dato;
    struct NodoRecordatorio* sgt;
} NodoRecordatorio;

void EnviarRecordatoriosMultas(struct NodoUsuario** InicioUsuarios);

#endif
