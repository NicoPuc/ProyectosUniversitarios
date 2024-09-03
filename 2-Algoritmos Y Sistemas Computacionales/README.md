## tarea4 ##
**IIC-1001-1**
Tarea 4 Algoritmos y sistemas computacionales Puc
Nicolás Hormann

La idea de esta tarea era familiarizarme con el uso de git.

# Ruleta de Tragos - Backend

Este script implementa un juego de ruleta de tragos que se puede jugar con un grupo de amigos. El juego selecciona aleatoriamente a los jugadores y determina cuántos tragos deben tomar en cada turno. Además, permite cambiar entre diferentes modos de juego: Virgen, Normal y Mortal, cada uno con distintos niveles de intensidad.

## Descripción del Juego

La **Ruleta de Tragos** es un juego en el que los jugadores deben tomar un número determinado de tragos en función del resultado de la ruleta. Hay tres modos de juego:

1. **Virgen**: Menos intenso, con menos probabilidades de tener que tomar muchos tragos.
2. **Normal**: Nivel medio de intensidad.
3. **Mortal**: Más intenso, con mayores probabilidades de tener que tomar muchos tragos.

## Funcionalidades

- **nom()**: Solicita la cantidad de jugadores y sus nombres.
- **quien()**: Selecciona aleatoriamente a un jugador para que tome un trago.
- **quien_1()**: Selecciona aleatoriamente a un jugador para que elija el modo de juego.
- **cuanto_virgen()**: Determina el número de tragos en el modo Virgen.
- **cuanto_mortal()**: Determina el número de tragos en el modo Mortal.
- **cuanto_normal()**: Determina el número de tragos en el modo Normal.
- **jugar(elijo)**: Ejecuta el juego según el modo seleccionado.
- **play()**: Función principal que inicia el juego, gestiona los turnos y permite cambiar el modo de juego.

## Cómo Jugar

1. **Iniciar el juego**: Al ejecutar el script, el juego pedirá la cantidad de jugadores y sus nombres.
2. **Seleccionar modo**: Un jugador será elegido al azar para seleccionar el modo de juego (Virgen, Normal o Mortal).
3. **Lanzar la ruleta**: Cada jugador lanzará la ruleta para determinar cuántos tragos debe tomar.
4. **Continuar jugando**: Después de 5 turnos, los jugadores pueden optar por continuar, cambiar el modo de juego o salir del juego.

## Ejecución

Para iniciar el juego, simplemente ejecuta el script en un entorno que soporte Python 3.x.

```bash
python ruletabackend.py
```

## Notas

- **Advertencia**: Este juego está diseñado para ser jugado de forma responsable. Asegúrate de que todos los jugadores estén de acuerdo con las reglas y las condiciones antes de comenzar. 
- **Cambiar de modo**: Si decides cambiar de modo, un nuevo jugador será seleccionado al azar para elegir el nuevo modo de juego.
