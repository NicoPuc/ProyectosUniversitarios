import sys
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *
import random

class Ruleta(QWidget):
    def __init__(self, lista_juegos):
        super().__init__()
        self.lista_juegos = lista_juegos
        self.setWindowTitle("Ruleta")
        self.setGeometry(200, 200, 400, 400)
        self.layout = QVBoxLayout()
        self.ruleta = QLabel()
        self.ruleta.setPixmap(QPixmap("ruleta.png")) # Aquí debes agregar la ruta a la imagen de la ruleta
        self.ruleta.setAlignment(Qt.AlignCenter)
        self.layout.addWidget(self.ruleta)
        self.boton = QPushButton("Jugar")
        self.boton.clicked.connect(self.jugar)
        self.layout.addWidget(self.boton)
        self.resultado = QLabel()
        self.resultado.setAlignment(Qt.AlignCenter)
        self.layout.addWidget(self.resultado)
        self.setLayout(self.layout)

    def jugar(self):
        juego = random.choice(self.lista_juegos)
        self.resultado.setText(f"¡Ganaste {juego}!")

if __name__ == '__main__':
    app = QApplication(sys.argv)
    lista_juegos = ["juego1", "juego2", "juego3", "juego4", "juego5", "juego6"]
    ventana = Ruleta(lista_juegos)
    ventana.show()
    sys.exit(app.exec_())
