#include <Arduino.h>
#include "SPIFFS.h"
//module conso théorique : 200mA
//module conso réel : 170 mA

/****************************************************************************************************************************
  AdvancedWebServer.h

  For Ethernet shields using ESP32_W5500 (ESP32 + W5500)

  WebServer_ESP32_W5500 is a library for the ESP32 with Ethernet W5500 to run WebServer

  Based on and modified from ESP32-IDF https://github.com/espressif/esp-idf
  Built by Khoi Hoang https://github.com/khoih-prog/WebServer_ESP32_W5500
  Licensed under GPLv3 license

  Copyright (c) 2015, Majenko Technologies
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification,
  are permitted provided that the following conditions are met:

  Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

  Redistributions in binary form must reproduce the above copyright notice, this
  list of conditions and the following disclaimer in the documentation and/or
  other materials provided with the distribution.

  Neither the name of Majenko Technologies nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
  ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************************************************************/

#if !( defined(ESP32) )
  #error This code is designed for (ESP32 + W5500) to run on ESP32 platform! Please check your Tools->Board setting.
#endif

#define DEBUG_ETHERNET_WEBSERVER_PORT       Serial

// Debug Level from 0 to 4
#define _ETHERNET_WEBSERVER_LOGLEVEL_       3

//////////////////////////////////////////////////////////

// Optional values to override default settings
// Don't change unless you know what you're doing
//#define ETH_SPI_HOST        SPI3_HOST
//#define SPI_CLOCK_MHZ       25

// Must connect INT to GPIOxx or not working
//#define INT_GPIO            4

//#define MISO_GPIO           19
//#define MOSI_GPIO           23
//#define SCK_GPIO            18
//#define CS_GPIO             5

//////////////////////////////////////////////////////////

#include <WebServer_ESP32_W5500.h>

WebServer server(80);

// Enter a MAC address and IP address for your controller below.
#define NUMBER_OF_MAC      20

byte mac[][NUMBER_OF_MAC] =
{
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x01 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x02 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x03 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x04 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x05 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x06 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x07 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x08 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x09 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x0A },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x0B },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x0C },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x0D },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x0E },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x0F },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x10 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x11 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x12 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x13 },
  { 0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0x14 },
};

// Select the IP address according to your local network
IPAddress myIP(192, 168, 0, 2);
IPAddress myGW(192, 168, 0, 1);
IPAddress mySN(255, 255, 255, 0);

// Google DNS Server IP
IPAddress myDNS(8, 8, 8, 8);

int reqCount = 0;                // number of requests received


int LED = 15;

void weblogin() {
  File file = SPIFFS.open("/index_login.html", "r");
  if (!file) {
    Serial.println("Failed to open HTML file");
    return;
  }

  server.streamFile(file, "text/html");
  file.close();
}

void login_CSS() {
  File file = SPIFFS.open("/style_login.css", "r");
  if (!file) {
    Serial.println("Failed to open CSS file");
    return;
  }

  server.streamFile(file, "text/css");
  file.close();
}

void login_JS() {
  File file = SPIFFS.open("/script_login.js", "r");
  if (!file) {
    Serial.println("Failed to open JavaScript file");
    return;
  }
    server.streamFile(file, "text/javascript");
  file.close();
}





void webgps() {
  File file = SPIFFS.open("/index_gps.html", "r");
  if (!file) {
    Serial.println("Failed to open HTML file");
    return;
  }

  server.streamFile(file, "text/html");
  file.close();
}

void gps_CSS() {
  File file = SPIFFS.open("/style_gps.css", "r");
  if (!file) {
    Serial.println("Failed to open CSS file");
    return;
  }

  server.streamFile(file, "text/css");
  file.close();
}

void gps_JS() {
  File file = SPIFFS.open("/script_gpd.js", "r");
  if (!file) {
    Serial.println("Failed to open JavaScript file");
    return;
  }
    server.streamFile(file, "text/javascript");
  file.close();
}



void webleds() {
  File file = SPIFFS.open("/index_leds.html", "r");
  if (!file) {
    Serial.println("Failed to open HTML file");
    return;
  }

  server.streamFile(file, "text/html");
  file.close();
}

void leds_CSS() {
  File file = SPIFFS.open("/style_leds.css", "r");
  if (!file) {
    Serial.println("Failed to open CSS file");
    return;
  }

  server.streamFile(file, "text/css");
  file.close();
}

void leds_JS() {
  File file = SPIFFS.open("/script_leds.js", "r");
  if (!file) {
    Serial.println("Failed to open JavaScript file");
    return;
  }
    server.streamFile(file, "text/javascript");
  file.close();
}



void websensors() {
  File file = SPIFFS.open("/index_sensors.html", "r");
  if (!file) {
    Serial.println("Failed to open HTML file");
    return;
  }

  server.streamFile(file, "text/html");
  file.close();
}

void sensors_CSS() {
  File file = SPIFFS.open("/style_sensors.css", "r");
  if (!file) {
    Serial.println("Failed to open CSS file");
    return;
  }

  server.streamFile(file, "text/css");
  file.close();
}

void sensors_JS() {
  File file = SPIFFS.open("/script_sensors.js", "r");
  if (!file) {
    Serial.println("Failed to open JavaScript file");
    return;
  }
    server.streamFile(file, "text/javascript");
  file.close();
}



void web10V() {
  File file = SPIFFS.open("/index_10V.html", "r");
  if (!file) {
    Serial.println("Failed to open HTML file");
    return;
  }

  server.streamFile(file, "text/html");
  file.close();
}

void dixV_CSS() {
  File file = SPIFFS.open("/style_10V.css", "r");
  if (!file) {
    Serial.println("Failed to open CSS file");
    return;
  }

  server.streamFile(file, "text/css");
  file.close();
}

void dixV_JS() {
  File file = SPIFFS.open("/script_10V.js", "r");
  if (!file) {
    Serial.println("Failed to open JavaScript file");
    return;
  }
    server.streamFile(file, "text/javascript");
  file.close();
}

void webhome() {
  File file = SPIFFS.open("/index_home.html", "r");
  if (!file) {
    Serial.println("Failed to open HTML file");
    return;
  }

  server.streamFile(file, "text/html");
  file.close();
}

void home_CSS() {
  File file = SPIFFS.open("/style_home.css", "r");
  if (!file) {
    Serial.println("Failed to open CSS file");
    return;
  }

  server.streamFile(file, "text/css");
  file.close();
}

void home_JS() {
  File file = SPIFFS.open("/script_home.js", "r");
  if (!file) {
    Serial.println("Failed to open JavaScript file");
    return;
  }
    server.streamFile(file, "text/javascript");
  file.close();
}

void LEDon(){
  digitalWrite(LED,HIGH);
}

void LEDoff(){
  digitalWrite(LED,LOW);
}



void setup()
{
  Serial.begin(115200);

  while (!Serial && (millis() < 5000));

  Serial.print(F("\nStart AdvancedWebServer on "));
  Serial.print(ARDUINO_BOARD);
  Serial.print(F(" with "));
  Serial.println(SHIELD_TYPE);
  Serial.println(WEBSERVER_ESP32_W5500_VERSION);

  ET_LOGWARN(F("Default SPI pinout:"));
  ET_LOGWARN1(F("SPI_HOST:"), ETH_SPI_HOST);
  ET_LOGWARN1(F("MOSI:"), MOSI_GPIO);
  ET_LOGWARN1(F("MISO:"), MISO_GPIO);
  ET_LOGWARN1(F("SCK:"),  SCK_GPIO);
  ET_LOGWARN1(F("CS:"),   CS_GPIO);
  ET_LOGWARN1(F("INT:"),  INT_GPIO);
  ET_LOGWARN1(F("SPI Clock (MHz):"), SPI_CLOCK_MHZ);
  ET_LOGWARN(F("========================="));

  ///////////////////////////////////

  // To be called before ETH.begin()
  ESP32_W5500_onEvent();

  // start the ethernet connection and the server:
  // Use DHCP dynamic IP and random mac
  //bool begin(int MISO_GPIO, int MOSI_GPIO, int SCLK_GPIO, int CS_GPIO, int INT_GPIO, int SPI_CLOCK_MHZ,
  //           int SPI_HOST, uint8_t *W6100_Mac = W6100_Default_Mac);
  ETH.begin( MISO_GPIO, MOSI_GPIO, SCK_GPIO, CS_GPIO, INT_GPIO, SPI_CLOCK_MHZ, ETH_SPI_HOST );
  //ETH.begin( MISO_GPIO, MOSI_GPIO, SCK_GPIO, CS_GPIO, INT_GPIO, SPI_CLOCK_MHZ, ETH_SPI_HOST, mac[millis() % NUMBER_OF_MAC] );

  // Static IP, leave without this line to get IP via DHCP
  //bool config(IPAddress local_ip, IPAddress gateway, IPAddress subnet, IPAddress dns1 = 0, IPAddress dns2 = 0);
  ETH.config(myIP, myGW, mySN, myDNS);

  ESP32_W5500_waitForConnect();

  ///////////////////////////////////

  server.on(F("/login"), weblogin);
  server.on(F("/style_login.css"), HTTP_GET, login_CSS);
  server.on(F("/script_login.js"), HTTP_GET, login_JS);

  server.on(F("/home"), webhome);
  server.on(F("/style_home.css"), HTTP_GET, home_CSS);
  server.on(F("/script_home.js"), HTTP_GET, home_JS);

  server.on(F("/gps"), webgps);
  server.on(F("/style_gps.css"), HTTP_GET, gps_CSS);
  server.on(F("/script_gps.js"), HTTP_GET, gps_JS);

  server.on(F("/leds"), webleds);
  server.on(F("/style_leds.css"), HTTP_GET, leds_CSS);
  server.on(F("/script_leds.js"), HTTP_GET, leds_JS);

  server.on(F("/sensors"), websensors);
  server.on(F("/style_sensors.css"), HTTP_GET, sensors_CSS);
  server.on(F("/script_sensors.js"), HTTP_GET, sensors_JS);

  server.on(F("/10V"), web10V);
  server.on(F("/style_10V.css"), HTTP_GET, dixV_CSS);
  server.on(F("/script_10V.js"), HTTP_GET, dixV_JS);
  
  server.on(F("/LEDon"), LEDon);
  server.on(F("/LEDoff"), LEDoff);

  server.begin();

  Serial.print(F("HTTP EthernetWebServer is @ IP : "));
  Serial.println(ETH.localIP());

   if (!SPIFFS.begin(true)) {
    Serial.println("Erreur lors de l'initialisation de SPIFFS");
    return;
  }

  pinMode(LED,OUTPUT);
}



void loop()
{
  server.handleClient();
}
