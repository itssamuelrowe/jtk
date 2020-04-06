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

// Monday, January 14, 2018

#ifndef JTK_NET_CLIENT_SOCKET_H
#define JTK_NET_CLIENT_SOCKET_H

/*******************************************************************************
 * ClientSocket                                                                *
 *******************************************************************************/

/**
 * @class ClientSocket
 * @ingroup jtk_net
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.1
 */
struct jtk_ClientSocket_t {
    void* m_handle;
    int32_t m_port;
    int32_t m_trafficClass;
};

/**
 * @memberof ClientSocket
 */
typedef struct jtk_ClientSocket_t jtk_ClientSocket_t;

/* Constructor */

/**
 * @memberof ClientSocket
 */
jtk_ClientSocket_t* jtk_ClientSocket_new();

/**
 * @memberof ClientSocket
 */
jtk_ClientSocket_t* jtk_ClientSocket_newWithHostAndPort(jtk_String_t* host, int32_t port);

/**
 * @memberof ClientSocket
 */
jtk_ClientSocket_t* jtk_ClientSocket_newWithHostAndPortEx(jtk_String_t* host, int32_t port, jtk_InetAddress_t* localAddress, int32_t localPort);

/**
 * @memberof ClientSocket
 */
jtk_ClientSocket_t* jtk_ClientSocket_newWithAddressAndPort(jtk_InetAddress_t* address, int32_t port);

/**
 * @memberof ClientSocket
 */
jtk_ClientSocket_t* jtk_ClientSocket_newWithAddressAndPortEx(jtk_InetAddress_t* address, int32_t port, jtk_InetAddress_t* localAddress, int32_t localPort);

/* Destructor */

/**
 * @memberof ClientSocket
 */
void jtk_ClientSocket_delete(jtk_ClientSocket_t* socket);

/* Bandwidth */

/**
 * @memberof ClientSocket
 */
void jtk_ClientSocket_setBandwidth(jtk_ClientSocket_t* socket, int32_t bandwidth);

/**
 * @memberof ClientSocket
 */
int32_t jtk_ClientSocket_getBandwidth(jtk_ClientSocket_t* socket);

/* Block Input */

/**
 * @memberof ClientSocket
 */
void jtk_ClientSocket_blockInput(jtk_ClientSocket_t* socket);

/**
 * @memberof ClientSocket
 */
bool jtk_ClientSocket_isInputBlocked(jtk_ClientSocket_t* socket);

/* Block Output */

/**
 * @memberof ClientSocket
 */
void jtk_ClientSocket_blockOutput(jtk_ClientSocket_t* socket);

/**
 * @memberof ClientSocket
 */
bool jtk_ClientSocket_isOutputBlocked(jtk_ClientSocket_t* socket);

/* Close */

/**
 * @memberof ClientSocket
 */
void jtk_ClientSocket_close(jtk_ClientSocket_t* socket);

/**
 * @memberof ClientSocket
 */
bool jtk_ClientSocket_isClosed(jtk_ClientSocket_t* socket);

/* Connect */

/**
 * @memberof ClientSocket
 */
bool jtk_ClientSocket_connect(jtk_ClientSocket_t* socket, jtk_SocketAddress_t* address);

/**
 * @memberof ClientSocket
 */
bool jtk_ClientSocket_connectEx(jtk_ClientSocket_t* socket, jtk_SocketAddress_t* address, int32_t timeout);

/**
 * @memberof ClientSocket
 */
bool jtk_ClientSocket_isConnected(jtk_ClientSocket_t* socket);

/* Connection Time */

/**
 * @memberof ClientSocket
 */
void jtk_ClientSocket_setConnectionTime(jtk_ClientSocket_t* socket, int32_t connectionTime);

/**
 * @memberof ClientSocket
 */
int32_t jtk_ClientSocket_getConnectionTime(jtk_ClientSocket_t* socket);

/* Enable Urgent Data */

/**
 * @memberof ClientSocket
 */
void jtk_ClientSocket_setUrgentDataReceivable(jtk_ClientSocket_t* socket, bool urgentDataReceivable);

/**
 * @memberof ClientSocket
 */
bool jtk_ClientSocket_isUrgentDataReceivable(jtk_ClientSocket_t* socket);

/* Input Stream */

/**
 * @memberof ClientSocket
 */
jtk_InputStream_t* jtk_ClientSocket_getInputStream(jtk_ClientSocket_t* socket);

/* Keep Alive */

/**
 * @memberof ClientSocket
 */
void jtk_ClientSocket_setKeepAlive(jtk_ClientSocket_t* socket, bool keepAlive);

/**
 * @memberof ClientSocket
 */
bool jtk_ClientSocket_getKeepAlive(jtk_ClientSocket_t* socket);

/* Latency */

/**
 * @memberof ClientSocket
 */
void jtk_ClientSocket_setLatency(jtk_ClientSocket_t* socket, int32_t latency);

/**
 * @memberof ClientSocket
 */
int32_t jtk_ClientSocket_getLatency(jtk_ClientSocket_t* socket);

/* Linger */

/**
 * @memberof ClientSocket
 */
void jtk_ClientSocket_setLingerDuration(jtk_ClientSocket_t* socket, int32_t duration);

/**
 * @memberof ClientSocket
 */
bool jtk_ClientSocket_getLingerDuration(jtk_ClientSocket_t* socket);

/* Local Port */

/**
 * @memberof ClientSocket
 */
int32_t jtk_ClientSocket_getLocalPort(jtk_ClientSocket_t* socket);

/* Output Stream */

/**
 * @memberof ClientSocket
 */
void jtk_ClientSocket_getOutputStream(jtk_ClientSocket_t* socket);

/* Receive Buffer Size */

/**
 * @memberof ClientSocket
 */
void jtk_ClientSocket_setReceiveBufferSize(jtk_ClientSocket_t* socket, int32_t receiveBufferSize);

/**
 * @memberof ClientSocket
 */
int32_t jtk_ClientSocket_getReceiveBufferSize(jtk_ClientSocket_t* socket);

/* Remote Port */

/**
 * @memberof ClientSocket
 */
int32_t jtk_ClientSocket_getRemotePort(jtk_ClientSocket_t* socket);

/* Reuse Address */

/**
 * @memberof ClientSocket
 */
void jtk_ClientSocket_setReuseAddress(jtk_ClientSocket_t* socket, bool reuseAddress);

/**
 * @memberof ClientSocket
 */
bool jtk_ClientSocket_canReuseAddress(jtk_ClientSocket_t* socket);

/* Send Buffer Size */

/**
 * @memberof ClientSocket
 */
void jtk_ClientSocket_setSendBufferSize(jtk_ClientSocket_t* socket, int32_t sendBufferSize);

/**
 * @memberof ClientSocket
 */
int32_t jtk_ClientSocket_getSendBufferSize(jtk_ClientSocket_t* socket);

/* TCP No Delay */

/**
 * @memberof ClientSocket
 */
void jtk_ClientSocket_setTcpNoDelay(jtk_ClientSocket_t* socket, bool tcpNoDelay);

/**
 * @memberof ClientSocket
 */
bool jtk_ClientSocket_getTcpNoDelay(jtk_ClientSocket_t* socket);

/* Timeout */

/**
 * @memberof ClientSocket
 */
void jtk_ClientSocket_setTimeout(jtk_ClientSocket_t* socket, int32_t timeout);

/**
 * @memberof ClientSocket
 */
bool jtk_ClientSocket_getTimeout(jtk_ClientSocket_t* socket);

/* Traffic Class */

/**
 * @memberof ClientSocket
 */
void jtk_ClientSocket_setTrafficClass(jtk_ClientSocket_t* socket, int32_t trafficClass);

/**
 * @memberof ClientSocket
 */
int32_t jtk_ClientSocket_getTrafficClass(jtk_ClientSocket_t* socket);

/* Urgent Data */

/**
 * @memberof ClientSocket
 */
void jtk_ClientSocket_sendUrgentData(int32_t data);

#endif /* JTK_NET_CLIENT_SOCKET_H */