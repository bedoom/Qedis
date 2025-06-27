#include <cassert>

#include <errno.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <sys/ioctl.h>
#include <net/if.h>

#if defined(__APPLE__)
#include <unistd.h>
#endif

#include "Socket.hpp"
#include "NetThreadPool.hpp"
#include "Log/Logger.hpp"