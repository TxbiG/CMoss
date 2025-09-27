
//                        MIT License
//
//                  Copyright (c) 2025 Toby
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
/* =================================================================
Modified ENet6 v6.1.2 by SirLynix https://github.com/SirLynix/enet6/
================================================================= */

#ifndef MOSS_ENET_H
#define MOSS_ENET_H


#include <Moss/Moss_stdinc.h>
#include <stdlib.h>


#ifdef MOSS_PLATFORM_WINDOWS
#  ifdef MOSS_COMPILER_MSVC
#     ifdef ENET_BUILDING_LIB
#        pragma warning (disable: 4267) // size_t to int conversion
#        pragma warning (disable: 4244) // 64bit to 32bit int
#        pragma warning (disable: 4018) // signed/unsigned mismatch
#        pragma warning (disable: 4146) // unary minus operator applied to unsigned type
#        ifndef _CRT_SECURE_NO_DEPRECATE
#           define _CRT_SECURE_NO_DEPRECATE
#        endif // _CRT_SECURE_NO_DEPRECATE
#        ifndef _CRT_SECURE_NO_WARNINGS
#           define _CRT_SECURE_NO_WARNINGS
#        endif // _CRT_SECURE_NO_WARNINGS
#     endif // ENET_BUILDING_LIB
#  endif // MOSS_COMPILER_MSVC

#include <winsock2.h>

typedef SOCKET ENetSocket;

#define ENET_SOCKET_NULL INVALID_SOCKET

#define ENET_HOST_TO_NET_16(value) (htons(value))
#define ENET_HOST_TO_NET_32(value) (htonl(value))

#define ENET_NET_TO_HOST_16(value) (ntohs(value))
#define ENET_NET_TO_HOST_32(value) (ntohl(value))

#define ENET_CALLBACK __cdecl

typedef fd_set ENetSocketSet;

#define ENET_SOCKETSET_EMPTY(sockset)          FD_ZERO (&(sockset))
#define ENET_SOCKETSET_ADD(sockset, socket)    FD_SET (socket, &(sockset))
#define ENET_SOCKETSET_REMOVE(sockset, socket) FD_CLR (socket, &(sockset))
#define ENET_SOCKETSET_CHECK(sockset, socket)  FD_ISSET (socket, &(sockset))
#endif // MOSS_PLATFORM_WINDOWS

#ifdef MOSS_PLATFORM_LINUX || MOSS_PLATFORM_MACOS || MOSS_PLATFORM_ANDROID || MOSS_PLATFORM_IOS || MOSS_PLATFORM_BSD // < Unix
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#ifdef MSG_MAXIOVLEN
#define ENET_BUFFER_MAXIMUM MSG_MAXIOVLEN
#endif

typedef int ENetSocket;

#define ENET_SOCKET_NULL -1

#define ENET_HOST_TO_NET_16(value) (htons(value)) /**< macro that converts host to net byte-order of a 16-bit value */
#define ENET_HOST_TO_NET_32(value) (htonl(value)) /**< macro that converts host to net byte-order of a 32-bit value */

#define ENET_NET_TO_HOST_16(value) (ntohs(value)) /**< macro that converts net to host byte-order of a 16-bit value */
#define ENET_NET_TO_HOST_32(value) (ntohl(value)) /**< macro that converts net to host byte-order of a 32-bit value */

#define ENET_CALLBACK

typedef fd_set ENetSocketSet;

#define ENET_SOCKETSET_EMPTY(sockset)          FD_ZERO (&(sockset))
#define ENET_SOCKETSET_ADD(sockset, socket)    FD_SET (socket, &(sockset))
#define ENET_SOCKETSET_REMOVE(sockset, socket) FD_CLR (socket, &(sockset))
#define ENET_SOCKETSET_CHECK(sockset, socket)  FD_ISSET (socket, &(sockset))
#endif // MOSS_PLATFORM_LINUX || MOSS_PLATFORM_MACOS || MOSS_PLATFORM_ANDROID || MOSS_PLATFORM_IOS


typedef struct { void* data; size_t dataLength; } ENetBuffer;

#define ENET_ADDRESS_MAX_LENGTH 40 /*full IPv6 addresses take 39 characters + 1 null byte */

#define ENET_DIFFERENCE(x, y) ((x) < (y) ? (y) - (x) : (x) - (y))

#define ENET_CALLBACK

#define ENET_HOST_ANY       0
#define ENET_HOST_BROADCAST 0xFFFFFFFFU
#define ENET_PORT_ANY       0

#define ENET_LIST_BEGIN (list) ((list) -> sentinel.next)
#define ENET_LIST_END(list) (& (list) -> sentinel)

#define ENET_LIST_EMPTY(list) (ENET_LIST_BEGIN(list) == ENET_LIST_END(list))

#define ENET_LIST_NEXT(iterator) ((iterator) -> next)
#define ENET_LIST_PREVIOUS(iterator) ((iterator) -> previous)

#define ENET_LIST_FRONT(list) ((void*) (list) -> sentinel.next)
#define ENET_LIST_BACK(list) ((void*) (list) -> sentinel.previous)


#ifndef ENET_BUFFER_MAXIMUM
#define ENET_BUFFER_MAXIMUM (1 + 2 * ENET_PROTOCOL_MAXIMUM_PACKET_COMMANDS)
#endif

#define ENET_TIME_OVERFLOW 86400000

#define ENET_TIME_LESS(a, b) ((a) - (b) >= ENET_TIME_OVERFLOW)
#define ENET_TIME_GREATER(a, b) ((b) - (a) >= ENET_TIME_OVERFLOW)
#define ENET_TIME_LESS_EQUAL(a, b) (! ENET_TIME_GREATER (a, b))
#define ENET_TIME_GREATER_EQUAL(a, b) (! ENET_TIME_LESS (a, b))

#define ENET_TIME_DIFFERENCE(a, b) ((a) - (b) >= ENET_TIME_OVERFLOW ? (b) - (a) : (a) - (b))


// Protocall
#ifdef MOSS_COMPILER_MSVC
#pragma pack(push, 1)
#define ENET_PACKED
#elif defined(__GNUC__) || defined(__clang__)
#define ENET_PACKED __attribute__ ((packed))
#else
#define ENET_PACKED
#endif


typedef enum _ENetSocketType { ENET_SOCKET_TYPE_STREAM = 1, ENET_SOCKET_TYPE_DATAGRAM = 2 } ENetSocketType;
typedef enum _ENetSocketShutdown { ENET_SOCKET_SHUTDOWN_READ = 0, ENET_SOCKET_SHUTDOWN_WRITE = 1, ENET_SOCKET_SHUTDOWN_READ_WRITE = 2 } ENetSocketShutdown;
typedef enum _ENetAddressType { ENET_ADDRESS_TYPE_ANY  = 0, ENET_ADDRESS_TYPE_IPV4 = 1, ENET_ADDRESS_TYPE_IPV6 = 2 } ENetAddressType;
typedef enum _ENetSocketWait { ENET_SOCKET_WAIT_NONE = 0, ENET_SOCKET_WAIT_SEND = (1 << 0), ENET_SOCKET_WAIT_RECEIVE = (1 << 1), ENET_SOCKET_WAIT_INTERRUPT = (1 << 2) } ENetSocketWait;

typedef enum _ENetSocketOption {
   ENET_SOCKOPT_NONBLOCK  = 1,
   ENET_SOCKOPT_BROADCAST = 2,
   ENET_SOCKOPT_RCVBUF    = 3,
   ENET_SOCKOPT_SNDBUF    = 4,
   ENET_SOCKOPT_REUSEADDR = 5,
   ENET_SOCKOPT_RCVTIMEO  = 6,
   ENET_SOCKOPT_SNDTIMEO  = 7,
   ENET_SOCKOPT_ERROR     = 8,
   ENET_SOCKOPT_NODELAY   = 9,
   ENET_SOCKOPT_TTL       = 10,
   ENET_SOCKOPT_IPV6ONLY  = 11
} ENetSocketOption;

enum {
   ENET_PROTOCOL_MINIMUM_MTU             = 576,
   ENET_PROTOCOL_MAXIMUM_MTU             = 4096,
   ENET_PROTOCOL_MAXIMUM_PACKET_COMMANDS = 32,
   ENET_PROTOCOL_MINIMUM_WINDOW_SIZE     = 4096,
   ENET_PROTOCOL_MAXIMUM_WINDOW_SIZE     = 65536,
   ENET_PROTOCOL_MINIMUM_CHANNEL_COUNT   = 1,
   ENET_PROTOCOL_MAXIMUM_CHANNEL_COUNT   = 255,
   ENET_PROTOCOL_MAXIMUM_PEER_ID         = 0xFFF,
   ENET_PROTOCOL_MAXIMUM_FRAGMENT_COUNT  = 1024 * 1024
};

typedef enum _ENetProtocolCommand {
   ENET_PROTOCOL_COMMAND_NONE               = 0,
   ENET_PROTOCOL_COMMAND_ACKNOWLEDGE        = 1,
   ENET_PROTOCOL_COMMAND_CONNECT            = 2,
   ENET_PROTOCOL_COMMAND_VERIFY_CONNECT     = 3,
   ENET_PROTOCOL_COMMAND_DISCONNECT         = 4,
   ENET_PROTOCOL_COMMAND_PING               = 5,
   ENET_PROTOCOL_COMMAND_SEND_RELIABLE      = 6,
   ENET_PROTOCOL_COMMAND_SEND_UNRELIABLE    = 7,
   ENET_PROTOCOL_COMMAND_SEND_FRAGMENT      = 8,
   ENET_PROTOCOL_COMMAND_SEND_UNSEQUENCED   = 9,
   ENET_PROTOCOL_COMMAND_BANDWIDTH_LIMIT    = 10,
   ENET_PROTOCOL_COMMAND_THROTTLE_CONFIGURE = 11,
   ENET_PROTOCOL_COMMAND_SEND_UNRELIABLE_FRAGMENT = 12,
   ENET_PROTOCOL_COMMAND_COUNT              = 13,

   ENET_PROTOCOL_COMMAND_MASK               = 0x0F
} ENetProtocolCommand;

typedef enum _ENetProtocolFlag {
   ENET_PROTOCOL_COMMAND_FLAG_ACKNOWLEDGE = (1 << 7),
   ENET_PROTOCOL_COMMAND_FLAG_UNSEQUENCED = (1 << 6),

   ENET_PROTOCOL_HEADER_FLAG_COMPRESSED = (1 << 14),
   ENET_PROTOCOL_HEADER_FLAG_SENT_TIME  = (1 << 15),
   ENET_PROTOCOL_HEADER_FLAG_MASK       = ENET_PROTOCOL_HEADER_FLAG_COMPRESSED | ENET_PROTOCOL_HEADER_FLAG_SENT_TIME,

   ENET_PROTOCOL_HEADER_SESSION_MASK    = (3 << 12),
   ENET_PROTOCOL_HEADER_SESSION_SHIFT   = 12
} ENetProtocolFlag;

/*          Forward Declorations         */
//struct _ENetHost;
//struct _ENetEvent;
//struct _ENetPacket;

/**
 * Portable internet address structure. 
 *
 * The host must be specified in network byte-order, and the port must be in host 
 * byte-order. The constant ENET_HOST_ANY may be used to specify the default 
 * server host. The constant ENET_HOST_BROADCAST may be used to specify the
 * broadcast address (255.255.255.255).  This makes sense for enet_host_connect,
 * but not for enet_host_create.  Once a server responds to a broadcast, the
 * address is updated from ENET_HOST_BROADCAST to the server's actual IP address.
 */
typedef struct _ENetAddress {  ENetAddressType type; uint16 port; union { uint8 v4[4]; uint16 v6[8]; } host; } ENetAddress;

/**
 * Packet flag bit constants.
 *
 * The host must be specified in network byte-order, and the port must be in
 * host byte-order. The constant ENET_HOST_ANY may be used to specify the
 * default server host.
 
   @sa ENetPacket
*/
typedef enum _ENetPacketFlag
{
   /** packet must be received by the target peer and resend attempts should be
     * made until the packet is delivered */
   ENET_PACKET_FLAG_RELIABLE    = (1 << 0),
   /** packet will not be sequenced with other packets
     */
   ENET_PACKET_FLAG_UNSEQUENCED = (1 << 1),
   /** packet will not allocate data, and user must supply it instead */
   ENET_PACKET_FLAG_NO_ALLOCATE = (1 << 2),
   /** packet will be fragmented using unreliable (instead of reliable) sends
     * if it exceeds the MTU */
   ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT = (1 << 3),

   /** whether the packet has been sent from all queues it has been entered into */
   ENET_PACKET_FLAG_SENT = (1<<8)
} ENetPacketFlag;

typedef void (ENET_CALLBACK* ENetPacketAcknowledgedCallback) (struct _ENetPacket*);
typedef void (ENET_CALLBACK* ENetPacketFreeCallback) (struct _ENetPacket*);
/**
 * ENet packet structure.
 *
 * An ENet data packet that may be sent to or received from a peer. The shown 
 * fields should only be read and never modified. The data field contains the 
 * allocated data for the packet. The dataLength fields specifies the length 
 * of the allocated data.  The flags field is either 0 (specifying no flags), 
 * or a bitwise-or of any combination of the following flags:
 *
 *    ENET_PACKET_FLAG_RELIABLE - packet must be received by the target peer
 *    and resend attempts should be made until the packet is delivered
 *
 *    ENET_PACKET_FLAG_UNSEQUENCED - packet will not be sequenced with other packets 
 *    (not supported for reliable packets)
 *
 *    ENET_PACKET_FLAG_NO_ALLOCATE - packet will not allocate data, and user must supply it instead
 *
 *    ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT - packet will be fragmented using unreliable
 *    (instead of reliable) sends if it exceeds the MTU
 *
 *    ENET_PACKET_FLAG_SENT - whether the packet has been sent from all queues it has been entered into
   @sa ENetPacketFlag
 */
typedef struct _ENetPacket {
   size_t                   referenceCount;  /**< internal use only */
   uint32              flags;           /**< bitwise-or of ENetPacketFlag constants */
   uint8 *             data;            /**< allocated data for packet */
   size_t                   dataLength;      /**< length of data */
   ENetPacketFreeCallback   freeCallback;    /**< function to be called when the packet is no longer in use */
   void *                   userData;        /**< application private data, may be freely modified */
} ENetPacket;

typedef struct _ENetListNode { struct _ENetListNode * next; struct _ENetListNode * previous; } ENetListNode;


typedef ENetListNode* ENetListIterator;

typedef struct _ENetList { ENetListNode sentinel; } ENetList;


typedef struct _ENetProtocolHeader { uint16 peerID; uint16 sentTime; } ENET_PACKED ENetProtocolHeader;
typedef struct _ENetProtocolCommandHeader { uint8 command; uint8 channelID; uint16 reliableSequenceNumber; } ENET_PACKED ENetProtocolCommandHeader;
typedef struct _ENetProtocolAcknowledge { ENetProtocolCommandHeader header; uint16 receivedReliableSequenceNumber; uint16 receivedSentTime; } ENET_PACKED ENetProtocolAcknowledge;
typedef struct _ENetProtocolConnect
{
   ENetProtocolCommandHeader header;
   uint16 outgoingPeerID;
   uint8  incomingSessionID;
   uint8  outgoingSessionID;
   uint32 mtu;
   uint32 windowSize;
   uint32 channelCount;
   uint32 incomingBandwidth;
   uint32 outgoingBandwidth;
   uint32 packetThrottleInterval;
   uint32 packetThrottleAcceleration;
   uint32 packetThrottleDeceleration;
   uint32 connectID;
   uint32 data;
} ENET_PACKED ENetProtocolConnect;

typedef struct _ENetProtocolVerifyConnect
{
   ENetProtocolCommandHeader header;
   uint16 outgoingPeerID;
   uint8  incomingSessionID;
   uint8  outgoingSessionID;
   uint32 mtu;
   uint32 windowSize;
   uint32 channelCount;
   uint32 incomingBandwidth;
   uint32 outgoingBandwidth;
   uint32 packetThrottleInterval;
   uint32 packetThrottleAcceleration;
   uint32 packetThrottleDeceleration;
   uint32 connectID;
} ENET_PACKED ENetProtocolVerifyConnect;

typedef struct _ENetProtocolBandwidthLimit { ENetProtocolCommandHeader header; uint32 incomingBandwidth; uint32 outgoingBandwidth; } ENET_PACKED ENetProtocolBandwidthLimit;
typedef struct _ENetProtocolThrottleConfigure { ENetProtocolCommandHeader header; uint32 packetThrottleInterval; uint32 packetThrottleAcceleration; uint32 packetThrottleDeceleration; } ENET_PACKED ENetProtocolThrottleConfigure;
typedef struct _ENetProtocolDisconnect { ENetProtocolCommandHeader header; uint32 data; } ENET_PACKED ENetProtocolDisconnect;
typedef struct _ENetProtocolPing { ENetProtocolCommandHeader header; } ENET_PACKED ENetProtocolPing;
typedef struct _ENetProtocolSendReliable { ENetProtocolCommandHeader header; uint16 dataLength; } ENET_PACKED ENetProtocolSendReliable;
typedef struct _ENetProtocolSendUnreliable { ENetProtocolCommandHeader header; uint16 unreliableSequenceNumber; uint16 dataLength; } ENET_PACKED ENetProtocolSendUnreliable;
typedef struct _ENetProtocolSendUnsequenced{ ENetProtocolCommandHeader header; uint16 unsequencedGroup; uint16 dataLength; } ENET_PACKED ENetProtocolSendUnsequenced;
typedef struct _ENetProtocolSendFragment { ENetProtocolCommandHeader header; uint16 startSequenceNumber; uint16 dataLength;  uint32 fragmentCount; uint32 fragmentNumber; uint32 totalLength; uint32 fragmentOffset; } ENET_PACKED ENetProtocolSendFragment;


typedef union _ENetProtocol
{
   ENetProtocolCommandHeader header;         ENetProtocolAcknowledge acknowledge;         ENetProtocolConnect connect;
   ENetProtocolVerifyConnect verifyConnect;  ENetProtocolDisconnect disconnect;           ENetProtocolPing ping;
   ENetProtocolSendReliable sendReliable;    ENetProtocolSendUnreliable sendUnreliable;   ENetProtocolSendUnsequenced sendUnsequenced;
   ENetProtocolSendFragment sendFragment;    ENetProtocolBandwidthLimit bandwidthLimit;   ENetProtocolThrottleConfigure throttleConfigure;
} ENET_PACKED ENetProtocol;

typedef struct _ENetAcknowledgement { ENetListNode acknowledgementList; uint32 sentTime; ENetProtocol command; } ENetAcknowledgement;

typedef struct _ENetOutgoingCommand
{
   ENetListNode outgoingCommandList;
   uint16  reliableSequenceNumber;
   uint16  unreliableSequenceNumber;
   uint32  sentTime;
   uint32  roundTripTimeout;
   uint32  queueTime;
   uint32  fragmentOffset;
   uint16  fragmentLength;
   uint16  sendAttempts;
   ENetProtocol command;
   ENetPacket * packet;
} ENetOutgoingCommand;

typedef struct _ENetIncomingCommand
{  
   ENetListNode     incomingCommandList;
   uint16      reliableSequenceNumber;
   uint16      unreliableSequenceNumber;
   ENetProtocol     command;
   uint32      fragmentCount;
   uint32      fragmentsRemaining;
   uint32 *    fragments;
   ENetPacket *     packet;
} ENetIncomingCommand;

typedef enum _ENetPeerState {
   ENET_PEER_STATE_DISCONNECTED                = 0,
   ENET_PEER_STATE_CONNECTING                  = 1,
   ENET_PEER_STATE_ACKNOWLEDGING_CONNECT       = 2,
   ENET_PEER_STATE_CONNECTION_PENDING          = 3,
   ENET_PEER_STATE_CONNECTION_SUCCEEDED        = 4,
   ENET_PEER_STATE_CONNECTED                   = 5,
   ENET_PEER_STATE_DISCONNECT_LATER            = 6,
   ENET_PEER_STATE_DISCONNECTING               = 7,
   ENET_PEER_STATE_ACKNOWLEDGING_DISCONNECT    = 8,
   ENET_PEER_STATE_ZOMBIE                      = 9 
} ENetPeerState;


enum
{
   ENET_HOST_RECEIVE_BUFFER_SIZE          = 256 * 1024,
   ENET_HOST_SEND_BUFFER_SIZE             = 256 * 1024,
   ENET_HOST_BANDWIDTH_THROTTLE_INTERVAL  = 1000,
   ENET_HOST_DEFAULT_MTU                  = 1392,
   ENET_HOST_DEFAULT_MAXIMUM_PACKET_SIZE  = 32 * 1024 * 1024,
   ENET_HOST_DEFAULT_MAXIMUM_WAITING_DATA = 32 * 1024 * 1024,

   ENET_PEER_DEFAULT_ROUND_TRIP_TIME      = 500,
   ENET_PEER_DEFAULT_PACKET_THROTTLE      = 32,
   ENET_PEER_PACKET_THROTTLE_SCALE        = 32,
   ENET_PEER_PACKET_THROTTLE_COUNTER      = 7, 
   ENET_PEER_PACKET_THROTTLE_ACCELERATION = 2,
   ENET_PEER_PACKET_THROTTLE_DECELERATION = 2,
   ENET_PEER_PACKET_THROTTLE_INTERVAL     = 5000,
   ENET_PEER_PACKET_LOSS_SCALE            = (1 << 16),
   ENET_PEER_PACKET_LOSS_INTERVAL         = 10000,
   ENET_PEER_WINDOW_SIZE_SCALE            = 64 * 1024,
   ENET_PEER_TIMEOUT_LIMIT                = 32,
   ENET_PEER_TIMEOUT_MINIMUM              = 5000,
   ENET_PEER_TIMEOUT_MAXIMUM              = 30000,
   ENET_PEER_PING_INTERVAL                = 500,
   ENET_PEER_UNSEQUENCED_WINDOWS          = 64,
   ENET_PEER_UNSEQUENCED_WINDOW_SIZE      = 1024,
   ENET_PEER_FREE_UNSEQUENCED_WINDOWS     = 32,
   ENET_PEER_RELIABLE_WINDOWS             = 16,
   ENET_PEER_RELIABLE_WINDOW_SIZE         = 0x1000,
   ENET_PEER_FREE_RELIABLE_WINDOWS        = 8
};

typedef struct _ENetChannel
{
   uint16  outgoingReliableSequenceNumber;
   uint16  outgoingUnreliableSequenceNumber;
   uint16  usedReliableWindows;
   uint16  reliableWindows [ENET_PEER_RELIABLE_WINDOWS];
   uint16  incomingReliableSequenceNumber;
   uint16  incomingUnreliableSequenceNumber;
   ENetList     incomingReliableCommands;
   ENetList     incomingUnreliableCommands;
} ENetChannel;

typedef enum _ENetPeerFlag
{
   ENET_PEER_FLAG_NEEDS_DISPATCH   = (1 << 0),
   ENET_PEER_FLAG_CONTINUE_SENDING = (1 << 1)
} ENetPeerFlag;

/**
 * An ENet peer which data packets may be sent or received from. 
 *
 * No fields should be modified unless otherwise specified. 
 */
typedef struct _ENetPeer { 
   ENetListNode  dispatchList;
   struct _ENetHost* host;
   uint16   outgoingPeerID;
   uint16   incomingPeerID;
   uint32   connectID;
   uint8    outgoingSessionID;
   uint8    incomingSessionID;
   ENetAddress    address;             /**< Internet address of the peer */
   void *         data;                /**< Application private data, may be freely modified */
   ENetPeerState  state;
   ENetChannel*   channels;
   size_t         channelCount;        /**< Number of channels allocated for communication with peer */
   uint32   incomingBandwidth;         /**< Downstream bandwidth of the client in bytes/second */
   uint32   outgoingBandwidth;         /**< Upstream bandwidth of the client in bytes/second */
   uint32   incomingBandwidthThrottleEpoch;
   uint32   outgoingBandwidthThrottleEpoch;
   uint32   incomingDataTotal;
   uint32   outgoingDataTotal;
   uint32   lastSendTime;
   uint32   lastReceiveTime;
   uint32   nextTimeout;
   uint32   earliestTimeout;
   uint32   packetLossEpoch;
   uint32   packetsSent;
   uint32   packetsLost;
   uint32   packetLoss;          /**< mean packet loss of reliable packets as a ratio with respect to the constant ENET_PEER_PACKET_LOSS_SCALE */
   uint32   packetLossVariance;
   uint32   packetThrottle;
   uint32   packetThrottleLimit;
   uint32   packetThrottleCounter;
   uint32   packetThrottleEpoch;
   uint32   packetThrottleAcceleration;
   uint32   packetThrottleDeceleration;
   uint32   packetThrottleInterval;
   uint32   pingInterval;
   uint32   timeoutLimit;
   uint32   timeoutMinimum;
   uint32   timeoutMaximum;
   uint32   lastRoundTripTime;
   uint32   lowestRoundTripTime;
   uint32   lastRoundTripTimeVariance;
   uint32   highestRoundTripTimeVariance;
   uint32   roundTripTime;            /**< mean round trip time (RTT), in milliseconds, between sending a reliable packet and receiving its acknowledgement */
   uint32   roundTripTimeVariance;
   uint32   mtu;
   uint32   windowSize;
   uint32   reliableDataInTransit;
   uint16   outgoingReliableSequenceNumber;
   ENetList acknowledgements;
   ENetList sentReliableCommands;
   ENetList outgoingSendReliableCommands;
   ENetList outgoingCommands;
   ENetList dispatchedCommands;
   uint16   flags;
   uint16   reserved;
   uint16   incomingUnsequencedGroup;
   uint16   outgoingUnsequencedGroup;
   uint32   unsequencedWindow [ENET_PEER_UNSEQUENCED_WINDOW_SIZE / 32]; 
   uint32   eventData;
   size_t        totalWaitingData;
} ENetPeer;

/** An ENet packet compressor for compressing UDP packets before socket sends or receives.
 */
typedef struct _ENetCompressor
{
   /** Context data for the compressor. Must be non-NULL. */
   void* context;
   /** Compresses from inBuffers[0:inBufferCount-1], containing inLimit bytes, to outData, outputting at most outLimit bytes. Should return 0 on failure. */
   size_t (ENET_CALLBACK* compress) (void* context, const ENetBuffer* inBuffers, size_t inBufferCount, size_t inLimit, uint8* outData, size_t outLimit);
   /** Decompresses from inData, containing inLimit bytes, to outData, outputting at most outLimit bytes. Should return 0 on failure. */
   size_t (ENET_CALLBACK* decompress) (void* context, const uint8* inData, size_t inLimit, uint8 * outData, size_t outLimit);
   /** Destroys the context when compression is disabled or the host is destroyed. May be NULL. */
   void (ENET_CALLBACK* destroy) (void* context);
} ENetCompressor;

/** Callback that computes the checksum of the data held in buffers[0:bufferCount-1] */
typedef uint32 (ENET_CALLBACK* ENetChecksumCallback) (const ENetBuffer* buffers, size_t bufferCount);

/** Callback for intercepting received raw UDP packets. Should return 1 to intercept, 0 to ignore, or -1 to propagate an error. */
typedef int (ENET_CALLBACK * ENetInterceptCallback) (struct _ENetHost* host, struct _ENetEvent * event);
 
/** An ENet host for communicating with peers.
  *
  * No fields should be modified unless otherwise stated.

    @sa enet_host_create()
    @sa enet_host_destroy()
    @sa enet_host_connect()
    @sa enet_host_service()
    @sa enet_host_flush()
    @sa enet_host_broadcast()
    @sa enet_host_compress()
    @sa enet_host_compress_with_range_coder()
    @sa enet_host_channel_limit()
    @sa enet_host_bandwidth_limit()
    @sa enet_host_bandwidth_throttle()
  */
typedef struct _ENetHost
{
   ENetSocket           socket;
   ENetAddress          address;                     /**< Internet address of the host */
   uint32          incomingBandwidth;           /**< downstream bandwidth of the host */
   uint32          outgoingBandwidth;           /**< upstream bandwidth of the host */
   uint32          bandwidthThrottleEpoch;
   uint32          mtu;
   uint32          randomSeed;
   int                  recalculateBandwidthLimits;
   ENetPeer*           peers;                       /**< array of peers allocated for this host */
   size_t               peerCount;                   /**< number of peers allocated for this host */
   size_t               channelLimit;                /**< maximum number of channels allowed for connected peers */
   uint32          serviceTime;
   ENetList             dispatchQueue;
   uint32          totalQueued;
   size_t               packetSize;
   uint16          headerFlags;
   ENetProtocol         commands [ENET_PROTOCOL_MAXIMUM_PACKET_COMMANDS];
   size_t               commandCount;
   ENetBuffer           buffers [ENET_BUFFER_MAXIMUM];
   size_t               bufferCount;
   ENetChecksumCallback checksum;                    /**< callback the user can set to enable packet checksums for this host */
   ENetCompressor       compressor;
   uint8           packetData [2][ENET_PROTOCOL_MAXIMUM_MTU];
   ENetAddress          receivedAddress;
   uint8*         receivedData;
   size_t               receivedDataLength;
   uint32          totalSentData;               /**< total data sent, user should reset to 0 as needed to prevent overflow */
   uint32          totalSentPackets;            /**< total UDP packets sent, user should reset to 0 as needed to prevent overflow */
   uint32          totalReceivedData;           /**< total data received, user should reset to 0 as needed to prevent overflow */
   uint32          totalReceivedPackets;        /**< total UDP packets received, user should reset to 0 as needed to prevent overflow */
   ENetInterceptCallback intercept;                  /**< callback the user can set to intercept received raw UDP packets */
   size_t               connectedPeers;
   size_t               bandwidthLimitedPeers;
   size_t               duplicatePeers;              /**< optional number of allowed peers from duplicate IPs, defaults to ENET_PROTOCOL_MAXIMUM_PEER_ID */
   size_t               maximumPacketSize;           /**< the maximum allowable packet size that may be sent or received on a peer */
   size_t               maximumWaitingData;          /**< the maximum aggregate amount of buffer space a peer may use waiting for packets to be delivered */
} ENetHost;

/**
 * An ENet event type, as specified in @ref ENetEvent.
 */
typedef enum _ENetEventType
{
   /** no event occurred within the specified time limit */
   ENET_EVENT_TYPE_NONE       = 0,  

   /** a connection request initiated by enet_host_connect has completed.  
     * The peer field contains the peer which successfully connected. 
     */
   ENET_EVENT_TYPE_CONNECT    = 1,  

   /** a peer has disconnected.  This event is generated on a successful 
     * completion of a disconnect initiated by enet_peer_disconnect, if 
     * a peer has timed out, or if a connection request intialized by 
     * enet_host_connect has timed out.  The peer field contains the peer 
     * which disconnected. The data field contains user supplied data 
     * describing the disconnection, or 0, if none is available.
     */
   ENET_EVENT_TYPE_DISCONNECT = 2,  

   /** a packet has been received from a peer.  The peer field specifies the
     * peer which sent the packet.  The channelID field specifies the channel
     * number upon which the packet was received.  The packet field contains
     * the packet that was received; this packet must be destroyed with
     * enet_packet_destroy after use.
     */
   ENET_EVENT_TYPE_RECEIVE    = 3
} ENetEventType;

/**
 * An ENet event as returned by enet_host_service().
   
   @sa enet_host_service
 */
typedef struct _ENetEvent  {
   ENetEventType        type;      /**< type of the event */
   ENetPeer *           peer;      /**< peer that generated a connect, disconnect or receive event */
   uint8                channelID; /**< channel on the peer that generated the event, if appropriate */
   uint32               data;      /**< data associated with the event, if appropriate */
   ENetPacket *         packet;    /**< packet associated with the event, if appropriate */
} ENetEvent;

// Call back
typedef struct _ENetCallbacks
{
    void* (ENET_CALLBACK* malloc) (size_t size);
    void (ENET_CALLBACK* free) (void * memory);
    void (ENET_CALLBACK* no_memory) (void);
} ENetCallbacks;

#ifdef MOSS_COMPILER_MSVC
#pragma pack(pop)
#endif


#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*! @brief Initializes ENet globally. Must be called prior to using any functions in ENet. */
MOSS_API int Moss_Init_Network(void);
/*! @brief Initializes ENet globally with callbacks. Must be called prior to using any functions in ENet. */
MOSS_API int enet_initialize_with_callbacks(const ENetCallbacks * inits);
/*! @brief Shuts down ENet globally. Should be called when a program that has initialized ENet exits. */
MOSS_API void Moss_TerminateNetwork(void);



// Call back
/** @defgroup callbacks ENet internal callbacks
    @{
    @ingroup private
*/
MOSS_API void* enet_malloc(size_t);
MOSS_API void  enet_free(void*);

// =============================================
// List
// =============================================
MOSS_API void enet_list_clear(ENetList*);

MOSS_API ENetListIterator enet_list_insert(ENetListIterator, void*);
MOSS_API void * enet_list_remove(ENetListIterator);
MOSS_API ENetListIterator enet_list_move(ENetListIterator, void*, void*);

MOSS_API size_t enet_list_size(ENetList*);


// =============================================
// Time
// =============================================
/*! @brief Returns the wall-time in milliseconds. Its initial value is unspecified unless otherwise set. */
MOSS_API uint32 enet_time_get(void);
/*! @brief Sets the current wall-time in milliseconds. */
MOSS_API void enet_time_set(uint32);


// =============================================
// Socket
// =============================================
/*! @brief X. @param type X. @param socket_type X.*/
MOSS_API ENetSocket enet_socket_create(ENetAddressType adress_type, ENetSocketType socket_type);
/*! @brief X.*/
MOSS_API int        enet_socket_bind(ENetSocket, const ENetAddress*);
/*! @brief X.*/
MOSS_API int        enet_socket_get_address(ENetSocket, ENetAddress*);
/*! @brief X.*/
MOSS_API int        enet_socket_listen(ENetSocket, int);
/*! @brief X.*/
MOSS_API ENetSocket enet_socket_accept(ENetSocket, ENetAddress *);
/*! @brief X.*/
MOSS_API int        enet_socket_connect(ENetSocket, const ENetAddress *);
/*! @brief X.*/
MOSS_API int        enet_socket_send(ENetSocket, const ENetAddress *, const ENetBuffer *, size_t);
/*! @brief X.*/
MOSS_API int        enet_socket_receive(ENetSocket, ENetAddress *, ENetBuffer *, size_t);
/*! @brief X.*/
MOSS_API int        enet_socket_wait(ENetSocket, uint32*, uint32);
/*! @brief X.*/
MOSS_API int        enet_socket_set_option(ENetSocket, ENetSocketOption, int);
/*! @brief X.*/
MOSS_API int        enet_socket_get_option(ENetSocket, ENetSocketOption, int *);
/*! @brief X.*/
MOSS_API int        enet_socket_shutdown(ENetSocket, ENetSocketShutdown);
/*! @brief X.*/
MOSS_API void       enet_socket_destroy(ENetSocket);
/*! @brief X.*/
MOSS_API int        enet_socketset_select(ENetSocket, ENetSocketSet *, ENetSocketSet *, uint32);

// =============================================
// Addresses
// =============================================
/** Attempts to parse the printable form of the IP address in the parameter hostName and sets the host field in the address parameter if successful. @param address destination to store the parsed IP address @param hostName IP address to parse @returns the address of the given hostName in address on success.*/
MOSS_API int enet_address_set_host_ip(ENetAddress* address, const char* hostName);
/** Attempts to resolve the host named by the parameter hostName and sets the host field in the address parameter if successful. @param address destination to store resolved address. @param type set the ip adress type (ENET_ADDRESS_TYPE_ANY/ENET_ADDRESS_TYPE_IPV4/ENET_ADDRESS_TYPE_IPV6). @param hostName host name to lookup. @returns the address of the given hostName in address on success.*/
MOSS_API int enet_address_set_host(ENetAddress* address, ENetAddressType type, const char* hostName);
/*! Gives the printable form of the IP address specified in the address parameter. @param address    address printed @param hostName   destination for name, must not be NULL @param nameLength maximum length of hostName. @returns the null-terminated name of the host in hostName on success.*/
MOSS_API int enet_address_get_host_ip(const ENetAddress* address, char* hostName, size_t nameLength);
/*! @brief Attempts to do a reverse lookup of the host field in the address parameter.  @param address address used for reverse lookup. @param hostName destination for name, must not be NULL. @param nameLength maximum length of hostName.  @returns the null-terminated name of the host in hostName on success.*/
MOSS_API int enet_address_get_host(const ENetAddress* address, char* hostName, size_t nameLength);
/*! @brief X.*/
MOSS_API int enet_address_equal_host(const ENetAddress* firstAddress, const ENetAddress * secondAddress);
/*! @brief X.*/
MOSS_API int enet_address_is_broadcast(const ENetAddress* address);
/*! @brief X.*/
MOSS_API void enet_address_build_any(ENetAddress* address, ENetAddressType type);
/*! @brief X.*/
MOSS_API void enet_address_build_loopback(ENetAddress* address, ENetAddressType type);
/*! @brief X.*/
MOSS_API void enet_address_convert_ipv6(ENetAddress* address);

// =============================================
// Host
// =============================================
/*! @brief X.*/
MOSS_API uint32      enet_crc32(const ENetBuffer*, size_t);

/*! @brief X. @param type*/
MOSS_API ENetHost*   enet_host_create(ENetAddressType type, const ENetAddress*, size_t, size_t, uint32, uint32);
/*! @brief X.*/
MOSS_API void        enet_host_destroy(ENetHost*);
/*! @brief X.*/
MOSS_API int         enet_host_check_events(ENetHost*, ENetEvent*);
/*! @brief X.*/
MOSS_API int         enet_host_service(ENetHost*, ENetEvent*, uint32);
/*! @brief X.*/
MOSS_API void        enet_host_flush(ENetHost*);
/*! @brief X.*/
MOSS_API void        enet_host_broadcast(ENetHost*, uint8, ENetPacket *);
/*! @brief X.*/
MOSS_API void        enet_host_compress(ENetHost*, const ENetCompressor*);
/*! @brief X.*/
MOSS_API int         enet_host_compress_with_range_coder(ENetHost * host);
/*! @brief X.*/
MOSS_API void        enet_host_channel_limit(ENetHost*, size_t);
/*! @brief X.*/
MOSS_API void        enet_host_bandwidth_limit(ENetHost*, uint32, uint32);
/*! @brief X.*/
MOSS_API void        enet_host_bandwidth_throttle(ENetHost*);
/*! @brief X.*/
MOSS_API uint32      enet_host_random_seed(void);
/*! @brief X.*/
MOSS_API uint32      enet_host_random(ENetHost*);


// =============================================
// Peer
// =============================================
/*! @brief X.*/
MOSS_API ENetPeer*   enet_host_connect(ENetHost*, const ENetAddress*, size_t, uint32);
/*! @brief X.*/
MOSS_API int                  enet_peer_send(ENetPeer*, uint8, ENetPacket*);
/*! @brief X.*/
MOSS_API void                 enet_peer_ping(ENetPeer*);
/*! @brief X.*/
MOSS_API void                 enet_peer_ping_interval(ENetPeer*, uint32);
/*! @brief X.*/
MOSS_API void                 enet_peer_timeout(ENetPeer*, uint32, uint32, uint32);
/*! @brief X.*/
MOSS_API void                 enet_peer_reset(ENetPeer*);
/*! @brief X.*/
MOSS_API void                 enet_peer_disconnect(ENetPeer*, uint32);
/*! @brief X.*/
MOSS_API void                 enet_peer_disconnect_now(ENetPeer*, uint32);
/*! @brief X.*/
MOSS_API void                 enet_peer_disconnect_later(ENetPeer*, uint32);
/*! @brief X.*/
MOSS_API void                 enet_peer_throttle_configure(ENetPeer*, uint32, uint32, uint32);
/*! @brief X.*/
MOSS_API int                  enet_peer_throttle(ENetPeer *, uint32);
/*! @brief X.*/
MOSS_API void                 enet_peer_reset_queues(ENetPeer *);
/*! @brief X.*/
MOSS_API int                  enet_peer_has_outgoing_commands(ENetPeer*);
/*! @brief X.*/
MOSS_API void                 enet_peer_setup_outgoing_command(ENetPeer*, ENetOutgoingCommand*);
/*! @brief X.*/
MOSS_API ENetOutgoingCommand* enet_peer_queue_outgoing_command(ENetPeer*, const ENetProtocol*, ENetPacket*, uint32, uint16);
/*! @brief X.*/
MOSS_API ENetIncomingCommand* enet_peer_queue_incoming_command(ENetPeer*, const ENetProtocol*, const void*, size_t, uint32, uint32);
/*! @brief X.*/
MOSS_API ENetAcknowledgement* enet_peer_queue_acknowledgement(ENetPeer*, const ENetProtocol*, uint16);
/*! @brief X.*/
MOSS_API void                 enet_peer_dispatch_incoming_unreliable_commands(ENetPeer*, ENetChannel*, ENetIncomingCommand*);
/*! @brief X.*/
MOSS_API void                 enet_peer_dispatch_incoming_reliable_commands(ENetPeer*, ENetChannel*, ENetIncomingCommand*);
/*! @brief X.*/
MOSS_API void                 enet_peer_on_connect(ENetPeer*);
/*! @brief X.*/
MOSS_API void                 enet_peer_on_disconnect(ENetPeer*);


// =============================================
// Packet
// =============================================
/*! @brief X.*/
MOSS_API ENetPacket* enet_packet_create(const void*, size_t, uint32);
/*! @brief X.*/
MOSS_API void        enet_packet_destroy(ENetPacket*);
/*! @brief X.*/
MOSS_API int         enet_packet_resize(ENetPacket*, size_t);
/*! @brief X.*/
MOSS_API ENetPacket*          enet_peer_receive(ENetPeer*, uint8 * channelID);
// =============================================
// Range Coder
// =============================================

MOSS_API void*  enet_range_coder_create(void);
MOSS_API void   enet_range_coder_destroy(void*);
MOSS_API size_t enet_range_coder_compress(void*, const ENetBuffer*, size_t, size_t, uint8*, size_t);
MOSS_API size_t enet_range_coder_decompress(void*, const uint8*, size_t, uint8*, size_t);
MOSS_API size_t enet_protocol_command_size(uint8);



// Unknown functions down here

MOSS_API void* enet_packet_get_data(const ENetPacket*);
MOSS_API void* enet_packet_get_user_data(const ENetPacket*);
MOSS_API void enet_packet_set_user_data(ENetPacket*, void* userData);
MOSS_API int enet_packet_get_length(const ENetPacket*);
MOSS_API void enet_packet_set_acknowledge_callback(ENetPacket*, ENetPacketAcknowledgedCallback);
MOSS_API void enet_packet_set_free_callback(ENetPacket*, ENetPacketFreeCallback);
MOSS_API int enet_packet_check_references(const ENetPacket*);
MOSS_API void enet_packet_dispose(ENetPacket*);

MOSS_API uint32 enet_host_get_peers_count(const ENetHost*);
MOSS_API uint32 enet_host_get_packets_sent(const ENetHost*);
MOSS_API uint32 enet_host_get_packets_received(const ENetHost*);
MOSS_API uint32 enet_host_get_bytes_sent(const ENetHost*);
MOSS_API uint32 enet_host_get_bytes_received(const ENetHost*);
MOSS_API void enet_host_set_max_duplicate_peers(ENetHost*, uint16);
MOSS_API void enet_host_set_intercept_callback(ENetHost*, ENetInterceptCallback);
MOSS_API void enet_host_set_checksum_callback(ENetHost*, ENetChecksumCallback);

MOSS_API uint32 enet_peer_get_id(const ENetPeer*);
MOSS_API int enet_peer_get_ip(const ENetPeer*, char*, size_t);
MOSS_API uint16 enet_peer_get_port(const ENetPeer*);
MOSS_API uint32 enet_peer_get_mtu(const ENetPeer*);
MOSS_API ENetPeerState enet_peer_get_state(const ENetPeer*);
MOSS_API uint32 enet_peer_get_rtt(const ENetPeer*);
MOSS_API uint32 enet_peer_get_last_rtt(const ENetPeer* peer);
MOSS_API uint32 enet_peer_get_lastsendtime(const ENetPeer*);
MOSS_API uint32 enet_peer_get_lastreceivetime(const ENetPeer*);
MOSS_API float enet_peer_get_packets_throttle(const ENetPeer*);
MOSS_API void* enet_peer_get_data(const ENetPeer*);
MOSS_API void enet_peer_set_data(ENetPeer*, const void*);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MOSS_ENET_H

