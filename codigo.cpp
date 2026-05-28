// ======================================================
// SISTEMA CENTRAL DE TRANSACCIONES
// Este programa simula el funcionamiento de un servidor
// bancario usando:
// - PILA  -> Tokens de seguridad
// - LISTA -> Historial de transacciones
// - COLA  -> Ejecución de procesos por prioridad
// ======================================================
#include <iostream>
#include <string>

using namespace std;

// ======================================================
// ESTRUCTURA DE LA PILA
// Esta estructura crea los nodos que almacenarán
// los tokens de autorización del sistema.
// ======================================================
struct NodoAutorizacion {
	// Guarda el número del token
    int idAutorizacion;
    // El asterisco (*) indica que es un puntero. Nos sirve para guardar la direccion 
    // de memoria del siguiente token que esta debajo en la pila.
    NodoAutorizacion* siguiente; 
};

// ======================================================
// ESTRUCTURA DE TRANSACCIONES
// Esta estructura almacena toda la información
// de una operación bancaria.
// ======================================================
struct NodoTransaccion {
	// Código único de la transacción
    int idTransaccion;
	// DNI del cliente
    int dniCliente;
	// Nombre del cliente
    string nombreCliente;
	// Tipo de operación realizada
    string tipoOperacion;
	// Dinero involucrado en la operación
    float monto;
	// Nivel de prioridad
    // 1 = más urgente
    // 3 = menos urgente
    int prioridad;
	// Estado actual de la transacción
    string estado;
    NodoTransaccion* siguiente; // Puntero para enlazar con la siguiente transaccion
};
// ======================================================
// PUNTEROS GLOBALES
// Estos punteros ayudan a controlar las estructuras.
// ======================================================

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

// ======================================================
// FUNCION: InicializarPila
// Crea automáticamente 15 tokens al iniciar el sistema.
// ======================================================
void InicializarPila() {
	// Recorre desde 15 hasta 1
    for (int i = 15; i >= 1; i--) {
        // Usamos 'new' para pedirle al sistema que nos reserve un espacio en la memoria dinamica
        NodoAutorizacion* nuevoToken = new NodoAutorizacion();
		// Guarda el número del token
        nuevoToken->idAutorizacion = i;
		// El nuevo token apunta al que antes estaba arriba
        nuevoToken->siguiente = cimaPila;
		// Ahora este token pasa a ser la nueva cima
        cimaPila = nuevoToken;
    }
    cout << "15 tokens disponibles." << endl;
}
// ======================================================
// FUNCION POP
// Saca el token que está en la parte superior de la pila.
// ======================================================
int PopAutorizacion() {
    int tokenAsignado;
	// Verifica si la pila está vacía
    if (cimaPila == NULL) {
        tokenAsignado = 0; // Si retorna 0 es porque ya no quedan tokens
    } 
	else {
		// Guarda temporalmente el nodo de arriba
        NodoAutorizacion* nodoAuxiliar = cimaPila;
		// Obtiene el ID del token
        tokenAsignado = cimaPila->idAutorizacion;
		// La cima avanza al siguiente nodo
        cimaPila = cimaPila->siguiente;
        
        // Usamos delete para eliminar el nodo que acabamos de sacar y liberar esa memoria
        delete nodoAuxiliar; 
    }
	// Devuelve el token obtenido
    return tokenAsignado;
}


// Funcion Push: Semana 9, sirve para insertar un elemento nuevo
// poniendolo en la cima de la pila. Le pide al operador el numero de token.
void PushAutorizacion() {
    int idRecuperado;
    cout << "Ingrese el ID del token a devolver (1-15): ";
    cin >> idRecuperado;
    // Crea un nuevo nodo
    NodoAutorizacion* nuevoToken = new NodoAutorizacion();
	// Guarda el ID ingresado
    nuevoToken->idAutorizacion = idRecuperado;
	// El nuevo nodo apunta al anterior tope
    nuevoToken->siguiente = cimaPila;
    cimaPila = nuevoToken; // Ahora el nuevo token pasa a ser la nueva cima
    
    cout << "Token de seguridad devuelto a la pila exitosamente." << endl;
}


// Esta funcion hace el Push pero de forma automatica internamente en el codigo
void PushAutorizacionAutomatica(int idRecuperado) {
    NodoAutorizacion* nuevoToken = new NodoAutorizacion();
    nuevoToken->idAutorizacion = idRecuperado;
    nuevoToken->siguiente = cimaPila;
    cimaPila = nuevoToken;
}


// Esta funcion permite visualizar en pantalla los tokens que quedan guardados en la Pila
void MostrarPila() {
    if (cimaPila == NULL) {
        cout << "La pila esta vacia, no hay tokens disponibles." << endl;
    } 
	else {
        NodoAutorizacion* actual = cimaPila;
        cout << "\n TOKENS DE SEGURIDAD EN LA PILA " << endl;
        // Recorremos hasta que actual sea NULL, lo que significa que llegamos al limite
        while (actual != NULL) {
            cout << "Token Numero: " << actual->idAutorizacion << endl;
            actual = actual->siguiente;
        }
    }
}

// ======================================================
// FUNCION INSERTAR TRANSACCION
// Registra una nueva operación bancaria.
// ======================================================
void InsertarTransaccion() {
    int tokenSeguridad = PopAutorizacion(); // Consumimos un token llamando a la pila
    // Verifica si aún existen tokens
    if (tokenSeguridad == 0) {
        cout << "ERRORRR No hay tokens disponibles." << endl;
    } 
	else {
        // Reservamos memoria dinamica para el nuevo registro usando la palabra new
        NodoTransaccion* nuevoNodo = new NodoTransaccion();
        nuevoNodo->idTransaccion = contadorID++; // Usamos el contador global y luego lo aumentamos
        
        cout << "Ingrese DNI del cliente: ";
        cin >> nuevoNodo->dniCliente;
        cout << "Ingrese nombre del cliente: ";
        cin >> nuevoNodo->nombreCliente;
        cout << "Ingrese tipo de operacion: ";
        cin >> nuevoNodo->tipoOperacion;
        cout << "Ingrese el monto: ";
        cin >> nuevoNodo->monto;
        cout << "Ingrese prioridad (1: Presencial, 2: Web, 3: Automatico): ";
        cin >> nuevoNodo->prioridad;
        // La transacción inicia como pendiente
        nuevoNodo->estado = "Pendiente";
        
        // Lo ponemos en NULL porque al ser el ultimo elemento que ingresa, no hay nadie detras de el
        nuevoNodo->siguiente = NULL; 
        
        // Si la lista esta vacia lo ponemos al inicio, si no, buscamos el ultimo lugar disponible
        if (inicioLista == NULL) {
            inicioLista = nuevoNodo;
        } 
		else {
			// Recorre hasta el último nodo
            NodoTransaccion* actual = inicioLista;
            while (actual->siguiente != NULL) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevoNodo;
        }
        cout << "Transaccion registrada. Token consumido: " << tokenSeguridad << endl;
    }
}


// Funcion para actualizar los datos de un nodo especifico usando punteros
void CambiarEstadoTransaccion() {
    int idBuscar;
    cout << "Ingrese el ID de la transaccion a modificar: ";
    cin >> idBuscar;
    
    NodoTransaccion* actual = inicioLista;
    bool encontrado = false;
    
    // Recorremos la lista hasta encontrar el ID o hasta chocar con el final (NULL)
    while (actual != NULL && encontrado == false) {
        if (actual->idTransaccion == idBuscar) {
            encontrado = true;
        } 
		else {
            actual = actual->siguiente;
        }
    }
    
    if (encontrado == true) {
        cout << "Transaccion encontrada. Cliente: " << actual->nombreCliente << endl;
        cout << "Ingrese el nuevo estado: ";
        cin >> actual->estado;
        cout << "Ingrese la nueva prioridad (1, 2 o 3): ";
        cin >> actual->prioridad;
        
        cout << "Los datos de la transaccion han sido actualizados." << endl;
    } 
	else {
        cout << "ERRORRR No existe transaccion con el ID ingresado." << endl;
    }
}

// Funcion para mostrar el historial completo de la Lista
void MostrarHistorial() {
    if (inicioLista == NULL) {
        cout << "La lista de transacciones esta vacia." << endl;
    } 
	else {
        NodoTransaccion* actual = inicioLista;
        cout << "\n HISTORIAL DE TRANSACCIONES EN LA LISTA " << endl;
        while (actual != NULL) {
            cout << "ID: " << actual->idTransaccion << " | Cliente: " << actual->nombreCliente 
			<< " | Prioridad: " << actual->prioridad << " | Estado: " << actual->estado << endl;
            actual = actual->siguiente;
        }
    }
}


// Funciones encargadas de manejar la Cola de Prioridad

// Esta funcion busca un elemento en la lista, lo saca de ahi y lo mete a la cola ordenandolo por urgencia
void EncolarConPrioridad() {
    int idMover;
    cout << "Ingrese el ID de la transaccion pendiente a procesar: ";
    cin >> idMover;
    
    NodoTransaccion* actualLista = inicioLista;
    NodoTransaccion* anteriorLista = NULL;
    NodoTransaccion* nodoMover = NULL;
    bool encontrado = false;
    
    // Primero, buscamos en la lista recorriendo nodo por nodo y lo desenlazamos para llevarnoslo
    while (actualLista != NULL && encontrado == false) {
        if (actualLista->idTransaccion == idMover) {
            encontrado = true;
            nodoMover = actualLista;
            if (anteriorLista == NULL) {
                inicioLista = actualLista->siguiente;
            } 
			else {
                anteriorLista->siguiente = actualLista->siguiente;
            }
        } 
		else {
            anteriorLista = actualLista;
            actualLista = actualLista->siguiente;
        }
    }
    
    // Segundo, ya que lo tenemos separado, lo insertamos en la cola comparando su nivel de prioridad
    if (encontrado == true) {
        nodoMover->estado = "En Proceso";
        nodoMover->siguiente = NULL;
        
        if (frenteCola == NULL) {
            frenteCola = nodoMover;
            finalCola = nodoMover;
        } 
		else {
            if (nodoMover->prioridad < frenteCola->prioridad) {
                nodoMover->siguiente = frenteCola;
                frenteCola = nodoMover;
            } 
			else {
                NodoTransaccion* actualCola = frenteCola;
                while (actualCola->siguiente != NULL && actualCola->siguiente->prioridad <= nodoMover->prioridad) {
                    actualCola = actualCola->siguiente;
                }
                
                if (actualCola->siguiente == NULL) {
                    finalCola = nodoMover;
                }
                
                nodoMover->siguiente = actualCola->siguiente;
                actualCola->siguiente = nodoMover;
            }
        }
        cout << "Transaccion encolada y ordenada segun su urgencia con exito." << endl;
    } 
	else {
        cout << "ERRORRR Transaccion no encontrada en la lista." << endl;
    }
}


// Funcion Desencolar: Saca al primer cliente que esta al frente de la cola, simula su ejecucion y libera memoria
void DesencolarYEjecutar() {
    if (frenteCola == NULL) {
        cout << "ERRORR La cola de ejecucion esta vacia." << endl;
    } 
	else {
        NodoTransaccion* nodoEjecutar = frenteCola;
        frenteCola = frenteCola->siguiente;
        
        // Validacion clave si sacamos al ultimo elemento de la cola, el puntero finalCola 
        // no puede quedarse apuntando a basura, debemos regresarlo a NULL
        if (frenteCola == NULL) {
            finalCola = NULL;
        }
        
        cout << "\n EJECUTANDO TRANSACCION " << endl;
        cout << "ID: " << nodoEjecutar->idTransaccion << " | Cliente: " << nodoEjecutar->nombreCliente << endl;
        cout << "Operacion: " << nodoEjecutar->tipoOperacion << " | Monto procesado: " << nodoEjecutar->monto << endl;
        
        // Simulamos que al terminar el tramite, devolvemos un token a la pila el ID 1 de ejemplo
        PushAutorizacionAutomatica(1); 
        
        // Eliminamos el nodo con delete para limpiar el espacio utilizado en la memoria
        delete nodoEjecutar; 
        cout << "Transaccion finalizada. Memoria liberada y token devuelto a la pila." << endl;
    }
}

// Esta funcion permite visualizar el orden de las transacciones que estan esperando ser atendidas
void MostrarCola() {
    if (frenteCola == NULL) {
        cout << "La cola de espera esta vacia." << endl;
    } 
	else {
        NodoTransaccion* actual = frenteCola;
        cout << "\n COLA DE PROCESOS PENDIENTES " << endl;
        while (actual != NULL) {
            cout << "Prioridad: " << actual->prioridad << " | ID: " << actual->idTransaccion 
                 << " | Cliente: " << actual->nombreCliente << " | Estado: " << actual->estado << endl;
            actual = actual->siguiente;
        }
    }
}
int main() {
    InicializarPila();
    int opcion;
    do {
        cout << "\n********************************************" << endl;
        cout << "* SISTEMA CENTRAL DE TRANSACCIONES         *" << endl;
        cout << "********************************************" << endl;
        cout << "* 1. Registrar transaccion (Usa Lista)     *" << endl;
        cout << "* 2. Mostrar historial     (Ver Lista)     *" << endl;
        cout << "* 3. Modificar datos       (Usa Lista)     *" << endl;
        cout << "* 4. Enviar a ejecucion    (Usa Cola)      *" << endl;
        cout << "* 5. Mostrar en espera     (Ver Cola)      *" << endl;
        cout << "* 6. Procesar operacion    (Usa Cola)      *" << endl;
        cout << "* 7. Devolver token manual (Usa Pila)      *" << endl;
        cout << "* 8. Mostrar espacios      (Ver Pila)      *" << endl;
        cout << "* 9. Salir                                 *" << endl;
        cout << "********************************************" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        switch (opcion) {
            case 1: 
                InsertarTransaccion(); 
                break;
            case 2: 
                MostrarHistorial(); 
                break;
            case 3: 
                CambiarEstadoTransaccion(); 
                break;
            case 4: 
                EncolarConPrioridad(); 
                break;
            case 5: 
                MostrarCola(); 
                break;
            case 6: 
                DesencolarYEjecutar(); 
                break;
            case 7: 
                PushAutorizacion(); 
                break;
            case 8: 
                MostrarPila(); 
                break;
            case 9: 
                cout << "SALIENDO..." << endl; 
                break;
        }					
    } while (opcion != 9);
    
    return 0;
}
// ======================================================
// POSIBLES MEJORAS PARA EL SISTEMA
// Estas funciones podrian implementarse para mejorar
// el funcionamiento y seguridad del programa.
// ======================================================


// ======================================================
// MEJORA 1:
// VALIDAR DATOS INGRESADOS
// Serviria para evitar que el usuario ingrese letras
// en campos numericos como DNI, monto o prioridad.
// ======================================================

// Ejemplo:
// while(cin.fail()) {
//     cin.clear();
//     cin.ignore(1000, '\n');
//     cout << "Dato invalido. Intente nuevamente: ";
// }


// ======================================================
// MEJORA 2:
// BUSQUEDA DE TRANSACCIONES
// Permitiria buscar operaciones usando ID o DNI.
// ======================================================

// Ejemplo:
// BuscarTransaccionPorID();
// BuscarTransaccionPorDNI();


// ======================================================
// MEJORA 3:
// GUARDAR DATOS EN ARCHIVOS
// Permitiria almacenar las transacciones en archivos
// .txt para no perder la informacion al cerrar.
// ======================================================

// Libreria necesaria:
// #include <fstream>


// ======================================================
// MEJORA 4:
// LOGIN DE ADMINISTRADOR
// Serviria para proteger el acceso al sistema.
// ======================================================

// Ejemplo:
// Usuario: admin
// Contraseña: 1234


// ======================================================
// MEJORA 5:
// REPORTE DE TRANSACCIONES
// Permitiria mostrar:
// - Total procesado
// - Cantidad de operaciones
// - Clientes atendidos
// ======================================================


// ======================================================
// MEJORA 6:
// ELIMINAR TRANSACCIONES
// Permitiria borrar operaciones canceladas
// o incorrectas dentro de la lista enlazada.
// ======================================================


// ======================================================
// MEJORA 7:
// MOSTRAR TOKENS DISPONIBLES
// Permitiria contar cuantos tokens quedan
// actualmente en la pila.
// ======================================================


// ======================================================
// MEJORA 8:
// ORDENAMIENTO DE HISTORIAL
// Permitiria ordenar las transacciones
// por prioridad, monto o ID.
// ======================================================


// ======================================================
// MEJORA 9:
// INTERFAZ MAS AMIGABLE
// Se podria usar colores, menus mas ordenados
// y mensajes visuales para el usuario.
// ======================================================


// ======================================================
// MEJORA 10:
// GENERAR CODIGOS AUTOMATICOS
// El sistema podria generar automaticamente
// tokens y codigos unicos mas seguros.
// ======================================================
