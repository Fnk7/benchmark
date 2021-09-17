#pragma once

class Workload
{
public:
    void* align_malloc(size_t size, size_t alignment);
    void align_free();
    virtual void init() = 0;
    virtual void run() = 0;
    virtual bool check() = 0;
    virtual void release() = 0;
    void evaluate();
}

