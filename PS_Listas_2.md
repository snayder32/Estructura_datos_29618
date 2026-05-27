# Modificar transaccion

```
Proceso CambiarEstadoTransaccion
    Definir idBuscar Como Entero
    Definir actual Como NodoTransaccion
    Definir encontrado Como Logico
    Escribir "Ingrese el ID de la transacción que desea modificar:"
    Leer idBuscar
    
    actual <- cabezaLista
    encontrado <- Falso
    
   nces Mientras actual <> Nulo Y encontrado = Falso Hacer
        Si actual.idTransaccion = idBuscar Ento
            encontrado <- Verdadero
        Sino
            actual <- actual.siguiente
        FinSi
    FinMientras
    
    Si encontrado = Verdadero Entonces
        Escribir "Transacción encontrada."
        Escribir "Socio: ", actual.nombreSocio
        Escribir "Estado actual: ", actual.estado
        Escribir "Prioridad actual: ", actual.prioridad
        
        Escribir "Ingrese el nuevo estado (Ej. En Proceso, Cancelado):"
        Leer actual.estado
        Escribir "Ingrese la nueva prioridad (1, 2 o 3):"
        Leer actual.prioridad
        
        Escribir "Los datos de la transacción han sido actualizados."
    Sino
        Escribir "Error: No existe ninguna transacción con el ID ingresado."
    FinSi
FinProceso