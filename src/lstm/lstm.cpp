#include "lstm.h"
#include "algorithm"

using namespace std;

void LSTM::init()
{
    W = (float *)aligned_malloc(layer_num * hidden_size * hidden_size * 4 * sizeof(float), 8);
    U = (float *)aligned_malloc(layer_num * hidden_size * hidden_size * 4 * sizeof(float), 8);
    bias = (float *)aligned_malloc(layer_num * hidden_size * 4 * sizeof(float), 8);
    input = (float *)aligned_malloc(time_steps * hidden_size * sizeof(float), 4);
    output = (float *)aligned_malloc(hidden_size * sizeof(float), 4);
    output2 = (float *)aligned_malloc(hidden_size * sizeof(float), 4);
    for (int i = 0; i < layer_num * hidden_size * hidden_size * 4; i++)
    {
        W[i] = 0.0;
        U[i] = 0.0;
    }
    for (int i = 0; i < layer_num * hidden_size * 4; i++)
        bias[i] = 0.0;
    // TODO: load from file?
    //       or directly use a memory address
}

bool LSTM::check()
{
    for (int i = 0; i < hidden_size; i++)
        if (abs(output[i] - output2[i]) / (abs(output2[i]) + 0.001) > 0.001)
            return false;
    return true;
}

void LSTM::release()
{
    aligned_free(W);
    aligned_free(U);
    aligned_free(bias);
    aligned_free(input);
    aligned_free(output);
    aligned_free(output2);
}

