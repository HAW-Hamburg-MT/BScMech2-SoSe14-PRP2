//
//  CorrectorLookupTable.h
//  BScMech2-SoSe14-PRP2
//
//  Created by Jannik Beyerstedt on 31.05.14.
//  Copyright (c) 2014 Jannik Beyerstedt. All rights reserved.
//

#ifndef __BScMech2_SoSe14_PRP2__CorrectorLookupTable__
#define __BScMech2_SoSe14_PRP2__CorrectorLookupTable__


#include <iostream>
using namespace std;
#include "Corrector.h"


#define LOOKUPTABLE_MAX 5


/*
 * class CorrectorLookupTable
 * correction by lookup table, 5 reference points, linear interpolation
 */
class CorrectorLookupTable : public Corrector{
    double xValues[LOOKUPTABLE_MAX];
    double yValues[LOOKUPTABLE_MAX];
        
public:
    
    // costrcutor: saves reference points and sorts them
    CorrectorLookupTable (double x[LOOKUPTABLE_MAX] , double y[LOOKUPTABLE_MAX] );
    
    // returns corrected value, uses calculate and chooses parameters
    virtual double correctValue(double value);
private:
    
    // calculates value by linear inter- and extrapolation
    double calculate(double value, double x1, double y1, double x2, double y2);
    
    // swaps it´s two parameters (call-by-Reference)
    void swap(double& x, double& y);
    
    // sorts reference points by increasing x-values, uses swap
    void sortTable();
};

#endif /* defined(__BScMech2_SoSe14_PRP2__CorrectorLookupTable__) */
