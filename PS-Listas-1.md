# Algoritmo: Insertar Transacción
## Pseudocódigo

```
Proceso InsertarTransaccion
    Definir nuevoNodo Como NodoTransaccion
    Definir paseSeguridad Como Entero
    
    paseSeguridad <- PopAutorizacion()
    
    Si paseSeguridad = 0 Entonces
        Escribir "Error: El servidor está lleno. No hay pases de seguridad disponibles."
    Sino
        nuevoNodo <- CrearNodo()
        nuevoNodo.idTransaccion <- GenerarIDAutomatico()
        
        Escribir "Ingrese DNI del socio:"
        Leer nuevoNodo.dniSocio
        Escribir "Ingrese nombre completo del socio:"
        Leer nuevoNodo.nombreSocio
        Escribir "Ingrese tipo de operación (Retiro, Deposito, Pago):"
        Leer nuevoNodo.tipoOperacion
        Escribir "Ingrese el monto:"
        Leer nuevoNodo.monto
        Escribir "Ingrese nivel de prioridad (1: Presencial, 2: Web, 3: Automatico):"
        Leer nuevoNodo.prioridad
        nuevoNodo.estado <- "Pendiente"
        nuevoNodo.siguiente <- Nulo
        
        Si inicioLista = Nulo Entonces
            inicioLista <- nuevoNodo
        Sino
            Definir actual Como NodoTransaccion
            actual <- inicioLista
            Mientras actual.siguiente Diferente De Nulo Hacer
                actual <- actual.siguiente
            FinMientras
            actual.siguiente <- nuevoNodo
        FinSi
        
        Escribir "Transacción registrada exitosamente. Pase consumido."
    FinSi
FinProceso