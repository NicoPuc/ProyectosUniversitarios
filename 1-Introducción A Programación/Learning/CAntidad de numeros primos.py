import time

print("Este programa calcula la cantidad de primos entre 1 y n\n")

while True:
    n = int(input("Ingresa un valor para n: "))

    inicio = time.time()

    contador = 0
    for num in range(2, n + 1):
        es_primo = True
        for div in range(2, num):
            if num % div == 0:
                es_primo = False
        if es_primo:
            contador += 1

    fin = time.time()

    print("Hay", contador, "numeros primos entre 1 y", n)
    print("El tiempo de ejecución fue de", fin - inicio, "seg\n")