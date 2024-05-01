//  Brief: Ce code est conçu pour un microcontrôleur Esp32-C3 XIAO SEED, utilisant le langage C++ et les bibliothèques Wire pour la communication I2C et ESP32-TWAI-CAN pour la 
//  communication CAN. L'objectif principal est la lecture d'une valeur analogique à partir d'un convertisseur analogique-numérique (CAN) 
//  MCP3221 et l'envoi de cette valeur sur le bus CAN.

//  Auteur: Mamoune Benmensour & Carl-Dominic Aubin

//  Date: 24 Avril 2024

//  Matériel: Esp32-C3 XIAO SEED, MCP3221, TJA1050, Potentiometre


//  Pour complier hors extension Plateformio: 
//  - cd C:\Users\mmanz\Desktop\Projet_Module_CAN\Session_H24\Logiciel\Esp32Arduino
//  - platformio run --target upload
//  -platformio device monitor

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
//unsigned long dernierTemps = 0;    // Stocke le dernier temps enregistré
const byte adresseCAN = 0x4D;      // Adresse I2C du MCP3221 sur le bus
const double vRef = 5.0;           // Référence de tension pour le calcul de la tension réelle
const int activer_Affichage = 1;     // Contrôle l'affichage des informations sur le port série

// Prototypes de fonction
double lireMCP3221(int adresseMCP3221, int printInfo);
void trame_CAN(double volts);

// Configuration initiale
void setup() {
    pinMode(GPIO_NUM_2, OUTPUT);    //Met le GPIO en sortie
    digitalWrite(GPIO_NUM_2, HIGH); // Mettre la broche GPIO en état haut

    Wire.begin(GPIO_NUM_6, GPIO_NUM_7); // initialise le bus I2C SDA 6/ SCL 7
    Serial.begin(115200); // Démarrer la communication série à 115200 bauds
    //dernierTemps = millis(); // Enregistrer le temps actuel

    // Configuration du bus CAN
    ESP32Can.setPins(CAN_TX, CAN_RX); // Définit les broches pour le CAN GPIO 21/GPIO 20
    ESP32Can.setRxQueueSize(1);  // Taille de la file d'attente de réception
    ESP32Can.setTxQueueSize(1);  // Taille de la file d'attente de transmission
    ESP32Can.setSpeed(ESP32Can.convertSpeed(1000)); // Vitesse du bus CAN à 1000 kbps 

    // Démarrage du bus CAN
    if (ESP32Can.begin()) {
        Serial.println("Bus CAN démarré !"); 
    } else {
        Serial.println("Échec du démarrage du bus CAN !");
    }
}



/**
 * @brief Lit les données analogiques depuis le MCP3221 via I2C et convertit ces données en tension.
 * 
 * Cette fonction établit une communication I2C avec le MCP3221 à l'adresse spécifiée, lit deux octets représentant la mesure analogique,
 * calcule la valeur ADC correspondante, et la convertit en tension en volts et affiche les résultats sur le port série.
 * 
 * @param adresseMCP3221 L'adresse I2C du MCP3221.
 * @param printInfo Contrôle l'affichage des informations sur le port série (1 pour activer, 0 pour désactiver).
 * 
 * @return La valeur de tension en volts calculée à partir des données brutes lues.
 */

double lireMCP3221(int adresseMCP3221, int printInfo) {
    Wire.beginTransmission(adresseMCP3221);  // Commence la transmission I2C à l'adresse spécifiée.
    Wire.endTransmission();                  // Termine la transmission I2C.
    delayMicroseconds(150);                  // Attente courte pour stabiliser la communication I2C.

    Wire.requestFrom(adresseMCP3221, 2);     // Demande de lecture de 2 octets depuis le MCP3221.
    byte octetMSB = Wire.read();             // Lecture de l'octet de poids fort.
    byte octetLSB = Wire.read();             // Lecture de l'octet de poids faible.

    int valeurADC_12bits = ((octetMSB & 0x0F) << 8) | octetLSB;  // Combine les octets lus en une valeur ADC de 12 bits.
    double tensionVolts = valeurADC_12bits * vRef / 4095.0;       // Convertit la valeur ADC en tension en utilisant la référence de tension de l'ADC.

    if (printInfo) {
        double tension_mV = tensionVolts * 1000;           // Conversion de la tension en millivolts pour l'affichage.
        Serial.print("                   mam                   Valeur ADC (12 bits) = ");           // Affiche la valeur ADC sur le port série.
        Serial.print(valeurADC_12bits);
        Serial.println();
        Serial.print("Tension (mV) = ");                   // Affiche la tension en millivolts sur le port série.
        Serial.println(tension_mV);
    }
    
    return tensionVolts;  // Retourne la tension calculée en volts.
}


/**
 * @brief Envoie la valeur de tension mesurée sur le bus CAN.
 * 
 * Cette fonction prépare une trame CAN en convertissant la valeur de tension en volts en deux composants:
 * les volts entiers et les centièmes de volt. Elle place ces valeurs dans les deux premiers octets d'une trame CAN,
 * met les autres octets à zéro pour le padding, et envoie cette trame sur le bus CAN.
 * 
 * @param volts La tension mesurée en volts à envoyer sur le bus CAN.
 * 
 * @return void Cette fonction ne retourne rien.
 */

void trame_CAN(double volts) {
    CanFrame trame = { 0 };
    trame.identifier = DECIMAL_ID; // Utilise l'ID défini pour la trame CAN
    trame.extd = 0; // Indique que c'est une trame standard (non étendue)
    trame.data_length_code = 8; // Taille de données fixée à 8 octets
    
    // Convertir la tension en volts entiers et en centièmes de volts
    unsigned char canVolts = (int)volts; // Partie entière des volts
    unsigned char canCentiVolts = (int)((volts - canVolts) * 100); // Calcul des centièmes de volts

    trame.data[0] = canVolts; // Stocker les volts entiers dans le premier octet
    trame.data[1] = canCentiVolts; // Stocker les centièmes de volts dans le deuxième octet

    // Initialiser les octets restants à zéro
    for (int i = 2; i < 8; i++) {
        trame.data[i] = 0; // Mettre à zéro les autres octets
    }

    // Afficher les informations sur la trame CAN à envoyer
    Serial.print("                                      Envoi de trame CAN avec ID: ");
    Serial.println(trame.identifier);
    Serial.print("trame CAN: ");
    for (int i = 0; i < 8; i++) {
        Serial.print((int)trame.data[i]);  // Afficher chaque octet sous forme de nombre entier
        Serial.print(" ");
    }
    Serial.println();

    // Envoyer la trame sur le bus CAN
    ESP32Can.writeFrame(trame);
}


// Boucle principale du programme
void loop() {
    double LectureMCP3221 = lireMCP3221(adresseCAN, activer_Affichage);   // stocke La valeur de tension en volts dans la vairable LectureMCP,
                                                                          // prend en parametre l'adresse I2C du MCP3221

    trame_CAN(LectureMCP3221); // Envoyer cette valeur via CAN
    delay(20); // Attendre 50 ms
}
