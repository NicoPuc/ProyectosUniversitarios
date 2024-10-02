# T0_Sistemas_Operativos

T0 Sistemas operativos y redes IIC2333

## Compilar

```
make
```

```
make clean && make
```

## Run

```
./lrsh
```

Luego de correr este comando se va a abrir la consola de "Nico&Vicho's : "

## Comandos

# Imprimir "Hello World!"

```
hello
```
# Sumar dos números
```
sum <num 1> <num 2>
```
# Verificar si un número es primo
```
is prime <num>
```
# Ejecutar un comando externo
```
lrexec <executable> <arg1> <arg2> ... <argn>
```
# Listar archivos en el directorio actual
```
lrlist
```

# Cerrar consola
Para salir de la consola esperando a que termine el comando:
```
lrexit
```
Para salir de la consola esperando a que termine el comando:
```
^c
```
Para salir de la consola sin esperar a que termine el comando:
```
^z
```
## Sobre el proyecto

El proyecto es una shell simple que permite ejecutar comandos en el sistema operativo Linux.

El proyecto se divide en los siguientes módulos:

- `input_manager`: Módulo que se encarga de la gestión de entradas del usuario.
- `lrsh`: Módulo que se encarga de la gestión de comandos del usuario e implementar la shell.

Implementamos todo lo que se nos pedia sin tener leaks de memoria ni errores de esta. Lo que no pudimos hacer es cuando hay un proceso largo la shell queda esperando que el proceso termine y no se puede interacturar con la shell, hasta que este termine. Aun asi si usamos multiprocesos para correr los comandos. El contador de tiempo esta en segundos por lo que muchas veces es 0 siendo en realidad mas de 0 y menos que 1.

## Autores

- Nicolas Hormann
- Vicente Cuitiño

