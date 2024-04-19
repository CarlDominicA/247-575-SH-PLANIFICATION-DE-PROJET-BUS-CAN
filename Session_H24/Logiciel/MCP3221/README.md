# Projet de Lecture Analogique avec MCP3221 et ESP32-C3

## Description
Ce projet utilise un microcontrôleur ESP32-C3-DEVKITC-02 pour lire des valeurs analogiques à partir d'un convertisseur analogique-numérique (CAN), le MCP3221. Le code est écrit en Arduino et utilise la bibliothèque `Wire` pour la communication I2C. L'objectif principal est de mesurer et afficher la valeur analogique convertie à partir d'un potentiomètre connecté au MCP3221.

## Auteurs
- Mamoune Benmensour
- Carl-Dominic Aubin

## Date
19 Avril 2024

## Matériel Requis
- ESP32-C3 DEVKIT-02
- MCP3221
- TJA1050 (transceiver CAN)
- Potentiomètre

## Bibliothèques Nécessaires
- `Arduino.h` : Bibliothèque de base pour la programmation Arduino.
- `Wire.h` : Pour la communication I2C avec le MCP3221.
- `MCP3X21.h` : Bibliothèque spécifique pour interagir avec le MCP3221.

## Installation
1. Assurez-vous que l'IDE Arduino est installé sur votre ordinateur.
2. Connectez votre ESP32-C3 à l'ordinateur via USB.
3. Ouvrez ce script dans l'IDE Arduino.
4. Installez les bibliothèques nécessaires via le Gestionnaire de bibliothèques de l'IDE Arduino.
5. Téléchargez le code sur le microcontrôleur.

## Configuration des broches
- **SDA** : GPIO 8
- **SCL** : GPIO 9
- Les broches pour la communication I2C doivent être correctement connectées entre l'ESP32 et le MCP3221.

## Fonctionnement
Le programme lit la tension analogique à travers le MCP3221, convertit cette valeur en données numériques, et affiche la valeur ADC et la tension correspondante en millivolts sur le port série. Il est configuré pour prendre une mesure toutes les secondes.

## Utilisation
Après avoir chargé le code sur l'ESP32, ouvrez le moniteur série de l'IDE Arduino réglé à 115200 bauds pour voir les résultats des mesures.

## Dépannage
- Vérifiez que toutes les connexions sont correctement établies si aucune donnée n'apparaît sur le moniteur série.
- Assurez-vous que le MCP3221 est alimenté et correctement configuré pour la communication I2C.

## Licence
Ce projet est libre d'utilisation et de modification pour des applications éducatives ou personnelles. Pour toute utilisation commerciale, veuillez contacter les auteurs.

