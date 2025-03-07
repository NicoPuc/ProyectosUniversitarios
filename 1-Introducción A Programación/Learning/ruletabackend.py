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
    j = random.randint(0,len(nombres)-1)
    toma = nombres[j]
    print(f"{toma} te toca elejir que modo vamos a jugar!")
def cuanto_virgen():
    tragos = []
    for i in range(8):
        for j in range(10-i):
            tragos.append(i)
    tragos.append("Matala")
    a = random.randint(0,len(tragos)-1)
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
    a = random.randint(0, len(tragos)-1)
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
    a = random.randint(0, len(tragos)-1)
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
            break
def play():
    nom()
    quien_1()
    elijo = int(input("Que modo quieres...\nVirgen: 1\nNormal: 2\nMortal: 3\n"))
    while True:
        for i in range(5):
            a = input("Lanzar ruleta:")
            if a == "":
                quien()
                jugar(elijo)
        a = int(input(f"Quieres seguir jugando: \n1 = Si\n2 = Cambiar de modo\n3 = No, SOY PUTAZO\n"))
        if a == 3:
            print("Por putazo mata lo que te queda en el vaso\nChao espero verte pronto ._.")
            break
        elif a == 2:
            quien_1()
            elijo = int(input("Que modo quieres...\nVirgen: 1\nNormal: 2\nMortal: 3\n"))
play()

