#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
// #include <ESP8266mDNS.h>

const char* ssid = "WiFi Apaya"; //Nama SSID AP/Hotspot
const char* password = "123123123"; //Password Wifi

ESP8266WebServer server(80); //Menyatakan Webserver pada port 80
const int buzzerPin = D9;  // Digital pin connected to the lamp
const int ledPin = D8;  // Digital pin connected to the lamp


void setup() {
  delay(1000);
  Serial.begin(9600);
  delay(10);

  // Connect ke WiFi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Mengatur WiFi 
  WiFi.mode(WIFI_STA); // Mode Station
  WiFi.begin(ssid, password); // Mencocokan SSID dan Password
    
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    Serial.print("Sedang menyambungkan ke WiFi");
  }

  // Tampilkan status Connected
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Set the hostname to "localhost"
  // WiFi.hostname("localhost");

  // MDNS.begin("localhost");


  // Membuat tampilan Web
  server.on("/", []() {
    server.send(200, "text/plain", "Hello Para Warrior IoT");
  });

  // Bagian ini untuk membuat halaman web lain
  server.on("/status", []() {
    server.send(200, "text/plain", "Ini adalah Page Status Aktif");
  });

   // Set the lamp pin as an OUTPUT
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  // Turn the lamp on
  server.on("/on", HTTP_GET, [](){
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(ledPin, HIGH);
    Serial.println("Nyala");

    server.send(200, "text/plain", "Lamp turned ON");
  });

  // Turn the lamp off
  server.on("/off", HTTP_GET, [](){    
    digitalWrite(buzzerPin, LOW);
    digitalWrite(ledPin, LOW);
    Serial.println("mati");

    server.send(200, "text/plain", "Lamp turned OFF");
  });

  // MDNS.addService("http", "tcp", 80);

  server.begin();
  Serial.println("Webserver dijalankan");
}

void loop() {
  server.handleClient();
}