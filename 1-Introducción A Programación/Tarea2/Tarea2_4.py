def buscar_espacio(trabalenguas, posicion):
    espacio = ' '
    for i in range(posicion, len(trabalenguas)):
        if trabalenguas[i] == espacio:
            espacio = i-posicion
            return espacio
    espacio_ = len(trabalenguas) - posicion
    return espacio_


def encontrar_cadena(trabalenguas, cadena, posicion):
    posiciones = []
    if posicion >= len(trabalenguas):
        return posiciones

    indice = trabalenguas.find(cadena, posicion)
    if indice != -1:
        posiciones.append(indice)
        posiciones += encontrar_cadena(trabalenguas, cadena, indice + 1)

    return posiciones


trabalenguas = input()
cadena = input()
posiciones = encontrar_cadena(trabalenguas, cadena, 0)
print(posiciones)
palabras = []
for i in posiciones:
    palabras.append(trabalenguas[i: i + buscar_espacio(trabalenguas, i)])
fin = ' '.join(palabras)
print(fin)
