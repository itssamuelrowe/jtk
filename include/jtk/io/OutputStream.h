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