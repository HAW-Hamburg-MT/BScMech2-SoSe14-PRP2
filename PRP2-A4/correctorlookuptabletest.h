/* 
 * \brief  Unit Test for CorrectorLookupTable
 * \file   correctorlookuptabletest.h
 * \author Lehmann
 * \date 2013-12-03
 */

#ifndef CORRECTORLOOKUPTABLETEST_H
#define	CORRECTORLOOKUPTABLETEST_H
#include "ti_assertion.h"
#include "correctorlookuptable.h"

#define TEST_EPSILON 0.0001

class TestCorrectorLookupTable {
public:
    TestCorrectorLookupTable();
private:
    void testSensorLookupTableSimple();
    void testSensorLookupTableSorting();
 };


#endif	/* CORRECTORLOOKUPTABLETEST_H */

