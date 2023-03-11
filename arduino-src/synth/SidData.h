#ifndef SidData_h
#define SidData_h

#include <SPI.h>

class SidData {
  private:
    //Pin connected to ST_CP of 74HC595
    byte latchPin;
    //Pin connected to SH_CP of 74HC595
    byte clockPin;
    //Pin connected to DS of 74HC595
    byte dataPin;

    bool reverse = false;

    byte flipByte(byte c) {
      c = ((c>>1)&0x55)|((c<<1)&0xAA);
      c = ((c>>2)&0x33)|((c<<2)&0xCC);
      c = (c>>4) | (c<<4) ;

      return c;
    }

    void shiftOut(byte dataOut) {
      // This shifts 8 bits out MSB first,
      //on the rising edge of the clock,
      //clock idles low
      //internal function setup
      int i = 0;
      int pinState;

      pinMode(clockPin, OUTPUT);
      pinMode(dataPin, OUTPUT);

      //clear everything out just in case to
      //prepare shift register for bit shifting
      digitalWrite(dataPin, 0);
      digitalWrite(clockPin, 0);

      //for each bit in the byte myDataOut&#xFFFD;
      //NOTICE THAT WE ARE COUNTING DOWN in our for loop
      //This means that %00000001 or "1" will go through such
      //that it will be pin Q0 that lights.
      for (i=7; i>=0; i--)  {
        digitalWrite(clockPin, 0);
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
        digitalWrite(dataPin, pinState);
        //register shifts bits on upstroke of clock pin
        digitalWrite(clockPin, 1);
        //zero the data pin after shift to prevent bleed through
        digitalWrite(dataPin, 0);
      }

      //stop shifting
      digitalWrite(clockPin, 0);
    }

  public:
    SidData(byte latchPin) {
      this->latchPin = latchPin;
      
      pinMode(latchPin, OUTPUT);
      digitalWrite(latchPin, HIGH); 

      SPI.begin();
      SPI.setBitOrder(LSBFIRST);
    }

    void setLatchPin(byte latchPin) {
      this->latchPin = latchPin;
    }

    void setClockPin(byte clockPin) {
      this->clockPin = clockPin;
    }

    void setDataPin(byte dataPin) {
      this->dataPin = dataPin;
    }

    void setReverse(bool reverse) {
      this->reverse = reverse;
    }

    void set(byte dataOut) {
      SPI.beginTransaction(SPISettings(1000000, LSBFIRST, SPI_MODE0));
      digitalWrite(latchPin, LOW); // Enable slave
      SPI.transfer(dataOut); // Send data to slave
      digitalWrite(latchPin, HIGH); // Disable slave
      SPI.endTransaction();
    }
};

#endif