from flask import Flask, request, render_template
import psycopg2
import traceback

app = Flask(__name__)

@app.route('/')
def pagina_inicio():
    return render_template('pagina_inicio.html')

@app.route('/form_basico/')
def form_basico():
    return render_template('form_basico.html')

@app.route('/form_avanzado/')
def form_avanzado():
    return render_template('form_avanzado.html')

@app.route('/procesar/', methods=['POST'])
def procesar():
    atributoA = request.form['atributoA']
    atributoB = request.form['atributoB']
    atributoC = request.form['atributoC']
    print(f"SELECT: {atributoA}, FROM: {atributoB}, WHERE: {atributoC}")

    try:
        conn = psycopg2.connect(
            database="grupo65",
            user="grupo65",
            host="pavlov.ing.puc.cl",
            port="5432",
            password="lostres"
        )
        cur = conn.cursor()
        
        # Construir la consulta SQL
        if atributoC:
            consulta_sql = f"SELECT {atributoA} FROM {atributoB} WHERE {atributoC} ORDER BY 1"
        else:
            consulta_sql = f"SELECT {atributoA} FROM {atributoB} ORDER BY 1"
        
        print(f"Ejecutando consulta SQL: {consulta_sql}")
        cur.execute(consulta_sql)
        resultados = cur.fetchall()
        
        # Obtener nombres de las columnas
        nombres_columnas = [desc[0] for desc in cur.description]
        
        cur.close()
        conn.close()
        
        print(f"Resultados obtenidos: {resultados}")
        return render_template('resultados_generales.html', resultados=resultados, nombres_columnas=nombres_columnas)
    except Exception as e:
        print(f"Error en la base de datos: {str(e)}")
        traceback.print_exc()
        return f"Error en la base de datos: {str(e)}"

@app.route('/primera/', methods=['POST'])
def primera():
    plato = request.form.get('plato')
    print(f"Plato recibido: {plato}")

    try:
        conn = psycopg2.connect(
            database="grupo65",
            user="grupo65",
            host="pavlov.ing.puc.cl",
            port="5432",
            password="lostres"
        )
        cur = conn.cursor()

        # Consulta para obtener los restaurantes que tienen el plato especificado y que está disponible
        consulta_sql = """
        SELECT r.nombre AS restaurant, p.nombre AS plato
        FROM restaurant r
        JOIN plato p ON r.id_restaurant = p.id_restaurant
        WHERE p.nombre = %s AND p.disponibilidad = true;
        """
        print(f"Ejecutando consulta SQL: {consulta_sql} con parámetro: {plato}")
        cur.execute(consulta_sql, (plato,))
        resultados = cur.fetchall()
        
        cur.close()
        conn.close()
        
        print(f"Resultados obtenidos: {resultados}")
        if not resultados:
            mensaje = "No se encontraron restaurantes con el plato especificado."
            return render_template('resultados_plato_restaurant.html', mensaje=mensaje, plato=plato, resultados=[])
        
        return render_template('resultados_plato_restaurant.html', resultados=resultados, plato=plato)
    except Exception as e:
        print(f"Error en la base de datos: {str(e)}")
        traceback.print_exc()
        return f"Error en la base de datos: {str(e)}"

@app.route('/busqueda/avanzada/platos_con_restaurantes/', methods=['POST'])
def platos_con_restaurantes():
    try:
        conn = psycopg2.connect(
            database="grupo65",
            user="grupo65",
            host="pavlov.ing.puc.cl",
            port="5432",
            password="lostres"
        )
        cur = conn.cursor()

        # Consulta para obtener todos los platos con sus respectivos restaurantes
        consulta_sql = """
        SELECT r.nombre AS restaurant, p.nombre AS plato
        FROM restaurant r
        JOIN plato p ON r.id_restaurant = p.id_restaurant
        ORDER BY r.nombre, p.nombre;
        """
        print(f"Ejecutando consulta SQL: {consulta_sql}")
        cur.execute(consulta_sql)
        resultados = cur.fetchall()
        cur.close()
        conn.close()
        print(f"Resultados obtenidos: {resultados}")
        return render_template('todos_los_platos_x_restaurant.html', resultados=resultados)
    except Exception as e:
        print(f"Error en la base de datos: {str(e)}")
        traceback.print_exc()
        return f"Error en la base de datos: {str(e)}"

@app.route('/busqueda/avanzada/platos_por_estilo/', methods=['POST'])
def platos_por_estilo():
    estilo = request.form.get('estilo')
    print(f"Estilo recibido: {estilo}")

    try:
        conn = psycopg2.connect(
            database="grupo65",
            user="grupo65",
            host="pavlov.ing.puc.cl",
            port="5432",
            password="lostres"
        )
        cur = conn.cursor()

        # Consulta para obtener los platos por estilo
        consulta_sql = """
        SELECT p.nombre AS plato, p.restriccion
        FROM plato p
        WHERE p.estilo = %s;
        """
        print(f"Ejecutando consulta SQL: {consulta_sql} con parámetro: {estilo}")
        cur.execute(consulta_sql, (estilo,))
        resultados = cur.fetchall()
        
        cur.close()
        conn.close()
        
        print(f"Resultados obtenidos: {resultados}")
        if not resultados:
            mensaje = "No se encontraron platos con el estilo especificado."
            return render_template('resultados_plato_por_estilo.html', mensaje=mensaje, estilo=estilo, resultados=[])
        
        return render_template('resultados_plato_por_estilo.html', resultados=resultados, estilo=estilo)
    except Exception as e:
        print(f"Error en la base de datos: {str(e)}")
        traceback.print_exc()
        return f"Error en la base de datos: {str(e)}"

@app.route('/busqueda/avanzada/plato_por_alergia/', methods=['POST'])
def plato_por_alergia():
    alergia = request.form.get('alergia')
    print(f"Alergia recibida: {alergia}")

    try:
        conn = psycopg2.connect(
            database="grupo65",
            user="grupo65",
            host="pavlov.ing.puc.cl",
            port="5432",
            password="lostres"
        )
        cur = conn.cursor()

        # Consulta para obtener los platos por ingrediente (alergia)
        consulta_sql = """
        SELECT p.nombre AS plato, i.ingrediente
        FROM plato p
        JOIN ingredientes i ON p.id_plato = i.id_plato
        WHERE i.ingrediente = %s;
        """
        print(f"Ejecutando consulta SQL: {consulta_sql} con parámetro: {alergia}")
        cur.execute(consulta_sql, (alergia,))
        resultados = cur.fetchall()
        
        cur.close()
        conn.close()
        
        print(f"Resultados obtenidos: {resultados}")
        if not resultados:
            mensaje = "No se encontraron platos con el ingrediente especificado."
            return render_template('resultados_plato_por_alergia.html', mensaje=mensaje, alergia=alergia, resultados=[])
        
        return render_template('resultados_plato_por_alergia.html', resultados=resultados, alergia=alergia)
    except Exception as e:
        print(f"Error en la base de datos: {str(e)}")
        traceback.print_exc()
        return f"Error en la base de datos: {str(e)}"

if __name__ == '__main__':
    app.run(debug=True)
