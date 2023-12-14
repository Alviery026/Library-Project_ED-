#ifndef Multas_h
#define Multas_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "LibreriaGeneral.h"
#include "Registro.h"

void Multar(NodoUsuario* UsuarioMultar, int DiasDiff){
    UsuarioMultar->Dato.Multa += DiasDiff*5;
    printf("Usuario %d multado $%d por tardar %d dias en retornar Libro", UsuarioMultar->Dato.id_usuario, DiasDiff*15, DiasDiff);
}

void PagarMultas(NodoUsuario** InicioUsuarios){
    int idUsuario;
    printf("Ingrese el ID del usuario al que se le pagaran sus multas: ");
    scanf("%d", &idUsuario);

    NodoUsuario **UsuarioLiberar = Buscar_NodoUsuario(InicioUsuarios, idUsuario);
    if (!UsuarioLiberar)
    {
        printf("Usuario no encontrado. Verifique el ID.\n");
        return; 
    }
    if ((*UsuarioLiberar)->Dato.Multa == 0){
        printf("Usuario sin multas\n");
        return;
    }
    (*UsuarioLiberar)->Dato.Multa = 0;
    printf("Multas pagadas con exito para usuario %s (ID %d)!", (*UsuarioLiberar)->Dato.nombre, (*UsuarioLiberar)->Dato.id_usuario);
}


#endif