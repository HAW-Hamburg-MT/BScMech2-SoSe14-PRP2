//
//  CorrectorLinear.h
//  BScMech2-SoSe14-PRP2
//
//  Created by Jannik Beyerstedt on 31.05.14.
//  Copyright (c) 2014 Jannik Beyerstedt. All rights reserved.
//

#ifndef __BScMech2_SoSe14_PRP2__CorrectorLinear__
#define __BScMech2_SoSe14_PRP2__CorrectorLinear__


#include <iostream>
using namespace std;
#include "Corrector.h"


/*
 * class Corrector Linear
 * performs a linear correction for a given value
 * values: gradient a, offset b
 */
class CorrectorLinear : public Corrector {
    double a, b;
    
public:
    CorrectorLinear();                  // sets: a=1, b=0
    CorrectorLinear(double a, double b);// sets Values for a, b
    virtual double correctValue(double value);  // corrects the value: y = a*x+b
};

#endif /* defined(__BScMech2_SoSe14_PRP2__CorrectorLinear__) */
