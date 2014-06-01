/**
 * \brief Alternative version of standard assertion macro. Just prints information
 * and doesn't terminate the programm. Additionally, a second form allows to 
 * add a self-defined text.
 *
 * File:   ti_assertion.h
 * \author Prof. Dr. Th. Lehmann
 * \version 1.0
 * \date    19.09.2012
 *  
 * \author Prof. Dr. Th. Lehmann
 * \version 2.0
 * \date    02.12.2013
 * \changes Version for additional text message
 */

#ifndef TI_ASSERTION_H
#define	TI_ASSERTION_H

#include <cstdio>
using namespace std;

#define ASSERT(e) do{ \
(e) ? 0 : printf("assertion fail %s, in %s, line %i\n", #e, __FILE__, __LINE__); \
} while(0)

#define ASSERT_M(m,e) do{ \
(e) ? 0 : printf(m ", assertion fail %s, in %s, line %i\n", #e, __FILE__, __LINE__); \
} while(0)

#endif	/* TI_ASSERTION_H */
