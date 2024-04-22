# Projet de Lecture de Tension avec MCP3221 et ESP32

## Description
Ce projet permet de lire une tension à partir d'un potentiomètre connecté à un convertisseur analogique-numérique MCP3221, et de transmettre cette valeur via un bus CAN en utilisant un microcontrôleur ESP32. Le but est de fournir une méthode simple et efficace pour surveiller des valeurs de tension et les communiquer sur un réseau CAN pour des applications telles que l'automatisation ou la surveillance de systèmes.

## Auteurs
- Mamoune Benmensour
- Carl-Dominic Aubin

## Date
22 Avril 2024

## Matériel Requis
- ESP32-C3 XIAO SEED
- MCP3221 (Convertisseur ADC I2C)
- Résistances et fils pour les connexions
- (Optionnel) Module transceiver CAN, comme le SN65HVD230

## Bibliothèques Nécessaires
- `Arduino.h` : Bibliothèque standard pour la programmation sur Arduino.
- `Wire.h` : Pour la communication I2C avec le MCP3221.
- `ESP32-TWAI-CAN.hpp` : Bibliothèque pour gérer la communication CAN sur l'ESP32.

## Installation
1. Installez l'IDE Arduino et configurez-le pour supporter l'ESP32.
2. Connectez l'ESP32 à votre ordinateur via USB.
3. Téléchargez ce projet et ouvrez-le avec l'IDE Arduino.
4. Installez toutes les bibliothèques requises via le Gestionnaire de bibliothèques dans l'IDE.
5. Téléversez le programme sur l'ESP32.

## Configuration des broches
- **CAN_TX** : Défini sur GPIO 21
- **CAN_RX** : Défini sur GPIO 20
- **I2C SDA** et **SCL** : GPIO 6 / GPIO 7

## Fonctionnement
Le code configure l'ESP32 pour lire des valeurs de tension via le MCP3221 à intervalles réguliers et pour envoyer ces valeurs via le bus CAN. Les valeurs de tension sont également affichées sur le port série pour le débogage et la vérification.

## Utilisation
Une fois le code téléversé et l'ESP32 démarré, vous pouvez observer les valeurs de tension via le moniteur série de l'IDE Arduino réglé à 115200 bauds. Les données CAN peuvent être capturées et analysées à l'aide d'un analyseur de bus CAN connecté au même réseau.

## Dépannage
- Assurez-vous que toutes les connexions sont bien établies et que les broches SDA et SCL sont correctement configurées.
- Vérifiez que le MCP3221 est alimenté et fonctionne dans les paramètres attendus pour la communication I2C.

## Licence
Ce projet est mis à disposition sous une licence libre pour une utilisation non commerciale. Pour toute utilisation commerciale ou modifications substantielles, veuillez contacter les auteurs.

