#ifndef BERT_CLUSTERINTERFACE_H
#define BERT_CLUSTERINTERFACE_H

#if QEDIS_CLUSTER

#include <vector>
#include <string>
#include <functional>

#include "Socket.h"

namespace ConnectionTag
{
   const int kSlaveClient = 3;
}

namespace qedis
{

class QClusterConn
{ 
public:
    virtual ~QClusterConn()
    {
    }

    void SetOnBecomeMaster(std::function<void (const std::vector<SocketAddr>& )> cb)
    {
        onBecomeMaster_ = std::move(cb);
    }

    void SetOnBecomeSlave(std::function<void (const std::string& )> cb)
    {
        onBecomeSlave_ = std::move(cb);
    }

public:
    virtual bool ParseMessage(const char*& data, size_t len) = 0;
    virtual void OnConnect() = 0;
    virtual void OnDisconnect() = 0;

protected:
    std::function<void (const std::vector<SocketAddr>& )> onBecomeMaster_;
    std::function<void (const std::string& )> onBecomeSlave_;

};

} // end namespace qedis

#endif // endif QEDIS_CLUSTER

#endif // endif BERT_CLUSTERINTERFACE_H

