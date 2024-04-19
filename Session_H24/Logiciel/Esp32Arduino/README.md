# Projet de communication CAN avec ESP32 et MCP3221

## Description
Ce projet utilise un microcontrôleur ESP32-C3 XIAO SEED pour lire une valeur analogique d'un convertisseur analogique-numérique (CAN), le MCP3221, et envoyer cette valeur sur un bus CAN. Il implémente le langage Arduino et utilise les bibliothèques `Wire` pour la communication I2C et `ESP32-TWAI-CAN` pour la communication CAN.

## Auteurs
- Mamoune Benmensour
- Carl-Dominic Aubin

## Date
13 Mars 2024

## Matériel Requis
- ESP32-C3 XIAO SEED
- MCP3221
- TJA1050 (transceiver CAN)
- Potentiomètre

## Bibliothèques Nécessaires
- `Arduino.h`
- `Wire.h` (pour la communication I2C)
- `MCP3X21.h` (pour le MCP3221)
- `ESP32-TWAI-CAN.hpp` (pour la communication CAN)

## Configuration des broches
- `CAN_TX` sur GPIO_NUM_21
- `CAN_RX` sur GPIO_NUM_20
- SDA sur GPIO_NUM_6
- SCL sur GPIO_NUM_7

## Fonctionnalités Principales
- **Lecture du CAN** : Lit les valeurs analogiques via I2C du MCP3221.
- **Conversion et affichage** : Convertit les données brutes en tension et affiche les résultats sur le port série.
- **Envoi sur le bus CAN** : Envoie les valeurs lues via le bus CAN.

## Utilisation
1. Assurez-vous que toutes les connexions matérielles sont correctement établies.
2. Téléchargez et installez toutes les bibliothèques nécessaires via le gestionnaire de bibliothèques de l'IDE Arduino.
3. Chargez ce script dans votre ESP32.
4. Ouvrez le moniteur série pour visualiser les sorties.

## Dépannage
Si vous rencontrez des problèmes lors de l'initialisation du bus CAN, assurez-vous que les connexions du transceiver CAN sont correctes et que le transceiver est bien alimenté.

## Licence
Ce projet est libre d'utilisation et peut être modifié. Toutefois, il reste sous la responsabilité de l'utilisateur de vérifier la compatibilité et la sécurité de l'utilisation dans des environnements spécifiques.
