#include "lstm.h"

class WaveLSTM : public LSTM
{
public:
    void init()
    {
        LSTM::init();
    }

    void run()
    {
        // TODO
    }
};

int main()
{
    Workload *workload = new WaveLSTM();
    workload->evaluate();
    return 0;
}
