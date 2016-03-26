/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Functions.h
 * Author: wookie
 *
 * Created on March 25, 2016, 8:02 PM
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <math.h>

class Functions {
public:
    Functions();
    Functions(const Functions& orig);
    virtual ~Functions();
    
    double myfunc(double x1, double x2);
    double deJong(double x1, double x2);
    double martin_gaddy(double x1, double x2);
private:

};

#endif /* FUNCTIONS_H */

