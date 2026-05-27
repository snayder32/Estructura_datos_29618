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

// Funciones encargadas de manejar la Pila

// Esta funcion se ejecuta ni bien abre el programa para llenar el servidor con 15 tokens
void InicializarPila() {
    for (int i = 15; i >= 1; i--) {
        // Usamos 'new' para pedirle al sistema que nos reserve un espacio en la memoria dinamica
        NodoAutorizacion* nuevoToken = new NodoAutorizacion();
        nuevoToken->idAutorizacion = i;
        nuevoToken->siguiente = cimaPila;
        cimaPila = nuevoToken;
    }
    cout << "15 tokens disponibles." << endl;
}
// Funcion Pop Sirve para extraer 
// y devolver el elemento que esta en la parte superior de la pila.
int PopAutorizacion() {
    int tokenAsignado;
    if (cimaPila == NULL) {
        tokenAsignado = 0; // Si retorna 0 es porque ya no quedan tokens
    } 
	else {
        NodoAutorizacion* nodoAuxiliar = cimaPila;
        tokenAsignado = cimaPila->idAutorizacion;
        cimaPila = cimaPila->siguiente;
        
        // Usamos delete para eliminar el nodo que acabamos de sacar y liberar esa memoria
        delete nodoAuxiliar; 
    }
    return tokenAsignado;
}
