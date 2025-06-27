#include <cassert>
#include "TaskManager.hpp"
#include "StreamSocket.hpp"
#include "Log/Logger.hpp"

namespace Internal
{

TaskManager::~TaskManager()
{
    assert(Empty() && "Why you do not clear container before exit?");
}

bool TaskManager::AddTask(PTCPSOCKET task)
{
    std::lock_guard<std::mutex> guard(lock_);
    newTasks_.push_back(task);
    return true;
}

TaskManager::PTCPSOCKET TaskManager::FindTCP(unsigned int id) const
{
    if (id > 0)
    {
        auto it = tcpSocket_.find(id);
        if(it != tcpSocket_.end())
        {
            return it->second;
        }
    }
    return PTCPSOCKET();
}

bool TaskManager::_AddTask(PTCPSOCKET task)
{
    bool succ = tcpSocket_.insert({task->GetID(), task}).second;
    return succ;
}

void TaskManager::_RemoveTask(std::map<int, PTCPSOCKET>::iterator& it)   
{
    tcpSocket_.erase(it);
}

bool TaskManager::DoMsgParse()
{
    if(newCnt_ > 0 && lock_.try_lock())
    {
        NEWTASK_T tmpNewTask;
        tmpNewTask.swap(newTasks_);
        newCnt_ = 0;
        lock_.unlock();

        for(const auto & task: tmpNewTask)
        {
            if(!_AddTask(task))
            {
                ERR << "Why can not insert tcp socket "
                    << task->GetSocket()
                    << ", id = "
                    << task->GetID();
            }
            else
            {
                INF << "New connection from "
                    << task->GetPeerAddr().ToString()
                    << ", id = "
                    << task->GetID();
                
                task->OnConnect();
            }
        }
    }

    bool busy = false;

    for(auto it(tcpSocket_.begin()); it != tcpSocket_.end(); )
    {
        if(!it->second || it->second->Invalid())
        {
            if(it->second)
            {
                INF << "Close connection from "
                    << it->second->GetPeerAddr().ToString()
                    << ", id = "
                    << it->second->GetID();

                it->second->OnDisconnect();
            }
            _RemoveTask(it);
        }
        else
        {
            if(it->second->DoMsgParse() && !busy)
                busy = true;

            ++it;
        }
    }
    
    return busy;
}


}