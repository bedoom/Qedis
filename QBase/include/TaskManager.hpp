#pragma once

#include <vector>
#include <map>
#include <mutex>
#include <memory>
#include <atomic>

class StreamSocket;

namespace Internal
{
class TaskManager
{
    typedef std::shared_ptr<StreamSocket>   PTCPSOCKET;
    typedef std::vector<PTCPSOCKET>      NEWTASK_T;

public:
    TaskManager(): newCnt_(0) {}
    ~TaskManager();

    bool AddTask(PTCPSOCKET );

    bool            Empty() const { return tcpSocket_.empty(); }
    void            Clear() { tcpSocket_.clear(); } 
    PTCPSOCKET   FindTCP(unsigned int id) const;

    size_t  TCPSize() const { return tcpSocket_.size();}

    bool    DoMsgParse();

private:
    bool _AddTask(PTCPSOCKET task);
    void _RemoveTask(std::map<int, PTCPSOCKET>::iterator& );
    std::map<int, PTCPSOCKET> tcpSocket_;

    //  Lock for new tasks
    std::mutex       lock_;
    NEWTASK_T        newTasks_;
    std::atomic<int> newCnt_; // vector::empty() is not thread-safe !!!
};
}