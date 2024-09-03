import sys
from iic2343 import Basys3

# Definimos el instruction set
instruction_set = {'SHR B,A': ['00000100001100000000'], 'OR DIR': ['00000000000111001000'], 'SHL (B),A': ['00000000001111010000'], 'XOR B,DIR': ['00000100111000001000'], 'ADD A,(B)': ['00001000110000010000'], 'SHL A': ['00001000001110000000'], 'XOR B,A': ['00000100001000000000'], 'INC A': ['01101000100000000000'], 'INC B': ['00000110000000000000'], 'MOV A,B': ['00001001000000000000'], 'OR A,B': ['00001000000110000000'], 'NOT DIR,A': ['00000000001011001000'], 'JCR Ins': ['11000000000000100000'], 'SUB B,(B)': ['00000100110010010000'], 'MOV A,DIR': ['00001001110000001000'], 'SUB B,DIR': ['00000100110010001000'], 'NOT (B),A': ['00000000001011010000'], 'CMP A,(B)': ['00000000110010010000'], 'MOV DIR,B': ['00000001000001001000'], 'MOV DIR,A': ['00000000010001001000'], 'ADD A,LIT': ['01001000100000000000'], 'INC (B)': ['00000010110001010000'], 'AND A,DIR': ['00001000110100001000'], 'MOV B,DIR': ['00000101110000001000'], 'ADD A,DIR': ['00001000110000001000'], 'POP A': ['11010000000000000100', '00001001110000000000'], 'POP B': ['11100000000000000100', '00000101110000000000'], 'INC DIR': ['00000010110001001000'], 'MOV A,LIT': ['00001001100000000000'], 'MOV B,LIT': ['00000101100000000000'], 'SHR DIR,A': ['00000000001101001000'], 'JMP Ins': ['00010000000000100000'], 'SUB A,DIR': ['00001000110010001000'], 'OR A,(B)': ['00001000110110010000'], 'MOV B,A': ['00000100010000000000'], 'SUB A,LIT': ['01011000100010000000'], 'XOR DIR': ['00000000001001001000'], 'AND B,(B)': ['00000100110100010000'], 'NOT B,A': ['00000100001010001000'], 'XOR B,LIT': ['00000100101000000000'], 'NOT A': ['00001000001010001000'], 'AND DIR': ['00000000000101001000'], 'SUB B,LIT': ['00000100100010000000'], 'JLE Ins': ['10110000000000100000'], 'PUSH B': ['00000001000001000010'], 'SHR A': ['00001000001100000000'], 'PUSH A': ['00000000010001000010'], 'NOP': ['00000000000000000000'], 'JLT Ins': ['10100000000000100000'], 'RET': ['00000000000000000100', '00000000000000100001'], 'CALL Ins': ['00000000000001100010'], 'CMP A,DIR': ['00000000110010001000'], 'OR B,LIT': ['00000100100110000000'], 'SHL B,A': ['00000100001110000000'], 'AND A,B': ['00001000000100000000'], 'SHL DIR,A': ['00000000001111001000'], 'XOR A,DIR': ['00001000111000001000'], 'CMP A,B': ['00000000000010000000'], 'SUB A,B': ['00001000000010000000'], 'MOV B,(B)': ['00000101110000010000'], 'JGT Ins': ['10000000000000100000'], 'ADD A,B': ['00001000000000000000'], 'OR A,LIT': ['00001000100110000000'], 'XOR A,LIT': ['00001000101000001000'], 'AND A,(B)': ['00001000110100010000'], 'SUB A,(B)': ['00001000110010010000'], 'AND A,LIT': ['00001000100100000000'], 'ADD DIR': ['00000000000001001000'], 'OR A,DIR': ['00001000110110001000'], 'OR B,A': ['00000100000110000000'], 'XOR B,(B)': ['00000100111000010000'], 'JEQ Ins': ['00100000000000100000'], 'ADD B,A': ['00000100000000000000'], 'AND B,DIR': ['00000100110100001000'], 'ADD B,(B)': ['00000100110000010000'], 'JNE Ins': ['00110000000000100000'], 'XOR A,B': ['00001000001000000000'], 'SUB DIR': ['00000000000011001000'], 'MOV (B),LIT': ['00000001100001010000'], 'OR B,(B)': ['00000100110110010000'], 'AND B,A': ['00000100000100000000'], 'SUB B,A': ['00000100000010000000'], 'AND B,LIT': ['00000100100100000000'], 'ADD B,DIR': ['00000100110000001000'], 'MOV (B),A': ['00000000010001010000'], 'ADD B,LIT': ['00000100100000000000'], 'MOV A,(B)': ['00001001110000010000'], 'OR B,DIR': ['00000100110110001000'], 'CMP A,LIT': ['00000000100010000000'], 'XOR A,(B)': ['00001000111000010000'], 'JGE Ins': ['10010000000000100000'], 'DEC A': ['01111000100010000000'], 'SHR (B),A': ['00000000001101010000']}

instruction_name = ['MOV', 'ADD', "SUB", 'AND', 'OR', 'XOR', 'NOT', 'SHL', 'SHR',
                    'INC', 'DEC', 'CMP', 'JMP', 'JEQ', 'JNE', 'JGT', 'JGE', 'JLT',
                    'JLE', 'JCR', 'NOP', 'PUSH', 'POP', 'CALL', 'RET']

defined_vars = [] # variables definidas en DATA

directory_order = []

instruction_blocks = {} # guardamos bloques de instrucciones

code = False # variable que determina si estamos en seccion CODE:


def convert_to_decimal(number):
    try:
        if number.endswith('d'):
            return int(number[:-1])
        elif number.endswith('b'):
            return int(number[:-1], 2)
        elif number.endswith('h'):
            return int(number[:-1], 16)
        else:
            return int(number)
    except ValueError:
        return None


def formatLine(operands, code, block, endOfCode):
    line = ""
    for i in operands:
        if i[0:2] == "//": # tambien puede ser i[0:1]
            if block is not False and line != '':
                #instruction_blocks[block].append(line)
                pass
            return line, code, block, endOfCode
        if code is True: # si estamos en la seccion CODE:
            if i in instruction_name: # si i es una instruccion
                line = i + ' '
            elif i != '':
                if i[-1] == ":": # es el nombre de un bloque
                    # AQUI DEBEMOS PARAR DE AGREGAR LINEAS!!!!!
                    endOfCode = True
                    line = i
                    # nameOfInstruction = i.replace(":", "")
                    #instruction_blocks[i] = [] # guardamos el bloque
                    block = i
                    return line, code, block, endOfCode
                else:
                    line = line + i
        else:
            if i == 'DATA:':
                line = 'DATA:'
            elif i == 'CODE:':
                line = 'CODE:'
                code = True
            else:
                if i != '':
                    line = line + i + ' '
    if block is not False and line != '':
        #instruction_blocks[block].append(line)
        pass
    return line, code, block, endOfCode


def orderLines(assembly_code):
    code = False
    block = False
    endOfCode = False
    orderedAssemblyList = []
    for line in assembly_code:
        operands = line.strip().split(" ")
        newLine, codeTrigger, block, endOfCode = formatLine(operands, code, block, endOfCode)
        if codeTrigger is True:
            code = True
        #if endOfCode is False:
        orderedAssemblyList.append(newLine)
    return orderedAssemblyList


def storeVars(orderedAssemblyList): # guarda variables en defined_vars y borra espacios en assembly
    noSpaces = []
    potentialLatestArray = ''
    arrayObjectID = 100
    for i in orderedAssemblyList:
        if i != '':
            noSpaces.append(i)
    for i in noSpaces:
        dummy = i.replace(" ", '')
        if dummy == 'CODE:':
            break
        if dummy != 'DATA:':
            # hacemos store VAR Y ARRAY
            arguments = i.strip().split(" ")
            if len(arguments) > 1:
                defined_vars.append([arguments[0], arguments[1]])
                directory_order.append(arguments[0])
                potentialLatestArray = arguments[0]
            else: 
                directory_order.append(potentialLatestArray+str(arrayObjectID))
                defined_vars.append([potentialLatestArray+str(arrayObjectID), arguments[0]])
                arrayObjectID = arrayObjectID + 1
    return noSpaces


def uploadDataOpcode(finalWords):
    # finalWords = []
    count = 0
    numberOfLines = 0
    print("UPLOADING DATA")
    for data in defined_vars:
        print(data)
        data[1] = convert_to_decimal(str(data[1]))
        binaryLit = bin(int(data[1]))[2:] # CONVERTIMOS DATA A BINARIO COMPATIBILITYFUNCT
        remainingBits = 16 - len(str(binaryLit))
        zeros = '0' * remainingBits
        sixteenBits = zeros + str(binaryLit)

        binaryCount = bin(count)[2:] # convertimos count a Binario
        remainingBits2 = 16 - len(str(binaryCount))
        zeros2 = '0' * remainingBits2
        sixteenBits2 = zeros2 + str(binaryCount)
        
        # MOV A, DATA
        # MOV (count) A
        finalWords.append(sixteenBits + instruction_set['MOV A,LIT'][0])
        finalWords.append(sixteenBits2 + instruction_set['MOV DIR,A'][0])

        numberOfLines = numberOfLines + 2
        count = count + 1
    
    print("DONE UPLOADING")
    return numberOfLines


def changeToInstructionSet(line):
    usingDirectory = False
    usingLiteral = False
    usingIns = False
    arguments = line.strip().split(" ")
    if len(arguments) > 1:
        if ',' in arguments[1]:
            operands = arguments[1].strip().split(",")
            operandA = operands[0]
            operandB = operands[1]
            if '(' in operandA and operandB == 'A':
                if operandA == "(B)":
                    mapped_operands = "(B),A"
                else:
                    mapped_operands = "DIR,A"
                    # GUARDAR DIR VALUE
                    usingDirectory = operandA.replace("(", "")
                    usingDirectory = usingDirectory.replace(")", "")
            elif '(' in operandA and operandB == 'B':
                mapped_operands = "DIR,B"
                # GUARDAR DIR VALUE
                usingDirectory = operandA.replace("(", "")
                usingDirectory = usingDirectory.replace(")", "")
            elif operandA == 'A' and '(' in operandB:
                if operandB == "(B)":
                    mapped_operands = "A,(B)"
                else:
                    mapped_operands = "A,DIR"
                    # GUARDAR DIR VALUE
                    usingDirectory = operandB.replace("(", "")
                    usingDirectory = usingDirectory.replace(")", "")
            elif operandA == 'B' and '(' in operandB:
                if operandB == "(B)":
                    mapped_operands = "B,(B)"
                else:
                    mapped_operands = "B,DIR"
                    # GUARDAR DIR VALUE
                    usingDirectory = operandB.replace("(", "")
                    usingDirectory = usingDirectory.replace(")", "")
            elif operandA == 'A' and operandB == 'B':
                mapped_operands = "A,B"
            elif operandA == 'B' and operandB == 'A':
                mapped_operands = "B,A"
            elif operandA == 'B' and operandB == 'A':
                mapped_operands = "B,A"
            elif operandA == "(B)" and operandB != 'A':
                mapped_operands = "(B),LIT"
                # GUARDAR LITERAL
                usingLiteral = operandB
            else:
                if operandA == 'A':
                    if operandB in directory_order:
                        usingLiteral = operandB
                    else:
                        usingLiteral = operandB # GUARDAR LITERAL
                    mapped_operands = "A,LIT"
                elif operandA == 'B':
                    if operandB in directory_order:
                        usingLiteral = operandB
                    else:
                        usingLiteral = operandB # GUARDAR LITERAL
                    mapped_operands = "B,LIT"
        else:
            if arguments[1] == 'A':
                mapped_operands = 'A'
            elif arguments[1] == 'B':
                mapped_operands = 'B'
            elif '(' in arguments[1]:
                if arguments[1] == '(B)':
                    mapped_operands = '(B)'
                else:
                    mapped_operands = 'DIR'
                    # GUARDAR DIR
                    usingDirectory = arguments[1].replace("(", "")
                    usingDirectory = usingDirectory.replace(")", "")
            else:
                mapped_operands = 'Ins'
                # GUARDAR INS
                usingIns = arguments[1]

    if len(arguments) > 1:
        print(arguments)
        mapped_instruction = arguments[0] + ' ' + mapped_operands
    else:
        mapped_instruction = arguments[0]

    opcodeInstructions = instruction_set[mapped_instruction]

    if usingDirectory != False:
        # encontrar DIR en lista directory_order, else estamos usando literal para encontrar DIR en MEM
        if usingDirectory in directory_order:
            dirLocation = directory_order.index(usingDirectory)
        else:
            usingDirectory = convert_to_decimal(str(usingDirectory))
            dirLocation = int(usingDirectory) # COMPATIBILITYFUNCT
        binaryDir = bin(dirLocation)[2:]
        remainingBits = 16 - len(str(binaryDir))
        zeros = '0' * remainingBits
        sixteenBits = zeros + str(binaryDir)
    elif usingLiteral != False:
        if usingLiteral in directory_order:
            usingLiteral = directory_order.index(usingLiteral) # AQUI HACER MODIFICACION PARA ACEPTAR LITERAL DE DIR
        else:
            pass
        usingLiteral = convert_to_decimal(str(usingLiteral))
        binaryLit = bin(int(usingLiteral))[2:] # SOLO ESTA IMPLEMENTADO PARA DECIMALES. CAMBIAR!!! COMPATIBILITYFUNCT
        remainingBits = 16 - len(str(binaryLit))
        zeros = '0' * remainingBits
        sixteenBits = zeros + str(binaryLit)
    elif usingIns != False:
        insIndex = instruction_blocks[usingIns+":"]
        binaryIns = bin(insIndex)[2:]
        remainingBits = 16 - len(str(binaryIns))
        zeros = '0' * remainingBits
        sixteenBits = zeros + str(binaryIns)
    else:
        if mapped_instruction == "INC A": 
            sixteenBits = '0000000000000001' # AQUI IMPLEMENTAMOS INC + 1
        elif mapped_instruction == "DEC A":
            sixteenBits = '0000000000000001'
        elif mapped_instruction == "INC (B)":
            sixteenBits = '0000000000000001'
        else:
            sixteenBits = '0000000000000000'
    
    finalWords = []
    for instruction in opcodeInstructions:
        finalWords.append(sixteenBits + instruction)

    return finalWords


def indexIns(dataUploadCount, noSpacesAssembly):
    codeSection = False
    for i in noSpacesAssembly:
        if codeSection is True:
            if i[-1] == ":":
                stopSearch = False
                startIndex = noSpacesAssembly.index(i)+1
                while stopSearch == False:
                    if noSpacesAssembly[startIndex][-1] != ":":
                        instruction_blocks[i] = dataUploadCount
                        stopSearch = True
                    else:
                        pass
                    startIndex = startIndex + 1
            else:
                if i[0:3] in ['POP', 'RET']:
                    dataUploadCount = dataUploadCount + 2
                else:
                    dataUploadCount = dataUploadCount + 1
        if i == 'CODE:':
            codeSection = True


##################################################################################
#FLUJO PROGRAMA

filename = sys.argv[1]
# Step 1: Read the assembly file
with open(filename, "r", encoding='utf-8', errors='ignore') as file:
    assembly_code = file.readlines()

# Definimos lista que representa el opcode final, con cada elemento siendo una linea
finalOpcode = []

# Estandarizamos el formato del assembly (sacamos comentarios, espacios)
orderedLines = orderLines(assembly_code)

# Guardamos las variables, en defined_vars, removemos las lineas en blanco del assembly
noSpacesAssembly = storeVars(orderedLines)

# Cargamos lineas opcode de DATA
dataUploadCount = uploadDataOpcode(finalOpcode)
# Indexamos los bloques (Ins)
indexIns(dataUploadCount, noSpacesAssembly)

# HACEMOS TRANSLATE A OPCODE en finalOpcode
codeSection = False
for i in noSpacesAssembly:
    if codeSection is True:
        if i[-1] != ':':
            words = changeToInstructionSet(i)
            for w in words:
                finalOpcode.append(w)
    if i == 'CODE:':
        codeSection = True

# Print Assembly ordenado
for i in noSpacesAssembly:
    print(i)

# Print Opcode
for i in finalOpcode:
    print('"'+ i + '",')
print(len(finalOpcode))

# BASYS3: START
instance = Basys3()
for i in instance.available_ports:
    print(i.name)
    print(i.device)
    print(i.description)
    print(i.location)
    print('-'*100)
    print(instance.available_ports[0].name)

########

instance.begin(port_number=2)  # port_number is optional  # port_number is optional
addyCount = 0 # START ADDRESS
for word in finalOpcode:
    byte_array_length = 5  # Desired length of the bytearray
    # Split the remaining bits into 8-bit chunks
    word = "0000" + word
    bits_chunks = [word[i:i+8] for i in range(0, len(word), 8)]
    # Convert each 8-bit chunk to an integer and append to the bytearray
    aux = []
    for chunk in bits_chunks:
        decimal_number = int(chunk, 2)
        aux.append(decimal_number)
    byte_array = bytearray(aux)
    instance.write(addyCount, byte_array)
    addyCount = addyCount + 1


instance.end()
# BASYS3: END

print(len(finalOpcode))

print(instruction_blocks)
print(defined_vars)
print(directory_order)