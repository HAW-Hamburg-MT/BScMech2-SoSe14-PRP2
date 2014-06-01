/**
 * \file correctorlookuptabletest.cpp
 * \autor Lehmann
 * \date 2013-12-03
 */

#include "correctorlookuptabletest.h"
#include <math.h>

TestCorrectorLookupTable::TestCorrectorLookupTable() {
    testSensorLookupTableSimple();
    testSensorLookupTableSorting();
}

void TestCorrectorLookupTable::testSensorLookupTableSimple() {
    double x[5] = {-2.0, 0.0, 2.0, 4.0, 5.0};
    double y[5] = {-1.0, 0.0, 2.0, 1.0, 3.0};
    Corrector* uutLookup = new CorrectorLookupTable(x, y);

    // within reference points
    ASSERT(uutLookup->correctValue(-1.0) == -.5);
    ASSERT(uutLookup->correctValue(0.0) == 0.0);
    ASSERT(uutLookup->correctValue(1.0) == 1.0);
    ASSERT(uutLookup->correctValue(3.0) == 1.5);
    ASSERT(uutLookup->correctValue(4.5) == 2.0);

    // outside reference points
    ASSERT(uutLookup->correctValue(-4.0) == -2.0);
    ASSERT(uutLookup->correctValue(6.0) == 5.0);
    delete uutLookup;
}

void TestCorrectorLookupTable::testSensorLookupTableSorting() {
    double x[5] = {4.0, 0.0, 1.0, -4.0, -2.0};
    double y[5] = {16.0, 0.0, 1.0, -16.0, -4.0};
    Corrector* uutLookup = new CorrectorLookupTable(x, y);

    // within reference points
    ASSERT_M("Sorting", uutLookup->correctValue(-1.0) == -2.0);
    ASSERT_M("Sorting", uutLookup->correctValue(-3.0) == -10.0);
    ASSERT_M("Sorting", uutLookup->correctValue(0.5) == 0.5);
    ASSERT_M("Sorting", uutLookup->correctValue(3.0) == 11.0);

    // outside reference points
    ASSERT_M("Sorting", uutLookup->correctValue(-5.0) == -22.0);
    ASSERT_M("Sorting", uutLookup->correctValue(6.0) == 26.0);
    delete uutLookup;
}

