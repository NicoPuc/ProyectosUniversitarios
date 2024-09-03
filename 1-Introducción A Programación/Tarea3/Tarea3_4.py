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
               f"{self.proteccion} kilometros de muralla de proteccion"

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
                        print(
                            f"{casillero.nombre} ha generado 10 puntos de avance tecnologico")
                    elif casillero.tipo == "fortaleza":
                        self.proteccion += 15
                        print(
                            f"{casillero.nombre} ha aportado con 15 puntos de proteccion")

    def aplicar_evento(self, nombre_evento, efecto_oro, efecto_soldados, efecto_tecnologia, efecto_proteccion):
        print(f'Ha ocurrido {nombre_evento}')
        self.oro += efecto_oro
        if self.oro < 0:
            self.oro = 0
        self.soldados += efecto_soldados
        if self.soldados < 0:
            self.soldados = 0
        self.tecnologia += efecto_tecnologia
        if self.tecnologia < 0:
            self.tecnologia = 0
        self.proteccion += efecto_proteccion
        if self.proteccion < 0:
            self.proteccion = 0


class DCCiudad:
    def __init__(self, nombre, tipo, fila, columna):
        self.nombre = nombre
        self.tipo = tipo
        self.vida = 100
        self.fila = fila
        self.columna = columna

    def __str__(self):
        return f"Esta es la gran DCCiudad de {self.nombre} de tipo {self.tipo} con {self.vida} de vida."


archivo = input()
archivo = open(archivo, 'r')
a = archivo.readline()
a = list(a.split(','))
nombre_civ = a[0]
edad_civ = a[1]
n = int(a[2])
civilizacion = DCCivilizacion(nombre_civ, int(edad_civ))
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
    nombre_evento, efecto_oro, efecto_soldados, efecto_tecnologia, efecto_proteccion = input().split(',')
    efecto_oro = int(efecto_oro)
    efecto_proteccion = int(efecto_proteccion)
    efecto_soldados = int(efecto_soldados)
    efecto_tecnologia = int(efecto_tecnologia)
    civilizacion.aplicar_evento(
        nombre_evento, efecto_oro, efecto_soldados, efecto_tecnologia, efecto_proteccion)

print(civilizacion)
if civilizacion.oro > 0 and civilizacion.proteccion > 0 and civilizacion.soldados > 0 and civilizacion.tecnologia > 0:
    print(f'{civilizacion.nombre} sobrevivio al paso del tiempo')
else:
    print(f'{civilizacion.nombre} cayo')
