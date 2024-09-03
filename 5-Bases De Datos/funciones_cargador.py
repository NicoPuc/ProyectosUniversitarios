import csv
import psycopg2
from datetime import datetime


def reemplazar_caracteres_especiales(texto):
    reemplazos = {
        '–': 'ñ',
        '√±': 'ñ',
        '¬∞': 'ñ',
        'Ã±' : 'ñ',
        'Ã³' : 'ó',
        'Ãº' : 'ú'
    }
    for caracter_erroneo, caracter_correcto in reemplazos.items():
        texto = texto.replace(caracter_erroneo, caracter_correcto)
    return texto

def leer_csv(archivo, determinar_delimitador):
    if determinar_delimitador:
        with open(archivo, newline='', encoding='cp1252') as archivo_csv: # mac_roman parece q lee bien
            # Detectar el delimitador automáticamente (; o ,)
            try:
                muestra = archivo_csv.read(1024)
                archivo_csv.seek(0)
                sniffer = csv.Sniffer()
                delimitador = sniffer.sniff(muestra).delimiter
            except csv.Error:
                delimitador = ';'  # Usar ; en caso de error
                archivo_csv.seek(0)  # Reiniciar el archivo para volver a leerlo

            leer = csv.reader(archivo_csv, delimiter=delimitador)
            encabezado = next(leer) # saltamos la fila de encabezado
            data = [fila for fila in leer]
    else:
        with open(archivo, newline='', encoding='cp1252') as archivo_csv:
            leer = csv.reader(archivo_csv, delimiter=';')
            encabezado = next(leer) # saltamos la fila de encabezado
            data = [fila for fila in leer]

    data = [[reemplazar_caracteres_especiales(campo) for campo in fila] for fila in data]
    return data
        
def encriptar_clave(clave, desplazamiento=3):
    """
    Encripta una clave utilizando un desplazamiento en la tabla ASCII.
    
    Args:
    clave (str): La clave a encriptar.
    desplazamiento (int): El número de posiciones a desplazar cada carácter (default es 3).
    
    Returns:
    str: La clave encriptada de máximo 30 caracteres.
    """
    clave_encriptada = []
    for char in clave:
        clave_encriptada.append(chr((ord(char) + desplazamiento) % 128))
    
    clave_encriptada_str = ''.join(clave_encriptada)
    return clave_encriptada_str[:30]

def cargar_cliente(archivo, cursor, conn):
    data = leer_csv(archivo, True)
    print("Cargando clientes...")

    for fila in data:
        nombre, correo, telefono, clave = fila[0], fila[1], fila[2], fila[3]
        clave_encriptada = encriptar_clave(clave)

        query_cliente = """
        INSERT INTO cliente (correo, nombre, clave, telefono)
        VALUES (%s, %s, %s, %s)
        ON CONFLICT (correo) DO NOTHING;
        """
        try:
            cursor.execute(query_cliente, (correo, nombre, clave_encriptada, telefono))
        except psycopg2.Error as e:
            print(f"Error al insertar en cliente: {e.pgcode}, {e.pgerror}")
            conn.rollback() # deshacer
            continue

    try:
        conn.commit()
        print("\nClientes cargados\n")
    except psycopg2.Error as e:
        print(f"Error al confirmar transacciones: {e.pgcode}, {e.pgerror}")
        conn.rollback()


# region -> provincia -> comuna -> direccion
def cargar_sectores(comuna, clientes, cursor, conn):
    data_comuna = leer_csv(comuna, True)
    data_clientes = leer_csv(clientes, False)
    print("Cargando region, provincia, comuna y direccion...")

    for fila in data_comuna:
        cut, nombre, provincia, region = fila[0], fila[1], fila[2], fila[3]

        query_region = """
            INSERT INTO region (nombre)
            VALUES (%s)
            ON CONFLICT (nombre) DO NOTHING;
            """
        
        query_provincia = """
            INSERT INTO provincia (nombre, region_nombre)
            VALUES (%s, %s)
            ON CONFLICT (nombre) DO NOTHING;
            """
        
        query_comuna = """
            INSERT INTO comuna (cut, nombre, provincia_nombre)
            VALUES (%s, %s, %s)
            ON CONFLICT (cut) DO NOTHING;
            """
        try:
            cursor.execute(query_region, (region,))
            cursor.execute(query_provincia, (provincia, region))
            cursor.execute(query_comuna, (cut, nombre, provincia))
        except psycopg2.Error as e:
            print(f"Error al insertar region/provincia/comuna: {e.pgcode}, {e.pgerror}")
            conn.rollback()
            continue
    
    id_direccion = 0
    for fila2 in data_clientes:
        id_direccion += 1
        correo = fila2[1]
        direccion= fila2[4]
        comuna_cut = fila2[5]

        query_direccion = """
            INSERT INTO direccion (id_direccion, direccion, comuna_cut, cliente_correo)
            VALUES (%s, %s, %s, %s)
            ON CONFLICT (id_direccion) DO NOTHING;
            """
        try:
            cursor.execute(query_direccion, (id_direccion, direccion, comuna_cut, correo))
        except psycopg2.Error as e:
            print(f"Error al insertar direccion: {e.pgcode}, {e.pgerror}")
            conn.rollback()
            continue

    try:
        conn.commit()
        print("\nCargados datos de region, provincia, comuna y direccion\n")
    except psycopg2.Error as e:
        print(f"Error al confirmar transacciones: {e.pgcode}, {e.pgerror}")
        conn.rollback()

def ids_restaurantes(restaurantes, restaurantes2):
    '''
    Retorna un diccionario con los ids de los restaurantes de:
    restaurantes.csv
    '''
    data_restaurantes = leer_csv(restaurantes, False)
    nombres_restaurantes = set()
    for fila in data_restaurantes:
        nombres_restaurantes.add(fila[0])

    ids_restaurantes = {}
    id = 0
    for restaurant in nombres_restaurantes:
        id += 1
        ids_restaurantes[restaurant] = id

    return ids_restaurantes

# restaurant -> sucursal -> plato -> ingrediente
def cargar_restaurant_sucursal_plato_ingrediente(archivo, archivo_plato, ids_restaurantes, cursor, conn):
    # "nombre";"vigente";"estilo";"repartomin";"sucursal";"direccion";"telefono";"area"
    data_restaurant = leer_csv(archivo, False)
    print("Cargando restaurantes y sucursales...")

    for fila in data_restaurant:
        nombre_restaurant, vigente, estilo = fila[0], fila[1], fila[2]
        direccion, telefono, area,  = fila[5], fila[6], fila[7]
        reparto_min, nombre_sucursal = fila[3], fila[4]
        id_restaurant = ids_restaurantes[nombre_restaurant]

        query_restaurant = """
        INSERT INTO restaurant (id_restaurant, nombre, vigente, estilo)
        VALUES (%s, %s, %s, %s)
        ON CONFLICT (nombre) DO NOTHING;
        """
        try:
            cursor.execute(query_restaurant, (id_restaurant, nombre_restaurant, vigente, estilo))
        except psycopg2.Error as e:
            print(f"Error al insertar restaurant: {e.pgcode}, {e.pgerror}")
            conn.rollback() # deshacer
            continue

        query_sucursal = """
            INSERT INTO sucursal (direccion, id_restaurant, nombre, telefono, area, precio_minimo_reparto_gratis)
            VALUES (%s, %s, %s, %s, %s, %s)
            ON CONFLICT (direccion) DO NOTHING;
            """
        try:
            cursor.execute(query_sucursal, (direccion, id_restaurant, nombre_sucursal, telefono, area, reparto_min))
        except psycopg2.Error as e:
                print(f"Error al insertar sucursal: {e.pgcode}, {e.pgerror}")
                conn.rollback()  # deshacer
                continue
    try:
        conn.commit()
    except psycopg2.Error as e:
        print(f"Error al confirmar transacciones: {e.pgcode}, {e.pgerror}")
        conn.rollback()

    print("\nCargado restaurantes y sucursales")

# id;nombre;descripcion;disponibilidad;estilo;restriccion;ingredientes;porciones;precio;tiempo;restaurant;repartomin;vigente
    data_plato = leer_csv(archivo_plato, False)
    print("\nCargando platos (se demora un poco)...")

    for fila in data_plato:
        id_plato, nombre, descripcion = fila[0], fila[1], fila[2]
        porciones, estilo, disponibilidad = fila[7], fila[4], fila[3]
        restriccion, tiempo, precio = fila[5], fila[9], fila[8]
        restaurant = fila[10]
        id_restaurant = ids_restaurantes[restaurant]
        ingredientes = fila[6].split(',')

        query_plato = """
        INSERT INTO plato (id_plato, nombre, descripcion, \
        porciones, estilo, disponibilidad, restriccion, id_restaurant, \
        tiempo, precio)
        VALUES (%s, %s, %s, %s, %s, %s, %s, %s, %s, %s)
        ON CONFLICT (id_plato) DO NOTHING;
        """
        try:
            cursor.execute(query_plato, (id_plato, nombre, descripcion, \
            porciones, estilo, disponibilidad, restriccion, id_restaurant, \
            tiempo, precio))
        except psycopg2.Error as e:
            print(f"Error al insertar en plato: {e.pgcode}, {e.pgerror}")
            conn.rollback() # deshacer
            continue


        for ingrediente in ingredientes:
            ingrediente = ingrediente.strip()
            if ingrediente:
                query_ingredientes = """
                INSERT INTO ingredientes (id_plato, ingrediente)
                VALUES (%s, %s)
                ON CONFLICT (id_plato, ingrediente) DO NOTHING;
                """
                try:
                    cursor.execute(query_ingredientes, (id_plato, ingrediente))
                except psycopg2.Error as e:
                    print(f"Error al insertar en ingredientes: {e.pgcode}, {e.pgerror}")
                    conn.rollback() # deshacer
                    continue
    try:
        conn.commit()
        print("\nPlatos e ingredientes cargados\n")
    except psycopg2.Error as e:
        print(f"Error al confirmar transacciones: {e.pgcode}, {e.pgerror}")
        conn.rollback()

def cargar_despachador(archivo, cursor, conn):
    data_cldeldes = leer_csv(archivo, False)
    print("Cargando despachador...")

    for fila in data_cldeldes:
        nombre, telefono = fila[-2], fila[-1]
    
        query_despachador = """
        INSERT INTO despachador (nombre, telefono)
        VALUES (%s, %s)
        ON CONFLICT (nombre) DO NOTHING;
        """
        try:
            cursor.execute(query_despachador, (nombre, telefono))
        except psycopg2.Error as e:
                print(f"Error al insertar en despachador: {e.pgcode}, {e.pgerror}")
                conn.rollback() # deshacer
                continue
    try:
        conn.commit()
        print("\nDespachadores cargados\n")
    except psycopg2.Error as e:
        print(f"Error al confirmar transacciones: {e.pgcode}, {e.pgerror}")
        conn.rollback()



def cargar_delivery(archivo, cursor, conn):
    data_cldeldes = leer_csv(archivo, False)
    print("Cargando delivery...")

    for fila in data_cldeldes:
        nombre_delivery, telefono = fila[4], fila[6]
        tiempo, vigencia = fila[7], fila[5]

        query_ddelivery = """
        INSERT INTO delivery (nombre_delivery, telefono, \
                            tiempo, vigencia)
        VALUES (%s, %s, %s, %s)
        ON CONFLICT (nombre_delivery) DO NOTHING;
        """
        try:
            cursor.execute(query_ddelivery, (nombre_delivery, telefono, tiempo, vigencia))
        except psycopg2.Error as e:
                print(f"Error al insertar en delivery: {e.pgcode}, {e.pgerror}")
                conn.rollback() # deshacer
                continue
    try:
        conn.commit()
        print("\nDeliverys cargados\n")
    except psycopg2.Error as e:
        print(f"Error al confirmar transacciones: {e.pgcode}, {e.pgerror}")
        conn.rollback()


def verificar_cliente(correo_cliente, cursor, conn):
    query_verificar_cliente = "SELECT 1 FROM cliente WHERE correo = %s"
    cursor.execute(query_verificar_cliente, (correo_cliente,))
    return cursor.fetchone() is not None


def cargar_pedido(archivo, cursor, conn):
    data_pedidos= leer_csv(archivo, False)
    print("Cargando pedidos...")
# id;cliente;delivery;despachador;plato;fecha;hora;estado
    for fila in data_pedidos:
        id_pedido, nombre_delivery = fila[0], fila[2]
        correo_cliente = fila[1]
        fecha, hora, estado = fila[5], fila[6], fila[7]
        # cambiar formato fecha:
        fecha = datetime.strptime(fecha, '%d-%m-%y').strftime('%Y-%m-%d')

        if verificar_cliente(correo_cliente, cursor, conn):
            query_pedidos = """
            INSERT INTO pedido (id_pedido, nombre_delivery, \
                                correo_cliente, fecha, hora, estado)
            VALUES (%s, %s, %s, %s, %s, %s)
            ON CONFLICT (id_pedido) DO NOTHING;
            """
            try:
                cursor.execute(query_pedidos, (id_pedido, nombre_delivery, correo_cliente,fecha, hora, estado ))
            except psycopg2.Error as e:
                    print(f"Error al insertar en pedidos: {e.pgcode}, {e.pgerror}")
                    conn.rollback() # deshacer
                    continue
    try:
        conn.commit()
        print("\nPedidos cargados\n")
    except psycopg2.Error as e:
        print(f"Error al confirmar transacciones: {e.pgcode}, {e.pgerror}")
        conn.rollback()