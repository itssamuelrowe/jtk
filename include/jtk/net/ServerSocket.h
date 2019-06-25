// Saturday, January 12, 2019

#ifndef JTK_NET_SERVER_SOCKET_H
#define JTK_NET_SERVER_SOCKET_H

/*******************************************************************************
 * ServerSocket                                                                *
 *******************************************************************************/

/**
 * @class ServerSocket
 * @ingroup jtk_net
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.1
 */
struct jtk_ServerSocket_t {
    void* m_handle;
    int32_t m_port;
    int32_t m_backlog;
    int32_t m_timeout;
    bool m_reuseAddress;
    int32_t m_receiveBufferSize;
    int32_t m_latency;
    int32_t m_bandwidth;
    int32_t m_connectionTime;
    jtk_ServerSocketFactory_t* m_serverSocketFactory;
};

/**
 * @memberof ServerSocket
 */
typedef struct jtk_ServerSocket_t jtk_ServerSocket_t;

/* Constructor */

/**
 * @memberof ServerSocket
 */
jtk_ServerSocket_t* jtk_ServerSocket_new();

/**
 * @memberof ServerSocket
 */
jtk_ServerSocket_t* jtk_ServerSocket_newWithPort(int32_t port);

/**
 * @memberof ServerSocket
 */
jtk_ServerSocket_t* jtk_ServerSocket_newWithPortAndBacklog(int32_t port, int32_t backlog);

/**
 * @memberof ServerSocket
 */
jtk_ServerSocket_t* jtk_ServerSocket_newEx(int32_t port, int32_t backlog, jtk_InetAddress_t* address);

/* Destructor */

/**
 * @memberof ServerSocket
 */
void jtk_ServerSocket_delete(jtk_ServerSocket_t* socket);

/* Accept */

/**
 * @memberof ServerSocket
 */
jtk_Socket_t* jtk_ServerSocket_accept(jtk_ServerSocket_t* socket);

/**
 * @memberof ServerSocket
 */
bool jtk_ServerSocket_hasAccepted(jtk_ServerSocket_t* socket);

/* Backlog */

/**
 * @memberof ServerSocket
 */
void jtk_ServerSocket_setBacklog(jtk_ServerSocket_t* socket, int32_t backlog);

/**
 * @memberof ServerSocket
 */
int32_t jtk_ServerSocket_getBacklog(jtk_ServerSocket_t* socket);

/* Close */

/**
 * @memberof ServerSocket
 */
bool jtk_ServerSocket_isClosed(jtk_ServerSocket_t* socket);

/**
 * @memberof ServerSocket
 */
void jtk_ServerSocket_close(jtk_ServerSocket_t* socket);

/* Bandwidth */

/**
 * @memberof ServerSocket
 */
void jtk_ServerSocket_setBandwidth(jtk_ServerSocket_t* socket, int32_t bandwidth);

/**
 * @memberof ServerSocket
 */
int32_t jtk_ServerSocket_getBandwidth(jtk_ServerSocket_t* socket);

/* Connection Time */

void jtk_ServerSocket_setConnectionTime(jtk_ServerSocket_t* socket, int32_t connectionTime);

int32_t jtk_ServerSocket_getConnectionTime(jtk_ServerSocket_t* socket);

/* Latency */

void jtk_ServerSocket_setLatency(jtk_ServerSocket_t* socket, int32_t latency);

int32_t jtk_ServerSocket_getLatency(jtk_ServerSocket_t* socket);

/* Receive Buffer Size */

void jtk_ServerSocket_setReceiveBufferSize(jtk_ServerSocket_t* socket, int32_t receiveBufferSize);

int32_t jtk_ServerSocket_getReceiveBufferSize(jtk_ServerSocket_t* socket);

/* Reuse Address */

void jtk_ServerSocket_setReuseAddress(jtk_ServerSocket_t* socket, bool reuseAddress);
bool jtk_ServerSocket_canReuseAddress(jtk_ServerSocket_t* socket);

/* Server Socket Factory */

void jtk_ServerSocket_setServerSocketFactory(jtk_ServerSocket_t* socket, jtk_ServerSocketFactory_t* serverSocketFactory);

jtk_ServerSocketFactory_t* jtk_ServerSocket_getServerSocketFactory(jtk_ServerSocket_t* socket);

/* Timeout */

void jtk_ServerSocket_setTimeout(jtk_ServerSocket_t* socket, int32_t timeout);
int32_t jtk_ServerSocket_getTimeout(jtk_ServerSocket_t* socket);

#endif /* JTK_NET_SERVER_SOCKET_H */