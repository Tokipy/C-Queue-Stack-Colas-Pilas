#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"

/**
MANEJO DE PILAS Y COLAS
FECHA: 13/11/2025
GARRIDO DANIEL ALEJANDRO
**/

int main()
{
    // Se trabaja con tres colas y una pila para el manejo de los pacientes que ingresan en un hospital.

    //C = Cola general
    TCola C;
    initCola(&C);

    TCola urgentes;
    initCola(&urgentes);

    TCola moderados;
    initCola(&moderados);

    TNodoPila * tope;
    initPila(&tope);

    int key = 0;

    TPaciente pacientePrueba; //Variable que fue utilizada para pruebas.
    TPaciente datos;

    do{
        printf("Bienvenido al menu del hospital. Ingrese una opcion indicada\n");
        printf("1- Ingresar Paciente\n2- Asignacion de prioridad\n3- Procesar colas Urgentes y Moderados\n4- Mostrar Pila de trabajo\n5- Salir\n\n");
        fflush(stdin);scanf("%d", &key);

        switch(key){

        case 1:
            datos = scanPaciente();

            //Datos utilizados en las pruebas:
            //pacientePrueba.dni = 123456;
            //pacientePrueba.gravedad = 1;
            //strcpy(pacientePrueba.estado, "Ingresado");

            encolar(&C, datos);
            printf("Paciente ingresado correctamente\n\n");

            break;
        case 2:
            ingresarPorPrioridad(&C, &urgentes, &moderados);
            break;
        case 3:
            procesarColas(&urgentes, &moderados, &tope);
            break;
        case 4:
            mostrarPilaR(&tope);
            break;
        case 5:
            //Saliendo
            break;
        default:
            printf("Ingrese una opcion correcta.\n");
            break;
        }

    }while(key != 5);

    freeCola(&C);
    freeCola(&urgentes);
    freeCola(&moderados);
    freePila(&tope);

    return 0;
}
