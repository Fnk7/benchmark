#include "database.h"

#include <iostream>

class Q1_1 : public Database
{
private:
    uint32_t *lineorder_lo_orderdate;
    uint8_t  *lineorder_lo_quantity;
    uint64_t *lineorder_lo_extendedprice;
    uint8_t  *lineorder_lo_discount;
    uint32_t *date_d_datekey;
    uint16_t *date_d_year;

public:
    Q1_1(string datapath) : Database(datapath) {}
    
    void init()
    {
        Database::init();
        // TODO
    }
    
    void run()
    {
        // TODO
    }
    
    bool check()
    {
        // TODO
    }
    
    void release()
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
    Workload *workload = new Q1_1(argv[1]);
    workload->evaluate();
    return 0;
}
