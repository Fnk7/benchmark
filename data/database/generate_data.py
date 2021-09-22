import os
import sys
import numpy as np

dst_dir = os.path.dirname(__file__)
if len(sys.argv) == 1:
    table_dir = dst_dir
else:
    table_dir = sys.argv[1]
size = [0] * 5

# Date begin
with open(os.path.join(table_dir, "date.tbl"), "r") as date:
    lines = date.readlines()
    size[4] = len(lines)
    D_DATEKEY = np.empty((len(lines), ), dtype=np.uint32)
    D_DATE = [None] * len(lines)
    D_DAYOFWEEK = [None] * len(lines)
    D_MONTH = [None] * len(lines)
    D_YEAR = np.empty((len(lines), ), dtype=np.uint16)
    D_YEARMONTHNUM = np.empty((len(lines), ), dtype=np.uint32)
    D_YEARMONTH = [None] * len(lines)
    D_DAYNUMINWEEK = np.empty((len(lines), ), dtype=np.uint8)
    D_DAYNUMINMONTH = np.empty((len(lines), ), dtype=np.uint8)
    D_DAYNUMINYEAR = np.empty((len(lines), ), dtype=np.uint16)
    D_MONTHNUMINYEAR = np.empty((len(lines), ), dtype=np.uint8)
    D_WEEKNUMINYEAR = np.empty((len(lines), ), dtype=np.uint8)
    D_SELLINGSEASON = [None] * len(lines)
    D_LASTDAYINWEEKFL = np.empty((len(lines), ), dtype=np.uint8)
    D_LASTDAYINMONTHFL = np.empty((len(lines), ), dtype=np.uint8)
    D_HOLIDAYFL = np.empty((len(lines), ), dtype=np.uint8)
    D_WEEKDAYFL = np.empty((len(lines), ), dtype=np.uint8)
    for i in range(len(lines)):
        items = lines[i].split("|")
        D_DATEKEY[i] = np.uint32(items[0])
        D_DATE[i] = items[1]
        D_DAYOFWEEK[i] = items[2]
        D_MONTH[i] = items[3]
        D_YEAR[i] = np.uint16(items[4])
        D_YEARMONTHNUM[i] = np.uint32(items[5])
        D_YEARMONTH[i] = items[6]
        D_DAYNUMINWEEK[i] = np.uint8(items[7])
        D_DAYNUMINMONTH[i] = np.uint8(items[8])
        D_DAYNUMINYEAR[i] = np.uint16(items[9])
        D_MONTHNUMINYEAR[i] = np.uint8(items[10])
        D_WEEKNUMINYEAR[i] = np.uint8(items[11])
        D_SELLINGSEASON[i] = items[12]
        D_LASTDAYINWEEKFL[i] = np.uint8(items[13])
        D_LASTDAYINMONTHFL[i] = np.uint8(items[14])
        D_HOLIDAYFL[i] = np.uint8(items[15])
        D_WEEKDAYFL[i] = np.uint8(items[16])

if not os.path.exists(os.path.join(dst_dir, "date")):
    os.mkdir(os.path.join(dst_dir, "date"))
D_DATEKEY.tofile(os.path.join(dst_dir, "date/D_DATEKEY.bin"))
D_YEAR.tofile(os.path.join(dst_dir, "date/D_YEAR.bin"))
D_YEARMONTHNUM.tofile(os.path.join(dst_dir, "date/D_YEARMONTHNUM.bin"))
D_DAYNUMINWEEK.tofile(os.path.join(dst_dir, "date/D_DAYNUMINWEEK.bin"))
D_DAYNUMINMONTH.tofile(os.path.join(dst_dir, "date/D_DAYNUMINMONTH.bin"))
D_DAYNUMINYEAR.tofile(os.path.join(dst_dir, "date/D_DAYNUMINYEAR.bin"))
D_MONTHNUMINYEAR.tofile(os.path.join(dst_dir, "date/D_MONTHNUMINYEAR.bin"))
D_WEEKNUMINYEAR.tofile(os.path.join(dst_dir, "date/D_WEEKNUMINYEAR.bin"))
D_LASTDAYINWEEKFL.tofile(os.path.join(dst_dir, "date/D_LASTDAYINWEEKFL.bin"))
D_LASTDAYINMONTHFL.tofile(os.path.join(dst_dir, "date/D_LASTDAYINMONTHFL.bin"))
D_HOLIDAYFL.tofile(os.path.join(dst_dir, "date/D_HOLIDAYFL.bin"))
D_WEEKDAYFL.tofile(os.path.join(dst_dir, "date/D_WEEKDAYFL.bin"))

lines = None
D_DATEKEY = None
D_DATE = None
D_DAYOFWEEK = None
D_MONTH = None
D_YEAR = None
D_YEARMONTHNUM = None
D_YEARMONTH = None
D_DAYNUMINWEEK = None
D_DAYNUMINMONTH = None
D_DAYNUMINYEAR = None
D_MONTHNUMINYEAR = None
D_WEEKNUMINYEAR = None
D_SELLINGSEASON = None
D_LASTDAYINWEEKFL = None
D_LASTDAYINMONTHFL = None
D_HOLIDAYFL = None
D_WEEKDAYFL = None
# Date end


# Lineorder
with open(os.path.join(table_dir, "lineorder.tbl"), "r") as lineorder:
    lines = lineorder.readlines()
    size[0] = len(lines)
    LO_ORDERKEY = np.empty((len(lines, )), np.uint64)
    LO_LINENUMBER = np.empty((len(lines, )), np.uint8)
    # LO_CUSTKEY = np.empty((len(lines, )), np.uint8)
    # LO_PARTKEY = np.empty((len(lines, )), np.uint8)
    # LO_SUPPKEY = np.empty((len(lines, )), np.uint8)
    LO_ORDERDATE = np.empty((len(lines, )), np.uint32)
    # LO_ORDERPRIORITY = np.empty((len(lines, )), np.uint8)
    # LO_SHIPPRIORITY = np.empty((len(lines, )), np.uint8)
    LO_QUANTITY = np.empty((len(lines, )), np.uint8)
    LO_EXTENDEDPRICE = np.empty((len(lines, )), np.uint64)
    LO_ORDTOTALPRICE = np.empty((len(lines, )), np.uint64)
    LO_DISCOUNT = np.empty((len(lines, )), np.uint8)
    LO_REVENUE = np.empty((len(lines, )), np.uint64)
    LO_SUPPLYCOST = np.empty((len(lines, )), np.uint64)
    LO_TAX = np.empty((len(lines, )), np.uint8)
    LO_COMMITDATE = np.empty((len(lines, )), np.uint32)
    # LO_SHIPMODE = np.empty((len(lines, )), np.uint8)
    for i in range(len(lines)):
        items = lines[i].split("|")
        LO_ORDERKEY[i] = np.uint64(items[0])
        LO_LINENUMBER[i] = np.uint8(items[1])
        # LO_CUSTKEY[i] = np.uint8(items[2])
        # LO_PARTKEY[i] = np.uint8(items[3])
        # LO_SUPPKEY[i] = np.uint8(items[4])
        LO_ORDERDATE[i] = np.uint32(items[5])
        # LO_ORDERPRIORITY[i] =  np.uint8(items[6])
        # LO_SHIPPRIORITY[i] = np.uint8(items[7])
        LO_QUANTITY[i] = np.uint8(items[8])
        LO_EXTENDEDPRICE[i] = np.uint64(items[9])
        LO_ORDTOTALPRICE[i] = np.uint64(items[10])
        LO_DISCOUNT[i] = np.uint8(items[11])
        LO_REVENUE[i] = np.uint64(items[12])
        LO_SUPPLYCOST[i] = np.uint64(items[13])
        LO_TAX[i] = np.uint8(items[14])
        LO_COMMITDATE[i] = np.uint32(items[15])
        # LO_SHIPMODE[i] = np.uint8(items[16])

if not os.path.exists(os.path.join(dst_dir, "lineorder")):
    os.mkdir(os.path.join(dst_dir, "lineorder"))
LO_ORDERKEY.tofile(os.path.join(dst_dir, "lineorder/LO_ORDERKEY.bin"))
LO_LINENUMBER.tofile(os.path.join(dst_dir, "lineorder/LO_LINENUMBER.bin"))
# LO_CUSTKEY.tofile(os.path.join(dst_dir, "lineorder/LO_CUSTKEY.bin"))
# LO_PARTKEY.tofile(os.path.join(dst_dir, "lineorder/LO_PARTKEY.bin"))
# LO_SUPPKEY.tofile(os.path.join(dst_dir, "lineorder/LO_SUPPKEY.bin"))
LO_ORDERDATE.tofile(os.path.join(dst_dir, "lineorder/LO_ORDERDATE.bin"))
# LO_ORDERPRIORITY.tofile(os.path.join(dst_dir, "lineorder/LO_ORDERPRIORITY.bin"))
# LO_SHIPPRIORITY.tofile(os.path.join(dst_dir, "lineorder/LO_SHIPPRIORITY.bin"))
LO_QUANTITY.tofile(os.path.join(dst_dir, "lineorder/LO_QUANTITY.bin"))
LO_EXTENDEDPRICE.tofile(os.path.join(dst_dir, "lineorder/LO_EXTENDEDPRICE.bin"))
LO_ORDTOTALPRICE.tofile(os.path.join(dst_dir, "lineorder/LO_ORDTOTALPRICE.bin"))
LO_DISCOUNT.tofile(os.path.join(dst_dir, "lineorder/LO_DISCOUNT.bin"))
LO_REVENUE.tofile(os.path.join(dst_dir, "lineorder/LO_REVENUE.bin"))
LO_SUPPLYCOST.tofile(os.path.join(dst_dir, "lineorder/LO_SUPPLYCOST.bin"))
LO_TAX.tofile(os.path.join(dst_dir, "lineorder/LO_TAX.bin"))
LO_COMMITDATE.tofile(os.path.join(dst_dir, "lineorder/LO_COMMITDATE.bin"))
# LO_SHIPMODE.tofile(os.path.join(dst_dir, "lineorder/LO_SHIPMODE.bin"))

lines = None
LO_ORDERKEY = None
LO_LINENUMBER = None
# LO_CUSTKEY = None
# LO_PARTKEY = None
# LO_SUPPKEY = None
LO_ORDERDATE = None
# LO_ORDERPRIORITY = None
# LO_SHIPPRIORITY = None
LO_QUANTITY = None
LO_EXTENDEDPRICE = None
LO_ORDTOTALPRICE = None
LO_DISCOUNT = None
LO_REVENUE = None
LO_SUPPLYCOST = None
LO_TAX = None
LO_COMMITDATE = None
# LO_SHIPMODE = None
# Lineorder end

size = np.array(size, dtype=np.uint32)
size.tofile(os.path.join(dst_dir, "size.bin"))
