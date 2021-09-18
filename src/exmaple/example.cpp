#include "workload.h"

#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

class Example : public Workload
{
private:
    string datapath;
    int size;
    float *a, *b, *c, *c2;

public:
    Example(string datapath) : datapath(move(datapath)) {}

    void init()
    {
        cout << "Init:" << endl;
        load_bin(datapath + "/size.bin", &size, sizeof(size));
        cout << "    size is " << size << endl;
        a = (float *)aligned_malloc(size * sizeof(float), 8);
        b = (float *)aligned_malloc(size * sizeof(float), 8);
        c = (float *)aligned_malloc(size * sizeof(float), 8);
        c2 = (float *)aligned_malloc(size * sizeof(float), 8);
        load_bin(datapath + "/a.bin", a, size * sizeof(float));
        load_bin(datapath + "/b.bin", b, size * sizeof(float));
        load_bin(datapath + "/c.bin", c, size * sizeof(float));
        load_bin(datapath + "/c2.bin", c2, size * sizeof(float));
    }

    void fma(float *__restrict__ a, float *__restrict__ b, float *__restrict__ c)
    {
        for (int i = 0; i < size; i++)
            c[i] += a[i] * b[i];
    }

    void run()
    {
        fma(a, b, c);
    }

    bool check()
    {
        for (int i = 0; i < size; i++)
            if (abs(c2[i] - c[i]) > 0.001)
                return false;
        return true;
    }

    void release()
    {
        aligned_free(a);
        aligned_free(b);
        aligned_free(c);
    }
};

int main(int argc, const char ** argv)
{
    if (argc != 2)
    {
        cerr << "Datapath should be specify!!!" << endl;
        return 1;
    }
    Workload *workload = new Example(argv[1]);
    workload->evaluate();
    return 0;
}
