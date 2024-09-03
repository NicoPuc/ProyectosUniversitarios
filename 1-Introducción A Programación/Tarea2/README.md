# Tarea 2 - Programas en Python

Este proyecto incluye cuatro scripts de Python que abordan diferentes desafíos de programación. A continuación se describen cada uno de los archivos, su funcionalidad y cómo ejecutarlos.

## Archivos

### 1. Tarea2_1.py

**Descripción**: Este script implementa un juego interactivo en el que el usuario debe adivinar la palabra secreta basada en una serie de descripciones proporcionadas. El juego compara las descripciones ingresadas con las características de varios animales predefinidos y determina cuál coincide más.

**Funciones**:

- `contar_coincidencias(lista_descripciones, descripcion_animal)`: Cuenta cuántas palabras de la lista de descripciones coinciden con las características de un animal.
- `tabu(a)`: Determina qué animal tiene más coincidencias con las descripciones ingresadas y lo devuelve como la palabra secreta.

**Cómo ejecutar**:

```bash
python Tarea2_1.py
```

### 2. Tarea2_2.py

**Descripción**: Este script es parte de un juego de Escape Room, en el que el usuario debe descifrar un código encriptado utilizando varias herramientas como una lupa, tijeras y una pirámide invertida. Dependiendo de las características de la clave ingresada, el código encriptado se descifra utilizando diferentes técnicas.

**Funciones**:

- `lupa_cuenta_vocales(palabra)`: Cuenta el número de vocales en la palabra dada.
- `tijeras_corta_letras(codigo)`: Corta letras específicas en un código basado en su posición.
- `piramide_invierte_palabras(codigo)`: Invierte fragmentos del código en orden creciente de longitud.

**Cómo ejecutar**:

```bash
python Tarea2_2.py
```

### 3. Tarea2_3.py

**Descripción**: Este script trabaja con el concepto de "jerigoncio", un lenguaje en el que las vocales se reemplazan por secuencias específicas de letras. El programa puede detectar si una frase está en jerigoncio o convertir una frase normal a este lenguaje.

**Funciones**:

- `detector_de_jerigoncio(frase)`: Detecta si una frase está escrita en jerigoncio.
- `jerigonciador(frase)`: Convierte una frase normal al lenguaje jerigoncio.

**Cómo ejecutar**:

```bash
python Tarea2_3.py
```

### 4. Tarea2_4.py

**Descripción**: Este script busca una cadena específica en un trabalenguas y devuelve todas las ocurrencias de la cadena junto con las palabras que la contienen. Es útil para analizar textos en busca de patrones o palabras específicas.

**Funciones**:

- `buscar_espacio(trabalenguas, posicion)`: Encuentra la distancia al siguiente espacio en el trabalenguas desde una posición dada.
- `encontrar_cadena(trabalenguas, cadena, posicion)`: Encuentra todas las posiciones donde una cadena específica aparece en el trabalenguas.

**Cómo ejecutar**:

```bash
python Tarea2_4.py
```

## Requisitos

- Python 3.x {x > 10}

## Notas

- Asegúrate de proporcionar las entradas adecuadas cuando se te solicite durante la ejecución de los scripts.
- Los scripts están diseñados para ser interactivos y requieren la participación del usuario para funcionar correctamente.
