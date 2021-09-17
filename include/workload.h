#pragma once

#include <cstddef>

class Workload
{
public:
    void* aligned_malloc(size_t size, size_t alignment);
    void aligned_free(void *p);
    virtual void init() = 0;
    virtual void run() = 0;
    virtual bool check() = 0;
    virtual void release() = 0;
    void evaluate();
};

