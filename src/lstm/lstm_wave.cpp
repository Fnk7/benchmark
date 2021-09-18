#include "lstm.h"

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

    void run()
    {
        // TODO
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
