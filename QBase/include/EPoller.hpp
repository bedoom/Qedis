#pragma once

#if defined(__gnu_linux__)

#include <sys/epoll.h>
#include <Poller.hpp>
#include <vector>

class EPoller: public Poller
{
public: 
    EPoller();
    ~EPoller();

    bool AddSocket(int sock, int events, void* userPtr) override;
    bool ModSocket(int sock, int events, void* userPtr) override;
    bool DelSocket(int sock, int events) override;

    int Poll(std::vector<FiredEvent>& events, std::size_t maxEvent, int timeoutMs) override;

private:
    std::vector<epoll_event> events_;
};

#endif