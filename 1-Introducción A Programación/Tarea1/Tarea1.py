maldad = 0
print("Te damos la bienvenida a DCCandyRush!\nSeleccionando corredor")
corredor = str(input())
print(corredor, "grita:")


def grito(corredor):
    if corredor == "Valeria Von Schweetz":
        s = "Correr esta en mi codigo!"
        return s
    elif corredor == "Flan Canela":
        s = "Hora de la canela!"
        return s
    elif corredor == "Sargento Daniela Dinamita":
        s = "La guerra, la guerra nunca cambia"
        return s
    elif corredor == "Ruz el Malvavisco":
        s = "Con o sin lag, ganare!"
        return s
    elif corredor == "Nico Nico Alfajor":
        s = "Hora del Nico Nico"
        return s
    elif corredor == "Enrico Vas Quesos":
        s = "Que es eso?"
        return s
    else:
        s = "Listos o no, aqui voy!"
        return s


print(grito(corredor))
print("Programadores, en posicion\n3 Donuts!\n2 Helados!\n1 Gomita!\nQue comience la carrera!")
while True:  # eventos de carrera
    ob = str(input())
    if ob == "python vIoLeNtA":
        print(f"{corredor} dobla a la derecha para esquivar a la python")
    elif ob == "Ola Malvavisco":
        print(f"{corredor} surfea la ola Malvavisco")
    elif ob == "Helado con papas fritas":
        print(f"{corredor} esquiva para evitar tomar malas decisiones")
    elif ob == "Profesor de calculo":
        print(f"{corredor} se equivoco de ramo, y regresa a la carrera")
    elif ob == "fin":
        print(f"{corredor} enfrento con exito todos los eventos de la carrera!")
        break
    elif ob == "choque":
        print("Ha ocurrido un choque!!")
        corredor_2 = str(input())
        masa_2 = float(input())
        velocidad_2 = int(input())
        masa = float(input())
        velocidad = int(input())
        c_2 = masa_2 * velocidad_2
        c = masa * velocidad
        if c >= c_2:
            print(f"{corredor} ha chocado con {corredor_2} y ha salido victorioso!")
        else:
            print(
                f"{corredor} ha sido descalificado de la carrera luego de chocar con {corredor_2} y perder :-(")
            print(f"{corredor} no fue capaz de terminar la carrera")
            break
    elif ob == "Cherry Bomb":
        print("Recarga de puntos de maldad")
        maldad += 1
    elif ob == "Agrio Bug":
        print("Estas son las palabras agrias que tengo para ti:")
        cont = 0
        lis = []
        while True:
            palabra = str(input())
            if palabra == "Preparate":
                cont += 1
                lis.append(str(input()))
                lis.append(str(input()))
            if cont == 3:
                print(f"{lis[0]}{lis[1]}{lis[2]}{lis[3]}{lis[4]}{lis[5]}")
                print("Es muy dulce por aca, mejor me voy...")
                break
    elif ob == "KingCandy":
        nu = int(input())
        for i in range(nu):
            a = nu-i
            if a % 3 == 0 and a % 5 == 0:
                N = a // (3 * 5)
                for i in range(N):
                    print("KingCandy")
            elif a % 3 == 0 and a % 5 != 0:
                N = a // 3
                for i in range(N):
                    print("King")
            elif a % 5 == 0 and a % 3 != 0:
                N = a // 5
                for i in range(N):
                    print("Candy")
            else:
                print(a)
    else:
        print(f"{corredor} hace un triple mortal sobre {ob} y sigue")
    if maldad == 2:
        print("Lanzamiento de Cherry Bomb!\n-- BOOM --")
        maldad = 1
