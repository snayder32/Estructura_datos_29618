# Devolver Token

```
Proceso PushAutorizacion
    Definir idRecuperado Como Entero
    Definir nuevoPase Como NodoAutorizacion
    
    Escribir "Ingrese el ID del pase a devolver (1-15):"
    Leer idRecuperado
    
    nuevoPase <- CrearNodo()
    nuevoPase.idAutorizacion <- idRecuperado
    nuevoPase.siguiente <- cimaPila
    
    cimaPila <- nuevoPase
    
    Escribir "Pase de seguridad devuelto a la pila exitosamente."
FinProceso