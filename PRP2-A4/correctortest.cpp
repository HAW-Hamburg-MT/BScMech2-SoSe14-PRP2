/**
 * \brief Tests suite for all tests of corrector classes.
 * \author Lehmann
 * \date 2013-12-03
 */
#include "correctortest.h"

CorrectorTestSuite::CorrectorTestSuite() {
    testAllCorrectors();
}

void CorrectorTestSuite::testAllCorrectors(){
    TestCorrectorLinear linearTester;           // IMPORTANT: without parentheses
    TestCorrectorLookupTable lookupTableTester; // IMPORTANT: without parentheses
}