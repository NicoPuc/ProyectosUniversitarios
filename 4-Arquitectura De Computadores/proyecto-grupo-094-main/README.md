# Informe Entrega 3 Proyecto Arquitectura de Computadores IIC2324

## Grupo 94

## Integrantes:

- Nicolas Hormann
    - Roles: Testing, desarrollo de juego de reacción
- Julian Araya 
    - Roles: Desarrollo de juego de reacción, juego 2
- Vicente Bragado
    - Roles: Desarrollo de componentes, juego 2

## 1. Estructura de palabra:

La palabra de 36 bits está dividida en dos partes. La primera (16 bits más significativos) corresponden a instrucciones para dirección de memoria o un literal de 16 bits. En el caso de dirección de memoria, los 12 bits menos significativos de estos 16 son utilizados, con el resto de los bits siendo 0s. En el caso de que se esté trabajando con un literal, se utilizan los 16 bits para representar el literal.

Los 13 bits menos significativos de la palabra de 36 bits corresponden al opcode. Por lo mismo, los 7 bits que sobran son 0s. 

## 2. Instrucciones juego 1: Reacción

El juego sigue las instrucciones del enunciado. Se debe correr el juego con clock speed en full (00).

- Archivo: juego_reaccion.txt

## 3. Instrucciones juego 2: Cachipun

El juego 2 consiste en una versión de cachipún de 4, osea, piedra, papel, tijera y pegamento. El juego parte cuando se levanta el switch 0, y aparecerá en el display el numero del jugador que tiene el turno (jugador 1). El jugador deberá apretar un botón para seleccionar su movida. El mapeo de botónes es el siguiente: 
- piedra = izquierda
- papel = arriba
- tijera = derecha
- pegamento = abajo

Notar que el botón del medio no está habilitado. Una vez que el jugador 1 apriete el botón, será el turno del jugador 2, con el display indicando su numero (2). Una vez apretado el botón, el display indicará el ganador de la partida. En caso de empatar, el display mostrará 100 en hexadecimal. En caso de quierer jugar denuevo, se deberá cambiar el switch 0. 

Nota: para correr este juego, clock speed debe estar en fast (01)

- Archivo: juego_2.txt


## Reglas del juego 2: Elemento y a quién le gana

- piedra
    - tijera
    - pegamento

- papel
    - piedra

- tijera
    - papel

- pegamento
    - papel
    - tijera

