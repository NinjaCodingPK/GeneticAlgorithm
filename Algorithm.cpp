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
/*
 * _minX - lower border.
 * _maxX - upper border.
 */
Algorithm::Algorithm(double _minX, double _maxX, double (Functions::*_f)(double x1, double x2)) {
    maxX = _maxX;
    minX = _minX;
    f = _f;
}

Algorithm::Algorithm(const Algorithm& orig) {
}

Algorithm::~Algorithm() {
}

void Algorithm::init() {
    double maxRandom = maxX + abs(minX);
    for(int i = 0; i < this->POPULATION_SIZE; i++) {
        ga_struct ga = {.x1 = maxRandom * (rand()/(RAND_MAX + 1.0)) - abs(minX), 
                        .x2 = maxRandom * (rand()/(RAND_MAX + 1.0)) - abs(minX),
                        .fitness = 0};
        this->population.push_back(ga);
    }
}

void Algorithm::print_population() {
    for(int i = 0; i < 10; i++) {
        std::cout << population[i].x1 << ", " << population[i].x2 << ", " << population[i].fitness << "\n";
    }
}

//void Algorithm::set_fitness(int i, double (Functions::*f)(double x1, double x2)) {
//    Functions func =  Functions();
//    population[i].fitness = (func.*f)(population[i].x1, population[i].x2);
//    //population[i].fitness = some_func(population[i].x1, population[i].x2);
//}

void Algorithm::calc_fitness() {
    Functions func =  Functions();
    
    for(int i = 0; i < population.size(); i++) {
        //this->set_fitness(i, &Functions::myfunc);
        population[i].fitness = (func.*f)(population[i].x1, population[i].x2);
    }
}

//double Algorithm::sum_fitness() {
//    double sum = 0;
//    for(int i = 0; i < population.size(); i++) {
//        sum += 1/population[i].fitness;
//    }
//}

std::vector<Algorithm::ga_struct> Algorithm::tournamentMax() {
    std::vector<ga_struct> buff;
    ga_struct tour[TOURNAMENT_SIZE];
    
    for(int i = 0; i < POPULATION_SIZE; i++) {
        for(int j = 0; j < TOURNAMENT_SIZE; j++) { //making a single tour
            //choosing randomly through the whole population
            tour[j] = this->population[(int)(POPULATION_SIZE * (rand()/(RAND_MAX + 1.0)))]; 
        }
        
        buff.push_back(getMax(tour)); //finding the best match in a tour (min or max)
    }
    
    return buff;
}

std::vector<Algorithm::ga_struct> Algorithm::tournamentMin() {
    std::vector<ga_struct> buff;
    ga_struct tour[TOURNAMENT_SIZE];
    
    for(int i = 0; i < POPULATION_SIZE; i++) {
        for(int j = 0; j < TOURNAMENT_SIZE; j++) { //making a single tour
            //choosing randomly through the whole population
            tour[j] = this->population[(int)(POPULATION_SIZE * (rand()/(RAND_MAX + 1.0)))]; 
        }
        
        buff.push_back(getMin(tour)); //finding the best match in a tour (min or max)
    }
    
    return buff;
}

Algorithm::ga_struct Algorithm::getMax(Algorithm::ga_struct tour[TOURNAMENT_SIZE]) {
    double maxFitness = tour[0].fitness;
    ga_struct max = tour[0];
    
    for(int i = 0; i < TOURNAMENT_SIZE; i++) 
        if(tour[i].fitness > maxFitness) {
            maxFitness = tour[i].fitness;
            max = tour[i];
        }
    
    return max;
}

Algorithm::ga_struct Algorithm::getMax() {
    double maxFitness = population[0].fitness;
    ga_struct max = population[0];
    
    for(int i = 0; i < POPULATION_SIZE; i++) 
        if(population[i].fitness > maxFitness) {
            maxFitness = population[i].fitness;
            max = population[i];
        }
    
    return max;
}

Algorithm::ga_struct Algorithm::getMin(Algorithm::ga_struct tour[TOURNAMENT_SIZE]) {
    double minFitness = tour[0].fitness;
    ga_struct min = tour[0];
    
    for(int i = 0; i < TOURNAMENT_SIZE; i++) 
        if(tour[i].fitness < minFitness) {
            minFitness = tour[i].fitness;
            min = tour[i];
        }
    
    return min;
}

Algorithm::ga_struct Algorithm::getMin() {
    double minFitness = population[0].fitness;
    ga_struct min = population[0];
    
    for(int i = 0; i < TOURNAMENT_SIZE; i++) 
        if(population[i].fitness < minFitness) {
            minFitness = population[i].fitness;
            min = population[i];
        }
    
    return min;
}

void Algorithm::newGenerationForm(std::vector<Algorithm::ga_struct> parents) {
    unsigned int dad, mom;
    for(int i = 0; i < POPULATION_SIZE; i++) {
        dad = (int)(POPULATION_SIZE * (rand()/(RAND_MAX + 1.0))); //random index from parents 
        mom = (int)(POPULATION_SIZE * (rand()/(RAND_MAX + 1.0))); //random index from parents
        
        population[i] = crossover(parents[dad], parents[mom]);
    }
}

Algorithm::ga_struct Algorithm::crossover(ga_struct dad, ga_struct mom) {
    int t1 = 0; //point 1 for dad
    int t2 = -1; //point 2 for mom
    ga_struct son;
    
    while(t1 >= t2) { //point1 should be less than point2
        t1 = (int)(2 * (rand()/(RAND_MAX + 1.0)) - 1);  //point 1 can get value 0 or 1.
        t2 = (int)(3 * (rand()/(RAND_MAX + 1.0)) - 1);  //point 1 can get value 1 or 2.
    }
    //std::cout << "points: " << t1 << ", " << t2 << std::endl;
    switch(t1) {
        case 0: 
           son.x1 = mom.x1;
           son.x2 = mom.x2;
           break;
        case 1:   
           son.x1 = dad.x1;
           son.x2 = mom.x2;
           break;
    }
    
    return son;
}

void Algorithm::findMax() {
    init();
    calc_fitness();
    std::cout << "pop 1 :" << std::endl;
    print_population();
    
    for(int i = 0; i < MAX_ITERATIONS; i ++) {
        newGenerationForm(tournamentMax());
        calc_fitness();
    }
    
    //std::cout << "pop last :" << std::endl;
    //print_population();
//    newGenerationForm(tournament());
//    calc_fitness();
//    std::cout << "pop 2 :" << std::endl;
//    print_population();
//    
//    newGenerationForm(tournament());
//    calc_fitness();
//    std::cout << "pop 3 :" << std::endl;
//    print_population();
//    
//    newGenerationForm(tournament());
//    calc_fitness();
//    std::cout << "pop 4 :" << std::endl;
//    print_population();
}

void Algorithm::findMin() {
    init();
    calc_fitness();
    std::cout << "pop 1 :" << std::endl;
    print_population();
    
    for(int i = 0; i < MAX_ITERATIONS; i ++) {
        newGenerationForm(tournamentMin());
        calc_fitness();
    }
    
}

void Algorithm::printMax() {
    Functions func = Functions();
    ga_struct max = getMax();
    
    std::cout << "X1: " << round(max.x1) << std::endl;
    std::cout << "X2: " << round(max.x2) << std::endl;
    std::cout << "Extremum: " << (func.*f)(round(max.x1), round(max.x2)) << std::endl;
}

void Algorithm::printMin() {
    Functions func = Functions();
    ga_struct min = getMin();
    
    std::cout << "X1: " << round(min.x1) << std::endl;
    std::cout << "X2: " << round(min.x2) << std::endl;
    std::cout << "Extremum: " << (func.*f)(round(min.x1), round(min.x2)) << std::endl;
}