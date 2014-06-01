/* \brief Test class for the sensor value correction classe. Tests various
 *        test case on creation of the test objcet.
 * \File   test.h
 * \author Lehmann
 * \date 2013-12-01
 * \version 1.0
 */

#ifndef CORRECTORTEST_H
#define	CORRECTORTEST_H

#include "correctorlineartest.h"
#include "correctorlookuptabletest.h"

class CorrectorTestSuite {
public:
    CorrectorTestSuite();
private:
    void testAllCorrectors();
};

#endif	/* CORRECTORTEST_H */

