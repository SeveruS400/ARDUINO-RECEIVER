/*  RF24 MODULES COMMUNICATION WITH ARDUINO
 *  IF THIS CODE DOESN'T RUN,FIRST CHECK CABLE AND PINS
 *  SECOND MAKE SURE THE RECEIVER IS RUNNING 
 *  I ADVISE LED CONNECTION TO THE CIRCUIT    *SEVERUS*
 */
#include <printf.h>               //RECEIVER
#include <RF24.h>
#include <nRF24L01p.h>
#include <SPI.h>

#define CE_PIN 9
#define CSN_PIN 10

const byte Address[5] = {'R','x','A','A','A'};   //CHANNEL ,IT HAS TO BE THE SAME WITH THE TRANSMITTER CHANEL
RF24 radio(CE_PIN, CSN_PIN);                     //CREATE RADIO  

char dataReceived[20];                          // THIS MUST MATCH THE dataToSend ON THE TRANSMITTER
bool newData = false;                     

//===========

void setup() {
                                              //START RECEİVER AND DECLARE PIPE
Serial.begin(9600);                           
Serial.println("SimpleRx Starting");
radio.begin();
radio.setDataRate( RF24_250KBPS );            // VARIABLE MUST BE BETWEEN 250KBPS TO 2MBPS
radio.openReadingPipe(1, Address);
radio.startListening();
}

//=============

void loop() {
  getData();
  showData();
  delay(1000);                                 //WAIT A SECOND
}

//==============

void getData() {
  
  if ( radio.available() ) {
      radio.read( &dataReceived, sizeof(dataReceived));     //INCOMING DATA WILL MATCH HERE
      newData = true;                                       
   }
}

void showData() {
  if (newData == true) {
    Serial.println("Data Received ");
    Serial.print(dataReceived);
    newData = false;
  }
}
