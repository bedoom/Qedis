#pragma once

#include <mutex>
#include <atomic>

#include <Buffer.hpp>
#include <UnboundedBuffer.hpp>

class AsyncBuffer
{
public:
    explicit
    AsyncBuffer(std::size_t size = 128 * 1024);
    ~AsyncBuffer();

    void Write(const void* data, std::size_t len);
    void Write(const BufferSequence& data);

    void ProcessBuffer(BufferSequence& data);
    void Skip(std::size_t size);

private:
    Buffer buffer_;

    qeids::UnboundedBuffer tmpBuf_;

    std::mutex backBufLock_;
    std::atomic<std::size_t> backBytes_;
    qeids::UnboundedBuffer backBuf_;
};