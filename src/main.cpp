#include <Project2_variables.h>

bool IS_RIGHT_SIDE = true; //* true = jambe droite, false = jambe gauche

// ----------------------------- Connecting to WIFI
String translateEncryptionType(wifi_auth_mode_t encryptionType)
{
  switch (encryptionType)
  {
  case (WIFI_AUTH_OPEN):
    return "Open";
  case (WIFI_AUTH_WEP):
    return "WEP";
  case (WIFI_AUTH_WPA_PSK):
    return "WPA_PSK";
  case (WIFI_AUTH_WPA2_PSK):
    return "WPA2_PSK";
  case (WIFI_AUTH_WPA_WPA2_PSK):
    return "WPA_WPA2_PSK";
  case (WIFI_AUTH_WPA2_ENTERPRISE):
    return "WPA2_ENTERPRISE";
  default:
    return "UNKNOWN";
  }
  return "UNKNOWN";
}

void scanNetworks()
{
  int numberOfNetworks = WiFi.scanNetworks();

  Serial.print("Number of networks found: ");
  Serial.println(numberOfNetworks);

  for (int i = 0; i < numberOfNetworks; i++)
  {

    Serial.print("Network name: ");
    Serial.println(WiFi.SSID(i));

    Serial.print("Signal strength: ");
    Serial.println(WiFi.RSSI(i));

    Serial.print("MAC address: ");
    Serial.println(WiFi.BSSIDstr(i));

    Serial.print("Encryption type: ");
    String encryptionTypeDescription = translateEncryptionType(WiFi.encryptionType(i));
    Serial.println(encryptionTypeDescription);
    Serial.println("-----------------------");
  }
}

void connectToNetwork()
{
  WiFi.begin(ssid, password);

  Serial.println("Connecting to wifi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.printf("Status: %d\r\n", WiFi.status());
    WiFi.printDiag(Serial);
    Serial.printf("TxPower: %d\r\n", WiFi.getTxPower());

    Serial.print(".");
    delay(100);
  }

  Serial.printf("Local IP address: %s\r\n", String(WiFi.localIP()));

  Serial.println("Connected to network");
}

void reconnectWIFI()
{
  // Check WiFi connection and reconnect if needed
  if (WiFi.status() != WL_CONNECTED)
  {
    analogWrite(BUILTIN_LED, 255);

    Serial.println("Wifi connection lost");
    delay(10000);
    ESP.restart();
  }
}
// ----------------------------- Connected to WIFI

// ----------------------------- MQTT Functions BEGIN
void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.println();
  Serial.println(" - - - New Message - - -");
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }

  Serial.println();
  Serial.println(" - - - END of Message - - -");
  Serial.println();
}

void reconnectMQTT()
{
  // Loop until we're reconnected
  if (!client.connected())
  {
    analogWrite(BUILTIN_LED, 127);

    Serial.print("Attempting MQTT connection...");
    // Attempt to connect

    if (IS_RIGHT_SIDE)
    {
      if (client.connect(MQTT_IDL)) // if (client.connect(MQTT_ID, MQTT_USER, MQTT_PASS))
      {
        Serial.println("connected");
        delay(5000);
      }
      else
      {
        Serial.print("failed, rc=");
        Serial.print(client.state());
        Serial.println(" try again in 5 seconds");
        // Wait 5 seconds before retrying
        delay(5000);
      }
    }
    else
    {

      if (client.connect(MQTT_IDR)) // if (client.connect(MQTT_ID, MQTT_USER, MQTT_PASS))
      {
        Serial.println("connected");
        delay(5000);
      }
      else
      {
        Serial.print("failed, rc=");
        Serial.print(client.state());
        Serial.println(" try again in 5 seconds");
        // Wait 5 seconds before retrying
        delay(5000);
      }
    }
  }
}

// ----------------------------- MQTT Functions END

// ----------------------------- Custom Functions
void conversion_Right()
{
  adcA2 = analogRead(A2);
  angleA2 = (((adcA2 * 170) / 4095.0) - 85) + osr_hip;
  if (angleA2 > 80)
  {
    angleA2 = 80;
  }
  else if (angleA2 < -79)
  {
    angleA2 = -80;
  }
  sprintf(ohmsA2, "%10.2f", angleA2);
  hip = (const char *)ohmsA2;

  delay(5);

  adcA3 = analogRead(A3);
  angleA3 = (((adcA3 * 170) / 4095.0) - 85) + osr_knee;
  if (angleA3 > 80)
  {
    angleA3 = 80;
  }
  else if (angleA3 < -79)
  {
    angleA3 = -80;
  }
  sprintf(ohmsA3, "%10.2f", angleA3);
  knee = (const char *)ohmsA3;

  delay(5);

  adcA4 = analogRead(A4);
  angleA4 = (((adcA4 * 170) / 4095.0) - 85) + osr_ankle;
  if (angleA4 > 80)
  {
    angleA4 = 80;
  }
  else if (angleA4 < -77)
  {
    angleA4 = -80;
  }
  sprintf(ohmsA4, "%10.2f", angleA4);
  ankle = (const char *)ohmsA4;

  delay(5);
}

void conversion_Left()
{
  adcA2 = analogRead(A2);
  angleA2 = (((adcA2 * 170) / 4095.0) - 85) + osl_hip;
  if (angleA2 > 80)
  {
    angleA2 = 80;
  }
  else if (angleA2 < -79)
  {
    angleA2 = -80;
  }
  sprintf(ohmsA2, "%10.2f", angleA2);
  hip = (const char *)ohmsA2;

  delay(5);

  adcA3 = analogRead(A3);
  angleA3 = (((adcA3 * 170) / 4095.0) - 85) + osl_knee;
  if (angleA3 > 80)
  {
    angleA3 = 80;
  }
  else if (angleA3 < -79)
  {
    angleA3 = -80;
  }
  sprintf(ohmsA3, "%10.2f", angleA3);
  knee = (const char *)ohmsA3;

  delay(5);

  adcA4 = analogRead(A4);
  angleA4 = (((adcA4 * 170) / 4095.0) - 85) + osl_ankle;
  if (angleA4 > 80)
  {
    angleA4 = 80;
  }
  else if (angleA4 < -77)
  {
    angleA4 = -80;
  }
  sprintf(ohmsA4, "%10.2f", angleA4);
  ankle = (const char *)ohmsA4;

  delay(5);
}

void publish()
{
  // Terminal
  Serial.println("MANUAL POTENTIOMETER : ");
  if (IS_RIGHT_SIDE)
  {
    Serial.println("  ---   --- ROBOT  `RIGHT` SIDE ---   ---");
  }
  else
  {
    Serial.println("  ---   --- ROBOT  `LEFT`  SIDE ---   ---");
  }

  Serial.print("HIP  - Potentiometre A2 : ");
  Serial.print(hip);
  Serial.print("  ---   ADC : ");
  Serial.print(adcA2);
  Serial.print("  ---   Angle: ");
  Serial.println(angleA2);

  Serial.print("KNEE  - Potentiometre A3 : ");
  Serial.print(knee);
  Serial.print("  ---   ADC : ");
  Serial.print(adcA3);
  Serial.print("  ---   Angle: ");
  Serial.println(angleA3);

  Serial.print("ANKLE   - Potentiometre A4 : ");
  Serial.print(ankle);
  Serial.print("  ---   ADC : ");
  Serial.print(adcA4);
  Serial.print("  ---   Angle: ");
  Serial.println(angleA4);

  // MQTT
  if (IS_RIGHT_SIDE)
  {
    client.publish("/cm/biped/3", hip);
    client.publish("/cm/biped/2", knee);
    client.publish("/cm/biped/1", ankle);
  }
  else
  {
    client.publish("/cm/biped/6", hip);
    client.publish("/cm/biped/5", knee);
    client.publish("/cm/biped/4", ankle);
  }
}

// ----------------------------- Main
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);

  scanNetworks();
  connectToNetwork();

  Serial.println(WiFi.macAddress());
  Serial.println(WiFi.localIP());

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  if (IS_RIGHT_SIDE)
  {
    client.connect(MQTT_IDL); // client.connect(MQTT_ID, MQTT_USER, MQTT_PASS);
  }
  else
  {
    client.connect(MQTT_IDR); // client.connect(MQTT_ID, MQTT_USER, MQTT_PASS);
  }

  // Assign pins
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(A2, ANALOG);
  pinMode(A3, ANALOG);
  pinMode(A4, ANALOG);

  Serial.println("- - - - - - - - - - - - - RESET - - - - - - - - - - - - - ");
}

void loop()
{
  // put your main code here, to run repeatedly:
  client.loop();

  reconnectWIFI();
  reconnectMQTT();

  if (millis() - lastMsg > 100)
  {
    lastMsg = millis();
    if (IS_RIGHT_SIDE)
    {
      conversion_Right();
    }
    else
    {
      conversion_Left();
    }
    publish();

    Serial.print("ESP32 Current Temp : ");
    Serial.println(temperatureRead());
    // client.publish("/cm/ESP-9/temp", (const char *)temperatureRead());

    Serial.println("- - - - LOADING - - - -");
    Serial.println("- - - Please Wait - - -");
    Serial.println();
  }
  digitalWrite(BUILTIN_LED, LOW);
}