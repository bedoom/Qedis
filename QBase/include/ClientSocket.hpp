#pragma once

#include <functional>
#include "Socket.hpp"

class ClientSocket: public Socket
{
public:
    explicit
    ClientSocket();
    ~ClientSocket();
    int Connect(const SocketAddr& addr);
    bool OnWritable();
    bool OnError();
    SocketType GetSocketType() const { return SocketType_Client; }

    void SetFailCallback(const std::function<void ()>& cb) { onConnectFail_ = cb; }

private:
    const int tag_;    
    sockaddr_in peerAddr_;
    std::function<void ()> onConnectFail_;

};