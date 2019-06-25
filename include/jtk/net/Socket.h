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