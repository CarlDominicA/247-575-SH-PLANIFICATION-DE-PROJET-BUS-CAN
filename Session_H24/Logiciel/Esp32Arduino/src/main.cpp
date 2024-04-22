//  Brief: Ce code est conçu pour un microcontrôleur esp32-c3-devkitc-02, utilisant le langage ARDUINO et les bibliothèques Wire pour la communication I2C et ESP32-TWAI-CAN pour la 
//  communication CAN. L'objectif principal est la lecture d'une valeur analogique à partir d'un convertisseur analogique-numérique (CAN) 
//  MCP3221 et l'envoi de cette valeur sur le bus CAN.

//  Auteur: Mamoune Benmensour & Carl-Dominic Aubin

//  Date: 22 Avril 2024

//  Matériel: Esp32-C3 devkit-02, MCP3221, TJA1050, Potentiometre


// Inclusion des bibliothèques nécessaires
#include "DecimalID.h"  // Fichier pour l'identification décimale dans les messages CAN
#include <Arduino.h>    // Bibliothèque principale pour Arduino
#include <Wire.h>       // Bibliothèque pour la communication I2C
#include "MCP3X21.h"    // Bibliothèque pour le capteur ADC MCP3221
#include <ESP32-TWAI-CAN.hpp> // Bibliothèque pour utiliser le protocole CAN avec un ESP32

// Définition des broches pour la transmission CAN
#define CAN_TX GPIO_NUM_21
#define CAN_RX GPIO_NUM_20

// Variables globales
unsigned long dernierTemps = 0;    // Stocke le dernier temps enregistré
const byte adresseCAN = 0x4D;      // Adresse I2C du MCP3221 sur le bus
const double vRef = 5.0;           // Référence de tension pour le calcul de la tension réelle
const int printInfosSerie = 1;     // Contrôle l'affichage des informations sur le port série

// Prototypes de fonction
double lireMCP3221(int adresseMCP3221, int printInfo);
double convertDbyte_Double(byte msb, byte lsb);
int printINFO(byte msb, byte lsb);
void sendPotentiometerValue(double volts);
int getDecimalID(int hexID);

// Configuration initiale
void setup() {
    pinMode(GPIO_NUM_2, OUTPUT);
    digitalWrite(GPIO_NUM_2, HIGH); // Mettre la broche GPIO en état haut

    Wire.begin(GPIO_NUM_6, GPIO_NUM_7); // Initialiser le bus I2C
    Serial.begin(115200); // Démarrer la communication série à 115200 bauds
    dernierTemps = millis(); // Enregistrer le temps actuel

    // Configuration du bus CAN
    ESP32Can.setPins(CAN_TX, CAN_RX); // Définir les broches pour le CAN
    ESP32Can.setRxQueueSize(1); // Taille de la file d'attente de réception
    ESP32Can.setTxQueueSize(1); // Taille de la file d'attente de transmission
    ESP32Can.setSpeed(ESP32Can.convertSpeed(1000)); // Vitesse du bus CAN à 1000 kbps

    // Démarrage du bus CAN
    if (ESP32Can.begin()) {
        Serial.println("Bus CAN démarré !");
    } else {
        Serial.println("Échec du démarrage du bus CAN !");
    }
}

// Lecture des données depuis le MCP3221
double lireMCP3221(int adresseMCP3221, int printInfo) {
    Wire.beginTransmission(adresseMCP3221);
    Wire.endTransmission();
    delayMicroseconds(150); // Petit délai pour la stabilité
    Wire.requestFrom(adresseMCP3221, 2); // Demander 2 octets depuis le MCP3221
    byte octetMSB = Wire.read(); // Lire l'octet de poids fort
    byte octetLSB = Wire.read(); // Lire l'octet de poids faible
    if (printInfo) {
        printINFO(octetMSB, octetLSB);
    }
    return convertDbyte_Double(octetMSB, octetLSB);
}

// Convertir les octets lus en une valeur de tension double
double convertDbyte_Double(byte msb, byte lsb) {
    int value = ((msb & 0x0F) << 8) | lsb; // Combinaison des deux octets en une valeur sur 12 bits
    return (double)value * vRef / 4095.0; // Convertir en tension en utilisant la référence et la résolution
}

// Afficher les informations de diagnostic sur la valeur ADC et la tension calculée
int printINFO(byte msb, byte lsb) {
    int valeurADC = ((msb & 0x0F) << 8) | lsb; // Calculer la valeur ADC
    Serial.print("Valeur ADC (12 bits) = ");
    Serial.print(valeurADC);
    Serial.println();
    double tension_mV = convertDbyte_Double(msb, lsb) * 1000; // Convertir en millivolts
    Serial.print("Tension (mV) = ");
    Serial.println(tension_mV);
    return valeurADC;
}

// Envoyer la valeur de tension mesurée sur le bus CAN
void sendPotentiometerValue(double volts) {
    CanFrame potFrame = { 0 };
    potFrame.identifier = DECIMAL_ID;
    potFrame.extd = 0;
    potFrame.data_length_code = 8;
    
    unsigned char canVolts = (int)volts;
    unsigned char canCentiVolts = (int)((volts - canVolts) * 100);

    potFrame.data[0] = canVolts;
    potFrame.data[1] = canCentiVolts;

    // Mettre à zéro les autres octets
    for (int i = 2; i < 8; i++) {
        potFrame.data[i] = 0;
    }

    Serial.print("Envoi de trame CAN avec ID: ");
    Serial.println(potFrame.identifier);
    Serial.print("Données: ");
    for (int i = 0; i < 8; i++) {
        Serial.print((int)potFrame.data[i]);
        Serial.print(" ");
    }
    Serial.println();

    ESP32Can.writeFrame(potFrame);
}

// Boucle principale du programme
void loop() {
    double valeurCanal = lireMCP3221(adresseCAN, printInfosSerie); // Lire la valeur du canal ADC
    sendPotentiometerValue(valeurCanal); // Envoyer cette valeur via CAN
    delay(500); // Attendre un demi-seconde
}
