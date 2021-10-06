#include <max6675.h>
#include <ModbusRtu.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(7, 8); // RX, TX

// data array for modbus network sharing
uint16_t au16data[16] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, -1
};

/**
    Modbus object declaration
    u8id : node id = 0 for master, = 1..247 for slave
    u8serno : serial port (use 0 for Serial)
    u8txenpin : 0 for RS-232 and USB-FTDI
                 or any pin number > 1 for RS-485
*/
Modbus slave(1, mySerial, 0); // this is slave @1 and RS-232 or USB-FTDI

// Pins for thermocouple MAX6675
int thermoDO = 6;
int thermoCS = 5;
int thermoCLK = 4;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

// declare variable for Arduino pin connected to solid state relay (SSR)
int relay = 9;

// declare variables for Arduino pins connected to fan controller (L293N)
int fan = 10; // ENA of L239N
int in1 = 11; // IN1 of L239N
int in2 = 12; // IN1 of L239N

// declare variables for Arduino pins to power MAX6675:
int vccPin = 3; // 5v power of MAX6675
int gndPin = 2; // gnd of MAX6675


void setup() {
  mySerial.begin(19200); // Soft Serial used for communication through Bluetooth module HC-06
  slave.start( ); // 19200 baud, 8-bits, even, 1-bit stop
  // use Arduino pins
  pinMode(relay, OUTPUT);
  pinMode(fan, OUTPUT);
  //fan direction can be reversed by interchanging values for in1 and in2
  pinMode(in1, OUTPUT); digitalWrite(in1, HIGH);
  pinMode(in2, OUTPUT); digitalWrite(in2, LOW);

  pinMode(vccPin, OUTPUT); digitalWrite(vccPin, HIGH);
  pinMode(gndPin, OUTPUT); digitalWrite(gndPin, LOW);
  delay(500);
}

void loop() {
  //write current thermocouple value
  au16data[2] = ((uint16_t) thermocouple.readCelsius() * 100);

  //write current fan value for air control
  analogWrite(fan, (au16data[5] / 100.0) * 255);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  //poll modbus registers
  slave.poll( au16data, 16 );

  // heater control:
  digitalWrite(relay, HIGH);
  delay(au16data[4] * 10);
  digitalWrite(relay, LOW);
  delay((100 - au16data[4]) * 10 );
}
