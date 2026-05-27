# Control de espacio o Tokens

```
Proceso PopAutorizacion
    Definir paseAsignado Como Entero
    
    Si cimaPila = Nulo Entonces
        paseAsignado <- 0
    Sino
        Definir nodoAuxiliar Como NodoAutorizacion
        nodoAuxiliar <- cimaPila
        paseAsignado <- cimaPila.idAutorizacion
        cimaPila <- cimaPila.siguiente
        
        LiberarMemoria(nodoAuxiliar)
    FinSi
    
    Retornar paseAsignado
FinProceso