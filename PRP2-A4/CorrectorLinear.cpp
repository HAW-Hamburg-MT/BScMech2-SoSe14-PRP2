//
//  CorrectorLinear.cpp
//  BScMech2-SoSe14-PRP2
//
//  Created by Jannik Beyerstedt on 31.05.14.
//  Copyright (c) 2014 Jannik Beyerstedt. All rights reserved.
//


#include "CorrectorLinear.h"


CorrectorLinear::CorrectorLinear() {
    a = 1;
    b = 0;
    cout << "INFO: here is: CorrectorLinear constructor (void)" << endl;
    
}// DONE


CorrectorLinear::CorrectorLinear(double aSet, double bSet) {
    a = aSet;
    b = bSet;
    cout << "INFO: here is: CorrectorLinear constructor (set)" << endl;
    
}// DONE


double CorrectorLinear::correctValue(double value) {
    return a*value+b;
    
}// DONE
