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

double Functions::myfunc(std::vector<double> x) {
    return x[0] + x[1];
}

double Functions::deJong(std::vector<double> x) {
    return (3905.93) - 100*pow((x[0]*x[0] - x[1]), 2) - pow((1 - x[0]), 2);
}

double Functions::martin_gaddy(std::vector<double> x) {
    return pow((x[0] - x[1]), 2) + pow(((x[0]+x[1]-10)/3), 2);
}

double Functions::hyper_sphere(std::vector<double> x) {
    double sum = 0;
    for(int i = 0; i < 6; i++) {
        sum += x[i]*x[i];
    }
    return sum;
}

double Functions::rosenbrock1(std::vector<double> x) {
    return 100*pow((x[0]*x[0] - x[1]), 2) + pow((1 - x[0]), 2);
}

double Functions::rosenbrock2(std::vector<double> x) {
    double sum = 0;
    
    for(int i = 0; i < 3; i)
        sum += 100*pow((x[i]*x[i] - x[i+1]), 2) + pow((1 - x[i]), 2);
    
    return sum; 
}

double Functions::griewangk(std::vector<double> x) {
    double sum = 0;
    double mult = 1;
    
    for(int i = 0; i < 10; i++) {
        sum += x[i]*x[i]/4000;
        mult *= cos(x[i]/sqrt(i+1));
    }
    
    return 1/(0.1 + sum - mult + 1);
}

//double Functions::griewangk(std::vector<double> x) {
//    double sum = 0;
//    double mult = 1;
//    
//    for(int i = 0; i < 10; i++) {
//        sum += x[i]*x[i]/4000;
//        mult *= cos(x[i]/sqrt(i+1));
//    }
//    
//    return mult;
//}