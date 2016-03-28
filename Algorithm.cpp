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
Algorithm::Algorithm(double _minX, double _maxX, int _pcount, double (Functions::*_f)(std::vector<double> x)) {
    maxX = _maxX;
    minX = _minX;
    f = _f;
    pcount = _pcount;
}

Algorithm::Algorithm(const Algorithm& orig) {
}

Algorithm::~Algorithm() {
}

void Algorithm::init() {
    double maxRandom = maxX + abs(minX);
    std::vector<double> parameters;
    for(int i = 0; i < this->POPULATION_SIZE; i++) {
        for(int j = 0; j < pcount; j++)
            parameters.push_back(maxRandom * (rand()/(RAND_MAX + 1.0)) - abs(minX));
        ga_struct ga = {.x = parameters, .fitness = 0};
        this->population.push_back(ga);
        parameters.clear();
    }
}

void Algorithm::print_population() {
    for(int i = 0; i < 10; i++) {
        std::cout << population[i].x[0] << ", " << population[i].x[1] << ", " << population[i].fitness << "\n";
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
        population[i].fitness = (func.*f)(population[i].x);
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

std::vector<Algorithm::ga_struct> Algorithm::elitism() {
    int randIndex;
    std::vector<Algorithm::ga_struct> buf;
    
    for(int i = 0; i < POPULATION_SIZE; i++) {
        if(random()/(RAND_MAX + 1.0) < ELITE_RATE) {
            randIndex = (int)(pcount * (rand()/(RAND_MAX + 1.0)));
            buf.push_back(population[randIndex]);
        }
            
    }
    
    return buf;
}

void Algorithm::newGenerationForm(std::vector<Algorithm::ga_struct> parents) {
    unsigned int dad, mom;
    ga_struct temp;
    int i = 0;
    
    //select elite individuals
//    std::vector<Algorithm::ga_struct> buf = elitism();
//    for(i; i < buf.size(); i++)
//        population[i] = buf[i];
        
    for(i; i < POPULATION_SIZE; i++) {
        dad = (int)(POPULATION_SIZE * (rand()/(RAND_MAX + 1.0))); //random index from parents 
        mom = (int)(POPULATION_SIZE * (rand()/(RAND_MAX + 1.0))); //random index from parents
        
        temp = population[i];
        population[i] = crossover(temp, parents[dad], parents[mom]);
    }
}

Algorithm::ga_struct Algorithm::crossover(ga_struct origin, ga_struct dad, ga_struct mom) { //NOT OKAY!
    int t1 = 0; //point 1 for dad
    int t2 = -1; //point 2 for mom
    std::vector<double> parameters;
    ga_struct son;
    
    while(t1 >= t2) { //point1 should be less than point2
        t1 = (int)(pcount * (rand()/(RAND_MAX + 1.0)));  
        t2 = (int)(pcount * (rand()/(RAND_MAX + 1.0)));  
    }
    //std::cout << "points: " << t1 << ", " << t2 << std::endl;
    for(int i = 0; i <= t1; i++)
        parameters.push_back(dad.x[i]);
    for(int i = t1+1; i <= t2; i++)
        parameters.push_back(mom.x[i]);
    for(int i = t2+1; i < pcount; i++)
        parameters.push_back(origin.x[i]);
    
    son.x = parameters;
    
    return son;
}

void Algorithm::findMax() {
    double originFitness, newFitness;
    int i = 0;
    init();
    calc_fitness();
    //std::cout << "pop 1 :" << std::endl;
   // print_population();
    
     do {
        originFitness = getAverageFitness();
        newGenerationForm(tournamentMax());
        mutation();
        calc_fitness();
        newFitness = getAverageFitness();
        
        i++;
        if(i >= POPULATION_SIZE)
            break;
    } while(newFitness > originFitness);
    //std::cout << "Iterations : " << i << std::endl;
//    for(int i = 0; i < MAX_ITERATIONS; i ++) {
//        newGenerationForm(tournamentMax());
//        //mutation();
//        calc_fitness();
//    }
    
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
    double originFitness, newFitness;
    int i = 0;
    init();
    calc_fitness();
    //std::cout << "pop 1 :" << std::endl;
    //print_population();
    
    do {
        originFitness = getAverageFitness();
        newGenerationForm(tournamentMin());
        mutation();
        calc_fitness();
        newFitness = getAverageFitness();
        
        i++;
        if(i >= POPULATION_SIZE)
            break;
    } while(newFitness < originFitness);
//    for(int i = 0; i < MAX_ITERATIONS; i ++) {
//        newGenerationForm(tournamentMin());
//        mutation();
//        calc_fitness();
//    }
    
}

void Algorithm::mutation() {
    int randIndex;
    for(int i = 0; i < POPULATION_SIZE; i++) {
        if(random()/(RAND_MAX + 1.0) < MUTATION_RATE) {
            randIndex = (int)(pcount * (rand()/(RAND_MAX + 1.0)));
            population[i].x[randIndex] =  maxX + abs(minX) * (rand()/(RAND_MAX + 1.0)) - abs(minX);
        }
            
    }
}

double Algorithm::getAverageFitness() {
    double sum = 0;
    
    for(int i = 0; i < POPULATION_SIZE; i++)
        sum += population[i].fitness;
    
    return sum/POPULATION_SIZE;
}

std::vector<double> Algorithm::roundResult(std::vector<double> input) {
    std::vector<double> temp;
    
    for(int i = 0; i < input.size(); i++) {
        temp.push_back(round(input[i]));
    }
    
    return temp;
}

void Algorithm::printMax() {
    Functions func = Functions();
    ga_struct max = getMax();
    
    for(int i = 0; i < pcount; i++) {
        std::cout << "X" << i << ": " << max.x[i] << std::endl;
    }
    std::cout << "Extremum: " << (func.*f)(roundResult(max.x)) << std::endl;
}

void Algorithm::printMin() {
    Functions func = Functions();
    ga_struct min = getMin();
    
   for(int i = 0; i < pcount; i++) {
        std::cout << "X" << i << ": " << min.x[i] << std::endl;
    }
    std::cout << "Extremum: " << (func.*f)(roundResult(min.x)) << std::endl;
}