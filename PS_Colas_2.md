# Liberar memoria o desencolar

```
Proceso DesencolarYEjecutar
    Definir nodoEjecutar Como NodoTransaccion
    
    Si frenteCola = Nulo Entonces
        Escribir "ERROR: La cola de ejecución esta vacia. No hay procesos pendientes."
    Sino
        nodoEjecutar <- frenteCola
        frenteCola <- frenteCola.siguiente
        
        // Si al desencolar el frente se vuelve nulo, la cola ahora esta vacia
        Si frenteCola = Nulo Entonces
            finalCola <- Nulo
        FinSi
        
        Escribir "--- EJECUTANDO TRANSACCION ---"
        Escribir "ID: ", nodoEjecutar.idTransaccion
        Escribir "Socio: ", nodoEjecutar.nombreSocio
        Escribir "Operacion: ", nodoEjecutar.tipoOperacion
        Escribir "Monto procesado: ", nodoEjecutar.monto
        Escribir "Estado: Finalizado"
        
        Escribir "Llamando a PushAutorizacion para devolver el pase..."
        PushAutorizacion() 
        
        LiberarMemoria(nodoEjecutar)
        Escribir "Transaccion ejecutada. Memoria liberada correctamente."
    FinSi
FinProceso