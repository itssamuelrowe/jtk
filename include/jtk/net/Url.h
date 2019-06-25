// Monday, January 14, 2018

#ifndef JTK_NET_URL_H
#define JTK_NET_URL_H

/*******************************************************************************
 * Url                                                                         *
 *******************************************************************************/

/**
 * @class Url
 * @ingroup jtk_net
 * @author Samuel Rowe <samuelrowe1999@gmail.com>
 * @since JTK 1.1
 */
struct jtk_Url_t {
    jtk_String_t* m_protocol;
    jtk_String_t* m_host;
    int32_t m_port;
    jtk_String_t* m_file;
    jtk_String_t* m_query;
    jtk_String_t* m_authority;
    jtk_String_t* m_reference;
};

typedef struct jtk_Url_t jtk_Url_t;

/* Constructor */

jtk_Url_t* jtk_Url_new(jtk_String_t* specification);

jtk_Url_t* jtk_Url_newWithContext(jtk_Url_t* context, jtk_String_t* specification);

jtk_Url_t* jtk_Url_newWithContextEx(jtk_Url_t* context, jtk_String_t* specification, jtk_UrlStreamHandler_t* streamHandler);

jtk_Url_t* jtk_Url_newEx(jtk_String_t* protocol, jtk_String_t* host, int32_t port, jtk_String_t* file, jtk_UrlStreamHandler_t* streamHandler);

/* Authority */

jtk_String_t* jtk_Url_getAuthority(jtk_Url_t* url);

/* File */

jtk_String_t* jtk_Url_getFile(jtk_Url_t* url);

/* Protocol */

jtk_String_t* jtk_Url_getProtocol(jtk_Url_t* url);

/* Host */

jtk_String_t* jtk_Url_getHost(jtk_Url_t* url);

/* Port */

int32_t jtk_Url_getPort(jtk_Url_t* url);

/* Reference */

jtk_String_t* jtk_Url_getReference(jtk_Url_t* url);

/* Query */

jtk_String_t* jtk_Url_getQuery(jtk_Url_t* url);

#endif /* JTK_NET_URL_H */