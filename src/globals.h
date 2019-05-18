
// Global definitions

#ifndef GLOBALS_H

#define GLOBALS_H

// Slots for RAW data recording
#define SLOTS_NUMBER 20 // Number of slots
#define SLOT_SIZE 300   // Size of single slot
#define SEQ_SIZE 10     // Raw sequnece size

#define DEBUG X

#define VERSION "0.10"

#ifdef DEBUG
 // dev device (wemos)
#define RECV_PIN 4    // D2 - GPIO4
#define TRANS_PIN 5   // D1 - GPIO5
#define TRIGGER_PIN 15 // D8 - GPIO15
#define LED_PIN 2      // D4 - GPIO2
#define BUTTON_ACTIVE_LEVEL HIGH

#else
 // production device - ESP01
#define RECV_PIN 4    // D2 - GPIO4
#define TRANS_PIN 5   // D1 - GPIO5
#define TRIGGER_PIN 15 // D8 - GPIO15
#define LED_PIN 2      // D4 - GPIO2
#define BUTTON_ACTIVE_LEVEL HIGH
#endif

#define   TRANSMITTER_FREQ 38

#define        SUFFIX_SUBSCRIBE "/sender/#"
#define             SUFFIX_WILL "/status"
#define             SUFFIX_WIPE "/sender/wipe"
#define           SUFFIX_REBOOT "/sender/reboot"
#define              SUFFIX_CMD "/sender/cmd"
#define       SUFFIX_CMD_RESULT "/sender/cmd/result"
#define          SUFFIX_RAWMODE "/sender/rawMode"
#define      SUFFIX_RAWMODE_VAL "/sender/rawMode/val"
#define     SUFFIX_AUTOSENDMODE "/sender/autoSendMode"
#define SUFFIX_AUTOSENDMODE_VAL "/sender/autoSendMode/val"
#define    SUFFIX_SENDSTOREDRAW "/sender/sendStoredRaw"
#define  SUFFIX_SENDSTORERAWSEQ "/sender/sendStoredRawSequence"
#define              SUFFIX_OTA "/sender/otaURL"

#define DEFAULT_MQTT_PORT 1883
// ----------------------------------------------------------------
// Global includes
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "FS.h"
#include <IRremoteESP8266.h>      // https://github.com/markszabo/IRremoteESP8266 (use local copy)
#include <IRrecv.h>
#include <IRsend.h>
#include <IRutils.h>
#include <PubSubClient.h>         // https://github.com/knolleary/pubsubclient (id: 89)
#include <DNSServer.h>            // Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     // Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          // https://github.com/tzapu/WiFiManager WiFi Configuration Magic (id: 567)
#include <ArduinoJson.h>          // https://github.com/bblanchon/ArduinoJson (id: 64)
#include <EEPROM.h>
#include <ESP8266httpUpdate.h>

// Global variables
extern uint16_t rawIrData[SLOT_SIZE+1]; // RAW data storage
extern uint16_t rawSequence[SEQ_SIZE];
extern uint16_t rawIR1[SLOT_SIZE+1];
extern uint16_t rawIR2[SLOT_SIZE+1];
extern uint16_t rawIR1size, rawIR2size;
extern char mqtt_server[40];
extern char mqtt_port[5];
extern char mqtt_user[32];
extern char mqtt_pass[32];
extern char mqtt_prefix[80];
extern char mqtt_secure[1];
extern bool mqtt_secure_b;
extern int mqtt_port_i;
extern bool buttonState; // State of control button
extern bool autoSendMode;
extern bool MQTTMode;
extern bool shouldSaveConfig ; //flag for saving data
extern String clientName; // MQTT client name
extern bool rawMode; // Raw mode receiver status
extern unsigned long lastTSAutoStart; // Last timestamp of auto sender
extern unsigned long lastTSMQTTReconect; // Last timestamp of MQTT reconnect
extern unsigned long autoStartFreq; // Frequency of autostart
extern bool autoStartSecond;
extern const bool useDebug;

// ------------------------------------------------
// STRUCTURES
struct EEpromDataStruct {
  bool autoSendMode;
};
// ------------------------------------------------
// Global objects

 extern IRrecv irrecv;
 extern IRsend irsend;
 extern WiFiClient wifiClient;
 extern WiFiClientSecure wifiClientSecure;
 extern PubSubClient mqttClient;
 extern EEpromDataStruct EEpromData;
// ------------------------------------------------
// Functions declaration
unsigned long StrToUL(String inputString);
bool writeDataFile(const char* fName, uint16_t sourceArray[], int sourceSize);
uint16_t readDataFile(char * fName, uint16_t destinationArray[]);
String macToStr(const uint8_t* mac);
void saveConfigCallback ();
void loadDefaultIR();
void connect_to_MQTT();
void  getIrEncoding (decode_results *results, char * result_encoding);

void MQTTcallback(char* topic, byte* payload, unsigned int length);
void connect_to_MQTT();
void loadDefaultIR();
void sendToDebug(String message);

#endif
