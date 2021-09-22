#include "database.h"

using namespace std;

void Database::init()
{
    cout << "Init:" << endl;
    uint32_t size[5];
    load_bin(datapath + "/size.bin", size, sizeof(size));
    lineorder_size = size[0];
    part_size = size[1];
    supplier_size = size[2];
    customer_size = size[3];
    date_size = size[4];
    cout << "lineorder_size " << lineorder_size << endl;
    cout << "part_size " << part_size << endl;
    cout << "supplier_size " << supplier_size << endl;
    cout << "customer_size " << customer_size << endl;
    cout << "date_size " << date_size << endl;
}
