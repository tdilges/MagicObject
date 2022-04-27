#include <Arduino.h>
#include <WiFi.h>
#include <BluetoothSerial.h>


//Konstanten.. evtl. auslagern in eine extra Datei, je nach Umfang.
#define WIFI_NETWORK "Netzwerkname" //anpassen
#define WIFI_PASSWORD "pw" //anpassen
#define WIFI_TIMEOUT_MS 20000 // ggf anpassen
#define LED_BUILTIN 2 //LED PIN Nummer checken, oftmals ist 2 aber richig.
#define BT_NAME "Testname" // anpassen



//BluetoothSerial Connection-Variable //position unklar, daher aktuell global
BluetoothSerial SerialBT;



// TODI 
void connectToWiFi(){
  Serial.println("Verbinde mit WLAN");
  WiFi.mode(WIFI_STA); // Static Wifi Status Mode
  WiFi.begin(WIFI_NETWORK, WIFI_PASSWORD);

  unsigned long startAttemptTime = millis(); // millis-Funktion gibt den Startzeitpunkt des ESP-32 wieder. Systemzeit

  while(WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < WIFI_TIMEOUT_MS){ //While Schleife, die läuft bis die WIFI_TIMEOUT-MS > als Startattempttime ist 
  // "&&" Ergebnis = 1, wenn beide Operanden Werte != 0 haben
    Serial.println("...");
    delay(100);
  }
  if (WiFi.status() != WL_CONNECTED){
    Serial.println("Connection Failed!");
    // evtl. timeout, HIER MUSS NOCH WAShin, was passieren soll, wenn der keine connection bekommt.
  } else {
    Serial.println("Connected!");
    Serial.println(WiFi.localIP());
  }
}




void setup() { Serial.begin(9600); // Datenrate über Serial
  // wird zu Beginn ausgeführt - BOOT-FUNKTION

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Hello Leute, hier spricht der BOOT-Funktion.");
  connectToWiFi();
  if(!SerialBT.begin(BT_NAME)){
    Serial.println("Es ist ein Fehler aufgetreten. Bluetooth-Verbindung unterbrochen oder nicht möglich.");
  }else{
    Serial.println("Bluetooth-Verbindung hergestellt.");
  }
}

void loop() { 
  // put your main code here, to run repeatedly:
  //kontinuierlich ausgeführter Code

  delay(1000); // 1000ms Delay zwischen jedem PrintLN
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("Ich bin die LOOP Funktion und ich bin auch dabei.");
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);

  if (Serial.available()){
  Serial.write(Serial.read()); //Serial.read returns die erhaltenen Daten
  }

  if(SerialBT.available()){
    Serial.write(SerialBT.read());
  }
  delay(100);
  }

