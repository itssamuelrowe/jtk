/*
 * Copyright 2017-2020 Samuel Rowe
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

#ifndef JTK_NET_SOCKET_H
#define JTK_NET_SOCKET_H

/*******************************************************************************
 * Socket                                                                      *
 *******************************************************************************/

/**
 * @class Socket
 * @ingroup jtk_net
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.1
 */
struct jtk_Socket_t {
};

/**
 * @memberof Socket
 */
typedef struct jtk_Socket_t jtk_Socket_t;

/* Constructor */

/**
 * @memberof Socket
 */
jtk_Socket_t* jtk_Socket_new();

/* Destructor */

/**
 * @memberof Socket
 */
void jtk_Socket_delete(jtk_Socket_t* socket);

#endif /* JTK_NET_SOCKET_H */