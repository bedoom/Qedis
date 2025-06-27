#pragma once

#include <set>
#include <functional>
#include "TaskManager.hpp"

struct SocketAddr;

class Server  // Should singleton
{
protected:
    virtual bool _RunLogic();
    virtual void _Recycle();
    virtual bool _Init() = 0;

    Server();

    Server(const Server& ) = delete;
    void operator= (const Server& ) = delete;

public:
    ~Server();

    bool TCPBind(const SocketAddr& listenAddr, int tag);
    void TCPReconnect(const SocketAddr& peer, int tag);

    static Server* Instance() { return sinstance_;}
    void Terminate() { bTerminate_ = true; }

    void MainLoop(bool daemon = false);
    void NewConnection(int sock, int tag, const std::function<void ()>& cb = std::function<void ()>());

    void TCPConnect(const SocketAddr& peer, int tag);
    void TCPConnect(const SocketAddr& peer, const std::function<void ()>& cb, int tag);

    size_t TCPSize() const { return tasks_.TCPSize(); }

    // SIGHUP handler, in fact, you should load config use this function;
    virtual void ReloadConfig() {}

    static void IntHandler(int sig);
    static void HupHandler(int sig);

    std::shared_ptr<StreamSocket>  FindTCP(unsigned int id) const { return tasks_.FindTCP(id); }

    static void AtForkHandler();
    static void DelListenSock(int sock);

private:
    virtual std::shared_ptr<StreamSocket> _OnNewConnection(int tcpsock, int tag);
    void _TCPConnect(const SocketAddr& peer, const std::function<void ()>* cb = nullptr, int tag = -1);

    std::atomic<bool>       bTerminate_;
    Internal::TaskManager   tasks_;
    bool                    reloadCfg_;
    static Server*          sinstance_;

    static std::set<int>    slistenSocks_;
};