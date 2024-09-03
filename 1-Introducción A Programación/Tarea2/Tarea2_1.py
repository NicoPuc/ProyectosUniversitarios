def contar_coincidencias(lista_descripciones, descripcion_animal):
    c = 0
    for i in lista_descripciones:
        if i in descripcion_animal:
            c += 1
    return c


def tabu(a):
    lista = []
    c_gato = contar_coincidencias(a, gato)
    c_perro = contar_coincidencias(a, perro)
    c_raton = contar_coincidencias(a, raton)
    c_jirafa = contar_coincidencias(a, jirafa)
    c_elefante = contar_coincidencias(a, elefante)
    c_tigre = contar_coincidencias(a, tigre)
    c_leon = contar_coincidencias(a, leon)
    c_avestruz = contar_coincidencias(a, avestruz)
    c_canario = contar_coincidencias(a, canario)
    lista.append(c_gato)
    lista.append(c_perro)
    lista.append(c_raton)
    lista.append(c_jirafa)
    lista.append(c_elefante)
    lista.append(c_tigre)
    lista.append(c_leon)
    lista.append(c_avestruz)
    lista.append(c_canario)
    m = max(lista)
    p = 0
    for i in lista:
        if m == i:
            p += 1
    if p == 1:
        ind = lista.index(m)
        if ind == 0:
            return 'gato'
        elif ind == 1:
            return 'perro'
        elif ind == 2:
            return 'raton'
        elif ind == 3:
            return 'jirafa'
        elif ind == 4:
            return 'elefante'
        elif ind == 5:
            return 'tigre'
        elif ind == 6:
            return 'leon'
        elif ind == 7:
            return 'avestruz'
        elif ind == 8:
            return 'canario'
    else:
        return 'empate'


gato = ['domestico', 'felino', 'peludo', 'maulla', 'chico', 'tierno']
perro = ['domestico', 'peludo', 'ladra', 'tierno', 'leal', 'mediano']
raton = ['chico', 'gris', 'chef', 'cola', 'roedor', 'plaga']
jirafa = ['salvaje', 'grande', 'africa', 'cuello', 'manchado', 'arboles']
elefante = ['africa', 'salvaje', 'grande', 'gris', 'herbivoro', 'trompa']
tigre = ['india', 'salvaje', 'naranja', 'grande', 'felino', 'rayado']
leon = ['africa', 'amarillo', 'ruge', 'melena', 'grande', 'felino']
avestruz = ['africa', 'plumas', 'cuello', 'oviparo', 'corre', 'gris']
canario = ['plumas', 'vuela', 'oviparo', 'canta', 'domestico', 'amarillo']
print('3, 2, 1... Empieza el juego!')
n = int(input())
a = []
for i in range(n):
    i = input()
    a.append(i)
    print(f'{i}!')
if tabu(a) == 'empate':
    print('No se cual es la palabra secreta :(')
else:
    print(f'La palabra secreta es {tabu(a)}!')
