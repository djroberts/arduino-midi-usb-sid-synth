#include "MIDIUSB.h"

// Sets all data pins to on and off every 5 seconds

//Pin connected to ST_CP of 74HC595
int latchPin = 3;
//Pin connected to SH_CP of 74HC595
int clockPin = 4;
////Pin connected to DS of 74HC595
int dataPin = 2;

int CLK = 9;
int RWS = 8;  // 11
int CS = 7;   // 12

midiEventPacket_t rx;

int attack = 0;
int decay = 0;
int sustain = 0;
int release = 0;

double midiFrequencyTable[127];

byte dataHi = 0;
byte dataLo = 0;

void setup() {
  Serial.begin(115200);

  initiFrequencyTable();

  noInterrupts();

  pinMode (CLK, OUTPUT); 

  TCCR1A = 0;
  TCCR1B = _BV(WGM12);
  // Set OCR1A to 7 for a 1MHz clock signal
  OCR1A = 7;
  // Set toggle for OC1A
  TCCR1A |= _BV(COM1A0);
  // Set prescaler to 1 for maximum frequency
  TCCR1B |= _BV(CS10);

  interrupts();

  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A10, OUTPUT);

  pinMode(CS, OUTPUT);       // execute on SID
  digitalWrite(CS, HIGH);    // and set to high
  pinMode(RWS, OUTPUT);       // R/W select line
  digitalWrite(RWS, LOW);     // Set R/W select to 0 for Write mode

  // 11000	00001111	Set maximum Volume
  setAddress(0b11000);
  setData(0b00001111);
  clockIn();
}

void loop() {
  do {
    rx = MidiUSB.read();
    if (rx.header != 0) {
      Serial.print("Received: ");
      Serial.print(rx.header, HEX);
      Serial.print("-");
      Serial.print(rx.byte1, HEX);
      Serial.print("-");
      Serial.print(rx.byte2, HEX);
      Serial.print("-");
      Serial.println(rx.byte3, HEX);

      if (rx.header == 9) {
        noteOn(rx.byte2);
      }

      if (rx.header == 8) {
        noteOff();
      }

      if (rx.header == 11) {
        if (rx.byte2 == 9) {
          attack = rx.byte3;
        }
        if (rx.byte2 == 10) {
          decay = rx.byte3;
        }
        if (rx.byte2 == 11) {
          sustain = rx.byte3;
        }
        if (rx.byte2 == 12) {
          release = rx.byte3;
        }

        setADSR();
      }
    }
  } while (rx.header != 0);
}

void setADSR() {
  setAddress(0b00101);
  setData(attack * 16 + decay);
  clockIn();

  setAddress(0b00110);
  setData(sustain * 16 + release);
  clockIn();
}

void clockIn() {
  digitalWrite(CS, LOW);
  delayMicroseconds(20);
  digitalWrite(CS, HIGH);
}

void setAddress(byte data) {
  digitalWrite(A3, data & 0b1);
  digitalWrite(A2, data & 0b10);
  digitalWrite(A1, data & 0b100);
  digitalWrite(A0, data & 0b1000);
  digitalWrite(A10, data & 0b10000);
}

void setData(byte data) {
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, flipByte(data));
  digitalWrite(latchPin, 1);
}

byte flipByte(byte c) {
  c = ((c>>1)&0x55)|((c<<1)&0xAA);
  c = ((c>>2)&0x33)|((c<<2)&0xCC);
  c = (c>>4) | (c<<4) ;

  return c;
}

void shiftOut(int myDataPin, int myClockPin, byte dataOut) {
  // This shifts 8 bits out MSB first,
  //on the rising edge of the clock,
  //clock idles low
  //internal function setup
  int i=0;
  int pinState;

  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);
  
  //clear everything out just in case to
  //prepare shift register for bit shifting
  digitalWrite(myDataPin, 0);
  digitalWrite(myClockPin, 0);

  //for each bit in the byte myDataOut&#xFFFD;
  //NOTICE THAT WE ARE COUNTING DOWN in our for loop
  //This means that %00000001 or "1" will go through such
  //that it will be pin Q0 that lights.
  for (i=7; i>=0; i--)  {
    digitalWrite(myClockPin, 0);
    //if the value passed to myDataOut and a bitmask result
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000
    // and proceeds to set pinState to 1.
    if ( dataOut & (1<<i) ) {
      pinState= 1;
    } else {
      pinState= 0;
    }

    //Sets the pin to HIGH or LOW depending on pinState
    digitalWrite(myDataPin, pinState);
    //register shifts bits on upstroke of clock pin
    digitalWrite(myClockPin, 1);
    //zero the data pin after shift to prevent bleed through
    digitalWrite(myDataPin, 0);
  }
  
  //stop shifting
  digitalWrite(myClockPin, 0);
}

void noteOn(int midiNote) {
  setFrequency(midiFrequencyTable[midiNote]);

  setAddress(0b00000);
  setData(dataLo);
  clockIn();

  setAddress(0b00001);
  setData(dataHi);
  clockIn();

  //00100	00010001	Set Triangle waveform and Gate bits
  setAddress(0b00100);
  setData(0b00010001);
  clockIn();
}

void noteOff() 
{ 
  //00100	00010000	Set Triangle waveform and Gate off bits
  setAddress(0b00100);
  setData(0b00010000);
  clockIn();
}

void initiFrequencyTable() {
  for (int i = 0; i <= 127; i++) {
    midiFrequencyTable[i] = 440.0 * pow(2.0, (i - 69) / 12.0);  
  }
}

void setFrequency(double frequency) {
  byte Fhi;
  
  // Commodore magic to calculate high and low frequency data
  double F = frequency/0.059605;

  dataHi = F/256;
  dataLo = (F + .5) - Fhi * 256;
}

