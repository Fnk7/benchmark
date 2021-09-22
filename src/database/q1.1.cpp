#include "database.h"

#include <iostream>

using namespace std;

class Q1_1 : public Database
{
private:
    uint32_t *lineorder_lo_orderdate;
    uint8_t  *lineorder_lo_quantity;
    uint64_t *lineorder_lo_extendedprice;
    uint8_t  *lineorder_lo_discount;
    uint32_t *date_d_datekey;
    uint16_t *date_d_year;

    uint64_t sum;

public:
    Q1_1(string datapath) : Database(datapath) {}
    
    void init()
    {
        Database::init();
        lineorder_lo_orderdate = (uint32_t *)aligned_malloc(lineorder_size * sizeof(uint32_t), 8);
        lineorder_lo_quantity = (uint8_t *)aligned_malloc(lineorder_size * sizeof(uint8_t), 8);
        lineorder_lo_extendedprice = (uint64_t *)aligned_malloc(lineorder_size * sizeof(uint64_t), 8);
        lineorder_lo_discount = (uint8_t *)aligned_malloc(lineorder_size * sizeof(uint8_t), 8);
        date_d_datekey = (uint32_t *)aligned_malloc(date_size * sizeof(uint32_t), 8);
        date_d_year = (uint16_t *)aligned_malloc(date_size * sizeof(uint16_t), 8);
        load_bin(datapath + "lineorder/LO_ORDERDATE.bin", lineorder_lo_orderdate, lineorder_size * sizeof(uint32_t));
        load_bin(datapath + "lineorder/LO_QUANTITY.bin", lineorder_lo_quantity, lineorder_size * sizeof(uint8_t));
        load_bin(datapath + "lineorder/LO_EXTENDEDPRICE.bin", lineorder_lo_extendedprice, lineorder_size * sizeof(uint64_t));
        load_bin(datapath + "lineorder/LO_DISCOUNT.bin", lineorder_lo_discount, lineorder_size * sizeof(uint8_t));
        load_bin(datapath + "date/D_DATEKEY.bin", date_d_datekey, date_size * sizeof(uint32_t));
        load_bin(datapath + "date/D_YEAR.bin", date_d_year, date_size * sizeof(uint16_t));
        sum = 0;
    }
    
    void run()
    {
        uint8_t *cond1_lo_discount = new uint8_t[lineorder_size];
        uint64_t *cond1_lo_extendedprice = new uint64_t[lineorder_size];
        uint32_t *cond1_lo_orderdate = new uint32_t[lineorder_size];
        uint64_t cond1_size = 0;
        for (uint32_t i = 0; i < lineorder_size; i++)
        {
            if (lineorder_lo_discount[i] <=3 && lineorder_lo_discount[i] >= 1 && lineorder_lo_quantity[i] < 25)
            {
                cond1_lo_discount[cond1_size] = lineorder_lo_discount[i];
                cond1_lo_extendedprice[cond1_size] = lineorder_lo_extendedprice[i];
                cond1_lo_orderdate[cond1_size] = lineorder_lo_orderdate[i];
	            cond1_size++;
            }
        }
        uint32_t *cond2_d_datekey = new uint32_t[date_size];
        uint32_t cond2_size = 0;
        for (uint32_t i = 0; i < date_size; i++)
        {
            if (date_d_year[i] == 1993)
            {
                cond2_d_datekey[cond2_size] = date_d_datekey[i];
                cond2_size++;
            }
        }
        for (uint32_t i = 0; i < cond1_size; i++)
        {
            for (uint32_t j = 0; j < cond2_size; j++)
            {
                if (cond1_lo_orderdate[i] == cond2_d_datekey[j])
                {
                    sum += cond1_lo_discount[i] * cond1_lo_extendedprice[i]; 
                    break; 
                }
            }
        }
    }
    
    bool check()
    {
        // TODO
        cout << "Result is:" << endl;
        cout << sum << endl;
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
