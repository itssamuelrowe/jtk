// Tuesday, July 31, 2018

#ifndef JTK_IO_OUTPUT_STREAM_H
#define JTK_IO_OUTPUT_STREAM_H

/*******************************************************************************
 * OutputStream                                                                *
 *******************************************************************************/

/**
 * A stream represents a sequence of bytes flowing in a particular direction,
 * that is, either as Output stream or output stream. A stream is considered as
 * an output stream if you are writing bytes to the stream. Similarly, a stream
 * is considered as an Output stream if you are reading bytes from the stream.
 * In either case, streams are abstract in nature and may be associated with
 * files, sockets, strings, arrays, etc.
 *
 * @class OutputStream
 * @ingroup jtk_io
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.1
 */
struct jtk_OutputStream_t {
};

/**
 * @memberof OutputStream
 */
typedef struct jtk_OutputStream_t jtk_OutputStream_t;
 
/* Constructor */

jtk_OutputStream_t* jtk_OutputStream_new();

/* Destructor */

/**
 * @memberof 
 */
void jtk_OutputStream_delete(jtk_OutputStream_t* stream);
 
#endif /* JTK_IO_OUTPUT_STREAM_H */