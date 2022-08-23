#include <lorawan.h>

//ABP Credentials
const char *devAddr = "your-device-address";
const char *nwkSKey = "your-network-session-key";
const char *appSKey = "your-application-session-key";

const unsigned long interval = 10000;    // 10 s interval to send message
unsigned long previousMillis = 0;  // will store last time message sent
unsigned int counter = 0;     // message counter

char myStr[50];
byte outStr[255];
byte recvStatus = 0;
int port, channel, freq;
bool newmessage = false;
bool isSent; //DIGUNAKAN APABILA HANYA INGIN MENGIRIM DATA 1x

const sRFM_pins RFM_pins = {
  .CS = 5,
  .RST = 0,
  .DIO0 = 27,
  .DIO1 = 2,
};

#include "DHTesp.h"

// deklarasi variable
// set pin yang digunakan
#define DHTPIN 14

// deklarasi object sensor
// set tipe DHT dan pin yang digunakan
DHTesp dht;

void setup() {

  Serial.begin(9600);

  Serial.println("EDSPERT - Akuisisi sensor DHT22 via ESP32");

  // inisiasi sensor DHT
  dht.setup(DHTPIN, DHTesp::DHT22);

  if (!lora.init()) {
    Serial.println("RFM95 not detected");
    delay(5000);
    return;
  }
  // Set LoRaWAN Class change CLASS_A or CLASS_C
  lora.setDeviceClass(CLASS_A);

  // Set Data Rate
  lora.setDataRate(SF10BW125);

  // Set FramePort Tx
  lora.setFramePortTx(5);

  // set channel to random
  lora.setChannel(MULTI);

  // Set TxPower to 15 dBi (max)
  lora.setTxPower(15);

  // Put ABP Key and DevAddress here
  lora.setNwkSKey(nwkSKey);
  lora.setAppSKey(appSKey);
  lora.setDevAddr(devAddr);
}

void loop() {

  /*// Check interval overflow
  if (millis() - previousMillis > interval) {
    previousMillis = millis(); Digunakan apabila ingin looping*/

  if (isSent==false && millis() - previousMillis > interval) {
    previousMillis = millis();
  isSent=true;
  sprintf(myStr, "Lora Counter-%d", counter++); // Mengirim data 1x

    TempAndHumidity data = dht.getTempAndHumidity();

    // ekstrak data temperature
    float temp = data.temperature;
    // ekstrak data humidity
    float hum = data.humidity;

    // menampilkan data di serial
    Serial.println("Suhu: " + String(temp, 2) + "°C");
    Serial.println("Kelembaban: " + String(hum, 1) + "%");
    Serial.println("---");

    sprintf(myStr, "Temp:%.2f C, Humidity:%.1f persen", temp, hum);

    //SET UP LORA
    Serial.println(myStr);
    lora.sendUplink(myStr, strlen(myStr), 0);


  // waktu jeda sampling data
  // minimal 2 detik
  // delay(2000);

  }
  // Check Lora RX
  lora.update();
  recvStatus = lora.readDataByte(outStr);
  if (recvStatus) {
    newmessage = true;
    int counter = 0;  
  }
}
