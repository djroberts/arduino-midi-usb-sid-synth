#ifndef SidAddress_h
#define SidAddress_h


class SidAddress {
  private:
      byte pin4 = A10;

  public:
    SidAddress() {
      pinMode(A0, OUTPUT);
      pinMode(A1, OUTPUT);
      pinMode(A2, OUTPUT);
      pinMode(A3, OUTPUT);
      pinMode(pin4, OUTPUT);
    }

    void set(uint8_t value) {
      uint8_t pin_values = value & 0x1F;

      PORTF = (PORTF & ~((1 << PF4) | (1 << PF5) | (1 << PF6) | (1 << PF7))) | (pin_values << PF4);

      digitalWrite(pin4, value & 0b10000);
    }
};

#endif