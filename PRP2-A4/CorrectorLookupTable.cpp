//
//  CorrectorLookupTable.cpp
//  BScMech2-SoSe14-PRP2
//
//  Created by Jannik Beyerstedt on 31.05.14.
//  Copyright (c) 2014 Jannik Beyerstedt. All rights reserved.
//


#include "CorrectorLookupTable.h"


CorrectorLookupTable::CorrectorLookupTable (double x[LOOKUPTABLE_MAX] , double y[LOOKUPTABLE_MAX]) {
    
    for (int i = 0; i < LOOKUPTABLE_MAX; i++) {
        xValues[i] = x[i];
        yValues[i] = y[i];
    }
    cout << "INFO: CorrectorLookupTable::CorrectorLookupTable - table copied" << endl;
    
    sortTable();
    
}// DONE


double CorrectorLookupTable::correctValue(double value) {
    double x1 = 0;
    double y1 = 0;
    double x2 = 0;
    double y2 = 0;
    
    if (value <= xValues[0]) {   // smaller than smallest x
        x1 = xValues[0];
        y1 = yValues[0];
        x2 = xValues[1];
        y2 = yValues[1];
        cout << "INFO: correctValue - small value" << endl;
    }else if (value >= xValues[LOOKUPTABLE_MAX-1]) { // higher than highest x
        x1 = xValues[LOOKUPTABLE_MAX-2];
        y1 = yValues[LOOKUPTABLE_MAX-2];
        x2 = xValues[LOOKUPTABLE_MAX-1];
        y2 = yValues[LOOKUPTABLE_MAX-1];
        cout << "INFO: correctValue - high value" << endl;
    }else {
        for (int i = 1; i < (LOOKUPTABLE_MAX); i++) { // everything between
            if (value < xValues[i]) {
                x1 = xValues[i-1];
                y1 = yValues[i-1];
                x2 = xValues[i];
                y2 = yValues[i];
                cout << "INFO: correctValue - interval " << i << " - " << (i+1) << endl;
                break;
            }
        }
    }
    
    return CorrectorLookupTable::calculate(value, x1, y1, x2, y2);

}// DONE


double CorrectorLookupTable::calculate(double value, double x1, double y1, double x2, double y2) {
    
    double a = (y2-y1) / (x2-x1);
    
    return a*(value-x1)+y1;
}// DONE


void CorrectorLookupTable::swap(double& x, double& y) {
    double temp;
    
    temp = x;
    x = y;
    y = temp;
    
}// DONE


void CorrectorLookupTable::sortTable() {
    int swapsDone;
    
    do {
        swapsDone = 0;
        
        for (int i = 0; i < (LOOKUPTABLE_MAX-1); i++) {
            if (xValues[i] > xValues[i+1]) {
                CorrectorLookupTable::swap(xValues[i], xValues[i+1]);
                CorrectorLookupTable::swap(yValues[i], yValues[i+1]);
                
                swapsDone++;
            }
        }
        
    } while (swapsDone > 0);
    
    cout << "INFO: sortTable - table sorted" << endl;
    
}// DONE
