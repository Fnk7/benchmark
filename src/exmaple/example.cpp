#include "workload.h"

#include <iostream>
#include <algorithm>

using namespace std;

class Example : public Workload
{
private:
    const int size = 64 * 2000;
    float *a, *b, *c;

public:
    void init()
    {
        cout << "init()" << endl;
        a = (float *)aligned_malloc(size * sizeof(float), 8);
        b = (float *)aligned_malloc(size * sizeof(float), 8);
        c = (float *)aligned_malloc(size * sizeof(float), 8);
        cout << a << endl;
        cout << b << endl;
        cout << c << endl;
        for (int i = 0; i < size; i++)
        {
            a[i] = 1.0 * i;
            b[i] = i & 1 == 0 ? 0.01 * i : 0.001 * i ;
            c[i] = 0.0;
        }
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
            if (abs(c[i] - a[i] * b[i]) / (abs(c[i]) + 1.0) > 0.001)
                return false;
        return true;
    }

    void release()
    {
        cout << "release()" << endl;
        aligned_free(a);
        aligned_free(b);
        aligned_free(c);
    }
};

int main()
{
    Workload *workload = new Example();
    workload->evaluate();
    return 0;
}
