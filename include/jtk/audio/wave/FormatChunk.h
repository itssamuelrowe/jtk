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

#ifndef JTK_AUDIO_WAVE_FORMAT_CHUNK_H
#define JTK_AUDIO_WAVE_FORMAT_CHUNK_H

/*******************************************************************************
 * FormatChunk                                                                 *
 *******************************************************************************/

#define JTK_FORMAT_CHUNK_FMT_IDENTIFIER 0x666d7420
 
/**
 * @class FormatChunk
 * @ingroup jtk_audio_wave
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.0
 */
struct jtk_FormatChunk_t {
    /**
     * The binary representation of the identifier 'fmt '. It is encoded in
     * ASCII.
     *
     * It is equivalent to the bit pattern represented by the integer value
     * `0x666d7420` (big-endian).
     *
     * It is stored in the big-endian byte ordering scheme.
     */
    uint32_t m_subchunk1Id;

    /**
     * The number of bytes in this subchunk following this field.
     *
     * It is 16 for PCM.
     *
     * It is stored in the little-endian byte ordering scheme.
     */
    uint32_t m_subchunk1Size;

    /**
     * For PCM it is 1, that is, linear quantization.
     * Values other than 1 indicate some form of compression.
     *
     * It is stored in the little-endian byte ordering scheme.
     */
    uint16_t m_audioFormat;

    /**
     * The number of channels.
     *
     * It is stored in the little-endian byte ordering scheme.
     */
    uint16_t m_numberOfChannels;

    /**
     * It is stored in the little-endian byte ordering scheme.
     */
    uint32_t m_sampleRate;

    /**
     * `m_sampleRate * m_numberOfChannels * m_bitsPerSample / 8`
     *
     * It is stored in the little-endian byte ordering scheme.
     */
    uint32_t m_byteRate;

    /**
     * The number of bytes for one sample, including all channels.
     *
     * It is stored in the little-endian byte ordering scheme.
     */
    uint16_t m_blockAlign;

    /**
     * The number of bits per sample.
     *
     * It is stored in the little-endian byte ordering scheme.
     */
    uint16_t m_bitsPerSample;
};

/**
 * @memberof FormatChunk
 */
typedef struct jtk_FormatChunk_t jtk_FormatChunk_t;

#endif /* JTK_AUDIO_WAVE_FORMAT_CHUNK_H */