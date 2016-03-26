/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: wookie
 *
 * Created on March 25, 2016, 2:15 PM
 */

#include <cstdlib>
#include "Algorithm.h"
#include "Functions.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
//    Algorithm alg1 = Algorithm(-2, 2, &Functions::myfunc);
//    alg1.resolve();
//    alg1.print_max();
    
//    Algorithm alg1 = Algorithm(-2.048, 2.048, 2, &Functions::deJong);
//    alg1.findMax();
//    alg1.printMax();
    
//    Algorithm alg2 = Algorithm(0, 10, 2, &Functions::martin_gaddy);
//    alg2.findMin();
//    alg2.printMin();
 
    Algorithm alg2 = Algorithm(-5.12, 5.12, 6, &Functions::hyper_sphere);
    alg2.findMin();
    alg2.printMin();    
    
    return 0;
}

