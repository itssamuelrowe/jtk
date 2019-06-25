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

// Saturday, January 12, 2019

#include <jtk/net/ServerSocket.h>

/*******************************************************************************
 * ServerSocket                                                                *
 *******************************************************************************/

/* Accept */

jtk_Socket_t* jtk_ServerSocket_accept(jtk_ServerSocket_t* socket) {
    jtk_Assert_assertObject(socket, "The specified server socket is null.");
    
    jtk_Socket_t* result = NULL;
    if ((socket->m_status & JTK_SOCKET_STATUS_OPEN) == 0) {
        jtk_Runtime_addError(JTK_ERROR_ILLEGAL_SERVER_SOCKET_STATE, "The server socket was previously closed.", NULL);
    }
    else if ((socket->m_status & JTK_SOCKET_STATUS_BOUND) == 1) {
        jtk_Runtime_reportError(JTK_ERROR_ILLEGAL_SERVER_SOCKET_STATE, "The server socket was previously bound.", NULL);
    }
    else {
        result = jtk_NativeServerSocket_accept(socket->m_handle);
    }
    return result;
}

bool jtk_ServerSocket_hasAccepted(jtk_ServerSocket_t* socket) {
    jtk_Assert_assertObject(socket, "The specified server socket is null.");
    
    return (socket->m_status & JTK_SOCKET_STATUS_ACCEPTED) != 0;
}

/* Backlog */

void jtk_ServerSocket_setBacklog(jtk_ServerSocket_t* socket, int32_t backlog) {
    jtk_Assert_assertObject(socket, "The specified server socket is null.");
    
    if ((socket->m_status & JTK_SOCKET_STATUS_OPEN) == 0) {
        jtk_Runtime_reportError(JTK_ERROR_ILLEGAL_SERVER_SOCKET_STATE, "The server socket was previously closed.", NULL);
    }
    else {
        socket->m_backlog = backlog;
    }
}

int32_t jtk_ServerSocket_getBacklog(jtk_ServerSocket_t* socket) {
    jtk_Assert_assertObject(socket, "The specified server socket is null.");
    
    return socket->m_backlog;
}

/* Close */

bool jtk_ServerSocket_isClosed(jtk_ServerSocket_t* socket) {
    jtk_Assert_assertObject(socket, "The specified server socket is null.");
    
    return (socket->m_status & JTK_SOCKET_STATUS_OPEN) == 0;
}

void jtk_ServerSocket_close(jtk_ServerSocket_t* socket) {
    jtk_Assert_assertObject(socket, "The specified server socket is null.");
    
    if ((socket->m_status & JTK_SOCKET_STATUS_OPEN) == 0) {
        jtk_Runtime_reportWarning(JTK_WARNING_ILLEGAL_SERVER_SOCKET_STATE, "The server socket was previously closed.", NULL);
    }
    else {
        socket->m_status &= ~JTK_SOCKET_STATUS_CLOSE;
        jtk_NativeServerSocket_close(socket->handle);
    }
}

/* Bandwidth */

void jtk_ServerSocket_setBandwidth(jtk_ServerSocket_t* socket, int32_t bandwidth) {
    jtk_Assert_assertObject(socket, "The specified server socket is null.");
    
    if ((socket->m_status & JTK_SOCKET_STATUS_OPEN) == 0) {
        jtk_Runtime_reportError(JTK_ERROR_ILLEGAL_SERVER_SOCKET_STATE, "The server socket was previously closed.", NULL);
    }
    else {
        socket->m_bandwidth = bandwidth;
    }
}

int32_t jtk_ServerSocket_getBandwidth(jtk_ServerSocket_t* socket) {
    jtk_Assert_assertObject(socket, "The specified server socket is null.");
    
    return socket->m_bandwidth;
}

/* Connection Time */

void jtk_ServerSocket_setConnectionTime(jtk_ServerSocket_t* socket, int32_t connectionTime) {
    jtk_Assert_assertObject(socket, "The specified server socket is null.");
    
    if ((socket->m_status & JTK_SOCKET_STATUS_OPEN) == 0) {
        jtk_Runtime_reportError(JTK_ERROR_ILLEGAL_SERVER_SOCKET_STATE, "The server socket was previously closed.", NULL);
    }
    else {
        socket->m_connectionTime = connectionTime;
    }
}

int32_t jtk_ServerSocket_getConnectionTime(jtk_ServerSocket_t* socket) {
    jtk_Assert_assertObject(socket, "The specified server socket is null.");
    
    return socket->m_connectionTime;
}

/* Latency */

void jtk_ServerSocket_setLatency(jtk_ServerSocket_t* socket, int32_t latency) {
    jtk_Assert_assertObject(socket, "The specified server socket is null.");
    
    if ((socket->m_status & JTK_SOCKET_STATUS_OPEN) == 0) {
        jtk_Runtime_reportError(JTK_ERROR_ILLEGAL_SERVER_SOCKET_STATE, "The server socket was previously closed.", NULL);
    }
    else {
        socket->m_latency = latency;
    }
}

int32_t jtk_ServerSocket_getLatency(jtk_ServerSocket_t* socket) {
    jtk_Assert_assertObject(socket, "The specified server socket is null.");
    
    return socket->m_latency;
}

/* Receive Buffer Size */

void jtk_ServerSocket_setReceiveBufferSize(jtk_ServerSocket_t* socket, int32_t receiveBufferSize) {
    jtk_Assert_assertObject(socket, "The specified server socket is null.");
    
    if ((socket->m_status & JTK_SOCKET_STATUS_OPEN) == 0) {
        jtk_Runtime_reportError(JTK_ERROR_ILLEGAL_SERVER_SOCKET_STATE, "The server socket was previously closed.", NULL);
    }
    else {
        socket->m_receiveBufferSize = receiveBufferSize;
    }
}

int32_t jtk_ServerSocket_getReceiveBufferSize(jtk_ServerSocket_t* socket) {
    jtk_Assert_assertObject(socket, "The specified server socket is null.");
    
    return socket->m_receiveBufferSize;
}

/* Reuse Address */

void jtk_ServerSocket_setReuseAddress(jtk_ServerSocket_t* socket, bool reuseAddress) {
    jtk_Assert_assertObject(socket, "The specified server socket is null.");
    
    if ((socket->m_status & JTK_SOCKET_STATUS_OPEN) == 0) {
        jtk_Runtime_reportError(JTK_ERROR_ILLEGAL_SERVER_SOCKET_STATE, "The server socket was previously closed.", NULL);
    }
    else {
        socket->m_reuseAddress = reuseAddress;
    }
}

bool jtk_ServerSocket_canReuseAddress(jtk_ServerSocket_t* socket) {
    jtk_Assert_assertObject(socket, "The specified server socket is null.");
    
    return socket->m_reuseAddress;
}

/* Server Socket Factory */

void jtk_ServerSocket_setServerSocketFactory(jtk_ServerSocket_t* socket, jtk_ServerSocketFactory_t* serverSocketFactory) {
    jtk_Assert_assertObject(socket, "The specified server socket is null.");
    jtk_Assert_assertObject(serverSocketFactory, "The specified server socket factory is null.");
    
    if ((socket->m_status & JTK_SOCKET_STATUS_OPEN) == 0) {
        jtk_Runtime_reportError(JTK_ERROR_ILLEGAL_SERVER_SOCKET_STATE, "The server socket was previously closed.", NULL);
    }
    else {
        socket->m_serverSocketFactory = serverSocketFactory;
    }
}

jtk_ServerSocketFactory_t* jtk_ServerSocket_getServerSocketFactory(jtk_ServerSocket_t* socket) {
    jtk_Assert_assertObject(socket, "The specified server socket is null.");
    
    return socket->m_serverSocketFactory;
}

/* Timeout */

void jtk_ServerSocket_setTimeout(jtk_ServerSocket_t* socket, int32_t timeout) {
    jtk_Assert_assertObject(socket, "The specified server socket is null.");
    jtk_Assert_assertTrue(timeout >= 0, "The specified timeout is invalid.");
    
    if ((socket->m_status & JTK_SOCKET_STATUS_OPEN) == 0) {
        jtk_Runtime_reportError(JTK_ERROR_ILLEGAL_SERVER_SOCKET_STATE, "The server socket was previously closed.", NULL);
    }
    else {
        socket->m_timeout = timeout;
    }
}

int32_t jtk_ServerSocket_getTimeout(jtk_ServerSocket_t* socket) {
    jtk_Assert_assertObject(socket, "The specified server socket is null.");
    
    return socket->m_timeout;
}