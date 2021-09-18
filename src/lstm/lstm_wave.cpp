#include "lstm.h"

#include <cstring>
#include <iostream>

using namespace std;

class WaveLSTM : public LSTM
{
public:
    WaveLSTM(string datapath) : LSTM(datapath) {}

    void init()
    {
        LSTM::init();
    }
    
    void forward(float *__restrict__ W, float *__restrict__ U, float *__restrict__ bias, float *__restrict__ input, float *__restrict__ output)
    {
        float state_c[layer_num][hidden_size];
        float state_h[2][layer_num + 1][hidden_size];
        float *state_h_next = &state_h[0][0][0];
        float *state_h_self = &state_h[1][0][0];
        memset(&state_c[0][0], 0, sizeof(state_c));
        memset(&state_h_self[hidden_size], 0, layer_num * hidden_size * sizeof(float));
        for (int wave = 0; wave < layer_num + time_steps - 1; wave++)
        {
            int layer_min = 0;
            int layer_max = layer_num;
            if (wave >= time_steps)
                layer_min = wave - time_steps + 1;
            else
                memcpy(state_h_self, &input[wave * hidden_size], hidden_size * sizeof(float));
            if (wave < layer_num)
                layer_max = wave + 1;
            // #pragma omp
            for (int layer = layer_min; layer < layer_max; layer++)
            {
                float h[4 * hidden_size];
                for (int i = 0; i < hidden_size * 4; i++)
                {
                    h[i] = bias[layer * 4 * hidden_size + i];
                }
                float *Wl = &W[layer * hidden_size * 4 * hidden_size];
                float *Ul = &U[layer * hidden_size * 4 * hidden_size];
                float *state_hl = &state_h_self[layer * hidden_size];
                float *state_hl1 = &state_hl[hidden_size];
                for (int j = 0; j < hidden_size; j++)
                {
                    float *Wj = &Wl[j * 4 * hidden_size];
                    float *Uj = &Ul[j * 4 * hidden_size];
                    float state_hj = state_hl[j];
                    float state_hj1 = state_hl1[j];
#pragma ivdep
#pragma vector always
                    for (int i = 0; i < hidden_size * 4; i++)
                    {
                        h[i] += Wj[i] * state_hj;
                        h[i] += Uj[i] * state_hj1;
                    }
                }
#pragma ivdep
#pragma vector always
                for (int i = 0; i < hidden_size; i++)
                {
                    float new_c = state_c[layer][i] * sigmoid(h[1 * hidden_size + i]);
                    float add_c = sigmoid(h[0 * hidden_size + i]) * tanhf(h[2 * hidden_size + i]);
                    new_c += add_c;
                    state_c[layer][i] = new_c;
                    state_h_next[(layer + 1) * hidden_size + i] = tanhf(new_c) * sigmoid(h[3 * hidden_size + i]);
                }
            }
            float *swap;
            swap = state_h_self;
            state_h_self = state_h_next;
            state_h_next = swap;
        }
        memcpy(output, &state_h_self[layer_num * hidden_size], hidden_size * sizeof(float));
    }

    void run()
    {
        forward(W, U, bias, input, output);
    }
};

int main(int argc, const char ** argv)
{
    if (argc != 2)
    {
        cerr << "Datapath should be specify!!!" << endl;
        return 1;
    }
    Workload *workload = new WaveLSTM(argv[1]);
    workload->evaluate();
    return 0;
}
