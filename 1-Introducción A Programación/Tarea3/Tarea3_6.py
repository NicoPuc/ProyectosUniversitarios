class DCCivilizacion:
    def __init__(self, nombre, edad):
        self.nombre = nombre
        self.edad = edad
        self.mapa = []
        self.oro = 0
        self.soldados = 0
        self.tecnologia = 0
        self.proteccion = 0
        self.moral = 100

    def __str__(self):
        return f"Esta es la gran {self.nombre} que ha sobrevivido {self.edad} inviernos.\n" \
               f"La gran {self.nombre} tiene:\n" \
               f"{self.oro} kilos de oro\n" \
               f"{self.soldados} miles de soldados\n" \
               f"{self.tecnologia} puntos de avance tecnologicos\n" \
               f"{self.proteccion} kilometros de muralla de proteccion\n" \
               f"{self.moral} puntos de moral"
    def crear_mapa(self, n):
        self.mapa = [["" for _ in range(n)] for _ in range(n)]

    def agregar_ciudad(self, ciudad):
        self.mapa[ciudad.fila][ciudad.columna] = ciudad

    def recolectar(self):
        for fila in self.mapa:
            for casillero in fila:
                if isinstance(casillero, DCCiudad):
                    if casillero.tipo == "financiera":
                        self.oro += 100
                        print(f"{casillero.nombre} recolecto 100 de oro")
                    elif casillero.tipo == "militar":
                        self.soldados += 10
                        print(f"{casillero.nombre} ha entrenado 10 mil soldados")
                    elif casillero.tipo == "cientifica":
                        self.tecnologia += 10
                        print(f"{casillero.nombre} ha generado 10 puntos de avance tecnologico")
                    elif casillero.tipo == "fortaleza":
                        self.proteccion += 15
                        print(f"{casillero.nombre} ha aportado con 15 puntos de proteccion")
    def aplicar_evento(self, nombre_evento, efecto_oro, efecto_soldados, efecto_tecnologia, efecto_proteccion):
        print(f'Ha ocurrido {nombre_evento}')
        self.oro += efecto_oro
        self.soldados += efecto_soldados
        self.tecnologia += efecto_tecnologia
        self.proteccion += efecto_proteccion
    def invasion_ciudad(self, civilizacion_atacante, fila, columna):
        ciudad_defensa = civilizacion.mapa[fila][columna]
        print(f'{civilizacion_atacante} ha atacado la ciudad de {ciudad_defensa.nombre}')
        ciudad_defensa.vida -= 50
        civilizacion.oro -= 80
        civilizacion.soldados -=  10
        civilizacion.moral -= 50
        if ciudad_defensa.vida <= 0:
            print(f'Se perdio la ciudad de {ciudad_defensa.nombre} a manos de {civilizacion_atacante}')
            civilizacion.mapa[fila][columna] = ''
        return ciudad_defensa

    def conquistar_ciudad(self, nombre_ciudad, tipo):
        fila = 0
        for i in civilizacion.mapa:
            columna = 0
            for e in i:
                if e == '':
                    ciudad = DCCiudad(nombre_ciudad, tipo, int(fila), int(columna))
                    civilizacion.agregar_ciudad(ciudad)
                    print(f'{civilizacion.nombre} ha conquistado la ciudad de {ciudad.nombre}')
                    if tipo == 'financiera':
                        civilizacion.oro += 100
                        print(f'{ciudad.nombre} recolecto 100 de oro')
                    elif tipo == 'militar':
                        civilizacion.soldados += 10
                        print(f'{ciudad.nombre} ha entrenado 10 mil soldados')
                    elif tipo == 'cientifica':
                        civilizacion.tecnologia += 10
                        print(f'{ciudad.nombre} ha generado 10 puntos de avance tecnologico')
                    elif tipo == 'fortaleza':
                        civilizacion.proteccion += 15
                        print(f'{ciudad.nombre} ha aportado con 15 puntos de proteccion')
                    return ciudad
                columna += 1
            fila += 1
        
class DCCiudad:
    def __init__(self, nombre, tipo, fila, columna):
        self.nombre = nombre
        self.tipo = tipo
        self.vida = 100
        self.fila = int(fila)
        self.columna = int(columna)
    def __str__(self):
        return f"Esta es la gran DCCiudad de {self.nombre} de tipo {self.tipo} con {self.vida} de vida."

archivo = input()
archivo = open(archivo,'r')
a = archivo.readline()
a = list(a.split(','))
nombre_civ = a[0]
edad_civ = int(a[1])
n = int(a[2])
civilizacion = DCCivilizacion(nombre_civ, edad_civ)
civilizacion.crear_mapa(n)
for i in archivo.readlines():
    i = list(i.split(','))
    if len(i) == 4:
        nombre_ciudad = i[0]
        tipo_ciudad = i[1]
        fila = int(i[2])
        columna = int(i[3])
        ciudad = DCCiudad(nombre_ciudad, tipo_ciudad, fila, columna)
        civilizacion.agregar_ciudad(ciudad)
archivo.close()
civilizacion.recolectar()
print(civilizacion)

for i in range(5):
    if civilizacion.oro < 0:
        civilizacion.oro = 0
    if civilizacion.proteccion < 0:
        civilizacion.proteccion = 0
    if civilizacion.soldados < 0:
        civilizacion.soldados = 0
    if civilizacion.tecnologia < 0:
        civilizacion.tecnologia = 0
    if civilizacion.moral < 0:
        civilizacion.moral = 0
    evento = input().split(",")
    if evento [0] == 'Conquista':
        nombre_ciudad_conquistada = evento[1]
        tipo_ciudad_conquistada = evento[2]
        civilizacion.conquistar_ciudad(nombre_ciudad_conquistada, tipo_ciudad_conquistada)
    elif evento[0] == 'Invasion':
        civilizacion_atacante = evento[1]
        fila = int(evento[2])
        columna = int(evento[3])
        civilizacion.invasion_ciudad(civilizacion_atacante, fila, columna)
    else:
        nombre_evento = evento[0]
        efecto_oro = int(evento[1])
        efecto_proteccion = int(evento[4])
        efecto_soldados = int(evento[2])
        efecto_tecnologia = int(evento[3])
        civilizacion.aplicar_evento(nombre_evento, efecto_oro, efecto_soldados, efecto_tecnologia, efecto_proteccion)


if civilizacion.oro < 0:
    civilizacion.oro = 0
if civilizacion.proteccion < 0:
    civilizacion.proteccion = 0
if civilizacion.soldados < 0:
    civilizacion.soldados = 0
if civilizacion.tecnologia < 0:
    civilizacion.tecnologia = 0
if civilizacion.moral < 0:
    civilizacion.moral = 0

print(civilizacion)
if civilizacion.moral <= 0:
    print(f'{civilizacion.nombre} cayo')
elif civilizacion.oro == 0 or civilizacion.proteccion == 0 or civilizacion.tecnologia == 0 or civilizacion.soldados == 0:
    print(f'{civilizacion.nombre} cayo')
else:
    print(f'{civilizacion.nombre} sobrevivio al paso del tiempo')