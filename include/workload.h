#pragma once

class Workload
{
public:
    Workload() = delete;
    void* align_malloc(size_t size, size_t alignment);
    void align_free();
    virtual void init() = delete;
    virtual void run() = delete;
    virtual bool check() = delete();
    virtual void release() = delete();
    void evaluate();
}

