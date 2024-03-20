//  Brief: Ce code est conçu pour un microcontrôleur esp32-c3-devkitc-02, utilisant le langage ARDUINO et les bibliothèques Wire pour la communication I2C et ESP32-TWAI-CAN pour la 
//  communication CAN. L'objectif principal est la lecture d'une valeur analogique à partir d'un convertisseur analogique-numérique (CAN) 
//  MCP3221 et l'envoi de cette valeur sur le bus CAN.

//  Auteur: Mamoune Benmensour & Carl-Dominic Aubin

//  Date: 13 Mars 2024

//  Matériel: Esp32-C3 devkit-02, MCP3221, TJA1050, Potentiometre

//Les Includes
#include <Arduino.h>
#include <Wire.h> // pour communication I2C
#include "MCP3X21.h" //librairie pour MP3221
#include <ESP32-TWAI-CAN.hpp> //TWAI Esp32

//broches TX RX pour la communication CAN
#define CAN_TX 1 
#define CAN_RX 6

//Constantes et variables globales
unsigned long dernierTemps = 0;
const byte adresseCAN = 0x4D; // Adresse du MCP3221A5T-E/OT 
const double vRef = 5.0;       // valeur de la référence de tension interne en Volts
const int printInfosSerie = 1;      // 1 pour imprimer les informations sur le port série, 0 pour ne pas afficher

//delcaration des fonctions
double lireMCP3221(int adresseMCP3221, int printInfo);
double convertDbyte_Double(byte msb, byte lsb);
int printINFO(byte msb, byte lsb);
void sendPotentiometerValue(int potValue, int valeurADC);

void setup() {
  Wire.begin(8, 9); // Configure les broches SDA = 8 et SCL = 9 // Initialisation de la communication I2C
  Serial.begin(115200); // initialisation du port série
  dernierTemps = millis(); // initialisation du temps

    ESP32Can.setPins(CAN_TX, CAN_RX); // Initialisation de la communication CAN
    ESP32Can.setRxQueueSize(5);
    ESP32Can.setTxQueueSize(5);
    ESP32Can.setSpeed(ESP32Can.convertSpeed(500));

    if (ESP32Can.begin()) {
        Serial.println("Bus CAN démarré !");
    } else {
        Serial.println("Échec du démarrage du bus CAN !");
    }
}



// Cette fonction communique avec le MCP3221 via le protocole I2C pour lire deux octets de données (MSB et LSB),
// les convertit en une valeur de tension et les retourne en double. Elle prend en compte un paramètre pour décider d'imprimer les informations ou non.
double lireMCP3221(int adresseMCP3221, int printInfo) {
  Wire.beginTransmission(adresseMCP3221);
  Wire.endTransmission();

  delayMicroseconds(150); // Pause avant de lire les données du MCP3221

  Wire.requestFrom(adresseMCP3221, 2); // Lecture de 2 octets de données
  byte octetMSB = Wire.read();          // Octet MSB, premier octet de données
  byte octetLSB = Wire.read();          // Octet LSB, deuxième octet de données

  if (printInfo) {
    printINFO(octetMSB, octetLSB);
  }

  return convertDbyte_Double(octetMSB, octetLSB);
}



//Convertit deux octets en une valeur double en tenant compte de la référence de tension et de la résolution ADC.
double convertDbyte_Double(byte msb, byte lsb) {
  int value = ((msb & 0x0F) << 8) | lsb; // Combinaison de l'octet MSB et de l'octet LSB en une valeur entière sur 12 bits.

  double v = (double)value * vRef / 4096.0; // Conversion de la valeur entière en tension en volts en utilisant la référence de tension et la résolution ADC.

  return v; // Retourne la valeur convertie en volts.
}


// Imprime les informations sur la valeur ADC et la tension correspondante en mV.
int printINFO(byte msb, byte lsb) {
  Serial.print("Valeur ADC (12 bits) = ");

  int valeurADC = ((msb & 0x0F) << 8) | lsb; // Conversion de l'octet MSB et de l'octet LSB en une valeur ADC sur 12 bits
  Serial.print(valeurADC);
  Serial.println();

  double tension_mV = convertDbyte_Double(msb, lsb) * 1000; // Conversion de la tension en mV
  Serial.print("Tension (mV) = ");
  Serial.println(tension_mV);
}


// Prépare et envoie la valeur du potentiomètre via le bus CAN en créant un message CAN avec l'ID approprié et les données correspondantes.
void sendPotentiometerValue(int potValue) {
    char bufferPotValue[5]; // Buffer for converting int to string with fixed length
    snprintf(bufferPotValue, sizeof(bufferPotValue), "%04d", potValue); // Convert int to string

    // Configure CAN message
    CanFrame potFrame = { 0 };
    potFrame.identifier = 0xB; // ID du message CAN
    potFrame.extd = 0;
    potFrame.data_length_code = 8;

    // Copy each character from the string into the CAN message data bytes
    for (int i = 0; i < 4; i++) {
        potFrame.data[i] = '0';
    }

    // Convertir les entiers en caractères ASCII
    char digit1 = '0' + (potValue / 1000) % 10;  // Milliers
    char digit2 = '0' + (potValue / 100) % 10; // Centaines
    char digit3 = '0' + (potValue / 10) % 10; // Dizaines
    char digit4 = '0' + potValue % 10; // Unités

    // Assigner chaque caractère à l'octet de données correspondant dans potFrame
    potFrame.data[4] = digit1;
    potFrame.data[5] = digit2;
    potFrame.data[6] = digit3;
    potFrame.data[7] = digit4;

    // Afficher les informations sur le message CAN avant l'envoi
    Serial.print("Envoi de trame CAN avec ID: ");
    Serial.println(potFrame.identifier);

    Serial.print("Données: ");
    for (int i = 0; i < 8; i++) {
        Serial.print((char)potFrame.data[i]); // Afficher chaque octet comme un caractère
        Serial.print(" ");
    }
    Serial.println();
    Serial.print("valeur du potentiomètre ");
    Serial.println(potValue);

    // Envoyer le message CAN
    ESP32Can.writeFrame(potFrame);
}

void loop() {
  double valeurCanal = lireMCP3221(adresseCAN, printInfosSerie); // mesurer et afficher les valeurs des canaux
  int intValue = static_cast<int>(valeurCanal); // Convert to int
  delay(1000); //1 seconde avant la prochaine mesure
  sendPotentiometerValue(intValue); // Send the value via CAN
}