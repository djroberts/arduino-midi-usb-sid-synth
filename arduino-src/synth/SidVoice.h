#ifndef SidVoice_h
#define SidVoice_h

#include "ByteArray.h"
#include "Sid.h"
#include "LFO.h"
#include "ADSR.h"

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

    byte voiceType = 1;

    double portamentoCoeff = 0;

    ByteArray notesOn;

    byte attack = 0;
    byte decay = 12;
    byte sustain = 12;
    byte release = 0;

    unsigned int pulseWidth = 2048;

    byte lowByte = 0;
    byte highByte = 0;

    double currentVoltage = -1;
    double targetVoltage = 0;
    double octave = 0;
    double fine = 0;

    byte lastFreqHighByte = 0;
    byte lastPWHighByte = 0;

    bool noise = false;
    bool saw = true;
    bool pulse = false;
    bool triangle = false;

    byte getControlReg() {
       byte reg = 0;

       reg += noise     ? 0b10000000 : 0;
       reg += pulse     ? 0b01000000 : 0;
       reg += saw       ? 0b00100000 : 0;
       reg += triangle  ? 0b00010000 : 0;

       return reg;
    }

    void sendAttackDecay() {
      this->sid->set(SID_VOICE_ATTACK_DECAY[voice], attack * 16 + decay);
    }

    void sendSustainRelease() {
     this->sid->set(SID_VOICE_SUSTAIN_RELEASE[voice], sustain * 16 + release);
    }

    void setFrequencyBytes(double frequency) {
      double sanitizedFrequency = min(4770, max(1, frequency));

      byte Fhi;

      // Commodore magic to calculate high and low frequency data
      double F = sanitizedFrequency / 0.059605;

      highByte = F/256;
      lowByte = (F + .5) - Fhi * 256;
    }

    void setFrequency() {
      if (lastFreqHighByte != highByte) {
        this->sid->set(SID_VOICE_FREQ_HI[voice], highByte);
      }

      lastFreqHighByte = highByte;

      this->sid->set(SID_VOICE_FREQ_LO[voice], lowByte);
    }

    void setPulseWidthBytes(unsigned int pulseWidth) {
      unsigned int sanitizedPulseWidth = min(4095, max(0, pulseWidth));

      lowByte = sanitizedPulseWidth & 0xFF;
      highByte = (sanitizedPulseWidth >> 8) & 0xFF;
    }

    void sendPulseWidth() {
      this->sid->set(SID_VOICE_PW_LO[voice], lowByte);

      if (highByte != lastPWHighByte) {
        this->sid->set(SID_VOICE_PW_HI[voice], highByte & 0b00001111);
      }

      lastPWHighByte = highByte;
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
    }

    void init() {
      sendAttackDecay();
      sendSustainRelease();

      // todo: becomes gate off
      //noteOff();

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
      this->noise = noise;
    }

    void setPulse(bool pulse) {
      this->pulse = pulse;
    }

    void setSaw(bool saw) {
      this->saw = saw;
    }

    void setTriangle(bool triangle) {
      this->triangle = triangle;
    }

    void setOctave(double octave) {
      this->octave = max(-2.0, min(2.0, octave));
    }

    void setFine(double fine) {
      this->fine = (1.0 / 12.0) * max(-1.0, min(1.0, fine));
    }

    void setPulseWidth(unsigned int pulseWidth) {
      this->pulseWidth = pulseWidth;

      setPulseWidthBytes(pulseWidth);
      sendPulseWidth();
    }

    void changeFrequency(double voltage) {
      double frequency =  440.0 * pow(2, (voltage + currentVoltage + octave + fine) - 5.0);

      setFrequencyBytes(frequency);
      setFrequency();
    }

    void handleNoteOn(byte midiNote) {
      if (!notesOn.exists(midiNote)) {
        notesOn.push(midiNote);
      }

      if (notesOn.length() == 1 || voiceType == 0) {
        noteOn(midiNote);
      } else if (notesOn.length() > 1) {
        targetVoltage = 5.0 + ((midiNote - 69.0) / 12.0);

        if (portamentoCoeff == 0 || currentVoltage == -1) {
          currentVoltage = targetVoltage;
          changeFrequency(0);
        }
      }
    }

    void handleNoteOff(byte midiNote) {
      notesOn.remove(midiNote);

      if (notesOn.length() == 0) {
        noteOff();
      } else {
        byte lastMidiNote = notesOn.getLast();

        if (voiceType == 0) {
          noteOn(lastMidiNote);
        } else {
          targetVoltage = 5.0 + ((lastMidiNote - 69.0) / 12.0);

          if (portamentoCoeff == 0) {
            currentVoltage = targetVoltage;
            changeFrequency(0);
          }
        }
      }
    }

    void noteOn(byte midiNote) {
      lfoPitch->reset();
      lfoPW->reset();
      adsrPitch->reset();
      adsrPW->reset();

      targetVoltage = 5.0 + ((midiNote - 69.0) / 12.0);

      if (voiceType == 1 || portamentoCoeff == 0 || currentVoltage == -1) {
        currentVoltage = targetVoltage;
        changeFrequency(0);
      }

      double frequency =  440.0 * pow(2, (currentVoltage + octave + fine) - 5.0);

      setFrequencyBytes(frequency);
      setFrequency();

      //this->sid->set(MODE_VOL, 0b00001111);

      this->sid->set(SID_VOICE_CONTROL_REG[voice], getControlReg() + 1);
    }

    void noteOff() {
      this->adsrPitch->release();
      this->adsrPW->release();
      this->sid->set(SID_VOICE_CONTROL_REG[voice], getControlReg());
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

      double coeff = 0.95;

      currentVoltage = targetVoltage + portamentoCoeff * (currentVoltage - targetVoltage);

      if (lfoPitchMultiplier != 0) {
        lfoPitch->process();
        pitchModulation = lfoPitchMultiplier * lfoPitch->getOutput() * MAX_PITCH_SWING;
      }

      if (lfoPWMultiplier != 0) {
        lfoPW->process();

        pwModulation = lfoPWMultiplier * lfoPW->getOutput() * MAX_PW_SWING;
      }

      if (adsrPitchMultiplier != 0) {
        adsrPitch->process();

        pitchModulation += adsrPitchMultiplier * adsrPitch->getOutput() * MAX_PITCH_SWING;
      }

      if (adsrPWMultiplier != 0) {
        adsrPW->process();

        pwModulation += adsrPWMultiplier * adsrPW->getOutput() * MAX_PW_SWING;
      }

      if (pitchModulation != 0 || portamentoCoeff > 0) {
        changeFrequency(pitchModulation);
      }

      if (pwModulation != 0) {
        changePulseWidth(pwModulation);
      }
    }

    void setVoiceType(byte voiceType) {
      this->voiceType = max(0, min(2, voiceType));
    }

    // todo: implement a samplerate dependent version: portamentoCoeff = 1 - exp(-2 * pi * portamentoTime / sampleRate)
    void setPortamento(double portamento) {
      double sanitized = max(0, min(1.0, portamento));

      portamentoCoeff = getCurved(sanitized, 0.9);
    }
};

#endif