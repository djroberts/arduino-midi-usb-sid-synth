#ifndef Sid_h
#define Sid_h

#include "SidData.h"
#include "SidAddress.h"

volatile bool sendLock = false;

class Sid {
  private:
    byte address;
    byte pinCS;
    byte pinRW;
    SidData *sidData;
    SidAddress *sidAddress;

  public:
    Sid(byte pinCS, byte pinRW, SidData *sidData, SidAddress *sidAddress) {
      this->pinCS = pinCS;
      this->pinRW = pinRW;
      this->sidData = sidData;
      this->sidAddress = sidAddress;

      pinMode(pinCS, OUTPUT);       // execute on SID
      digitalWrite(pinCS, HIGH);    // and set to high
      pinMode(pinRW, OUTPUT);       // R/W select line
      digitalWrite(pinRW, LOW);     // Set R/W select to 0 for Write mode
    };

    void setPinCS(byte pinCS) {
      this->pinCS = pinCS;
    }

    void setPinRW(byte pinRW) {
      this->pinRW = pinRW;
    }

    void setAddress(byte addressValue) {
      this->sidAddress->set(addressValue);
    };

    void setData(byte dataValue) {
      this->sidData->set(dataValue);
    };

    void waitCycle() {
      int SID6581_PIN_TIMER = 9;
      byte clock = digitalRead( SID6581_PIN_TIMER );
      while( clock != HIGH ) {
        clock = digitalRead( SID6581_PIN_TIMER );
      }

      clock = digitalRead( SID6581_PIN_TIMER );

      while( clock == HIGH ) {
        clock = digitalRead( SID6581_PIN_TIMER );
      }
    }

    void set(byte addressValue, byte dataValue) {
      while (sendLock);

      sendLock = true;

      setAddress(addressValue);
      setData(dataValue);
      digitalWrite(pinCS, LOW);
      //delayMicroseconds(20);
      digitalWrite(pinCS, HIGH);

      sendLock = false;
    }
};

#endif