#include "workload.h"

#include <fstream>
#include <iostream>
#include <time.h>

using namespace std;

void *Workload::aligned_malloc(size_t size, size_t alignment)
{
    if (alignment < 3)
        alignment = 3;
    if (alignment > 8)
        alignment = 8;
    alignment = 1 << alignment;
    size_t offset = alignment -1 + sizeof(uint8_t *);
    uint8_t *p1 = new uint8_t[size + offset];
    offset = offset - ((size_t)(p1 + offset) & (alignment - 1));
    void **p2 = (void **)(p1 + offset);
    p2[-1] = p1;
    return (void *)p2;
}

void Workload::aligned_free(void *p)
{
    delete ((uint8_t **)p)[-1];
}

void Workload::evaluate()
{
    // init
    init();
    auto begin = clock();
    // run
    run();
    auto end = clock();
    // check
    if (check())
        cout << "Used clock: " << (end - begin) << endl;
    else
        cout << "Check failed!!!" << endl << "Used clock: " << (end - begin) << endl;
    // release
    release();
}

void Workload::load_bin(string filename, void *data, size_t size)
{
    ifstream in(filename, ios::in | ios::binary);
    in.read((char *)data, size);
    in.close();
}
