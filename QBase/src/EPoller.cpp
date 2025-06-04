#if defined(__gnu_linux__)

#include <EPoller.hpp>
#include <Log/Logger.hpp>

#include <errno.h>
#include <unistd.h>

namespace EPoll
{
    bool ModSocket(int epfd, int socket, uint32_t events, void* ptr);

    bool AddSocket(int epfd, int socket, uint32_t events, void* ptr)
    {
        if(socket < 0)
        {
            return false;
        }

        epoll_event ev;
        ev.data.ptr = ptr;

        ev.events = 0;
        if(events & EventTypeRead)
        {
            ev.events |= EPOLLIN;
        }
        if(events & EventTypeWrite)
        {
            ev.events |= EPOLLOUT;
        } 

        return 0==epoll_ctl(epfd, EPOLL_CTL_ADD, socket, &ev);
    }

    bool DelSocket(int epfd, int socket)
    {
        if(socket < 0)
        {
            return false;
        }

        epoll_event dummy;

        return 0==epoll_ctl(epfd, EPOLL_CTL_DEL, socket, &dummy);
    }

    bool ModSocket(int epfd, int socket, uint32_t events, void* ptr)
    {
        if(socket < 0)
            return false;
        
        epoll_event ev;
        ev.data.ptr = ptr;

        ev.events = 0;
        if(events & EventTypeRead)
        {
            ev.events |= EPOLLIN;
        }
        if(events & EventTypeWrite)
        {
            ev.events |= EPOLLOUT;
        }

        return 0==epoll_ctl(epfd, EPOLL_CTL_MOD, socket, &ev);
    }
}

EPoller::EPoller()
{
    multiplexer = epoll_create(512);
    INF << "create epoll fd: " << multiplexer;
}

#endif