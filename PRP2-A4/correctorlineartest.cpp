/**
 * \file correctorlineartest.cpp
 * \author Lehmann
 * \date 2013-12-03
 */

#include "correctorlineartest.h"

TestCorrectorLinear::TestCorrectorLinear(){
    testCorrectorLinearFull();
}

void TestCorrectorLinear::testCorrectorLinearFull() {
    Corrector* uutLinear = new CorrectorLinear();
    ASSERT(uutLinear->correctValue(1.0) == 1.0);
    ASSERT(uutLinear->correctValue(-1.0) == -1.0);
    ASSERT(uutLinear->correctValue(2.0) == 2.0);
    ASSERT(uutLinear->correctValue(10) == 10);
    delete uutLinear;


    uutLinear = new CorrectorLinear(2, -1);
    ASSERT(uutLinear->correctValue(0) == -1);
    ASSERT(uutLinear->correctValue(10) == 19);
    delete uutLinear;
}
