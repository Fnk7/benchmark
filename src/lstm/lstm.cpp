#include "lstm.h"

#include <cassert>
#include <iostream>
#include <algorithm>

using namespace std;

void LSTM::init()
{
    cout << "Init:" << endl;
    uint32_t size[4];
    load_bin(datapath + "/size.bin", size, sizeof(size));
    batch_size = size[0];
    time_steps = size[1];
    layer_num = size[2];
    hidden_size = size[3];
    cout << "    batch_size : " << batch_size << endl;
    cout << "    time_steps : " << time_steps << endl;
    cout << "    layer_num  : " << layer_num << endl;
    cout << "    hidden_size: " << hidden_size << endl;
    assert(batch_size == 1);
    W = (float *)aligned_malloc(layer_num * hidden_size * hidden_size * 4 * sizeof(float), 8);
    load_bin(datapath + "/W.bin", W, layer_num * hidden_size * hidden_size * 4 * sizeof(float));
    U = (float *)aligned_malloc(layer_num * hidden_size * hidden_size * 4 * sizeof(float), 8);
    load_bin(datapath + "/U.bin", U, layer_num * hidden_size * hidden_size * 4 * sizeof(float));
    bias = (float *)aligned_malloc(layer_num * hidden_size * 4 * sizeof(float), 8);
    load_bin(datapath + "/bias.bin", bias, layer_num * hidden_size * 4 * sizeof(float));
    input = (float *)aligned_malloc(time_steps * hidden_size * sizeof(float), 4);
    load_bin(datapath + "/input.bin", input, time_steps * hidden_size * sizeof(float));
    output = (float *)aligned_malloc(hidden_size * sizeof(float), 4);
    output2 = (float *)aligned_malloc(hidden_size * sizeof(float), 4);
    load_bin(datapath + "/output.bin", output2, hidden_size * sizeof(float));
}

bool LSTM::check()
{
    for (int i = 0; i < hidden_size; i++)
        if (abs(output[i] - output2[i]) > 0.001)
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

