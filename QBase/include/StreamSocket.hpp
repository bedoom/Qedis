#pragma once

#include "AsyncBuffer.hpp"
#include "Socket.hpp"
#include <sys/types.h>
#include <sys/socket.h>

using PacketLength = int32_t;

// Abstraction for a TCP connection
class StreamSocket: public Socket
{
    friend class SendThread;
public:
    StreamSocket();
    ~StreamSocket();

    bool        Init(int localfd, const SocketAddr& peer);
    SocketType  GetSocketType() const { return SocketType_Stream; }

public:
    // Receive data    
    int Recv();
public:
    // send data
    bool SendPacket(const void* , std::size_t );
    bool SendPacket(Buffer& bf);
    bool SendPacket(AttachedBuffer& abf);
    bool SendPacket(qeids::UnboundedBuffer& ubf);
    template <int N>
    bool SendPacket(StackBuffer<N>& sb);

    bool OnReadable();
    bool OnWritable();
    bool OnError();

    bool DoMsgParse();  // false if no msg

    void SetOnDisconnect(const std::function<void ()>& cb = std::function<void ()>()) {onDisconnect_ = cb; }

    // send thread
    bool Send();

    const SocketAddr& GetPeerAddr() { return peerAddr_; }


protected:
    SocketAddr peerAddr_;

private:
    std::function<void ()> onDisconnect_;
    virtual PacketLength _HandlePacket(const char* msg, std::size_t len) = 0;

    // For human readability
    enum
    {
        TIMEOUTSOCKET   = 0,
        ERRORSOCKET     = -1,
        EOFSOCKET       = -2
    };

    Buffer recvBuf_;
    AsyncBuffer sendBuf_;
};