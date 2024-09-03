# DCCivilización - Tarea 3

Este proyecto consiste en una serie de scripts de Python que simulan el desarrollo y gestión de una civilización ficticia llamada DCCivilización. A lo largo de los diferentes scripts, se implementan diversas funcionalidades como la creación de un mapa, la adición de ciudades, la recolección de recursos, la aplicación de eventos y la simulación de invasiones y conquistas.

## Archivos

### 1. Tarea3_1.py

**Descripción**: Este script inicializa una civilización con un nombre y una edad específica. La civilización tiene diferentes atributos como oro, soldados, tecnología, protección y moral, que son mostrados al usuario.

**Funciones**:
- `__init__(self, nombre, edad)`: Constructor de la clase `DCCivilizacion`, que inicializa la civilización con atributos básicos.
- `__str__(self)`: Método que retorna una descripción detallada de la civilización.

**Cómo ejecutar**:
```bash
python Tarea3_1.py
```

### 2. Tarea3_2.py

**Descripción**: Este script extiende la funcionalidad del anterior al permitir la creación de un mapa de la civilización y la adición de ciudades. Cada ciudad puede ser de un tipo específico (financiera, militar, científica, fortaleza), y contribuye al desarrollo de la civilización en términos de oro, soldados, tecnología y protección.

**Funciones**:
- `crear_mapa(self, n)`: Crea un mapa cuadrado de tamaño `n x n`.
- `agregar_ciudad(self, ciudad)`: Añade una ciudad a una posición específica en el mapa.
- `recolectar(self)`: Recolecta recursos de todas las ciudades en el mapa, según su tipo.

**Cómo ejecutar**:
```bash
python Tarea3_2.py
```

### 3. Tarea3_3.py

**Descripción**: Este script es similar al anterior pero con entradas y salidas adicionales. Se agregan múltiples ciudades al mapa y se recolectan recursos de todas ellas. Se sigue el mismo procedimiento para crear el mapa, agregar ciudades y recolectar recursos.

**Cómo ejecutar**:
```bash
python Tarea3_3.py
```

### 4. Tarea3_4.py

**Descripción**: Este script introduce la capacidad de aplicar eventos que pueden afectar a la civilización en diferentes aspectos, como la cantidad de oro, soldados, tecnología y protección. Los eventos se leen desde un archivo de entrada.

**Funciones**:
- `aplicar_evento(self, nombre_evento, efecto_oro, efecto_soldados, efecto_tecnologia, efecto_proteccion)`: Aplica los efectos de un evento a la civilización.

**Cómo ejecutar**:
```bash
python Tarea3_4.py
```

### 5. Tarea3_5.py

**Descripción**: Este script añade la funcionalidad de invasión y conquista de ciudades. La civilización puede atacar ciudades de otras civilizaciones, reduciendo la vida de la ciudad atacada, y también puede conquistar nuevas ciudades.

**Funciones**:
- `invasion_ciudad(self, civilizacion_atacante, fila, columna)`: Simula la invasión de una ciudad específica por parte de otra civilización.
- `conquistar_ciudad(self, nombre_ciudad, tipo)`: Conquista una ciudad vacía y la añade al mapa de la civilización.

**Cómo ejecutar**:
```bash
python Tarea3_5.py
```

### 6. Tarea3_6.py

**Descripción**: Este script finaliza la simulación permitiendo la aplicación de múltiples eventos que afectan a la civilización. Además, se verifica si la civilización ha sobrevivido al paso del tiempo o ha caído debido a la pérdida de moral, soldados, tecnología, protección o recursos.

**Cómo ejecutar**:
```bash
python Tarea3_6.py
```

## Requisitos

- Python 3.x {x > 10}


## Notas

- Algunos archivos requieren la lectura de archivos de entrada específicos que contienen datos de la civilización y eventos. Debido a que estos archivos eran proporcionados por los profesores para evaluar la tarea, no están disponibles en este repositorio.
- Asegúrate de proporcionar las entradas adecuadas cuando se te solicite durante la ejecución de los scripts.