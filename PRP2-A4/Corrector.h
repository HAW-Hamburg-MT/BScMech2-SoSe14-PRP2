//
//  Corrector.h
//  BScMech2-SoSe14-PRP2
//
//  Created by Jannik Beyerstedt on 31.05.14.
//  Copyright (c) 2014 Jannik Beyerstedt. All rights reserved.
//

#ifndef __BScMech2_SoSe14_PRP2__Corrector__
#define __BScMech2_SoSe14_PRP2__Corrector__


#include <iostream>
using namespace std;


/*
 * class Corrector
 * is base class for the two different corrections. Doesn´t change the value
 */
class Corrector {
public:
    virtual double correctValue (double value);     // should return unchanged value
};

#endif /* defined(__BScMech2_SoSe14_PRP2__Corrector__) */
