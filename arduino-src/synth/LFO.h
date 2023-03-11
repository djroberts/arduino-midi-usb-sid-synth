#ifndef LFO_h
#define LFO_h

#include "SidDefines.h"

class LFO {
  private:
    double sampleRate = 100; // hz
    double frequency = 1.0; // hz

    double phase = 0;

    bool resetPhase = true;

    byte shape = 0; // 0  = sin 1 = triangle 2 = pulse

    double attackTime = 0; // ms
    double attackCurve = 0.3;

    double attackAccumulator = 0;

    double output = 0;

    void updatePhase() {
      phase += (frequency / sampleRate);

      if (phase >= 1.0) {
        phase -= 1.0;
      }
    }

    void updateAttackAccumulator() {
      if (attackAccumulator >= 1) {
        return;
      }

      if (attackTime == 0) {
        attackAccumulator = 1.0;

        return;
      }

      double increment = 1.0 / (sampleRate * (attackTime  / 1000.0));

      attackAccumulator += increment;

      if (attackAccumulator >= 1) {
        attackAccumulator = 1.0;
      }
    }

    double getValue() {
      if (shape == 0) {
        return sin(phase * TWO_PI);
      }

      if (shape == 1) {
        double triOffset = phase - 0.25;

        if (phase < 0) {
          phase += 1;
        }

        if (phase < 0.5) {
          return -1 + 4 * phase;
        } else {
          return 1 - 4 * phase;
        }
      }

      if (phase < 0.5) {
        return 1;
      }

      return -1;
    }

  public:
    LFO(double sampleRate) {
      this->sampleRate = sampleRate;
    }

    double reset() {
      if (resetPhase) {
        phase = 0;
      }

      attackAccumulator = 0;
    }

    void setSampleRate(double sampleRate) {
      this->sampleRate = sampleRate;
    }

    void setAttackTime(double ms) {
      attackTime = ms;
    }

    void setFrequency(double frequency) {
      this->frequency = frequency;
    }

    void setShape(byte shape) {
      this->shape = max(0, min(3, shape));
    }

    double process() {
      updatePhase();

      double value = getValue();

      updateAttackAccumulator();

      output = getCurved(attackAccumulator, attackCurve) * value;

      return output;
    }

    void setResetPhase(bool resetPhase) {
       this->resetPhase = resetPhase;
    }

    double getOutput() {
      return output;
    }
};

#endif