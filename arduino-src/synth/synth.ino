#include <avr/io.h>
#include <avr/interrupt.h>
#include "LFO.h"
#include "MIDIUSB.h"
#include "Sid.h"
#include "SidData.h"
#include "SidAddress.h"
#include "SidDefines.h"
#include "SidVoice.h"
#include "MidiHandler.h"

double microPeriod = 1.0 / MODULATION_SAMPLERATE * 1000000.0;

SidData *sidData;
SidAddress *sidAddress;
Sid *sid;
SidVoice *voice;
LFO *lfoPitch1;
LFO *lfoPW1;

ADSR *adsrPitch1;
ADSR *adsrPW1;

MidiHandler *midiHandler;
midiEventPacket_t rx;

bool synthReady = false;

void setup() {
  Serial.begin(115200);

  lfoPitch1 = new LFO(MODULATION_SAMPLERATE);
  lfoPW1 = new LFO(MODULATION_SAMPLERATE);
  adsrPitch1 = new ADSR(MODULATION_SAMPLERATE);
  adsrPW1 = new ADSR(MODULATION_SAMPLERATE);

  sidData = new SidData(SD_LATCH_PIN);
  sidAddress = new SidAddress();
  sid = new Sid(S_CS, S_RWS, sidData, sidAddress);
  voice = new SidVoice(1, sid, lfoPitch1, adsrPitch1, lfoPW1, adsrPW1);

  midiHandler = new MidiHandler(voice, lfoPitch1, lfoPW1, adsrPitch1, adsrPW1);

  noInterrupts();

  initInterrupts(MODULATION_INTERRUPT_ENABLED);

  interrupts();

  delay(1500);

  voice->init();

//   voice->setSaw(true);
//   voice->setTriangle(false);
//   voice->noteOn(69);

  synthReady = true;
}

double lastTime = 0;

void loop() {
  double currentTime = micros();

  do {
    rx = MidiUSB.read();

    if (rx.header != 0) {
      Serial.print("Received: ");
      Serial.print(rx.header, HEX);
      Serial.print("-");
      Serial.print(rx.byte1, HEX);
      Serial.print("-");
      Serial.print(rx.byte2);
      Serial.print("-");
      Serial.println(rx.byte3, HEX);

      midiHandler->handleMidiMessage(rx);
    }
  } while (rx.header != 0);

  double difference = currentTime - lastTime;

  if (MODULATION_INTERRUPT_ENABLED || difference < microPeriod) {
    return;
  }

  lastTime = currentTime + microPeriod - difference;

  voice->process();
}

void initInterrupts(bool initModulationInterrupt) {
  pinMode (S_CLK, OUTPUT);

  TCCR1A = 0;
  TCCR1B = _BV(WGM12);
  // Set OCR1A to 7 for a 1MHz clock signal
  OCR1A = 7;
  // Set toggle for OC1A
  TCCR1A |= _BV(COM1A0);
  // Set prescaler to 1 for maximum frequency
  TCCR1B |= _BV(CS10);

//   if (initModulationInterrupt) {
//     TCCR0A = _BV(WGM01);
//     TCCR0B = _BV(CS12) | _BV(CS10);
//     // Set OCR0A to achieve 100 Hz interrupt frequency
//     OCR0A = 156;
//     // Enable Timer 0 COMPA interrupt
//     TIMSK0 |= _BV(OCIE0A);
//   }
}

//
// void initTimerInterrupt() {
//   // TCCR0A = (1 << WGM01);
//   // TCCR0B = (1 << CS02) | (1 << CS00); // Set prescaler to 1024
//   // OCR0A = 15624; // Set OCR0A to achieve 50 Hz interrupt frequency
//   // TCNT0 = 0; // Clear the timer counter register
//
//   // // Enable Timer 0 COMPA interrupt
//   // TIMSK0 |= (1 << OCIE0A);
//
//
// // // Set up Timer 0 to generate a 50 Hz interrupt
// // TCCR0A = _BV(WGM01);
// // TCCR0B = _BV(CS12) | _BV(CS10);
// // // Set OCR0A to achieve 50 Hz interrupt frequency
// // OCR0A = 155;
// // // Enable Timer 0 COMPA interrupt
// //TIMSK0 |= _BV(OCIE0A)
// }

int timerCounter = 0;

ISR(TIMER0_COMPA_vect)
{
  if (!synthReady) {
    return;
  }

  int midiMessagesProcessed = 0;

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

      midiHandler->handleMidiMessage(rx);

      midiMessagesProcessed++;
    }
  } while (rx.header != 0 && midiMessagesProcessed < 10);

  if (rx.header) {
      midiHandler->handleMidiMessage(rx);
  }

  voice->process();

  timerCounter++;

  if (timerCounter >= 100) {
    timerCounter = 0;
    Serial.println("S");
  }
}