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