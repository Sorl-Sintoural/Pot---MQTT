
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

#include "secrets.h"

// WIFI creation
const char *ssid = WIFI_SSID;
const char *password = WIFI_PASSWORD;
WiFiClient espClient;

// MQTT client creation
PubSubClient client(espClient);
const char *mqtt_server = MQTT_SERVER;
const char *clientUser = MQTT_USER;
const char *clientPass = MQTT_PASS;

// MQTT message creation
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
const char *msg[MSG_BUFFER_SIZE];

// Potentiometres Variables
char ohmsA2[20], ohmsA3[20], ohmsA4[20];
int adcA2, adcA3, adcA4;
float osr_hip = 7.10, osr_knee = 4.59, osr_ankle = 5.50,
      osl_hip = 3.50, osl_knee = 3.90, osl_ankle = 4.00;
double angleA2, angleA3, angleA4;
const char *ankle = "100", *knee = "200", *hip = "300";



// Formula for millisec(1-2ms) from ADC : ms = 100 + ((adc*100)/4095.0);
