#include <iostream>
#include <string>

using namespace std;

// Estructura para crear los nodos de la Pila que controlara los tokens de seguridad
struct NodoAutorizacion {
    int idAutorizacion;
    // El asterisco (*) indica que es un puntero. Nos sirve para guardar la direccion 
    // de memoria del siguiente token que esta debajo en la pila.
    NodoAutorizacion* siguiente; 
};

// Estructura para crear los nodos de la Lista y la Cola
struct NodoTransaccion {
    int idTransaccion;
    int dniCliente;
    string nombreCliente;
    string tipoOperacion;
    float monto;
    int prioridad;
    string estado;
    NodoTransaccion* siguiente; // Puntero para enlazar con la siguiente transaccion
};
// Punteros globales que marcan el punto de partida de nuestras estructuras en la memoria.
// Se igualan a NULL al inicio para indicarle al programa que las estructuras estan vacias 
// y no apuntan a ningun lado todavia.

// cimaPila nos sirve para saber cual es el token que esta mas arriba listo para usarse
NodoAutorizacion* cimaPila = NULL;

// inicioLista nos ayuda a no perder el rastro del primer registro historico que hagamos
NodoTransaccion* inicioLista = NULL;

// frenteCola y finalCola son necesarios para la cola, uno atiende al primero y el otro inserta al final
NodoTransaccion* frenteCola = NULL;
NodoTransaccion* finalCola = NULL;

// Este contador funciona como un generador de tickets. 
// Empieza en 1000 y cada vez que registremos a un cliente subira a 1001, 1002, etc.
int contadorID = 1000; 
