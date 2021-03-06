/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Algorithm.h
 * Author: wookie
 *
 * Created on March 25, 2016, 2:16 PM
 */

#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <iostream>			// for cout etc.
#include <vector>			// for vector class
#include <string>		     // for string class
#include <algorithm>		     // for sort algorithm
#include <time.h>			// for random seed
#include <math.h>			// for abs()

#include "Functions.h"

class Algorithm {
public:
    Algorithm(double, double, int _pcount, double (Functions::*_f)(std::vector<double> x));
    Algorithm(const Algorithm& orig);
    virtual ~Algorithm();
    
    struct ga_struct {
	std::vector<double> x;
	double fitness;		
    };
    
    void init();
    void print_population();
    void calc_fitness();
    //void set_fitness(int i, double (Functions::*f)(double, double));
    //double sum_fitness(); //return sum of reverse values of _fitness_
    
    void findMax(); //find max extremum
    void findMin(); //find min extremum
    void printMax();
    void printMin();
    
private:
    double (Functions::*f)(std::vector<double> x); // function 
    int pcount; // count of parameters in function
    static const int POPULATION_SIZE = 2048;
    static const int MAX_ITERATIONS = 2000; // 16384;
    static const double ELITE_RATE = 0.10f;
    static const double MUTATION_RATE = 0.1f;		
    const double MUTATION = RAND_MAX * MUTATION_RATE;
    static const int TOURNAMENT_SIZE = 100;
    double maxX, minX; // upper and lower borders
    std::vector<ga_struct> population; 

    std::vector<ga_struct> tournamentMax(); // Tournament selection for max extremum
    std::vector<ga_struct> tournamentMin(); // Tournament selection for min extremum
    ga_struct getMax(ga_struct tour[TOURNAMENT_SIZE]); // find max fitness through tour (for max extremum)
    ga_struct getMin(ga_struct tour[TOURNAMENT_SIZE]); // find min fitness through tour (for min extremum)
    ga_struct getMax(); // find max fitness through population (for max extremum)
    ga_struct getMin(); // find min fitness through population (for min extremum)
    
    ga_struct crossover(ga_struct origin, ga_struct, ga_struct); // Two-point crossover
    void newGenerationForm(std::vector<Algorithm::ga_struct>); // parents - winners of a tournament 
    void mutation(); // Random mutation
    std::vector<ga_struct> elitism(); // Returns vector of elite individuals which will appear in next generation
    
    double getAverageFitness(); // find average fitness through the whole population
    std::vector<double> roundResult(std::vector<double>);
};

#endif /* ALGORITHM_H */

