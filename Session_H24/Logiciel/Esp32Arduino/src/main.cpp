//  Brief: Ce code est conçu pour un microcontrôleur esp32-c3-devkitc-02, utilisant le langage ARDUINO et les bibliothèques Wire pour la communication I2C et ESP32-TWAI-CAN pour la 
//  communication CAN. L'objectif principal est la lecture d'une valeur analogique à partir d'un convertisseur analogique-numérique (CAN) 
//  MCP3221 et l'envoi de cette valeur sur le bus CAN.
//  Auteur: Mamoune Benmensour & Carl-Dominic Aubin
//  Date: 13 Mars 2024
//  Matériel: Esp32-C3 devkit-02, MCP3221, TJA1050, Potentiometre

//esp32-c3-devkitc-02


//Les Includes
#include <Arduino.h>
#include <Wire.h> // pour communication I2C
#include "MCP3X21.h" //librairie pour MP3221
#include <ESP32-TWAI-CAN.hpp> //TWAI Esp32


//broches TX RX pour la communication CAN
//#define CAN_TX GPIO_NUM_1 
//#define CAN_RX GPIO_NUM_6
#define CAN_TX GPIO_NUM_21
#define CAN_RX GPIO_NUM_20

CanFrame rxFrame;

//Constantes et variables globales
unsigned long dernierTemps = 0;
const byte adresseCAN = 0x4D; // Adresse du MCP3221A5T-E/OT 
const double vRef = 5.0;       // valeur de la référence de tension interne en Volts
const int printInfosSerie = 1;      // 1 pour imprimer les informations sur le port série, 0 pour ne pas afficher

//delcaration des fonctions
double lireMCP3221(int adresseMCP3221, int printInfo);
double convertDbyte_Double(byte msb, byte lsb);
int printINFO(byte msb, byte lsb);
void sendPotentiometerValue(int potValue, int valeurADC, int decimalID);
int getDecimalID(int hexID);

void setup() {

    /*pinMode(GPIO_NUM_2, OUTPUT); // Définir la broche GPIO comme sortie
    digitalWrite(GPIO_NUM_2, LOW); // Mettre la broche GPIO en niveau haut */

    Wire.begin(GPIO_NUM_6, GPIO_NUM_7);
  //Wire.begin(GPIO_NUM_8, GPIO_NUM_9); // Configure les broches SDA = 8 et SCL = 9 // Initialisation de la communication I2C
  Serial.begin(115200); // initialisation du port série
  dernierTemps = millis(); // initialisation du temps

    ESP32Can.setPins(CAN_TX, CAN_RX); // Initialisation de la communication CAN
    ESP32Can.setRxQueueSize(1); //5
    ESP32Can.setTxQueueSize(1); //5
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

 // i2cRead();

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

  return valeurADC;
}

int valeurADC_12(byte msb, byte lsb) {
    int valeur_ADC = ((msb & 0x0F) << 8) | lsb; // Conversion de l'octet MSB et de l'octet LSB en une valeur ADC sur 12 bits
    return valeur_ADC;
}



void sendPotentiometerValue(int potValue, int valeurADC, int decimalID) {
    // Configurer le message CAN
    CanFrame potFrame = { 0 };
    potFrame.identifier = decimalID; // Utiliser l'ID décimal correspondant
    potFrame.extd = 0; // 0 pour une trame standard (11 bits) et 1 pour une trame étendue (29 bits)
    potFrame.data_length_code = 8;
    //potFrame.rtr = 0;
    
    // Remplir le reste des octets de données avec des zéros
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
    //ESP32Can.readFrame(potFrame)
}

// Retourne le ID (en décimal) correspondant pour chaque type de capteurs
int getDecimalID(int hexID) {
    int decimalID = -1; // Initialiser à -1 pour gérer les ID non répertoriés

    switch (hexID) {
        case 0xA0:
            decimalID = 528; //Temperature Set 1
            break;
        case 0xA1:
            decimalID = 529; //Temperature Set 2
            break;
        case 0xA2:
            decimalID = 530; //Temperature Set 3
            break;
        case 0xA3:
            decimalID = 531; //Analog input Voltages
            break;
        case 0xA4:
            decimalID = 532; //Digital input status
            break;
        case 0xA5:
            decimalID = 533; //Motor position info
            break;
        case 0xA6:
            decimalID = 534; //Current Info
            break;
        case 0xA7:
            decimalID = 535;  //Voltage info
            break;
        case 0xA8:
            decimalID = 536; //Flux ID IQ info
            break;
        case 0xA9:
            decimalID = 537;  //Internal Voltages
            break;
        case 0xAA:
            decimalID = 538;  //Internal states
            break;
        case 0xAB:
            decimalID = 539;  //Fault Codes
            break;
        case 0xAC:
            decimalID = 540;  //Torque and Timer info
            break;
        case 0xAD:
            decimalID = 541; //Modulation and Flux info
            break;
        case 0xAE:
            decimalID = 542;  //Firmware info
            break;
        case 0xAF:
            decimalID = 543; //Diag Data
            break;
        case 0xB0:
            decimalID = 544; //Fast info
            break;
        case 0xBB:
            decimalID = 545; //U2C Command Txd
            break;
        case 0xBC:
            decimalID = 546; //U2C Command Rxd
            break;
        case 0xC0:
            decimalID = 547; //Command Message
            break;
        case 0xC1:
            decimalID = 548; //Read Write Param Command
            break;
        case 0xC2:
            decimalID = 549; //Read Write Param Response
            break;
        case 0x1D5:
            decimalID = 550;  //U2C_Message_Rxd
            break;
        case 0x1D7:
            decimalID = 551;  //U2C_Command_Txd
            break;
        case 0x202:
            decimalID = 552; //BMS Current Limit
            break;
    }

    return decimalID;
}


void loop() {
    // Mesurer et afficher les valeurs des canaux
    double valeurCanal = lireMCP3221(adresseCAN, printInfosSerie);
    //int intValue = static_cast<int>(valeurCanal); // Convertir en entier

    // Récupérer les valeurs MSB et LSB en appelant lireMCP3221
    byte msb, lsb;
    Wire.beginTransmission(adresseCAN);
    Wire.endTransmission();
    delayMicroseconds(150);
    Wire.requestFrom(adresseCAN, 2);
    msb = Wire.read();
    lsb = Wire.read();

    // Appel de la fonction valeurADC_12 avec les octets MSB et LSB
    int v = valeurADC_12(msb, lsb);
    int value = printINFO(msb, lsb);

    int hexID = 0x202; // ID hexadécimal pour BMS Current Limit
    int decimalID = getDecimalID(hexID); // Obtenir l'ID décimal correspondant

    delay(50); // 1 seconde avant la prochaine mesure
    
    
    sendPotentiometerValue(value, v, decimalID);  // Envoyer la valeur via CAN avec l'ID correspondant

}
