#ifndef SidDefines_H
#define SidDefines_H

#define getCurved(x, a) (x/(x+(1-1/a)*(x-1))) // 0.5 = straight, < 0.5 = slow start, fast end, > 0.5 = fast start, slow end

#define MAX_LFO_FREQUENCY 10.0
#define MAX_ATTACK_TIME 5000.0
#define MAX_DECAY_TIME 5000.0
#define MAX_RELEASE_TIME 5000.0
#define MAX_PW_SWING 2048.0

#define MODULATION_INTERRUPT_ENABLED  false
#define MODULATION_SAMPLERATE  100.0  // leave at 100 for interrupt enabled

#define MIDI_CHANNEL_VOICE_1  0 // midi channel - 1
#define MIDI_CHANNEL_VOICE_2  1
#define MIDI_CHANNEL_VOICE_3  2

#define MIDI_CHANNEL_FILTER 1
#define MIDI_CHANNEL_FILTER_GATE 1

#define CC_VOICE_TYPE 7 // on MIDI Channel 1 --- 1 = single voice, 2 = two voices / oscillators 3 = thtree voices / oscillators
#define CC_VOICE_PITCH_OFFSET 8

#define CC_AMP_ATTACK 9
#define CC_AMP_DECAY 10
#define CC_AMP_SUSTAIN 11
#define CC_AMP_RELEASE 12

#define CC_TRIANGLE 13
#define CC_SAW 14
#define CC_PULSE 15
#define CC_NOISE 16

#define CC_SYNC 17
#define CC_RING_MOD 18

#define CC_FINE 19
#define CC_OCTAVE 20

#define CC_PW_SINGLE_BYTE 21
#define CC_PW_LO_BYTE 22
#define CC_PW_HI_BYTE 23

#define CC_PITCH_LFO_FREQ 24
#define CC_PITCH_LFO_SHAPE 25
#define CC_PITCH_LFO_FREE 26
#define CC_PITCH_LFO_ATTACK 27
#define CC_PITCH_LFO_ENV 28 // 63 = 0

#define CC_PITCH_ADSR_ATTACK 29
#define CC_PITCH_ADSR_DECAY 30
#define CC_PITCH_ADSR_SUSTAIN 31
#define CC_PITCH_ADSR_RELEASE 32
#define CC_PITCH_ADSR_ENV 33

#define CC_PW_LFO_FREQ 34
#define CC_PW_LFO_SHAPE 35
#define CC_PW_LFO_FREE 36
#define CC_PW_LFO_ATTACK 37
#define CC_PW_LFO_ENV 38 // 63 = 0

#define CC_PW_ADSR_ATTACK 39
#define CC_PW_ADSR_DECAY 40
#define CC_PW_ADSR_SUSTAIN 41
#define CC_PW_ADSR_RELEASE 42
#define CC_PW_ADSR_ENV 43

#define CC_VOICE_TYPE_2 44 // 0 = MONO 1 = MONO LEGATO 2 = ARP

#define CC_TABLE_ENABLED 45 // Always disabled if ARP enabled

#define CC_ARP_SPEED 46
#define CC_ARP_TYPE 47 // 0 = loop up 1 = loop down 2 = ping pong
#define CC_ARP_OCTAVES 48

#define CC_TABLE_SPEED 49
#define CC_TABLE_LENGTH 50 // 0 to 12
#define CC_TABLE_TYPE 51 // 0 = once 1 = loop 2 = ping pong

#define CC_TABLE_WAVEFORM_1 52 // 0 = tri 1 = saw 2 = pulse 3 = noise
#define CC_TABLE_WAVEFORM_2 53
#define CC_TABLE_WAVEFORM_3 54
#define CC_TABLE_WAVEFORM_4 55
#define CC_TABLE_WAVEFORM_5 56
#define CC_TABLE_WAVEFORM_6 57
#define CC_TABLE_WAVEFORM_7 58
#define CC_TABLE_WAVEFORM_8 59
#define CC_TABLE_WAVEFORM_9 60
#define CC_TABLE_WAVEFORM_10 61
#define CC_TABLE_WAVEFORM_11 62
#define CC_TABLE_WAVEFORM_12 63

#define CC_TABLE_PW_1     64  // 0 = center 127 = end
#define CC_TABLE_PW_2     65
#define CC_TABLE_PW_3     66
#define CC_TABLE_PW_4     67
#define CC_TABLE_PW_5     68
#define CC_TABLE_PW_6     69
#define CC_TABLE_PW_7     70
#define CC_TABLE_PW_8     71
#define CC_TABLE_PW_9     72
#define CC_TABLE_PW_10    73
#define CC_TABLE_PW_11    74
#define CC_TABLE_PW_12    75

#define CC_TABLE_PITCH_1  76  // half steps 63 = center
#define CC_TABLE_PITCH_2  77
#define CC_TABLE_PITCH_3  78
#define CC_TABLE_PITCH_4  79
#define CC_TABLE_PITCH_5  80
#define CC_TABLE_PITCH_6  81
#define CC_TABLE_PITCH_7  82
#define CC_TABLE_PITCH_8  83
#define CC_TABLE_PITCH_9  84
#define CC_TABLE_PITCH_10 85
#define CC_TABLE_PITCH_11 86
#define CC_TABLE_PITCH_12 87

#endif