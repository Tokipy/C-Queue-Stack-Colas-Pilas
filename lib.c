#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"

//FUNCIONES COLA

//Funcion que genera cada nodo/elemento a ingresar en la cola
TNodoCola * generarNodoCola(TPaciente datos){
    TNodoCola * nuevo = malloc(sizeof(TNodoCola));
    if(nuevo){
        nuevo->sig = NULL;
        nuevo->datosPaciente = datos;
    }else{
        printf("Error en la generacion del nodo\n");
    }
    return nuevo;
}

//Funcion para confirmar si una cola esta vacia o no
int esColaVacia(TCola *C){
    return (*C).pri == NULL && (*C).ult == NULL;
}

//Funcion para que los punteros "primero" y "ultimo" de la cola vuelvan a apuntar a NULL
void initCola(TCola *C){
    (*C).pri = NULL;
    (*C).ult = NULL;
}

//Funcion para ingresar un elemento a una cola
void encolar(TCola *C, TPaciente datos){
    TNodoCola * nuevo = generarNodoCola(datos);
    if(nuevo){
        if(esColaVacia(C)){
            (*C).pri = nuevo;
            (*C).ult = nuevo;
        }else{
            (*C).ult->sig = nuevo;
            (*C).ult = nuevo;
        }
    }else{
        printf("No se puede encolar debido al error de generacion.\n");
    }
}

//Funcion para "desencolar" y remover un elemento de una cola
TPaciente desencolar(TCola *C){
    TPaciente aux;
    if(!esColaVacia(C)){
        TNodoCola * target = (*C).pri;
        if( (*C).pri == (*C).ult ){
            initCola(C);
        }else{
            (*C).pri = (*C).pri->sig;
        }
        aux = target->datosPaciente;
        free(target);
    }
    return aux;
}

//FUNCIONES PILA

//Funcion que genera cada nodo/elemento a ingresar en la pila
TNodoPila * generarNodoPila(TPaciente datos){
    TNodoPila * nuevo = malloc(sizeof(TNodoPila));
    if(nuevo){
        nuevo->sig = NULL;
        nuevo->datosPila = datos;
    }else{
        printf("Error al generar nodo de la pila\n");
    }
}

//Funcion para confirmar si una pila esta vacia
int esPilaVacia(TNodoPila *tope){
    return tope == NULL;
}

//Funcion para que el puntero inicial de una pila apunte a NULL
void initPila(TNodoPila **tope){
    return *tope = NULL;
}

//Funcion para ingresar un elemento en una pila
void apilar(TNodoPila **tope, TPaciente datos){
    TNodoPila * nuevo = generarNodoPila(datos);
    if(nuevo){
        nuevo->sig = *tope;
        *tope = nuevo;
    }else{
        printf("No se puede apilar por error de generacion.\n");
    }
}

//Funcion para "desapilar" o remover un elemento de una pila
TPaciente desapilar(TNodoPila **tope){
    TPaciente aux;
    if(!esPilaVacia(*tope)){
        TNodoPila * target = *tope;
        aux = target->datosPila;
        *tope = (*tope)->sig;
        free(target);
    }
    return aux;
}

//Funcion auxiliar para facilitar el print de un tipo paciente con todos sus datos.
void printPaciente(TPaciente datos){
    printf("Paciente:\nDNI: %d\nGravedad: %d\nEstado: %s\n", datos.dni, datos.gravedad, datos.estado);
}

void mostrarPilaR(TNodoPila **tope){
    if(!esPilaVacia(*tope)){
        TPaciente aux = desapilar(tope);
        mostrarPilaR(tope);
        printPaciente(aux);
        apilar(tope, aux);
    }
}


//FUNCIONES AUXILIARES

void ingresarPorPrioridad(TCola *C, TCola *urgentes, TCola *moderados){
    if(!esColaVacia(C)){
        do{
        TPaciente aux;
        aux = desencolar(C);

        if(aux.gravedad == 1 || aux.gravedad == 2){
            printf("Paciente: %d - Ingresado a la cola de urgencias.\n", aux.dni);
            encolar(urgentes, aux);
        }else{
            printf("Paciente: %d - Ingresado a la cola de asuntos moderados.\n", aux.dni);
            encolar(moderados, aux);
        }

        }while(!esColaVacia(C));
    }else{
        printf("No hay pacientes en la cola\n");
    }
}


void procesarColas(TCola *urgentes, TCola *moderados, TNodoPila **tope){
    if(!esColaVacia(urgentes)){
        TPaciente aux;
        aux = desencolar(urgentes);
        strcpy(aux.estado, "Atendido.");
        apilar(tope, aux);
        printf("Cola de urgencias procesada.\n");
    }else{
        printf("La cola de urgencias esta vacia.\n");
    }

    if(!esColaVacia(moderados)){
        TPaciente aux;
        aux = desencolar(moderados);
        strcpy(aux.estado, "Atendido.");
        apilar(tope, aux);
        printf("Cola de asuntos moderados procesada.\n");
    }else{
        printf("La cola de asuntos moderados esta vacia.\n");
    }
}

void freeCola(TCola *C){
    while(!esColaVacia(C)){
        desencolar(C);
    }
    initCola(C);
}

void freePila(TNodoPila **tope){
    while(!esColaVacia(tope)){
        desapilar(tope);
    }
}

TPaciente scanPaciente(){
    TPaciente datos;
    printf("Ingrese el DNI del paciente: ");
    fflush(stdin);scanf("%d", &datos.dni);

    printf("Ingrese la gravedad del problema: ");
    fflush(stdin);scanf("%d", &datos.gravedad);

    printf("Ingrese el Estado del paciente: ");
    fflush(stdin);gets(datos.estado); //SE UTILIZA LA FUNCION gets() PARA ESTA MUESTRA, NO ES OPTIMO NI RECOMENDADO PARA UNA SITUACION REAL.

    return datos;
}



