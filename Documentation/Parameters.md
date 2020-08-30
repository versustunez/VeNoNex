# Parameters

a list of all available Parameters and they values

## Base

| name            | id              | Modulate | min | max | default | Type    |
|-----------------|-----------------|----------|-----|-----|---------|---------|
| Synth Volume    | master__volume  | Yes      | 0   | 1.5 | 1       | Float   |
| Pitch Wheel     | pitch__wheel    | No       | -1  | 1   | 0       | Float   |
| Pitch Bend Up   | pitchbend__up   | No       | 0   | 36  | 12      | Integer |
| Pitch Bend Down | pitchbend__down | No       | 0   | 36  | 12      | Integer |
| MOD1            | mod1            | No       | 0   | 1   | 0       | Float   |
| MOD2            | mod2            | No       | 0   | 1   | 0       | Float   |
| MOD3            | mod3            | No       | 0   | 1   | 0       | Float   |
| MOD4            | mod4            | No       | 0   | 1   | 0       | Float   |
 
## Per OSC
{i} is the Index!

| name                      | id                    | Modulate | min  | max  | default  | Type    |
|---------------------------|-----------------------|----------|------|------|----------|---------|
| OSC{i} Active             | osc{i}__active        | No       | 0    | 1    | {i} == 1 | Boolean |
| OSC{i} Voices             | osc{i}__voices        | No       | 1    | 9    | 1        | Integer |
| OSC{i} Semitones          | osc{i}__semitones     | No       | -24  | 24   | 0        | Integer |
| OSC{i} Fine               | osc{i}__cents         | Yes      | -100 | 100  | 0        | Integer |
| OSC{i} Volume             | osc{i}__level         | Yes      | 0    | 1    | 0.8      | Float   |
| OSC{i} Pan                | osc{i}__panning       | Yes      | -1   | 1    | 0        | Float   |
| OSC{i} Detune Amount      | osc{i}__detune_amount | Yes      | 0    | 1    | 0        | Float   |
| OSC{i} Detune Dense       | osc{i}__detune_dense  | Yes      | 0    | 200  | 0        | Float   |
| OSC{i} Detune Mode        | osc{i}__detune_mode   | No       | 1    | 3    | 1        | Integer |
| OSC{i} Phase offset       | osc{i}__phase         | Yes      | 0    | 1    | 0        | Float   |
| OSC{i} Random Phase       | osc{i}__random_phase  | No       | 0    | 1    | 0        | Boolean |
| OSC{i} Stereo Wideness    | osc{i}__stereo        | Yes      | 0    | 200  | 0        | Float   |
|                           |                       |          |      |      |          |         |
| OSC{i} Attack             | osc{i}__attack        | No       | 0    | 2    | 0.01     | Float   |
| OSC{i} Decay              | osc{i}__decay         | No       | 0    | 2    | 0        | Float   |
| OSC{i} Sustain            | osc{i}__sustain       | No       | 0    | 1    | 1        | Float   |
| OSC{i} Release            | osc{i}__release       | No       | 0    | 2    | 0.01     | Float   |
|                           |                       |          |      |      |          |         |
| OSC{i} Waveform Primary   | osc{i}__waveform_base | No       | 1    | 9    | 1        | Integer |
| OSC{i} Waveform Secondary | osc{i}__waveform_sec  | No       | 1    | 9    | 3        | Integer |
| OSC{i} Waveform Mix       | osc{i}__waveform_mix  | Yes      | 0    | 1    | 9        | Float   |

## LFO

| name                      | id                    | Modulate | min  | max  | default  | Type    |
|---------------------------|-----------------------|----------|------|------|----------|---------|
| LFO{i} Active             | lfo{i}__active        | No       | 0    | 1    | 1        | Boolean |
| LFO{i} Voices             | lfo{i}__voices        | No       | 1    | 9    | 1        | Integer |
| LFO{i} Rate               | lfo{i}__rate          | Yes      | 0    | 30   | 0        | Float   |
| LFO{i} Volume             | lfo{i}__level         | Yes      | 0    | 1    | 0.8      | Float   |
| LFO{i} Detune Amount      | lfo{i}__detune_amount | Yes      | 0    | 1    | 0        | Float   |
| LFO{i} Detune Dense       | lfo{i}__detune_dense  | Yes      | 0    | 200  | 0        | Float   |
| LFO{i} Detune Mode        | lfo{i}__detune_mode   | No       | 1    | 3    | 1        | Integer |
| LFO{i} Phase offset       | lfo{i}__phase         | Yes      | 0    | 1    | 0        | Float   |
| LFO{i} Random Phase       | lfo{i}__random_phase  | No       | 0    | 1    | 0        | Boolean |
|                           |                       |          |      |      |          |         |
| LFO{i} Waveform Primary   | lfo{i}__waveform_base | No       | 1    | 9    | 1        | Integer |
| LFO{i} Waveform Secondary | lfo{i}__waveform_sec  | No       | 1    | 9    | 3        | Integer |
| LFO-{i} Waveform Mix       | lfo{i}__waveform_mix  | Yes      | 0    | 1    | 9        | Float   |

## FX Series
    