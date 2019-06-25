// Tuesday, October 09, 2018

#ifndef JTK_AUDIO_WAVE_DATA_CHUNK_H
#define JTK_AUDIO_WAVE_DATA_CHUNK_H

/*******************************************************************************
 * DataChunk                                                                   *
 *******************************************************************************/

#define JTK_DATA_CHUNK_DATA_IDENTIFIER 0x64617461
 
/**
 * @class DataChunk
 * @ingroup jtk_audio_wave
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.0
 */
struct jtk_DataChunk_t {

    /**
     * The binary representation of the identifier 'data'. It is encoded in
     * ASCII.
     *
     * It is equivalent to the bit pattern represented by the integer value
     * `0x64617461` (big-endian).
     *
     * It is stored in the big-endian byte ordering scheme.
     */
    uint32_t m_subchunk2Id;


    /**
     * The number of bytes in this subchunk following this field.
     *
     * It is evaluated with the following formula:
     * `numberOfSamples * m_numberOfChannels * m_bitsPerSample / 8`.
     *
     * It is stored in the little-endian byte ordering scheme.
     */
    uint32_t m_subchunk2Size;

    /**
     * The actual sound data.
     */
    uint8_t* m_data;
};

/**
 * @memberof DataChunk
 */
typedef struct jtk_DataChunk_t jtk_DataChunk_t;

#endif /* JTK_AUDIO_WAVE_DATA_CHUNK_H */