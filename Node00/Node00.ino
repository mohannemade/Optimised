/*
  Arduino Wireless Network - Multiple NRF24L01 
        == Node 02 (Child of Master node 00) ==
*/
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
//#include <Servo.h>
//#define led 2
RF24 radio(9, 10);               // nRF24L01 (CE,CSN)
RF24Network network(radio);      // Include the radio in the network
const uint16_t this_node = 00;   // Address of our node in Octal format ( 04,031, etc)
const uint16_t node01 = 01;    // Address of the other node in Octal format
const uint16_t node02 = 02;
int val;0
char msg[18] = "Motion detected 0";
char txNum = '0';

//Servo myservo;  // create servo object to control a servo
void setup() {
  SPI.begin();
  Serial.begin(9600);
  radio.begin();
  network.begin(90, this_node); //(channel, node address)
  radio.setDataRate(RF24_2MBPS);
  //myservo.attach(3);   // (servo pin)
  //pinMode(led, OUTPUT);
}
void loop() {
  network.update();
  //===== Receiving =====//
  while ( network.available() ) {     // Is there any incoming data?
    RF24NetworkHeader header;
    //unsigned long incomingData;
 
    network.read(header, &val, sizeof(val)); // Read the incoming data
    if (header.from_node == 1) {    // If data comes from Node 02
      //myservo.write(incomingData);  // tell servo to go to a particular angle
      Serial.println("From node 1");
      RF24NetworkHeader header2(node01);     // (Address where the data is going)
      updateMessage();
      bool ok = network.write(header2, &msg, sizeof(msg)); // Send the data

    }
    else if (header.from_node == 2) {    // If data comes from Node 012
      //digitalWrite(led, !incomingData);  // Turn on or off the LED 02
      Serial.println("From node 2");
      RF24NetworkHeader header3(node02);     // (Address where the data is going)
      updateMessage();
      bool ok = network.write(header3, &msg, sizeof(msg)); // Send the data
    }
  }
}

void updateMessage() {
        // so you can see that new data is being sent
    txNum += 1;
    if (txNum > '9') {
        txNum = '0';
    }
    msg[16] = txNum;

}

//==============
