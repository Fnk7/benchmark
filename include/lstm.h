#include "workload.h"

#include <cmath>
#include <string>

class LSTM : public Workload
{
protected:
    std::string datapath;
    float *W, *U, *bias;
    float *input, *output;
    float *output2;
    uint32_t batch_size;
    uint32_t time_steps;
    uint32_t layer_num;
    uint32_t hidden_size;

public:
    LSTM(std::string datapath) : datapath(move(datapath)) {}
    void init();
    void run() = 0;
    bool check();
    void release();

public:
    static inline float sigmoid(float x)
    {
        return 1.0f / (1.0f + expf(-x));
    }
};
