//
//  DataReader.cpp
//  BScMech2-SoSe14-PRP2
//
//  Created by Jannik Beyerstedt on 31.05.14.
//  Copyright (c) 2014 Jannik Beyerstedt. All rights reserved.
//


#include "DataReader.h"
#include <fstream>


DataReader::DataReader () {
    
} // SOMETHING TO DO HERE ???


DataReader::~DataReader() {
    if (rawData != NULL) {
        delete [] rawData;
    }else {
        cout << "INFO: DataReader::~DataReader - no data to free" << endl;
    }
}// DONE


void DataReader::readDataFrom(const char *FileName) {
    if (rawData == NULL) {
        rawData = (double *) calloc(MAX_DATA, sizeof(*rawData));
    }else {
        cout << "INFO: DataReader::readDataFrom - rawData already read" << endl;
    }
    
    ifstream rawInput(FileName);
    for (int i = 0; i < MAX_DATA; i++) {
        rawInput >> rawData[i];
    }
    
    rawInput.close();
}// DONE


void DataReader::setDataCorrection(Corrector *corrector) {
    ptrCorrector = corrector;
}// DONE


void DataReader::writeCorrectedDataToFile(const char* FileName) {
    ofstream outputFile(FileName);
    
    if (rawData != NULL && ptrCorrector != NULL) {
        for (int i = 0; i < MAX_DATA; i++) {
            outputFile << ptrCorrector->correctValue(rawData[i]) << endl;
        }
    }else {
        cerr << "ERROR: DataReader::writeCorrectedDataToFile - NULL pointer found" << endl;
    }
    outputFile.close();
}// DONE

