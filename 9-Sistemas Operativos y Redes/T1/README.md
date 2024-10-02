# T1_Sistemas_Operativos

T1 Sistemas operativos y redes IIC2333

## Compilar
Va a generar dentro de la carpeta T1 una carpeta obj/ con los archivos .o y un ejecutable en T1/ llamado "oscheduler" el cual es el que es necesario ejecutar para poner en marcha en programa.

```
make
```

```
make clean && make
```

## Run

```
./oscheduler <input_file> <output_file> <quantum>
```


## Sobre el proyecto

El proyecto nos costo desarrollarlo y es por esto que no pudimos tener todos los outputs correctos, no logramos implementar bien el manejo de interrupciones y por esto el output no coincide en su totalidad con el output esperado. El codigo esta modulado:
file_manager/ esta encargada de la correcta lectura de los datos, del input_file, y tambien se encarga de liberar la memoria de este.

lrscheduler/ se encarga del manejo principal del programa, la parte mas significativa y donde se manejan los procemos es dentro del while entre las lineas 59-194 ahi esta detallado el paso a paso como lo recomendaba el enunciado.

process/ estructura de los procesos, creacion y destruccion de estos.

queue/ estructura de la queue low y high.

Implementamos todo lo que se nos pedia sin tener leaks de memoria ni errores de esta. Pero aún así no pudimos lograr los outputs solicitados en su totalidad.

## Autores

- Nicolas Hormann
- Vicente Cuitiño

