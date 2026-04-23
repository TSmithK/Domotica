#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// --- CONFIGURACIÓN WIFI ---
const char* ssid = "INFINITUM3904_2.4";
const char* password = "nJGG3UAGF9";

// --- CONFIGURACIÓN PANTALLA OLED  ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET    -1 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

WebServer server(80);

const int relayPins[] = {12, 14, 27, 26};
bool states[] = {HIGH, HIGH, HIGH, HIGH}; 

// --- FUNCIONES DE LA PANTALLA ---
void actualizarPantalla(String msg, String ip = "") {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("FIME DOMOTICA");
  display.println("---------------------");
  display.println(msg);
  if(ip != "") {
    display.setCursor(0,24);
    display.print("IP: ");
    display.println(ip);
  }
  display.display();
}

// --- LOGICA WEB  ---
void handleRoot() {
  String html = "<!DOCTYPE html><html><head>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'><meta charset='UTF-8'>";
  html += "<style>body{font-family:sans-serif;text-align:center;background-color:#121212;color:white;padding:20px;}.btn{display:block;width:100%;padding:20px;margin:10px 0;border-radius:15px;border:none;color:white;font-weight:bold;cursor:pointer;}.on{background-color:#2ecc71;}.off{background-color:#e74c3c;}</style>";
  html += "<script>function toggle(p){fetch('/toggle?pin='+p);}setInterval(()=>{fetch('/status').then(r=>r.json()).then(d=>{d.forEach((s,i)=>{let b=document.getElementById('btn'+i);b.className='btn '+(s?'off':'on');b.innerText='RELE '+(i+1)+': '+(s?'APAGADO':'ENCENDIDO');});});},1000);</script></head><body>";
  html += "<h1>CONTROL DOMOTICO</h1>";
  for(int i=0; i<4; i++) html += "<button id='btn"+String(i)+"' class='btn "+String(states[i]?"off":"on")+"' onclick='toggle("+String(i)+")'>RELE "+String(i+1)+"</button>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleStatus() {
  String json = "[";
  for(int i=0;i<4;i++) { json += String(states[i]); if(i<3) json+=","; }
  json += "]";
  server.send(200, "application/json", json);
}

void handleToggle() {
  if(server.hasArg("pin")){
    int i = server.arg("pin").toInt();
    if(i>=0 && i<4){ states[i]=!states[i]; digitalWrite(relayPins[i], states[i]); }
  }
  server.send(200, "text/plain", "ok");
}

void setup() {
  Serial.begin(115200);

  // Inicializar pantalla
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Error OLED");
  }
  actualizarPantalla("Conectando WiFi...");

  // Configurar pines
  for(int i=0; i<4; i++){ pinMode(relayPins[i], OUTPUT); digitalWrite(relayPins[i], HIGH); }

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }

  actualizarPantalla("SISTEMA ONLINE", WiFi.localIP().toString());
  
  server.on("/", handleRoot);
  server.on("/toggle", handleToggle);
  server.on("/status", handleStatus);
  server.begin();
}

void loop() {
  server.handleClient();
}