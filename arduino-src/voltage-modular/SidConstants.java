package com.goblin.utils;

public class SidConstants {
    public static final byte CC_VOICE_TYPE = 7; // on MIDI Channel 1 --- 1 = single voice, 2 = two voices / oscillators 3 = thtree voices / oscillators
    public static final byte CC_VOICE_PITCH_OFFSET = 8;

    public static final byte CC_AMP_ATTACK = 9;
    public static final byte CC_AMP_DECAY = 10;
    public static final byte CC_AMP_SUSTAIN = 11;
    public static final byte CC_AMP_RELEASE = 12;
    
    public static final byte CC_TRIANGLE = 13;
    public static final byte CC_SAW = 14;
    public static final byte CC_PULSE = 15;
    public static final byte CC_NOISE = 16;
    
    public static final byte CC_SYNC = 17;
    public static final byte CC_RING_MOD = 18;
    
    public static final byte CC_FINE = 19;
    public static final byte CC_OCTAVE = 20;
    
    public static final byte CC_PW_SINGLE_BYTE = 21;
    public static final byte CC_PW_LO_BYTE = 22;
    public static final byte CC_PW_HI_BYTE = 23;

    public static final byte CC_PITCH_LFO_FREQ = 24;
    public static final byte CC_PITCH_LFO_SHAPE = 25;
    public static final byte CC_PITCH_LFO_FREE = 26;
    public static final byte CC_PITCH_LFO_ATTACK = 27;
    public static final byte CC_PITCH_LFO_ENV = 28; // 63 = 0

    public static final byte CC_PITCH_ADSR_ATTACK = 29;
    public static final byte CC_PITCH_ADSR_DECAY = 30;
    public static final byte CC_PITCH_ADSR_SUSTAIN = 31;
    public static final byte CC_PITCH_ADSR_RELEASE = 32;
    public static final byte CC_PITCH_ADSR_ENV = 33;

    public static final byte CC_PW_LFO_FREQ = 34;
    public static final byte CC_PW_LFO_SHAPE = 35;
    public static final byte CC_PW_LFO_FREE = 36;
    public static final byte CC_PW_LFO_ATTACK = 37;
    public static final byte CC_PW_LFO_ENV = 38; // 63 = 0

    public static final byte CC_PW_ADSR_ATTACK = 39;
    public static final byte CC_PW_ADSR_DECAY = 40;
    public static final byte CC_PW_ADSR_SUSTAIN = 41;
    public static final byte CC_PW_ADSR_RELEASE = 42;
    public static final byte CC_PW_ADSR_ENV = 43;
}