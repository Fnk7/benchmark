#include "workload.h"

#include <iostream>
#include <time.h>

using namespace std;

void *Workload::align_malloc(size_t size, size_t alignment)
{
    // TODO
    return (void *)0;
}

void Workload::align_free()
{
    // TODO
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
    bool success = check();
    if (success)
        cout << "Used clock: " << (end - begin) << endl;
    else
        cout << "Check failed!!!" << endl << "Used clock: " << (end - begin) << endl;
    // release
    release();
    return success ? 0 : 1;
}

