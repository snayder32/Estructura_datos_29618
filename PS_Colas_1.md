# Priorizar transacción

```
Proceso EncolarConPrioridad
    Definir idMover Como Entero
    Definir actualLista, anteriorLista, nodoMover, actualCola Como NodoTransaccion
    Definir encontrado Como Logico
    
    Escribir "Ingrese el ID de la transacción pendiente a procesar:"
    Leer idMover
    
    actualLista <- inicioLista
    anteriorLista <- Nulo
    encontrado <- Falso
    
    // Buscar y desvincular el nodo de la Lista
    Mientras actualLista Diferente De Nulo Y encontrado = Falso Hacer
        Si actualLista.idTransaccion = idMover Entonces
            encontrado <- Verdadero
            nodoMover <- actualLista
            Si anteriorLista = Nulo Entonces
                inicioLista <- actualLista.siguiente
            Sino
                anteriorLista.siguiente <- actualLista.siguiente
            FinSi
        Sino
            anteriorLista <- actualLista
            actualLista <- actualLista.siguiente
        FinSi
    FinMientras
    
    // Insertar el nodo en la Cola respetando el orden de prioridad
    Si encontrado = Verdadero Entonces
        nodoMover.estado <- "En Proceso"
        nodoMover.siguiente <- Nulo
        
        Si frenteCola = Nulo Entonces
            frenteCola <- nodoMover
            finalCola <- nodoMover
        Sino
            // Si la prioridad es más urgente (menor número) que la del frente
            Si nodoMover.prioridad < frenteCola.prioridad Entonces
                nodoMover.siguiente <- frenteCola
                frenteCola <- nodoMover
            Sino
                // Buscar la posición correcta en el medio o final de la cola
                actualCola <- frenteCola
                Mientras actualCola.siguiente Diferente De Nulo Y actualCola.siguiente.prioridad <= nodoMover.prioridad Hacer
                    actualCola <- actualCola.siguiente
                FinMientras
                
                // Si llegamos al final, actualizamos el puntero finalCola
                Si actualCola.siguiente = Nulo Entonces
                    finalCola <- nodoMover
                FinSi
                
                nodoMover.siguiente <- actualCola.siguiente
                actualCola.siguiente <- nodoMover
            FinSi
        FinSi
        Escribir "Transaccion encolada y ordenada segun su urgencia con exito."
    Sino
        Escribir "Error: Transaccion no encontrada."
    FinSi
FinProceso