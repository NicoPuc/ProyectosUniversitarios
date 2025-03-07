# T3_Sistemas_Operativos

T3 Sistemas operativos y redes IIC2333

## Preguntas

### 1.

**Pregunta:**  
¿Cuál es la dirección de destino del paquete cuando el paquete viene de vuelta y el último dispositivo visitado por este fue el switch dentro de la red FTP?

**Respuesta:**  
La direccion de destino del paquete es "172.100.15.119", el PC conectado a la red FTP. El pquete sale desde el PC haciendo todo el recorrido para llegar hasta el servidor. Luego el servidor manda el paquete de vuelta al PC pasando por los routers y por ultimo cuando llega al switch solamente le falta llegar al PC.

### 2.

**Pregunta:**  
¿Qué tipo de paquete es el primer paquete enviado?

**Respuesta:**  
El PC envia un paquete de tipo DNS en busqueda de la traduccion a IP para luego preguntar al servidor HTTP.

### 3.

**Pregunta:**  
Cuando el paquete anterior va de vuelta al computador, es decir, en el paquete de respuesta, ¿qué representan los últimos 2 bytes de esta respuesta?

**Respuesta:**  
No sabemos bien como se lee el paquete en si. Pero creemos segun ese diagrama que genera que 1 byte es para representar el largo de la respuesta, y el otro con la IP traducida.

### 4.

**Pregunta:**  
¿Qué tipo de paquete es este? ¿Cuál es la dirección IP de origen del paquete, una vez pasado el home router?

**Respuesta:**  
De tipo HTTP. La direccion de origen el el Ip del home router en este caso "150.100.10.2", depende del home router al cual este conectado el dispositivo del cual se hacen las solicitudes.

---

### 5.

**Pregunta:**  
Describa, de manera detallada, todo el proceso de conexión, desde que se ingresa el comando hasta que se acepta la conexión. La descripción debe contener qué paquetes fueron enviados y recibidos, la utilidad u objetivo de estos paquetes y la información que contienen.

**Respuesta:**  
Primero ingresamos en la terminal del PC conectado a la red FTP, "ftp 172.100.15.66" buscando conectarnos con el servidor.
Se envian 3 paquetes de tipo TCP, buscando hacer el handshake triple. EL primero enviado por el cliente con la informacion del puerto del cliente y el destino en este caso el servidor FTP.
Responde el servidor con un numero para establecer la conexion y "acusa recibo" del primer paquete. El cliente cuando recibe envia el ultimo paquete diciendo que se logro conectar.

### 6.

**Pregunta:**  
Describa en detalle el proceso de enviar y recibir un correo electrónico. Recuerde mencionar todos los paquetes involucrados y la información que considere relevante en el proceso.

**Respuesta:**

## Autores

- Nicolas Hormann
- Vicente Cuitiño
