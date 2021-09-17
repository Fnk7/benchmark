#include "workload.h"

class LSTM : public Workload
{
protected:
    float *W, *U, *bias;
    float *input, *output;
    float *output2;
    int batch_size = 1;
    int time_steps = 64;
    int layer_num = 8;
    int hidden_size = 256;

public:
    void init();
    void run() = 0;
    bool check();
    void release();
};
