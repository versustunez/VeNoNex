# Parameters

a list of all available Parameters and they values

## Base

| name            | id              | Modulate | min | max | default | Type    | Internal ID |
|-----------------|-----------------|----------|-----|-----|---------|---------|-------------|
| Synth Volume    | master__volume  | Yes      | 0   | 1.5 | 1       | Float   | 0           |
| Pitch Wheel     | pitch__wheel    | No       | -1  | 1   | 0       | Float   | 1           |
| Pitch Bend Up   | pitchbend__up   | No       | 0   | 36  | 12      | Integer | 2           |
| Pitch Bend Down | pitchbend__down | No       | 0   | 36  | 12      | Integer | 3           |
 
## Per OSC
{i} is the Index!

| name                   | id                    | Modulate | min  | max  | default  | Type    | Internal ID |
|------------------------|-----------------------|----------|------|------|----------|---------|-------------|
| OSC{i} Active          | osc{i}__active        | No       | 0    | 1    | {i} == 1 | Boolean | 0           |
| OSC{i} Voices          | osc{i}__voices        | No       | 1    | 9    | 1        | Integer | 1           |
| OSC{i} Semitones       | osc{i}__semitones     | No       | -24  | 24   | 0        | Integer | 2           |
| OSC{i} Fine            | osc{i}__cents         | Yes      | -100 | 100  | 0        | Integer | 3           |
| OSC{i} Volume          | osc{i}__level         | Yes      | 0    | 1    | 0.8      | Float   | 4           |
| OSC{i} Pan             | osc{i}__panning       | Yes      | -1   | 1    | 0        | Float   | 5           |
| OSC{i} Detune Amount   | osc{i}__detune_amount | Yes      | 0    | 1    | 0        | Float   | 6           |
| OSC{i} Detune Dense    | osc{i}__detune_dense  | Yes      | 0    | 200  | 0        | Float   | 7           |
| OSC{i} Detune Mode     | osc{i}__detune_mode   | No       | 1    | 3    | 1        | Integer | 8           |
| OSC{i} Phase offset    | osc{i}__phase         | Yes      | 0    | 1    | 0        | Float   | 9           |
| OSC{i} Random Phase    | osc{i}__random_phase  | No       | 0    | 1    | 0        | Boolean | 10          |
| OSC{i} Stereo Wideness | osc{i}__stereo        | Yes      | 0    | 200  | 0        | Float   | 11          |
|                        |                       |          |      |      |          |         |             |
| OSC{i} Attack          | osc{i}__attack        | No       | 0    | 2    | 0.01     | Float   | 12          |
| OSC{i} Decay           | osc{i}__decay         | No       | 0    | 2    | 0        | Float   | 13          |
| OSC{i} Sustain         | osc{i}__sustain       | No       | 0    | 1    | 1        | Float   | 14          |
| OSC{i} Release         | osc{i}__release       | No       | 0    | 2    | 0.01     | Float   | 15          |
|                        |                       |          |      |      |          |         |             |
| OSC{i} Base Waveform   | osc{i}__waveform_base | No       | 1    | 9    | 1        | Integer | 16          |
| OSC{i} Waveform        | osc{i}__waveform      | No       | 1    | 9    | 3        | Integer | 17          |
| OSC{i} Waveform Mix    | osc{i}__waveform_mix  | Yes      | 0    | 1    | 9        | Float   | 18          |

## FX Series
    