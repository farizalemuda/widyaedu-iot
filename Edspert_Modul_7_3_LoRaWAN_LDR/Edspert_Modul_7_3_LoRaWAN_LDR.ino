#include <lorawan.h>

//ABP Credentials
const char *devAddr = "your-device-address";
const char *nwkSKey = "your-network-session-key";
const char *appSKey = "your-application-session-key";

const unsigned long interval = 500;    // 5 s interval to send message
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

//Penggunaan LDR
const int pinSensor = A0;

void setup()
{
  // inisiasi Serial comm dengan baud rate 9600
  Serial.begin(9600);
  pinMode(pinSensor, INPUT);

  if (!lora.init()) {
    Serial.println("RFM95 not detected");
    delay(500);
    return;
  }
  // Set LoRaWAN Class change CLASS_A or CLASS_C
  lora.setDeviceClass(CLASS_A);

  // Set Data Rate
  lora.setDataRate(SF12BW125);

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

  // Check interval overflow
  /*if (millis() - previousMillis > interval) {
    previousMillis = millis(); Digunakan apabila ingin looping*/

  if (isSent==false && millis() - previousMillis > interval) {
    previousMillis = millis();
  isSent=true;
  sprintf(myStr, "Lora Counter-%d", counter++); //kalo mau ngirim cmn 1x

  int analogValue = analogRead(A0);


  //Print
  Serial.println("ADC Value:");
  Serial.println(analogValue, DEC); // prints the value read

  sprintf(myStr, "ADC Value: %d", analogValue);

  //SET UP LORA
  Serial.println(myStr);
  lora.sendUplink(myStr, strlen(myStr), 0);  

  // CHECK LORA RX
  lora.update();
  recvStatus = lora.readDataByte(outStr);
  if (recvStatus) {
    newmessage = true;
    int counter = 0;  
 }
}
}
