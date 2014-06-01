//
//  DataReader.h
//  BScMech2-SoSe14-PRP2
//
//  Created by Jannik Beyerstedt on 31.05.14.
//  Copyright (c) 2014 Jannik Beyerstedt. All rights reserved.
//

#ifndef __BScMech2_SoSe14_PRP2__DataReader__
#define __BScMech2_SoSe14_PRP2__DataReader__


#include <iostream>
using namespace std;
#include "Corrector.h"

#define MAX_DATA 200


/*
 * class DataReader
 * reads sensor data from input file to dynamic array
 * corrects data at writing to output file
 */
class DataReader {
    double *rawData = NULL;
    Corrector *ptrCorrector = NULL;
public:
    DataReader();
    
    // Der Destruktor soll ein ggf. dynamisch allokiertes Array freigeben.
    ~DataReader();
    
    // reads data to dynamic allocated array, uses array if there is already one
    void readDataFrom(char const* FileName);
    
    // chooses correction method
    void setDataCorrection (Corrector *corrector);
    
    // corrects values ad writes to output file
    void writeCorrectedDataToFile (const char* FileName);
};


#endif /* defined(__BScMech2_SoSe14_PRP2__DataReader__) */
