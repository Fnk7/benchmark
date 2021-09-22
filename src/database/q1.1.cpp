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
        lineorder_lo_orderdate = (uint32_t *)aligned_malloc(lineorder_size * sizeof(uint32_t), 8);
        lineorder_lo_quantity = (uint8_t *)aligned_malloc(lineorder_size * sizeof(uint8_t), 8);
        lineorder_lo_extendedprice = (uint64_t *)aligned_malloc(lineorder_size * sizeof(uint64_t), 8);
        lineorder_lo_discount = (uint8_t *)aligned_malloc(lineorder_size * sizeof(uint8_t), 8);
        date_d_datekey = (uint32_t *)aligned_malloc(lineorder_size * sizeof(uint32_t), 8);
        date_d_year = (uint16_t *)aligned_malloc(lineorder_size * sizeof(uint16_t), 8);
        load_bin(datapath + "lineorder/LO_ORDERDATE.bin", lineorder_lo_orderdate, lineorder_size * sizeof(uint32_t));
        load_bin(datapath + "lineorder/LO_QUANTITY.bin", lineorder_lo_quantity, lineorder_size * sizeof(uint8_t));
        load_bin(datapath + "lineorder/LO_EXTENDEDPRICE.bin", lineorder_lo_extendedprice, lineorder_size * sizeof(uint64_t));
        load_bin(datapath + "lineorder/LO_DISCOUNT.bin", lineorder_lo_discount, lineorder_size * sizeof(uint8_t));
        load_bin(datapath + "date/D_DATEKEY.bin", date_d_datekey, lineorder_size * sizeof(uint32_t));
        load_bin(datapath + "date/D_YEAR.bin", date_d_year, lineorder_size * sizeof(uint16_t));
    }
    
    void run()
    {
        // TODO
    }
    
    bool check()
    {
        // TODO
        return true;
    }
    
    void release()
    {
        aligned_free(lineorder_lo_orderdate);
        aligned_free(lineorder_lo_quantity);
        aligned_free(lineorder_lo_extendedprice);
        aligned_free(lineorder_lo_discount);
        aligned_free(date_d_datekey);
        aligned_free(date_d_year);
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
