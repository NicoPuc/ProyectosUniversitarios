from pygments import highlight
from pygments.lexers import PythonLexer
from pygments.formatters import HtmlFormatter

import random
nombres = []
def nom():
    cant = int(input("Cantidad de jugadores:\n"))
    for i in range(cant):
        nombre = str(input(f"Nombre jugador {i+1}:\n"))
        nombres.append(nombre)
def quien():
    a = len(nombres)
    j = random.randint(0,a-1)
    toma = nombres[j]
    print(f"{toma} te toca tomar!")
def quien_1():
    j = random.randint(0,len(nombres))
    toma = nombres[j]
    print(f"{toma} te toca elejir que modo vamos a jugar!")
def cuanto_virgen():
    tragos = []
    for i in range(8):
        for j in range(10-i):
            tragos.append(i)
    tragos.append("Matala")
    a = random.randint(0,len(tragos))
    if tragos[a] == "Matala":
        print(f"{tragos[a]}")
    else:
        print(f"Teni que tomar: {tragos[a]}")
def cuanto_mortal():
    tragos = []
    for i in range(8):
        for j in range(i):
            tragos.append(i)
    for e in range(10):
        tragos.append("Matala")
    a = random.randint(0, len(tragos))
    if tragos[a] == "Matala":
        print(f"{tragos[a]}")
    else:
        print(f"Teni que tomar: {tragos[a]}")
def cuanto_normal():
    tragos = []
    for i in range(8):
        for j in range(10 - i):
            tragos.append(i+1)
    for e in range(4):
        tragos.append("Matala")
    a = random.randint(0, len(tragos))
    if tragos[a] == "Matala":
        print(f"{tragos[a]}")
    else:
        print(f"Teni que tomar: {tragos[a]}")
def jugar(elijo):
    while True:
        if elijo == 1:
            cuanto_virgen()
            break
        elif elijo == 2:
            cuanto_normal()
            break
        elif elijo == 3:
            cuanto_mortal()
            break
        else:
            print("Pon la wea bien po CSM")
nom()
quien_1()
elijo = int(input("Que modo quieres...\nVirgen: 1\nNormal: 2\nMortal: 3\n"))
while True:
    quien()
    jugar(elijo)
    a = int(input(f"Quieres seguir jugando: \n1 = Si\n2 = NO, SOY PUTAZO\n3 = Camiar modo\n"))
    if a == 2:
        break
    elif a == 3:
        quien_1()
        elijo = int(input("Que modo quieres...\nVirgen: 1\nNormal: 2\nMortal: 3\n"))
# create a formatter that will add CSS styling
formatter = HtmlFormatter(style='colorful')

# highlight the code and format it as HTML
highlighted_code = highlight(code, PythonLexer(), formatter)

# write the formatted HTML to a file
with open('code.html', 'w') as f:
    f.write(highlighted_code)