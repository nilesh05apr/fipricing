#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <future>
#include <ctime>
#include <limits>
#include <random>
#include "MonteCarlo.h"
#include "Paytype.h"


using namespace std;
using std::normal_distribution;
using std::mt19937_64;

MonteCarlo::MonteCarlo(int time, double vol, double spot, double rate, double strike, Paytype pt_, int n_samples) {

                        this->timeperiod = time;
                        this->volatility = vol;
                        this->initPrice = spot;
                        this->rate = rate;
                        this->strike = strike;
                        this->n_samples = n_samples;
                        this->ptype = pt_;
                        this->paths.resize(this->n_samples, vector<double>(this->timeperiod,this->initPrice));
                        this->seeds.reserve(this->n_samples);
                        std::iota(this->seeds.begin(),this->seeds.end(),this->stdNormalGeneration(this->seed));

}


double MonteCarlo::stdNormalGeneration(double seed) {
        mt19937_64 mtre(seed);
        normal_distribution<> stnd;
        return stnd(mtre);
}


double MonteCarlo::calc(double initPrice, double seed) {
        double epsilon =  stdNormalGeneration(seed);
        double param_1 = this->rate - ((this->volatility * this->volatility) / 2);
        double param_2 = this->volatility * sqrt(this->timeperiod) * epsilon;
        return initPrice * exp(param_1*this->timeperiod + param_2);
}

double MonteCarlo::payoffPrice(double terminalPrice, double strikPrice) {
        switch(this->ptype){
            case Paytype::CALL: return std::max(terminalPrice - strikPrice, 0.0); break;
            case Paytype::PUT: return std::max(strikPrice - terminalPrice, 0.0); break;
            default: return 0.0; break;
        }
}

double MonteCarlo::getOptionPrice() {
    for(int i = 0; i < n_samples; i++){
        for(int j = 1; j < timeperiod; j++){
            this->paths[i][j] = calc(this->paths[i][j-1], this->seeds[i]);
        }
    }
    vector<double> finalPrices(this->n_samples);
    for(auto x: paths){
        finalPrices.push_back(payoffPrice(x.back(), this->strike));
    }
    return std::accumulate(finalPrices.begin(), finalPrices.end(), 0.0) / (double)this->n_samples; 
}
