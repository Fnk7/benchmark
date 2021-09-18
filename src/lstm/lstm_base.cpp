#include "lstm.h"

#include <cmath>
#include <cstring>
#include <iostream>

using namespace std;

class BaseLSTM : public LSTM
{
public:
    BaseLSTM(string datapath) : LSTM(datapath) {}

    void init()
    {
        LSTM::init();
    }

    float sigmoid(float x)
    {
        return 1.0f / (1.0f + expf(-x));
    }

    void forward(float *__restrict__ W, float *__restrict__ U, float *__restrict__ bias,
                    float *__restrict__ input, float *__restrict__ state,
                    float *__restrict__ state_c, float *__restrict__ state_h,
                    float *__restrict__ state_h2)
    {
        for (int j = 0; j < hidden_size * 4; j++)
            state[j] = bias[j];
        for (int i = 0; i < hidden_size; i++)
        {
            for (int j = 0; j < hidden_size * 4; j++)
            {
                state[j] += W[j] * input[i];
                state[j] += U[j] * state_h[i];
            }
            W += hidden_size * 4;
            U += hidden_size * 4;
        }
        float *s_i = &state[0 * hidden_size];
        float *s_f = &state[1 * hidden_size];
        float *s_c = &state[2 * hidden_size];
        float *s_h = &state[3 * hidden_size];
        for (int i = 0; i < hidden_size; i++)
        {
            float new_c = state_c[i] * sigmoid(s_f[i]);
            float add_c = sigmoid(s_i[i]) * tanhf(s_c[i]);
            new_c += add_c;
            state_c[i] = new_c;
            state_h2[i] = tanhf(new_c) * sigmoid(s_h[i]);
        }
    }

    void run()
    {
        float *state_c = (float *)aligned_malloc(hidden_size * sizeof(float), 8);
        float *state_h = (float *)aligned_malloc((time_steps + 1) * hidden_size * sizeof(float), 8);
        float *state = (float *)aligned_malloc(hidden_size * 4 * sizeof(float), 8);
        float *W2 = W;
        float *U2 = U;
        float *bias2 = bias;
        memset(state_h, 0, hidden_size * sizeof(float));
        for (uint32_t layer = 0; layer < layer_num; layer++)
        {
            if (layer != 0)
                memcpy(input, &state_h[hidden_size], time_steps * hidden_size * sizeof(float));
            memset(state_c, 0, hidden_size * sizeof(float));
            for (uint32_t time = 0; time < time_steps; time++)
                forward(W2, U2, bias2, &input[time * hidden_size], state, state_c,
                        &state_h[time * hidden_size], &state_h[(time + 1) * hidden_size]);
            W2 += hidden_size * hidden_size * 4;
            U2 += hidden_size * hidden_size * 4;
            bias2 += hidden_size * 4;
        }
        memcpy(output, &state_h[time_steps * hidden_size], hidden_size * sizeof(float));
        aligned_free(state_c);
        aligned_free(state_h);
        aligned_free(state);
    }
};

int main(int argc, const char ** argv)
{
    if (argc != 2)
    {
        cerr << "Datapath should be specify!!!" << endl;
        return 1;
    }
    Workload *workload = new BaseLSTM(argv[1]);
    workload->evaluate();
    return 0;
}
