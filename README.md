Servidor Web de Control Domótico (ESP32)
Descripción del Proyecto
Este proyecto consiste en un nodo de automatización IoT basado en el microcontrolador ESP32, diseñado para gestionar de forma remota 4 cargas eléctricas a través de un módulo de relevadores. El sistema despliega un servidor web con una interfaz dinámica y asíncrona, permitiendo el control global mediante un túnel seguro con Ngrok y monitoreo local a través de una pantalla OLED.

Requisitos e Instalación
Hardware: ESP32 DevKit V1, Módulo Relé 4CH, Pantalla OLED SSD1306 e interfaz I2C.
Software: Arduino IDE con el paquete de tarjetas ESP32 instalado.
Librerías: Instalar desde el gestor de bibliotecas: Adafruit SSD1306 y Adafruit GFX.
En "Gestor de URLs Adicionales de Tarjetas", pegue: https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json y vaya a Herramientas > Placa > Gestor de tarjetas, busque "esp32" e instale la versión de Espressif Systems.
Configuración: Clonar el repositorio y editar las variables ssid y password en el código fuente antes de cargar al microcontrolador.

Cómo usarlo (Comandos y Endpoints)
Acceso Local: Ingresar la IP mostrada en la pantalla OLED en cualquier navegador dentro de la misma red Wi-Fi.
Acceso Remoto: Ejecutar en terminal ngrok http http://[IP_DEL_ESP32]:80 y usar la URL pública generada.

API Endpoints:
GET /: Carga la interfaz de control.
GET /status: Obtiene el estado actual de los pines en formato JSON.
GET /toggle?pin=X: Conmuta el estado del relevador en el pin especificado.

Guía de carpetas
 Proyecto-Domotica-FIME
 ┣ 📂 src
 ┃ ┗ 📜 CodigoDomotica.ino    # Código fuente principal
 ┣ 📂 docs
 ┃ ┗ 📜 Practica 6.pdf      
 ┃ ┗ 📜 Practica 7.pdf      
 ┃ ┗ 📜 Practica 8.pdf     
  ┣ 📂 diagramas
  ┃ ┗ 📜 Diagrama de bloques.png      
  ┃ ┗ 📜 Diagrama Pictorico.png      
  ┃ ┗ 📜 Diagrama Esquematico.png
  ┃ ┗ 📜 Listado de componentes.pdf    
 ┃  📜 Documentación      # Este archivo con la documentación completa
  ┗ 📜 README.md              # Documentación técnica para primera ejecución

Resumen Técnico
El proyecto se fundamenta en el microcontrolador ESP32 DevKit V1, el cual opera con un procesador Dual-Core de 240 MHz y conectividad Wi-Fi integrada bajo el estándar IEEE 802.11 b/g/n. Internamente, el sistema levanta un servidor web asíncrono en el puerto 80 que procesa peticiones HTTP y transmite estados en formato JSON para optimizar el consumo de memoria y ancho de banda. La interfaz visual se gestiona mediante el bus de comunicación I2C a 400 kHz, que alimenta una pantalla OLED SSD1306. Finalmente, la exposición a redes globales se logra mediante un túnel seguro de Ngrok con cifrado TLS/SSL, permitiendo una comunicación cifrada y estable entre el cliente externo y el servidor local.

FAQ (Preguntas Frecuentes)
•	¿Qué hago si la pantalla OLED se queda en negro? Verifique que los cables SDA y SCL no estén invertidos y que la dirección I2C en el código coincida con el hardware (usualmente 0x3C).
•	¿Puedo usar el proyecto sin internet? Sí, el control vía IP local siempre estará activo siempre y cuando los 2 dispositivos estén conectados a la misma red (local, aunque no tengas internet).
•	¿Por qué el módulo de relés debe estar desconectado durante el arranque (boot)? Para no tener caídas de voltaje que puedan hacer que el esp falle.
