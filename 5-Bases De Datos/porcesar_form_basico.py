from flask import Flask, request, render_template
import psycopg2

app = Flask(__name__)


@app.route('/')
def index():
    return render_template('form_basico.html')


@app.route('/procesar', methods=['POST'])
def procesar():
    atributoA = request.form['atributoA']
    atributoB = request.form['atributoB']
    atributoC = request.form['atributoC']

    # Establece la conexión con la base de datos
    try:
        conn = psycopg2.connect(
            database="grupo65",
            user="grupo65",
            host="pavlov.ing.puc.cl",
            port="5432",
            password="lostres"
        )
        cur = conn.cursor()
        # Suponiendo que quieres hacer una consulta de selección
        consulta_sql = f"SELECT {atributoA} FROM {atributoB} WHERE {atributoC}"
        cur.execute(consulta_sql)
        resultados = cur.fetchall()
        cur.close()
        conn.close()
        return f"Resultados: {resultados}"
    except Exception as e:
        return f"Error en la base de datos: {str(e)}"


if __name__ == "__main__":
    app.run(debug=True)
