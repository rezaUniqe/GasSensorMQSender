//
// Created by reza on 9/12/19.
//


#include <RF24.h>

#include <MQUnifiedsensor.h>
#include <Wire.h>

//Definitions
#define pin A0 //Analog input 0 of your arduino
#define type 2 //MQ2

MQUnifiedsensor MQ2(pin, type);

float H2, LPG, CO, Alcohol, Propane, Benzene;

void onRequestEvent();
void sendData(float f);

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";



void setup() {
    radio.begin();
    Serial.begin(9600);
    MQ2.inicializar();
    radio.openWritingPipe(address);
    radio.setPALevel(RF24_PA_MIN);
    radio.stopListening();
}
void loop() {
    MQ2.update();

    H2 =  MQ2.readSensor("H2"); // Return H2 concentration
    LPG =  MQ2.readSensor("LPG"); // Return LPG concentration
    CO =  MQ2.readSensor("CO"); // Return CO concentration
    Alcohol =  MQ2.readSensor("Alcohol"); // Return Alcohol concentration
    Propane =  MQ2.readSensor("Propane"); // Return Propane concentration
    onRequestEvent();
    delay(1000);
}








void onRequestEvent(){

    //H2
    sendData(H2);
    //LPG
    sendData(LPG);
    //CO
    sendData(CO);
    //Alcohol
    sendData(Alcohol);
    //Propane
    sendData(Propane);

}



void sendData(float f){
    radio.write(&f, sizeof(f));

}