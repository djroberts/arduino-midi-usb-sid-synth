#ifndef ADSR_h
#define ADSR_h

#include "SidDefines.h"

class ADSR {
  private:
    double sampleRate = 100.0; // hz

    double attackTime = 0; // ms
    double decayTime = 2000;  // ms
    double sustainLevel = 0.5;
    double releaseTime = 2000; // ms

    double curve = 0.3;

    byte state = 0; // 0 = attack, 1 = decay, 2 = sustain, 3 = release, 4 = complete

    double level = 0;

    handleAttack() {
      level += 1 / (0.001 * attackTime * sampleRate);

      if (level > 1.0) {
        level = 1.0;

        state = 1;
      }
    }

    handleDecay() {
      double target = 1.0 - sustainLevel;

      level -= target * (1 / (0.001 * decayTime * sampleRate));

      if (level <= sustainLevel) {
        level = sustainLevel;
        state = 2;
      }
    }

    handleRelease() {
      // todo: this should not be sustainLevel, but storing the level at release time which may be higher
      level -= sustainLevel * (1 / (0.001 * releaseTime * sampleRate));

      if (level <= 0) {
        level = 0;
        state = 4;
      }
    }

  public:
    ADSR(double sampleRate) {
      this->sampleRate = sampleRate;
    }

    void setSampleRate(double sampleRate) {
      this->sampleRate = sampleRate;
    }

    void setAttackTime(double attackTime) {
      this->attackTime = attackTime;
    }

    void setDecayTime(double decayTime) {
      this->decayTime = decayTime;
    }

    void setSustainLevel(double sustainLevel) {
      this->sustainLevel = sustainLevel;
    }

    void setReleaseTime(double releaseTime) {
      this->releaseTime = releaseTime;
    }

    void reset() {
      state = 0;
    }

    void release() {
      state = 3;
    }

    void process() {
      if (state == 4) {
        level = 0;

        return;
      }

      if (state == 2) {
        return;
      }

      if (state == 0) {
        handleAttack();

        return;
      }

      if (state == 1) {
        handleDecay();
      }

      if (state == 3) {
        handleRelease();
      }
    }

    double getOutput() {
      return getCurved(level, curve) * level;
    }
};

#endif