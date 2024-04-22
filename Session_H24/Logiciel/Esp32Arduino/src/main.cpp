//  Brief: Ce code est conçu pour un microcontrôleur esp32-c3-devkitc-02, utilisant le langage ARDUINO et les bibliothèques Wire pour la communication I2C et ESP32-TWAI-CAN pour la 
//  communication CAN. L'objectif principal est la lecture d'une valeur analogique à partir d'un convertisseur analogique-numérique (CAN) 
//  MCP3221 et l'envoi de cette valeur sur le bus CAN.

//  Auteur: Mamoune Benmensour & Carl-Dominic Aubin

//  Date: 19 Avril 2024

//  Matériel: Esp32-C3 devkit-02, MCP3221, TJA1050, Potentiometre


#include "DecimalID.h"  // Inclure le fichier pour DECIMAL_ID
#include <Arduino.h>
#include <Wire.h> // pour communication I2C
#include "MCP3X21.h" //librairie pour MP3221
#include <ESP32-TWAI-CAN.hpp> //TWAI Esp32

#define CAN_TX GPIO_NUM_21
#define CAN_RX GPIO_NUM_20

CanFrame rxFrame;

unsigned long dernierTemps = 0;
const byte adresseCAN = 0x4D;
const double vRef = 5.0;
const int printInfosSerie = 1;

double lireMCP3221(int adresseMCP3221, int printInfo);
double convertDbyte_Double(byte msb, byte lsb);
int printINFO(byte msb, byte lsb);
void sendPotentiometerValue(double volts);
int getDecimalID(int hexID);

void setup() {
    pinMode(GPIO_NUM_2, OUTPUT);
    digitalWrite(GPIO_NUM_2, HIGH);

    Wire.begin(GPIO_NUM_6, GPIO_NUM_7);
    Serial.begin(115200);
    dernierTemps = millis();

    ESP32Can.setPins(CAN_TX, CAN_RX);
    ESP32Can.setRxQueueSize(1);
    ESP32Can.setTxQueueSize(1);
    ESP32Can.setSpeed(ESP32Can.convertSpeed(1000));

    if (ESP32Can.begin()) {
        Serial.println("Bus CAN démarré !");
    } else {
        Serial.println("Échec du démarrage du bus CAN !");
    }
}

double lireMCP3221(int adresseMCP3221, int printInfo) {
    Wire.beginTransmission(adresseMCP3221);
    Wire.endTransmission();
    delayMicroseconds(150);
    Wire.requestFrom(adresseMCP3221, 2);
    byte octetMSB = Wire.read();
    byte octetLSB = Wire.read();
    if (printInfo) {
        printINFO(octetMSB, octetLSB);
    }
    return convertDbyte_Double(octetMSB, octetLSB);
}

double convertDbyte_Double(byte msb, byte lsb) {
    int value = ((msb & 0x0F) << 8) | lsb;
    return (double)value * vRef / 4095.0;
}

int printINFO(byte msb, byte lsb) {
    int valeurADC = ((msb & 0x0F) << 8) | lsb;
    Serial.print("Valeur ADC (12 bits) = ");
    Serial.print(valeurADC);
    Serial.println();
    double tension_mV = convertDbyte_Double(msb, lsb) * 1000;
    Serial.print("Tension (mV) = ");
    Serial.println(tension_mV);
    return valeurADC;
}

void sendPotentiometerValue(double volts) {
    CanFrame potFrame = { 0 };
    potFrame.identifier = DECIMAL_ID;
    potFrame.extd = 0;
    potFrame.data_length_code = 8;
    
    unsigned char canVolts = (int)volts;
    unsigned char canCentiVolts = (int)((volts - canVolts) * 100);

    potFrame.data[0] = canVolts;
    potFrame.data[1] = canCentiVolts;

    for (int i = 2; i < 8; i++) {
        potFrame.data[i] = 0; // remplir les autres octets de données avec des zéros
    }

    Serial.print("Envoi de trame CAN avec ID: ");
    Serial.println(potFrame.identifier);
    Serial.print("Données: ");
    for (int i = 0; i < 8; i++) {
        Serial.print((int)potFrame.data[i]);  // Afficher chaque octet comme un nombre entier
        Serial.print(" ");
    }
    Serial.println();

    ESP32Can.writeFrame(potFrame);
}


void loop() {
    double valeurCanal = lireMCP3221(adresseCAN, printInfosSerie);
    sendPotentiometerValue(valeurCanal);
    delay(500);
}
