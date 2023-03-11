#ifndef SidVoice_h
#define SidVoice_h

#include "Sid.h"
#include "LFO.h"
#include "ADSR.h"

#define VOICE_1_FREQ_LO 0b00000
#define VOICE_1_FREQ_HI 0b00001
#define VOICE_1_ATTACK_DECAY 0b00101
#define VOICE_1_PW_LO 0b00010
#define VOICE_1_PW_HI 0b00011
#define VOICE_1_SUSTAIN_RELEASE 0b00110
#define VOICE_1_CONTROL_REG 0b00100
#define MODE_VOL 0b11000
#define FC_LO 0b10101
#define FC_HI 0b10110
#define RES_FILT 0b10111
#define MODE_VOL 0b11000

class SidVoice {

  private:
    Sid *sid;
    LFO *lfoPitch;
    LFO *lfoPW;
    ADSR *adsrPitch;
    ADSR *adsrPW;

    double lfoPitchMultiplier = 0;
    double lfoPWMultiplier = 0;
    double adsrPitchMultiplier = 0;
    double adsrPWMultiplier = 0;

    byte voice = 0; // 0 = all

    byte attack = 0;
    byte decay = 10;
    byte sustain = 12;
    byte release = 0;

    unsigned int pulseWidth = 2048;

    byte lowByte = 0;
    byte highByte = 0;

    double currentVoltage = 0;

    byte lastFreqHighByte = 0;
    byte lastPWHighByte = 0;

    bool noise = false;
    bool saw = false;
    bool pulse = false;
    bool triangle = true;

    double midiFrequencyTable[127];

    byte getControlReg() {
       byte reg = 0;

       reg += noise     ? 0b10000000 : 0;
       reg += pulse     ? 0b01000000 : 0;
       reg += saw       ? 0b00100000 : 0;
       reg += triangle  ? 0b00010000 : 0;

       return reg;
    }

    void sendAttackDecay() {
      if (voice == 0 || voice == 1) {
        this->sid->set(VOICE_1_ATTACK_DECAY, attack * 16 + decay);
      }
    }

    void sendSustainRelease() {
      if (voice == 0 || voice == 1) {
        this->sid->set(VOICE_1_SUSTAIN_RELEASE, sustain * 16 + release);
      }
    }

    void setFrequencyBytes(double frequency) {
      double sanitizedFrequency = min(4770, max(1, frequency));

      byte Fhi;

      // Commodore magic to calculate high and low frequency data
      double F = sanitizedFrequency / 0.059605;

      highByte = F/256;
      lowByte = (F + .5) - Fhi * 256;
    }

    void initFrequencyTable() {
      for (int i = 0; i <= 127; i++) {
        midiFrequencyTable[i] = 440.0 * pow(2.0, (i - 69) / 12.0);
      }
    }

    void setFrequency() {
      if (voice == 0 || voice == 1) {
        if (lastFreqHighByte != highByte) {
          this->sid->set(VOICE_1_FREQ_HI, highByte);
        }

        lastFreqHighByte = highByte;

        this->sid->set(VOICE_1_FREQ_LO, lowByte);
      }
    }

    void setPulseWidthBytes(unsigned int pulseWidth) {
      unsigned int sanitizedPulseWidth = min(4095, max(0, pulseWidth));

      lowByte = sanitizedPulseWidth & 0xFF;
      highByte = (sanitizedPulseWidth >> 8) & 0xFF;
    }

    void sendPulseWidth() {
      if (voice == 0 || voice == 1) {
        this->sid->set(VOICE_1_PW_LO, lowByte);

        if (highByte != lastPWHighByte) {
          this->sid->set(VOICE_1_PW_HI, highByte & 0b00001111);
        }

        lastPWHighByte = highByte;
      }
    }

    void changePulseWidth(unsigned int pulseWidth) {
       setPulseWidthBytes(this->pulseWidth + pulseWidth);
       sendPulseWidth();
    }

  public:
    SidVoice(byte voice, Sid *sid, LFO *lfoPitch, ADSR *adsrPitch, LFO *lfoPW, ADSR *adsrPW) {
      this->voice = voice;
      this->sid = sid;
      this->lfoPitch = lfoPitch;
      this->lfoPW = lfoPW;
      this->adsrPitch = adsrPitch;
      this->adsrPW = adsrPW;

      initFrequencyTable();
    }

    void init() {
      sendAttackDecay();
      sendSustainRelease();

      noteOff();

      this->sid->set(MODE_VOL, 0b00001111);
    };

    void setAttack(byte attack) {
      this->attack = attack;

      sendAttackDecay();
    }

    void setDecay(byte decay) {
      this->decay = decay;

      sendAttackDecay();
    }

    void setSustain(byte sustain) {
      this->sustain = sustain;

      sendSustainRelease();
    }

    void setRelease(byte release) {
      this->release = release;

      sendSustainRelease();
    }

    void setNoise(bool noise) {
      Serial.println("NOISE");
      Serial.println(noise);
      this->noise = noise;
    }

    void setPulse(bool pulse) {
      Serial.println("PULSE");
      Serial.println(pulse);
      this->pulse = pulse;
    }

    void setSaw(bool saw) {
      Serial.println("SAW");
      Serial.println(saw);
      this->saw = saw;
    }

    void setTriangle(bool triangle) {
      Serial.println("TRIANGLE");
      Serial.println(triangle);
      this->triangle = triangle;
    }

    void setPulseWidth(unsigned int pulseWidth) {
      this->pulseWidth = pulseWidth;

      setPulseWidthBytes(pulseWidth);
      sendPulseWidth();
    }

    void changeFrequency(double voltage) {
      double frequency =  440.0 * pow(2, (voltage + currentVoltage) - 5.0);

      setFrequencyBytes(frequency);
      setFrequency();
    }

    void noteOn(byte midiNote) {
      lfoPitch->reset();
      lfoPW->reset();
      adsrPitch->reset();
      adsrPW->reset();

      currentVoltage = 5.0 + ((midiNote - 69.0) / 12.0);

      setFrequencyBytes(midiFrequencyTable[midiNote]);
      setFrequency();

      //this->sid->set(MODE_VOL, 0b00001111);

      if (voice == 0 || voice == 1) {
        Serial.println(getControlReg(), BIN);
        this->sid->set(VOICE_1_CONTROL_REG, getControlReg() + 1);
      }
    }

    void noteOff() {
      if (voice == 0 || voice == 1) {
        this->adsrPitch->release();
        this->adsrPW->release();
        this->sid->set(VOICE_1_CONTROL_REG, getControlReg());
      }
    }

    void setLFOPitchMultiplier(double lfoPitchMultiplier) {
      this->lfoPitchMultiplier = lfoPitchMultiplier;
    }

    void setLFOPWMultiplier(double lfoPWMultiplier) {
      this->lfoPWMultiplier = lfoPWMultiplier;
    }

    void setADSRPitchMultiplier(double adsrPitchMultiplier) {
      this->adsrPitchMultiplier = adsrPitchMultiplier;
    }

    void setADSRPWMultiplier(double adsrPWMultiplier) {
      this->adsrPWMultiplier = adsrPWMultiplier;
    }

    void process() {
      double pitchModulation = 0;
      double pwModulation = 0;

      if (lfoPitchMultiplier != 0) {
        lfoPitch->process();
        pitchModulation = lfoPitchMultiplier * lfoPitch->getOutput();
      }

      if (lfoPWMultiplier != 0) {
        lfoPW->process();

        pwModulation = lfoPWMultiplier * lfoPW->getOutput() * MAX_PW_SWING;
      }

      if (adsrPitchMultiplier != 0) {
        adsrPitch->process();

        pitchModulation += adsrPitchMultiplier * adsrPitch->getOutput();
      }

      if (adsrPWMultiplier != 0) {
        adsrPW->process();

        pwModulation += adsrPWMultiplier * adsrPW->getOutput() * MAX_PW_SWING;
      }

      if (pitchModulation != 0) {
        changeFrequency(pitchModulation);
      }

      if (pwModulation != 0) {
        changePulseWidth(pwModulation);
      }
    }
};

#endif