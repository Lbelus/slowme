#ifndef __HTTP2_H_
#define __HTTP2_H_

#define __HTTP2_PREFACE "PRI * HTTP/2.0\r\n\r\n"

// Unoptimized bitsfield
#ifndef __HTTP2_FRAME_
#define __HTTP2_FRAME_
struct http2_frame_struct
{
    uint32_t length : 24;
    uint8_t type;
    uint8_t flags;
    uint32_t stream_id : 31;
    uint8_t reserved : 1;
};
typedef struct http2_frame_struct Frame;
#endif
 
#endif
