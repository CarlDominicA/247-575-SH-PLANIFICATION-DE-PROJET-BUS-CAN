#ifndef DECIMAL_ID_H
#define DECIMAL_ID_H

/**
 * @file DecimalID.h
 * @brief Fichier d'entête pour la définition des identifiants décimaux utilisés dans les messages CAN.
 * 
 * Ce fichier contient les définitions des identifiants décimaux pour les différents capteurs et leurs données
 * correspondantes transmises via le bus CAN. Chaque identifiant est unique et est utilisé pour différencier
 * les types de données envoyées ou reçues dans le réseau CAN. Modifier cet en-tête pour ajouter ou modifier
 * les identifiants selon les besoins spécifiques du projet.
 * 
 * Les identifiants sont utilisés pour catégoriser les données envoyées, facilitant ainsi la gestion et le décodage
 * des trames CAN par les dispositifs récepteurs. Il est crucial de maintenir une cohérence dans les identifiants
 * utilisés pour éviter des conflits ou des erreurs de communication.
 */

// Définir l'ID décimal souhaité ici
#define DECIMAL_ID 528

// Liste des capteurs et leur ID correspondant
#define TEMP_SET_1_ID 528 // Temperature Set 1
#define TEMP_SET_2_ID 529 // Temperature Set 2
#define TEMP_SET_3_ID 530 // Temperature Set 3
#define ANALOG_VOLTAGE_ID 531 // Analog input Voltages
#define DIGITAL_INPUT_STATUS_ID 532 // Digital input status
#define MOTOR_POSITION_INFO_ID 533 // Motor position info
#define CURRENT_INFO_ID 534 // Current Info
#define VOLTAGE_INFO_ID 535 // Voltage info
#define FLUX_IQ_INFO_ID 536 // Flux ID IQ info
#define INTERNAL_VOLTAGES_ID 537 // Internal Voltages
#define INTERNAL_STATES_ID 538 // Internal states
#define FAULT_CODES_ID 539 // Fault Codes
#define TORQUE_TIMER_INFO_ID 540 // Torque and Timer info
#define MODULATION_FLUX_INFO_ID 541 // Modulation and Flux info
#define FIRMWARE_INFO_ID 542 // Firmware info
#define DIAG_DATA_ID 543 // Diag Data
#define FAST_INFO_ID 544 // Fast info
#define U2C_COMMAND_TXD_ID 545 // U2C Command Txd
#define U2C_COMMAND_RXD_ID 546 // U2C Command Rxd
#define COMMAND_MESSAGE_ID 547 // Command Message
#define READ_WRITE_PARAM_CMD_ID 548 // Read Write Param Command
#define READ_WRITE_PARAM_RSP_ID 549 // Read Write Param Response
#define U2C_MESSAGE_RXD_ID 550 // U2C_Message_Rxd
#define U2C_COMMAND_TXD2_ID 551 // U2C_Command_Txd
#define BMS_CURRENT_LIMIT_ID 552 // BMS Current Limit

#endif // DECIMAL_ID_H
