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

#include <jtk/audio/wave/WaveDecoder.h>

/*******************************************************************************
 * WaveDecoder                                                                 *
 *******************************************************************************/

jtk_WaveFile_t* jtk_WaveDecoder_decode(jtk_WaveDecoder_t* decoder,
    jtk_DataInputStream_t* stream) {
    jtk_WaveFile_t* result = jtk_Memory_allocate(jtk_WaveFile_t, 1);

    jtk_WaveDecoder_parseRiffChunk(decoder, stream, &result->m_riffChunk);
    jtk_WaveDecoder_parseFormatChunk(decoder, stream, &result->m_formatChunk);
    jtk_WaveDecoder_parseDataChunk(decoder, stream, &result->m_dataChunk);

    return result;
}

void jtk_WaveDecoder_parseRiffChunk(jtk_WaveDecoder_t* decoder,
    jtk_DataInputStream_t* stream, jtk_RiffChunk_t* chunk) {
    /* The binary representation of the identifier 'RIFF'. It is encoded in
     * ASCII.
     */
    chunk->m_chunkId = jtk_DataInputStream_readIntegerEx(stream, JTK_ENDIAN_BIG);
    if (chunk->m_chunkId == JTK_RIFF_CHUNK_RIFF_IDENTIFIER) {
        /* The default byte ordering scheme for WAVE data files is little-endian. */
        jtk_DataInputStream_setEndian(stream, JTK_ENDIAN_LITTLE);
    }
    else if (chunk->m_chunkId == JTK_RIFF_CHUNK_RIFX_IDENTIFIER) {
        /* Files written using the big-endian byte ordering scheme have the
         * identifier `RIFX` instead of `RIFF`.
         */
        jtk_DataInputStream_setEndian(stream, JTK_ENDIAN_BIG);
    }
    else {
        /* That's an error! Unknown RIFF identifier encountered. */
    }

    /* The number of bytes in the stream following this field. */
    chunk->m_chunkSize = jtk_DataInputStream_readInteger(stream);

    /* The binary representation of the identifier 'WAVE'. It is encoded in
     * ASCII.
     *
     * It is equivalent to the bit pattern represented by the integer value
     * `0x57415645` (big-endian).
     */
    chunk->m_format = jtk_DataInputStream_readInteger(stream);
    if (chunk->m_format != JTK_RIFF_CHUNK_WAVE_IDENTIFIER) {
        /* That's an error! Unknown WAVE identifier encountered. */
    }
}

void jtk_WaveDecoder_parseFormatChunk(jtk_WaveDecoder_t* decoder,
    jtk_DataInputStream_t* stream, jtk_FormatChunk_t* chunk) {
    /* The binary representation of the identifier 'fmt '. It is encoded in
     * ASCII.
     *
     * It is equivalent to the bit pattern represented by the integer value
     * `0x666d7420` (big-endian).
     */
    chunk->m_subchunk1Id = jtk_DataInputStream_readIntegerEx(stream, JTK_ENDIAN_BIG);
    if (chunk->m_subchunk1Id != JTK_FORMAT_CHUNK_FMT_IDENTIFIER) {
        /* That's an error! Unknown format identifier encountered, was expecting
         * "fmt ".
         */
    }

    /* The number of bytes in this subchunk following this field. */
    chunk->m_subchunk1Size = jtk_DataInputStream_readInteger(stream);

    /* For PCM it is 1, that is, linear quantization. Values other than 1
     * indicate some form of compression.
     */
    chunk->m_audioFormat = jtk_DataInputStream_readShort(stream);

    /* The number of channels. */
    chunk->m_numberOfChannels = jtk_DataInputStream_readShort(stream);

    /* The sample rate. */
    chunk->m_sampleRate = jtk_DataInputStream_readInteger(stream);

    /* The byte rate. */
    chunk->m_byteRate = jtk_DataInputStream_readInteger(stream);

    /* The number of bytes for one sample, including all channels. */
    chunk->m_blockAlign = jtk_DataInputStream_readShort(stream);

    /* The number of bits per sample. */
    chunk->m_bitsPerSample = jtk_DataInputStream_readShort(stream);
}

void jtk_WaveDecoder_parseDataChunk(jtk_WaveDecoder_t* decoder,
    jtk_DataInputStream_t* stream, jtk_DataChunk_t* chunk) {
    /* The binary representation of the identifier 'data'. It is encoded in
     * ASCII.
     *
     * It is equivalent to the bit pattern represented by the integer value
     * `0x64617461` (big-endian).
     */
    chunk->m_subchunk2Id = jtk_DataInputStream_readIntegerEx(stream, JTK_ENDIAN_BIG);
    if (chunk->m_subchunk2Id != JTK_DATA_CHUNK_DATA_IDENTIFIER) {
        /* That's an error! Unknown data identifier encountered, was expecting
         * "data".
         */
    }

    /* The number of bytes in this subchunk following this field. */
    chunk->m_subchunk2Size = jtk_DataInputStream_readInteger(stream);
    
    
}
