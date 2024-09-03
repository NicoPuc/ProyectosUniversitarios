def lupa_cuenta_vocales(palabra):
    palabra = palabra.lower()
    vocales = 'aeiou'
    cont = 0
    for i in palabra:
        if i in vocales:
            cont += 1
    return cont


def tijeras_corta_letras(codigo):
    codigo = list(codigo)
    for i in range(len(codigo)-1, -1, -1):
        if i % 4 == 0:
            codigo.pop(i)
    codigo = ''.join(codigo)
    return codigo


def piramide_invierte_palabras(codigo):
    conjuntos = []
    n = 1
    while codigo:
        conjunto = codigo[:n]
        conjuntos.append(conjunto)
        codigo = codigo[n:]
        n += 1

    nuevo_codigo = ''.join(conjuntos[::-1])
    return nuevo_codigo


print('Hora de ganar esta partida de Escape Room!')
clave = input()
codigo_encriptado = input()
print(f'El codigo encriptado es: {codigo_encriptado}')
print('Descifrando codigo...')
if lupa_cuenta_vocales(clave) % 2 == 0:
    codigo = piramide_invierte_palabras(codigo_encriptado)
    print(codigo)
    codigo = tijeras_corta_letras(codigo)
    print(codigo)
    codigo = piramide_invierte_palabras(codigo)
    print(codigo)
else:
    codigo = tijeras_corta_letras(codigo_encriptado)
    print(codigo)
    codigo = piramide_invierte_palabras(codigo)
    print(codigo)
    codigo = tijeras_corta_letras(codigo)
    print(codigo)
print(f'El codigo de escape es: {codigo}')
