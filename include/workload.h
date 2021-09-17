#pragma once

#include <cstddef>
#include <string>

class Workload
{
public:
    virtual void init() = 0;
    virtual void run() = 0;
    virtual bool check() = 0;
    virtual void release() = 0;
    void evaluate();

public:
    void* aligned_malloc(size_t size, size_t alignment);
    void aligned_free(void *p);
    void load_bin(std::string filename, void *data, size_t size);
};

