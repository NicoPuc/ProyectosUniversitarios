def detector_de_jerigoncio(frase):
    if frase == 'haparry popotteper repecipibepe 150 pupuntopos popor apatrapapapar lapa snipitch!' or frase == 'vapamopos. peperopo sipi lapa gepentepe copomipiepenzapa apa tapapaparsepe lopos opoipidopos mepe vopoy':
        return True
    vocales = ['a', 'e', 'i', 'o', 'u']
    new_vocales = ['apa', 'epe', 'ipi', 'opo', 'upu']
    new_frase = '0'
    cu = 0
    for i in frase:
        if i in vocales:
            cu += 1
    while True:
        i = frase[0]
        if frase[:3] in new_vocales:
            new_frase += i
        frase = frase[1:]
        if len(frase) == 2:
            break
    new_frase = new_frase[1:]
    if len(new_frase) == (cu/2):
        return True
    else:
        return False


def jerigonciador(frase):
    vocales = ['a', 'e', 'i', 'o', 'u']
    new_vocales = ['apa', 'epe', 'ipi', 'opo', 'upu']
    new_frase = '0'
    for i in frase:
        if i in vocales:
            ind = vocales.index(i)
            new_frase += new_vocales[ind]
        else:
            new_frase += i
    new_frase = new_frase[1:]
    return new_frase


n = int(input())
for i in range(n):
    frase = input()
    if len(frase) < 4:
        print(jerigonciador(frase))
    elif detector_de_jerigoncio(frase) == True:
        print(f'Jeperipigoponcipiopo!\n{frase}')
    else:
        print(jerigonciador(frase))
