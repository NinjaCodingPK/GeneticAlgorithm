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
    
    std::cout << "DeJong" << std::endl;
    Algorithm alg1 = Algorithm(-2.048, 2.048, 2, &Functions::deJong);
    alg1.findMax();
    alg1.printMax();
    
    std::cout << std::endl << "Martin Gabby" << std::endl;
    Algorithm alg2 = Algorithm(0, 10, 2, &Functions::martin_gaddy);
    alg2.findMin();
    alg2.printMin();
 
    std::cout << std::endl << "Rosenbrock 1a" << std::endl;
    Algorithm alg3 = Algorithm(-1.2, 1.2, 2, &Functions::rosenbrock1);
    alg3.findMin();
    alg3.printMin();
    
    std::cout << std::endl << "Rosenbrock 1b" << std::endl;
    Algorithm alg4 = Algorithm(-10, 10, 2, &Functions::rosenbrock1);
    alg4.findMin();
    alg4.printMin();

    std::cout << std::endl << "Rosenbrock 2" << std::endl;
    Algorithm alg5 = Algorithm(-1.2, 1.2, 4, &Functions::rosenbrock1);
    alg5.findMin();
    alg5.printMin();    
    
    std::cout << std::endl << "Hyper sphere" << std::endl;
    Algorithm alg6 = Algorithm(-5.12, 5.12, 6, &Functions::hyper_sphere);
    alg6.findMin();
    alg6.printMin();

//    std::cout << "Griewangk" << std::endl;
//    Algorithm alg7 = Algorithm(-512, 512, 10, &Functions::griewangk);
//    alg7.findMax();
//    alg7.printMax();      
    
//    std::cout << "Griewangk" << std::endl;
//    Algorithm alg6 = Algorithm(-512, 512, 10, &Functions::griewangk);
//    alg6.findMin();
//    alg6.printMin();
    
    return 0;
}

