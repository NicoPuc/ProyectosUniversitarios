import re
def cantidad_de_digitos(numero):
    cotador = 0
    if numero == 0:
        cotador = 1
    else:
        cotador = 1
        while (numero >= 10):
            cotador += 1
            numero = numero//10
    return cotador
def en_posicion(numero, indice, reversa):
    a = []
    nume = str(numero)
    for d in re.findall('(\d)', nume):
        a.append(d)
    if reversa == True:
        ede = int(nume)
        c = cantidad_de_digitos(ede) - indice - 1
        p = a[c]
    else:
        p = a[indice]
    return p


def reemplazar(numero, indice, nuevo, reversa):
    digitos = list(str(numero))
    longitud = len(digitos)
    if reversa:
        i = longitud - 1 - indice
    else:
        i = indice
    digitos[i] = str(nuevo)
    return int(''.join(digitos))


numero = 316
indice = 0
nuevo = 5
reversa = False
print(cantidad_de_digitos(numero))
print(en_posicion(numero, indice, reversa))
print(reemplazar(numero, indice, nuevo, reversa))