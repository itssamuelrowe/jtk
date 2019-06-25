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

#ifndef JTK_AUDIO_WAVE_WAVE_FILE_H
#define JTK_AUDIO_WAVE_WAVE_FILE_H

#include <jtk/Configuration.h>
#include <jtk/audio/wave/DataChunk.h>
#include <jtk/audio/wave/FormatChunk.h>
#include <jtk/audio/wave/RiffChunk.h>

/*******************************************************************************
 * WaveFile                                                                    *
 *******************************************************************************/

/**
 * RIFF stands for *Resource Interchange File Format*.
 *
 * The default byte ordering scheme for WAVE data files is little-endian.
 * Files written using the big-endian byte ordering scheme have the identifier
 * `RIFX` instead of `RIFF`.
 *
 * The canonical WAVE format begins with the RIFF header.
 *
 * Further, the WAVE format consists of two subchunks: `fmt` and `data`. The `fmt`
 * subchunk describes the format of the sound data. The `data` subchunk
 * contains the size of the data and the actual sound data.
 *
 * @class WaveFile
 * @ingroup jtk_audio_wave
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.0
 */
struct jtk_WaveFile_t {

    /**
     * The canonical WAVE format starts with the RIFF header.
     */
    jtk_RiffChunk_t m_riffChunk;

    /**
     * The `fmt` subchunk describes the format of the sound data.
     */
    jtk_FormatChunk_t m_formatChunk;

    /**
     * The `data` subchunk contains the size of the data and the actual sound
     * data.
     */
    jtk_DataChunk_t m_dataChunk;
};

/**
 * @memberof WaveFile
 */
typedef struct jtk_WaveFile_t jtk_WaveFile_t;

#endif /* JTK_AUDIO_WAVE_WAVE_FILE_H */