// Tuesday, October 09, 2018

#ifndef JTK_AUDIO_WAVE_RIFF_CHUNK_H
#define JTK_AUDIO_WAVE_RIFF_CHUNK_H

/*******************************************************************************
 * RiffChunk                                                                   *
 *******************************************************************************/

#define JTK_RIFF_CHUNK_RIFF_IDENTIFIER 0x52494646
#define JTK_RIFF_CHUNK_RIFX_IDENTIFIER 0x52494658
#define JTK_RIFF_CHUNK_WAVE_IDENTIFIER 0x57415645
 
/**
 * @class RiffChunk
 * @ingroup jtk_audio_wave
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.0
 */
struct jtk_RiffChunk_t {
    /**
     * The binary representation of the identifier RIFF (little-endian) or
     * RIFX (big-endian). It is encoded in ASCII.
     *
     * It is stored in the big-endian byte ordering scheme.
     *
     * It is equivalent to `0x52494646` for RIFF and `` for RIFX.
     */
    uint32_t m_chunkId;

    /**
     * The number of bytes in the stream following this field.
     * This is the size of the entire stream in bytes minus 8 bytes for the
     * first two fields, that is, `m_chunkId` and `m_chunkSize`.
     *
     * It is evaluated with the follow formula:
     * `4 + (8 + m_subChunk1Size) + (8 + m_subChunk2Size)`
     *
     * It is stored in the little-endian byte ordering scheme.
     */
    uint32_t m_chunkSize;

    /**
     * The binary representation of the identifier 'WAVE'. It is encoded in
     * ASCII.
     *
     * It is equivalent to the bit pattern represented by the integer value
     * `0x57415645` (big-endian).
     *
     * It is stored in the big-endian byte ordering scheme.
     */
    uint32_t m_format;
};

/**
 * @memberof RiffChunk
 */
typedef struct jtk_RiffChunk_t jtk_RiffChunk_t;

#endif /* JTK_AUDIO_WAVE_RIFF_CHUNK_H */