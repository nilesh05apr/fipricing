#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <future>
#include <ctime>
#include <limits>
#include <random>




using namespace std;
using std::normal_distribution;
using std::mt19937_64;




















double stdNormalGeneration(int seed)
{
    mt19937_64 mtre(seed);
    normal_distribution<> stnd;
    return stnd(mtre);
}

double montecarlo(double initPrice, double time, double returnRate, double volatility, double seed)
{
    double epsilon =  stdNormalGeneration(seed);
    double param_1 = returnRate - ((volatility * volatility) / 2);
    double param_2 = volatility * sqrt(time) * epsilon;
    return initPrice * exp(param_1*time + param_2);
}

enum Paytype {
        CALL,
        PUT    
        };

double payoffPrice(double terminalPrice, double strikPrice, Paytype pt)
{
    switch(pt)
    {
        case CALL: return std::max(terminalPrice - strikPrice, 0.0); break;
        case PUT: return std::max(strikPrice - terminalPrice, 0.0); break;
        default: return 0.0; break;
    }
    
}

double getOptionPrice(int n_samples, vector<vector<double>> paths, double strikePrice, Paytype pt)
{
    vector<double> finalPrices(n_samples);
    for(auto x: paths)
    {
        finalPrices.push_back(payoffPrice(x.back(), strikePrice, pt));
    }
    return std::accumulate(finalPrices.begin(), finalPrices.end(), 0.0) / (double)n_samples; 
}



int main()
{
    int timeperiod = 30; //30 days
    double volatility = 0.02; //2% volatility
    double initPrice = 600.0; // initial price of derivative (spot price)
    double rate = 0.06; //6% expected return rate
    int n_samples = 5;
    double seed = time(nullptr);
    double strike = 650.0; // strike price of derivative
    Paytype pt = CALL;  //'Payoff type call or put'

    vector <double> seeds(n_samples);
    std::iota(seeds.begin(), seeds.end(),stdNormalGeneration(seed));



    vector<vector<double>> paths(n_samples, vector<double>(timeperiod,600)); // initialise a 2d matrix with all values = 600
    

    for(int i = 0; i < n_samples; i++)
    {
        for(int j = 1; j < timeperiod; j++)
        {
            paths[i][j] = montecarlo(paths[i][j-1],(double)j/30.0, rate, volatility, seeds[i]);
        }
    }


    cout<<getOptionPrice(n_samples,paths,strike, pt)<<endl;







    return 0;
}
