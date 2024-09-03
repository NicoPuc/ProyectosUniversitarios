import os
import psycopg2
import funciones_cargador

# Conexion al server
try:
    conn = psycopg2.connect(
        database="grupo65",
        user="grupo65",
        host="pavlov.ing.puc.cl",
        port=5432,
        password="lostres") 
    print("Conexion aceptada\n")
except:
    print("Conexion fallida")


# Construir la ruta relativa al archivo CSV
def ruta(archivo):
    current_dir = os.path.dirname(__file__)
    archivo = os.path.join(current_dir, 'Datos', f'{archivo}.csv')
    return archivo

def cargar_tablas(conn):
    cursor = conn.cursor()
    ids_restaurantes = funciones_cargador.ids_restaurantes(ruta('restaurantes'), ruta('restaurantes2'))

    # Llamamos a funciones para cargar datos:
    funciones_cargador.cargar_cliente(ruta('clientes'), cursor, conn)
    funciones_cargador.cargar_sectores(ruta('comuna2'), ruta('clientes'), cursor, conn)
    funciones_cargador.cargar_restaurant_sucursal_plato_ingrediente(ruta('restaurantes2'),ruta('platos') ,ids_restaurantes, cursor, conn)
    funciones_cargador.cargar_despachador(ruta('cldeldes'), cursor, conn)
    funciones_cargador.cargar_delivery(ruta('cldeldes'), cursor, conn)
    funciones_cargador.cargar_pedido(ruta('pedidos2'), cursor, conn)

    cursor.close()
    conn.close()

cargar_tablas(conn)