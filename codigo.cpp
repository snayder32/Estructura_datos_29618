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
