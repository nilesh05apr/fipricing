#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <future>
#include <ctime>
#include <limits>
#include <random>
#include "Paytype.h"


#ifndef MONTECARLO_H
#define MONTECARLO_H

class MonteCarlo {
    private:
    int timeperiod;                // days
    double volatility;             // volatility
    double initPrice;              // initial price of derivative (spot price)
    double rate;                   // expected return rate
    int n_samples;
    double seed = time(nullptr);
    double strike;                  // strike price of derivative
    Paytype ptype;                  //'Payoff type call or put'

    public:

    std::vector<std::vector<double>> paths;
    std::vector <double> seeds;

    MonteCarlo(int time, double vol, double spot, double rate, double strike, Paytype pt_, int n_samples);
    double stdNormalGeneration(double seed);
    double calc(double initPrice, double seed);
    double payoffPrice(double terminalPrice, double strikPrice);
    double getOptionPrice();



};

#endif