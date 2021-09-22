#include "workload.h"

class Database : public Workload
{
protected:
    std::string datapath;
    uint32_t lineorder_size;
    uint32_t part_size;
    uint32_t supplier_size;
    uint32_t customer_size;
    uint32_t date_size;

public:
    Database(std::string datapath) : datapath(move(datapath)) {}
    void init();
    void run() = 0;
    bool check() = 0;
    void release() = 0;
};

