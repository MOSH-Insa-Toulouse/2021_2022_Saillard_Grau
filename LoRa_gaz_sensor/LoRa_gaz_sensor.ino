#include <TheThingsNetwork.h>
#include <SoftwareSerial.h>
#include <rn2xx3.h>

// Set your DevAddr, NwkSKey, AppSKey and the frequency plan
const char *devAddr = "260BE1B1";
const char *nwkSKey = "54427BFCD027CFE39C07171AA0162581";
const char *appSKey = "91F6AB105BF31EB6F5185BA4A740E997";


#define debugSerial Serial

#define TX 10
#define RX 11
#define RST 12
#define PWM 9

#define gas_PIN A0

SoftwareSerial loraSerial(TX, RX);


//test
float gas_value_float;
uint16_t gas_value;

int lora = 0;

rn2xx3 myLora(loraSerial);

void maRoutine() {
  Serial.println("ok");
  lora = 1;
  
 }

void setup() {

  pinMode(gas_PIN, INPUT);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  analogWrite(PWM,10);
  
  gas_value_float=0;
  gas_value=0;

  Serial.begin(9600);
  loraSerial.begin(9600);
  Serial.println("Start");
  pinMode(RST, OUTPUT);
  
  digitalWrite(RST, HIGH);
  digitalWrite(RST, LOW);
  delay(500);
  digitalWrite(RST, HIGH);

  myLora.autobaud();

  Serial.println("RN483 version number: ");
  Serial.println(myLora.sysver());
  
  myLora.initABP(devAddr, appSKey, nwkSKey);
  attachInterrupt(digitalPinToInterrupt(2), maRoutine, HIGH);

  
  delay(2000);

  


}

void loop() {

  gas_value_float=analogRead(gas_PIN);
  Serial.println(gas_value_float);

 
  if(lora==1){
    uint32_t alert=1;
    byte tab_alert[2];
    tab_alert[0]=highByte(alert);
    tab_alert[1]=lowByte(alert);
    myLora.txBytes(tab_alert, sizeof(tab_alert));
  }
  gas_value=gas_value_float*100;
  byte payload[2];
  payload[0]=highByte(gas_value);
  payload[1]=lowByte(gas_value);

  myLora.txBytes(payload, sizeof(payload));
  

}
