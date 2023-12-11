#ifndef Multas_h
#define Multas_h

#include "LibreriaGeneral.h"
#include "Transacciones.h"

// declaración de avance
struct NodoUsuario;

typedef struct multas
{
    struct NodoTransaccion* transaccion;
    float monto;
} multas;

typedef struct NodoMulta
{
    multas Dato;
    struct NodoMulta* sgt;
} NodoMulta;

void AplicarMultas(struct NodoUsuario** usuario, float monto); // Cambiado a "struct NodoUsuario**"

void VerificarRetraso(struct NodoTransaccion** transaccion, struct NodoUsuario** usuario, float montoMulta); // Cambiado a "struct NodoUsuario**"

void menuMultas(struct NodoUsuario** InicioUsuarios);

#endif
