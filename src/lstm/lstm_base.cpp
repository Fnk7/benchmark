#include "lstm.h"

class BaseLSTM : public LSTM
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
    Workload *workload = new BaseLSTM();
    workload->evaluate();
    return 0;
}
