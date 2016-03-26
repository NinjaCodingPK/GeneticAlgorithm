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
    Algorithm al = Algorithm(-2, 2, &Functions::myfunc);
    al.resolve();
    al.print_max();
    return 0;
}

