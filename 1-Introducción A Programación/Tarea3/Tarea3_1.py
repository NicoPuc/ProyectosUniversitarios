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


nombre_civ, edad_civ = input().split(",")
edad_civ = int(edad_civ)
civilizacion = DCCivilizacion(nombre_civ, edad_civ)
print(civilizacion)
