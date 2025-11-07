/********************************************************************
 * Projeto: PlantCare - Envio de Dados MQTT com ESP32
 * Placa: DOIT ESP32 DEVKIT V1
 * 
 * Descrição:
 * Este projeto conecta o ESP32 à rede Wi-Fi e a um Broker MQTT (Node-RED).
 * A cada 10 segundos, envia uma mensagem JSON com:
 * - ID do grupo
 * - ID do módulo (sensor)
 * - IP local
 * - Data e hora (via NTP)
 * - Temperatura (°C)
 * - Umidade do ar (%)
 * - Umidade do solo (simulada)
 ********************************************************************/
//----------------------------------------------------------
// Bibliotecas padrão ESP32
#include <WiFi.h>
#include <time.h>

//----------------------------------------------------------
// Bibliotecas externas

#include <PubSubClient.h>
#include <ArduinoJson.h>



#define boardLED 2 

const char* ID        = "PlantCare01";
const char* moduleID  = "Sensor_A1";

// Wi-Fi
const char* SSID      = "Wokwi-GUEST";
const char* PASSWORD  = "";

// MQTT Broker
const char* BROKER_MQTT  = "broker.hivemq.com";
const int   BROKER_PORT  = 1883;
const char* mqttUser     = "";
const char* mqttPassword = "";

#define TOPICO_PUBLISH  "plantcare/sensores"

//----------------------------------------------------------

WiFiClient espClient;
PubSubClient MQTT(espClient);
char buffer[300]; 

//----------------------------------------------------------

void setup() {
    Serial.begin(115200);
    pinMode(boardLED, OUTPUT);
    digitalWrite(boardLED, LOW);

    initWiFi();
    initNTP();
    initMQTT();
}

//----------------------------------------------------------

void loop() {
    verificaConexoesWiFiEMQTT();

    struct tm timeinfo;
    getLocalTime(&timeinfo);

    char data[11]; 
    char hora[9];  
    strftime(data, sizeof(data), "%Y-%m-%d", &timeinfo);
    strftime(hora, sizeof(hora), "%H:%M:%S", &timeinfo);

    float temperatura = random(200, 300) / 10.0; 
    float umidadeAr   = random(400, 800) / 10.0; 
    int umidadeSolo   = random(300, 800);        

    StaticJsonDocument<300> doc;

    doc["ID"]          = ID;
    doc["Modulo"]      = moduleID;
    doc["IP"]          = WiFi.localIP().toString();
    doc["Data"]        = data;
    doc["Hora"]        = hora;
    doc["Temperatura"] = temperatura;
    doc["UmidadeAr"]   = umidadeAr;
    doc["UmidadeSolo"] = umidadeSolo;

    serializeJson(doc, buffer);

    Serial.println(buffer);

    enviaEstadoOutputMQTT();

    piscaLed();

    delay(10000);
}

//----------------------------------------------------------
void initWiFi() {
    WiFi.begin(SSID, PASSWORD);
    Serial.print("Conectando ao Wi-Fi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nWi-Fi conectado!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
    Serial.print("MAC Address: ");
    Serial.println(WiFi.macAddress());
}

void reconectaWiFi() {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Reconectando Wi-Fi...");
        initWiFi();
    }
}

//----------------------------------------------------------

void initNTP() {
    configTime(-3 * 3600, 0, "pool.ntp.org", "time.nist.gov");
    struct tm timeinfo;
    while (!getLocalTime(&timeinfo)) {
        Serial.println("Aguardando sincronização NTP...");
        delay(1000);
    }
    Serial.println("Horário sincronizado via NTP.");
}

//----------------------------------------------------------

void initMQTT() {
    MQTT.setServer(BROKER_MQTT, BROKER_PORT);
    while (!MQTT.connected()) {
        Serial.println("Conectando ao Broker MQTT...");
        if (MQTT.connect(moduleID, mqttUser, mqttPassword)) {
            Serial.println("Conectado ao Broker!");
        } else {
            Serial.print("Falha na conexão. Estado: ");
            Serial.println(MQTT.state());
            delay(2000);
        }
    }
}

void verificaConexoesWiFiEMQTT() {
    reconectaWiFi();
    if (!MQTT.connected()) {
        initMQTT();
    }
    MQTT.loop();
}

//----------------------------------------------------------

void enviaEstadoOutputMQTT() {
    MQTT.publish(TOPICO_PUBLISH, buffer);
    Serial.println("Mensagem publicada com sucesso!");
}

void piscaLed() {
    digitalWrite(boardLED, HIGH);
    delay(300);
    digitalWrite(boardLED, LOW);
}
