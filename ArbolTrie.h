#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "LibreriaGeneral.h"



#ifndef ArbolTrie_h
#define ArbolTrie_h
#define NUM_CHARS 256


typedef struct NodoTrie{
   libros InfoLibro;
   struct NodoTrie *hijos[NUM_CHARS];
   bool terminal; 
   struct NodoTrie *local;
}NodoTrie;

NodoTrie *Crear_NodoTrie(){
    NodoTrie *newNode = (NodoTrie*)malloc(sizeof *newNode);

    for (int i = 0; i < NUM_CHARS; i++){
        newNode->hijos[i] = NULL;
    }
    newNode->terminal = false;
    newNode->local = NULL;
    return newNode;
}

int Insertar_Trie(NodoTrie** root, libros LibroInsert){
    if (!*root){
        *root = Crear_NodoTrie();
    }
    int i = 0;

    unsigned char *text = (unsigned char *)LibroInsert.titulo;
    NodoTrie *temp = *root;
    int length = strlen(LibroInsert.titulo);

    for (i = 0; i<length; i++){
        if (temp->hijos[text[i]] == NULL){
            temp->hijos[text[i]] = Crear_NodoTrie();
        }
        temp = temp->hijos[text[i]];
    }
    
    if (temp->terminal){
        return false;
    } else {
        temp->terminal = true;
        temp->local = temp;
        temp->InfoLibro = LibroInsert;
        temp->InfoLibro.Reservas = CrearCola();
        return true;
    }
}

void ImprimirLibro(libros Libro){
    printf("ID\t\t %d", Libro.id_libro);
    puts("");
    printf("Titulo\t %s", Libro.titulo);
    puts("");
    printf("Autor\t %s", Libro.autor);
    puts("");
    printf("Editorial\t %s", Libro.editorial);
    puts("");
    printf("Ejemplares\t %d", Libro.numero_ejemplares);
    puts("");
    printf("Fecha Publicacion %d/%d/%d", Libro.anio_publicacion.dia, Libro.anio_publicacion.mes, Libro.anio_publicacion.anio);
    puts("");
    puts("");
    return;
}

void ImprimirTrieRec(NodoTrie *nodo, unsigned char *prefijo, int tam){
    unsigned char newPrefix[tam+2];
    //printf("%s", prefijo); //Debug
    memcpy(newPrefix, prefijo, tam);
    newPrefix[tam+1] = 0;
    
    if (nodo->terminal){
        ImprimirLibro((nodo->InfoLibro));
    }

    for (int i=0; i < NUM_CHARS; i++){
        if (nodo->hijos[i]){
            newPrefix[tam] = i;
            ImprimirTrieRec(nodo->hijos[i], newPrefix, tam+1); 
        }
    }
}

void Imprimir_Trie(NodoTrie* root){
    if (root == NULL){
        printf("No hay libros en el catalogo");
    }
    ImprimirTrieRec(root, NULL, 0);
}

libros Escribir_Libro(int *ID){
    libros NuevoLibro;
    NuevoLibro.id_libro = *ID;
    NuevoLibro.numero_ejemplares = 0;
    NuevoLibro.Reservas = CrearCola();

    fflush(stdin);
    printf("Ingrese el nombre del libro: ");
    scanf("%40[^\n]", NuevoLibro.titulo);
    fflush(stdin);
    printf("Ingrese el nombre del autor: ");
    scanf("%40[^\n]", NuevoLibro.autor);
    fflush(stdin);
    printf("Ingrese el nombre de la editorial: ");
    scanf("%40[^\n]", NuevoLibro.editorial);
    fflush(stdin);
    printf("Ingrese la fecha de publicacion(DD/MM/AAAA): ");
    scanf("%02d/%02d/%04d", &NuevoLibro.anio_publicacion.dia, &NuevoLibro.anio_publicacion.mes, &NuevoLibro.anio_publicacion.anio);
    fflush(stdin);
    *ID += 1;
    return NuevoLibro;
}

void Insertar_ManualLibro(NodoTrie** root, int* ID){
    libros LibroInsert = Escribir_Libro(ID);
    Insertar_Trie(root, LibroInsert);
    printf("Libro registrado, favor de ingresar numero de ejemplares\n");
}

NodoTrie** Buscar_NodoLibro(NodoTrie **root, char *signedtext){
    unsigned char *texto = (unsigned char * ) signedtext;
    int length = strlen(signedtext);
    NodoTrie *temp = *root;
    for (int i = 0; i< length; i++){
        if (temp->hijos[texto[i]] == NULL)
            return NULL;
        temp = temp->hijos[texto[i]];
    }
    if (temp->terminal == true){
        return &(temp->local);
    }
        else {
            return NULL;
        }
}

void modificarEjemplares(NodoTrie** root, char* signedtext, int mod){
    unsigned char *texto = (unsigned char * ) signedtext;
    int length = strlen(signedtext);
    NodoTrie *temp = *root;

    for (int i = 0; i< length; i++){
        if (temp->hijos[texto[i]] == NULL){
            return;
        }
        temp = temp->hijos[texto[i]];
    }
    if (temp->terminal == true){
        temp->InfoLibro.numero_ejemplares+= mod;
        return;
        }
        else {
            return;
        }
}


#endif