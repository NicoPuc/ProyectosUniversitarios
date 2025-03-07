numero_1 = int(input()) #canal objetivo
numero_2 = int(input()) #canal actual

diferencia_entre_canales = numero_2 - numero_1
ab = abs(diferencia_entre_canales)
if numero_1 < numero_2 and ab > 50:
    p = 100 - ab
    print(f"{p} veces arriba")
elif numero_1 > numero_2 and ab > 50:
    p = 100-ab
    print(f"{p} veces abajo")

elif diferencia_entre_canales < 0:
    print(f"{ab} veces arriba")
elif diferencia_entre_canales > 0:
    print(f"{ab} veces abajo")