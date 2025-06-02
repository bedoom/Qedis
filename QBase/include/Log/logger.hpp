#pragma once

#include <string>
#include <set>
#include <memory>

#include <Threads/ThreadPool.hpp>
#include <AsyncBuffer.hpp>
#include <Log/MemoryFile.hpp>
#include <Timer.hpp>

enum LogLevel
{
    logINFO     = 0x01 << 0,
    logDEBUG    = 0x01 << 1,
    logWARN     = 0x01 << 2,
    logERROR    = 0x01 << 3,
    logUSR      = 0x01 << 4,
    logALL      = 0xFFFFFFFF,
};

enum LogDest
{
    logConsole  = 0x01 << 0,     
    logFILE     = 0x01 << 1,     
    logSocket   = 0x01 << 2,     
};

unsigned int ConvertLogLevel(const std::string& level);

class Logger
{
public:
    Logger(const Logger&) = delete;
    void operator= (const Logger&) = delete;

    bool Init(unsigned int level = logDEBUG, 
                unsigned int dest = logConsole,
                const char* pDir = 0);
    
    void Flush(LogLevel level);
    bool IsLevelForbid(unsigned int level) { return !(level & level_); };

    Logger&  operator<<(const char* msg);
    Logger&  operator<<(const unsigned char* msg);
    Logger&  operator<<(const std::string& msg);
    Logger&  operator<<(void* );
    Logger&  operator<<(unsigned char a);
    Logger&  operator<<(char a);
    Logger&  operator<<(unsigned short a);
    Logger&  operator<<(short a);
    Logger&  operator<<(unsigned int a);
    Logger&  operator<<(int a);
    Logger&  operator<<(unsigned long a);
    Logger&  operator<<(long a);
    Logger&  operator<<(unsigned long long a);
    Logger&  operator<<(long long a);
    Logger&  operator<<(double a);

private:
    Logger();
    ~Logger();

    static const size_t MAXLINE_LOG = 2048;
    char tmpBuffer_[MAXLINE_LOG];
    std::size_t pos_;

    Time time_;

    unsigned int level_;
    std::string directory;
    unsigned int dest_;
    std::string fileName_;

    unsigned int curLevel_;

    AsyncBuffer buffer_;
    OutputMemoryFile file_;
}
