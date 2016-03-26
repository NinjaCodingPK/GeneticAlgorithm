/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Functions.cpp
 * Author: wookie
 * 
 * Created on March 25, 2016, 8:02 PM
 */

#include "Functions.h"

Functions::Functions() {
}

Functions::Functions(const Functions& orig) {
}

Functions::~Functions() {
}

double Functions::myfunc(double x1, double x2) {
    return x1 + x2;
}

double Functions::deJong(double x1, double x2) {
    return (3905.93) - 100*pow((x1*x1 - x2), 2) - pow((1 - x1), 2);
}

double Functions::martin_gaddy(double x1, double x2) {
    return pow((x1 - x2), 2) + pow(((x1+x2-10)/3), 2);
}
