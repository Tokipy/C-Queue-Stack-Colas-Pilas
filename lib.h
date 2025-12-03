#ifndef LIB_H_INCLUDED
#define LIB_H_INCLUDED
#define MAX_CHAR 50

typedef struct paciente{
    int dni;
    int gravedad;
    char estado[MAX_CHAR];
}TPaciente;

typedef struct NodoCola{
    TPaciente datosPaciente;
    struct NodoCola * sig;
}TNodoCola;

typedef struct Cola{
    TNodoCola * pri;
    TNodoCola * ult;
}TCola;

typedef struct NodoPila{
    TPaciente datosPila;
    struct NodoPila * sig;
}TNodoPila;

//COLA
TNodoCola * generarNodoCola(TPaciente datos);
int esColaVacia(TCola *C);
void initCola(TCola *C);
void encolar(TCola *C, TPaciente datos);
TPaciente desencolar(TCola *C);

//PILA
TNodoPila * generarNodoPila(TPaciente datos);
int esPilaVacia(TNodoPila *tope);
void initPila(TNodoPila **tope);
void apilar(TNodoPila **tope, TPaciente datos);
TPaciente desapilar(TNodoPila **tope);
void mostrarPilaR(TNodoPila **tope);
void printPaciente(TPaciente datos);

//FUNCIONES AUXILIARES
void ingresarPorPrioridad(TCola *C, TCola *urgentes, TCola *moderados);
void procesarColas(TCola *urgentes, TCola *moderados, TNodoPila **tope);
void freeCola(TCola *C);
void freePila(TNodoPila **tope);

TPaciente scanPaciente();

#endif // LIB_H_INCLUDED
