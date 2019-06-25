/*
 * Copyright 2018-2019 OneCube
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// Tuesday, October 09, 2018

#ifndef JTK_AUDIO_WAVE_WAVE_DECODER_H
#define JTK_AUDIO_WAVE_WAVE_DECODER_H

/*******************************************************************************
 * WaveDecoder                                                                 *
 *******************************************************************************/

/**
 * @class WaveDecoder
 * @ingroup jtk_audio_wave
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.0
 */
struct jtk_WaveDecoder_t {
};

/**
 * @memberof WaveDecoder
 */
typedef struct jtk_WaveDecoder_t jtk_WaveDecoder_t;

/* Constructor */

/**
 * @memberof WaveDecoder
 */
jtk_WaveDecoder_t* jtk_WaveDecoder_new();

/* Destructor */

/**
 * @memberof WaveDecoder
 */
void jtk_WaveDecoder_delete(jtk_WaveDecoder_t* decoder);


jtk_WaveFile_t* jtk_WaveDecoder_decode(jtk_WaveDecoder_t* decoder, jtk_DataInputStream_t* stream);

#endif /* JTK_AUDIO_WAVE_WAVE_DECODER_H */