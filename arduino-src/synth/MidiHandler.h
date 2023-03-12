#ifndef MidiHandler_h
#define MidiHandler_h

#include "SidVoice.h"
#include "MIDIUSB.h"

class MidiHandler {
  public:
    MidiHandler(SidVoice *voice1, LFO *lfoPitch1, LFO *lfoPW1, ADSR *adsrPitch1, ADSR *adsrPW1) {
      this->voice1 = voice1;
      this->lfoPitch1 = lfoPitch1;
      this->lfoPW1 = lfoPW1;
      this->adsrPitch1 = adsrPitch1;
      this->adsrPW1 = adsrPW1;
    }

    void handleMidiMessage(midiEventPacket_t rx) {
      if (rx.header == 9) {
        handleNoteOn(rx);
      }

      if (rx.header == 8) {
        handleNoteOff(rx);
      }

      if (rx.header == 0xb) {
        handleControlChange(rx);
      }
    }

  private:
    SidVoice *voice1;
    LFO *lfoPitch1;
    LFO *lfoPW1;
    ADSR *adsrPitch1;
    ADSR *adsrPW1;

    byte lowByte = 0;

    void handleNoteOn(midiEventPacket_t rx) {
      if (rx.byte1 - 0x90 == 1 || rx.byte1 - 0x90 == 0) {
        this->voice1->handleNoteOn(rx.byte2);
      }
    }

    void handleNoteOff(midiEventPacket_t rx) {
      if (rx.byte1 - 0x80 == 1 || rx.byte1 - 0x80 == 0) {
        this->voice1->handleNoteOff(rx.byte2);
      }
    }

    void handleControlChange(midiEventPacket_t rx) {
      if (rx.byte2 == CC_VOICE_TYPE) {
        handleVoiceType(rx);
      }

      if (rx.byte2 == CC_PORTAMENTO) {
        handlePortamento(rx);
      }

      if (rx.byte2 == CC_AMP_ATTACK) {
        handleAttack(rx);
      }

      if (rx.byte2 == CC_AMP_DECAY) {
        handleDecay(rx);
      }

      if (rx.byte2 == CC_AMP_SUSTAIN) {
        handleSustain(rx);
      }

      if (rx.byte2 == CC_AMP_RELEASE) {
        handleRelease(rx);
      }

      if (rx.byte2 == CC_TRIANGLE) {
        handleTriangle(rx);
      }

      if (rx.byte2 == CC_SAW) {
        handleSaw(rx);
      }

      if (rx.byte2 == CC_PULSE) {
        handlePulse(rx);
      }

      if (rx.byte2 == CC_NOISE) {
        handleNoise(rx);
      }

      if (rx.byte2 == CC_PW_LO_BYTE) {
        handlePulseWidthLowByte(rx);
      }

      if (rx.byte2 == CC_PW_HI_BYTE) {
        handlePulseWidthHighByte(rx);
      }

      if (rx.byte2 == CC_PW_SINGLE_BYTE) {
        handlePulseWithSingleByte(rx);
      }

      if (rx.byte2 == CC_PW_SINGLE_BYTE) {
        handlePulseWithSingleByte(rx);
      }

      if (rx.byte2 == CC_PITCH_LFO_FREQ) {
        handleLFOPitchFreq(rx);
      }

      if (rx.byte2 == CC_PITCH_LFO_SHAPE) {
        handleLFOPitchShape(rx);
      }

      if (rx.byte2 == CC_PITCH_LFO_FREE) {
        handleLFOPitchFree(rx);
      }

      if (rx.byte2 == CC_PITCH_LFO_ATTACK) {
        handleLFOPitchAttack(rx);
      }

      if (rx.byte2 == CC_PITCH_LFO_ENV) {
        handleLFOPitchEnvelope(rx);
      }

      if (rx.byte2 == CC_PW_LFO_FREQ) {
        handleLFOPWFreq(rx);
      }

      if (rx.byte2 == CC_PW_LFO_SHAPE) {
        handleLFOPWShape(rx);
      }

      if (rx.byte2 == CC_PW_LFO_FREE) {
        handleLFOPWFree(rx);
      }

      if (rx.byte2 == CC_PW_LFO_ATTACK) {
        handleLFOPWAttack(rx);
      }

      if (rx.byte2 == CC_PW_LFO_ENV) {
        handleLFOPWEnvelope(rx);
      }

      if (rx.byte2 == CC_PITCH_ADSR_ATTACK) {
        handleADSRPitchAttack(rx);
      }

      if (rx.byte2 == CC_PITCH_ADSR_DECAY) {
        handleADSRPitchDecay(rx);
      }

      if (rx.byte2 == CC_PITCH_ADSR_SUSTAIN) {
        handleADSRPitchSustain(rx);
      }

      if (rx.byte2 == CC_PITCH_ADSR_RELEASE) {
        handleADSRPitchRelease(rx);
      }

      if (rx.byte2 == CC_PITCH_ADSR_ENV) {
        handleADSRPitchEnvelope(rx);
      }

      if (rx.byte2 == CC_PW_ADSR_ATTACK) {
        handleADSRPWAttack(rx);
      }

      if (rx.byte2 == CC_PW_ADSR_DECAY) {
        handleADSRPWDecay(rx);
      }

      if (rx.byte2 == CC_PW_ADSR_SUSTAIN) {
        handleADSRPWSustain(rx);
      }

      if (rx.byte2 == CC_PW_ADSR_RELEASE) {
        handleADSRPWRelease(rx);
      }

      if (rx.byte2 == CC_PW_ADSR_ENV) {
        handleADSRPWEnvelope(rx);
      }

      if (rx.byte2 == CC_OCTAVE) {
        handleOctave(rx);
      }

      if (rx.byte2 == CC_FINE) {
        handleFine(rx);
      }

    }

    SidVoice *getVoice(byte byte1) {
      if (byte1 % 10 == 1) {
        return this->voice1;
      }

      if (byte1 % 10 == 2) {
        return this->voice1;
      }

      return this->voice1;
    }

    LFO *getLFOPitch(byte byte1) {
      if (byte1 % 10 == 1) {
        return this->lfoPitch1;
      }

      if (byte1 % 10 == 2) {
        return this->lfoPitch1;
      }

      return this->lfoPitch1;
    }

    LFO *getLFOPW(byte byte1) {
      if (byte1 % 10 == 1) {
        return this->lfoPW1;
      }

      if (byte1 % 10 == 2) {
        return this->lfoPW1;
      }

      return this->lfoPW1;
    }

    ADSR *getADSRPW(byte byte1) {
      if (byte1 % 10 == 1) {
        return this->adsrPW1;
      }

      if (byte1 % 10 == 2) {
        return this->adsrPW1;
      }

        return this->adsrPW1;
    }

    ADSR *getADSRPitch(byte byte1) {
      if (byte1 % 10 == 1) {
        return this->adsrPitch1;
      }

      if (byte1 % 10 == 2) {
        return this->adsrPitch1;
      }

        return this->adsrPitch1;
    }

    void handleAttack(midiEventPacket_t rx) {
      SidVoice *voice = getVoice(rx.byte1);
      voice->setAttack(min(rx.byte3, 15));
    }

    void handleDecay(midiEventPacket_t rx) {
      SidVoice *voice = getVoice(rx.byte1);
      voice->setDecay(min(rx.byte3, 15));
    }

    void handleSustain(midiEventPacket_t rx) {
      SidVoice *voice = getVoice(rx.byte1);
      voice->setSustain(min(rx.byte3, 15));
    }

    void handleRelease(midiEventPacket_t rx) {
      SidVoice *voice = getVoice(rx.byte1);
      voice->setRelease(min(rx.byte3, 15));
    }

    void handleTriangle(midiEventPacket_t rx) {
      SidVoice *voice = getVoice(rx.byte1);
      voice->setTriangle(!!rx.byte3);
    }

    void handleSaw(midiEventPacket_t rx) {
      SidVoice *voice = getVoice(rx.byte1);
      voice->setSaw(!!rx.byte3);
    }

    void handlePulse(midiEventPacket_t rx) {
      SidVoice *voice = getVoice(rx.byte1);
      voice->setPulse(!!rx.byte3);
    }

    void handleNoise(midiEventPacket_t rx) {
      SidVoice *voice = getVoice(rx.byte1);
      voice->setNoise(!!rx.byte3);
    }

    void handlePulseWidthLowByte(midiEventPacket_t rx) {
      lowByte = rx.byte3;
    }

    void handlePulseWidthHighByte(midiEventPacket_t rx) {
      unsigned int pw = (rx.byte3 << 8) | lowByte;

      SidVoice *voice = getVoice(rx.byte1);
      voice->setPulseWidth(pw);
    }

    void handlePulseWithSingleByte(midiEventPacket_t rx) {
      SidVoice *voice = getVoice(rx.byte1);
      voice->setPulseWidth(rx.byte3 * 32);
    }

    void handleLFOPitchFreq(midiEventPacket_t rx) {
      LFO *lfo = getLFOPitch(rx.byte1);

      double value = (rx.byte3 / 127.0);
      lfo->setFrequency(getCurved(value, 0.2) * MAX_LFO_FREQUENCY);
    }

    void handleLFOPWFreq(midiEventPacket_t rx) {
      LFO *lfo = getLFOPW(rx.byte1);

      double value = (rx.byte3 / 127.0);
      lfo->setFrequency(getCurved(value, 0.2) * MAX_LFO_FREQUENCY);
    }

    void handleLFOPitchShape(midiEventPacket_t rx) {
      LFO *lfo = getLFOPitch(rx.byte1);
      lfo->setShape(max(0, min(3, rx.byte3)));
    }

    void handleLFOPWShape(midiEventPacket_t rx) {
      LFO *lfo = getLFOPW(rx.byte1);
      lfo->setShape(max(0, min(3, rx.byte3)));
    }

    void handleLFOPitchFree(midiEventPacket_t rx) {
      LFO *lfo = getLFOPitch(rx.byte1);
      lfo->setResetPhase(!rx.byte3);
    }

    void handleLFOPWFree(midiEventPacket_t rx) {
      LFO *lfo = getLFOPW(rx.byte1);
      lfo->setResetPhase(!rx.byte3);
    }

    void handleLFOPitchAttack(midiEventPacket_t rx) {
      LFO *lfo = getLFOPitch(rx.byte1);
      lfo->setAttackTime((rx.byte3 / 127.0) * MAX_ATTACK_TIME);
    }

    void handleLFOPWAttack(midiEventPacket_t rx) {
      LFO *lfo = getLFOPW(rx.byte1);
      lfo->setAttackTime((rx.byte3 / 127.0) * MAX_ATTACK_TIME);
    }

    void handleLFOPitchEnvelope(midiEventPacket_t rx) {
      SidVoice *voice = getVoice(rx.byte1);

      float value = (rx.byte3 - 63.0) / 63.0;

      voice->setLFOPitchMultiplier(getCurved(value, 0.1));
    }

    void handleLFOPWEnvelope(midiEventPacket_t rx) {
      SidVoice *voice = getVoice(rx.byte1);

      float value = (rx.byte3 - 63.0) / 63.0;

      voice->setLFOPWMultiplier(getCurved(value, 0.1));
    }

    void handleADSRPitchAttack(midiEventPacket_t rx) {
      ADSR *adsr = getADSRPitch(rx.byte1);
      adsr->setAttackTime((rx.byte3 / 127.0) * MAX_ATTACK_TIME);
    }

    void handleADSRPitchDecay(midiEventPacket_t rx) {
      ADSR *adsr = getADSRPitch(rx.byte1);
      adsr->setDecayTime((rx.byte3 / 127.0) * MAX_DECAY_TIME);
    }

    void handleADSRPitchRelease(midiEventPacket_t rx) {
      ADSR *adsr = getADSRPitch(rx.byte1);
      adsr->setReleaseTime((rx.byte3 / 127.0) * MAX_RELEASE_TIME);
    }

    void handleADSRPitchSustain(midiEventPacket_t rx) {
      ADSR *adsr = getADSRPitch(rx.byte1);
      adsr->setSustainLevel((rx.byte3 / 127.0));
    }

    void handleADSRPitchEnvelope(midiEventPacket_t rx) {
      SidVoice *voice = getVoice(rx.byte1);

      float value = (rx.byte3 - 63.0) / 63.0;

      voice->setADSRPitchMultiplier(getCurved(value, 0.6));
    }

    void handleADSRPWAttack(midiEventPacket_t rx) {
      ADSR *adsr = getADSRPW(rx.byte1);
      adsr->setAttackTime((rx.byte3 / 127.0) * MAX_ATTACK_TIME);
    }

    void handleADSRPWDecay(midiEventPacket_t rx) {
      ADSR *adsr = getADSRPW(rx.byte1);
      adsr->setDecayTime((rx.byte3 / 127.0) * MAX_DECAY_TIME);
    }

    void handleADSRPWRelease(midiEventPacket_t rx) {
      ADSR *adsr = getADSRPW(rx.byte1);
      adsr->setReleaseTime((rx.byte3 / 127.0) * MAX_RELEASE_TIME);
    }

    void handleADSRPWSustain(midiEventPacket_t rx) {
      ADSR *adsr = getADSRPW(rx.byte1);
      adsr->setSustainLevel((rx.byte3 / 127.0));
    }

    void handleADSRPWEnvelope(midiEventPacket_t rx) {
      SidVoice *voice = getVoice(rx.byte1);

      float value = (rx.byte3 - 63.0) / 63.0;

      voice->setADSRPWMultiplier(getCurved(value, 0.6));
    }

    void handleOctave(midiEventPacket_t rx) {
      SidVoice *voice = getVoice(rx.byte1);

      voice->setOctave(rx.byte3 - 2.0);
    }

    void handleFine(midiEventPacket_t rx) {
      SidVoice *voice = getVoice(rx.byte1);

      float value = (rx.byte3 - 63.0) / 63.0;

      voice->setFine(getCurved(value, 0.3));
    }

    void handlePortamento(midiEventPacket_t rx) {
      SidVoice *voice = getVoice(rx.byte1);
      voice->setPortamento((rx.byte3 / 127.0));
    }

    void handleVoiceType(midiEventPacket_t rx) {
      SidVoice *voice = getVoice(rx.byte1);
      voice->setVoiceType(rx.byte3);
    }
};

#endif
