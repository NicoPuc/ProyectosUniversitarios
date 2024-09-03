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


class DCCiudad:
    def __init__(self, nombre, tipo, fila, columna):
        self.nombre = nombre
        self.tipo = tipo
        self.vida = 100
        self.fila = fila
        self.columna = columna

    def __str__(self):
        return f"Esta es la gran DCCiudad de {self.nombre} de tipo {self.tipo} con {self.vida} de vida."


nombre_civ, edad_civ = input().split(",")
edad_civ = int(edad_civ)
civilizacion = DCCivilizacion(nombre_civ, edad_civ)

n = int(input())
civilizacion.crear_mapa(n)

nombre_ciudad, tipo_ciudad = input().split(',')
fila, columna = input().split(',')
ciudad = DCCiudad(nombre_ciudad, tipo_ciudad, int(fila), int(columna))
civilizacion.agregar_ciudad(ciudad)

nombre_ciudad, tipo_ciudad = input().split(',')
fila, columna = input().split(',')
ciudad_2 = DCCiudad(nombre_ciudad, tipo_ciudad, int(fila), int(columna))
civilizacion.agregar_ciudad(ciudad_2)

print(ciudad)
print(ciudad_2)
civilizacion.recolectar()
print(civilizacion)
