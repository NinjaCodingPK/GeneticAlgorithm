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
#include <vector>

class Functions {
public:
    Functions();
    Functions(const Functions& orig);
    virtual ~Functions();
    
    double myfunc(std::vector<double> x);
    double deJong(std::vector<double> x);
    double martin_gaddy(std::vector<double> x);
    double hyper_sphere(std::vector<double> x);
private:

};

#endif /* FUNCTIONS_H */

