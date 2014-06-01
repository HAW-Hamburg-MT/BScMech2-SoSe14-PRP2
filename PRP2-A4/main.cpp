/* Example for main that corrects sensor data from a file with linear correction
 * and lookup-table.
 * \file   main.cpp
 * \author Lehmann
 * \data 2013-12-02
 * \version 1.0
 */

#include <cstdlib>

using namespace std;

#include "correctortest.h"
#include "datareader.h"

/**
 * \brief Example programm for measurement data correction with reader and
 * correction classes.
 * \author Lehmann
 * \date 2013-12-03
 *
 */
int main(int argc, char** argv) {
    volatile CorrectorTestSuite t; // run all tests
    
    DataReader sensordata; // container for sensor data
    sensordata.readDataFrom("data.txt");    // path might be changed
    
    // linear correction
    CorrectorLinear linear(2, 3);
    sensordata.setDataCorrection(&linear);
    sensordata.writeCorrectedDataToFile("corrected_linear.txt");  // path might be changed
    
    // lookup-table correction
    double x[5] = {-2.0, -1.5, -1.75, -1.0, -1.25};
    double y[5] = {-1.0,  0.0, -0.8,   1.0,  0.8,};
    CorrectorLookupTable lookup(x, y);
    sensordata.setDataCorrection(&lookup);
    sensordata.writeCorrectedDataToFile("corrected_lookup.txt"); // path might be changed
    
    return 0;
}
