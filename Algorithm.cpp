/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Algorithm.cpp
 * Author: wookie
 * 
 * Created on March 25, 2016, 2:16 PM
 */

#include "Algorithm.h"

Algorithm::Algorithm() {
}

Algorithm::Algorithm(const Algorithm& orig) {
}

Algorithm::~Algorithm() {
}

void Algorithm::init() {
    for(int i = 0; i < this->POPULATION_SIZE; i++) {
        ga_struct ga = {.x1 = (double)rand() / RAND_MAX, 
                        .x2 = (double)rand() / RAND_MAX,
                        .fitness = 0};
        this->population.push_back(ga);
    }
}

void Algorithm::print_population() {
    for(int i = 0; i < 10; i++) {
        std::cout << population[i].x1 << ", " << population[i].x2 << ", " << population[i].fitness << "\n";
    }
}

double Algorithm::some_func(double x1, double x2) {
    return x1 + x2;
}

void Algorithm::set_fitness(int i, double (Functions::*f)(double x1, double x2)) {
    Functions func =  Functions();
    population[i].fitness = (func.*f)(population[i].x1, population[i].x2);
    //population[i].fitness = some_func(population[i].x1, population[i].x2);
}

void Algorithm::calc_fitness() {
    
    for(int i = 0; i < population.size(); i++) {
        this->set_fitness(i, &Functions::myfunc);
    }
}

double Algorithm::sum_fitness() {
    double sum = 0;
    for(int i = 0; i < population.size(); i++) {
        sum += 1/population[i].fitness;
    }
}