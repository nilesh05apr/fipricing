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



enum Paytype {
    CALL,
    PUT
};


class MonteCarloPricing{
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

    vector<vector<double>> paths;
    vector <double> seeds;

    MonteCarloPricing(int time, 
                    double vol, 
                    double spot, 
                    double rate, 
                    double strike, 
                    Paytype pt_, 
                    int n_samples=5000){
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
    
    double stdNormalGeneration(double seed){
        mt19937_64 mtre(seed);
        normal_distribution<> stnd;
        return stnd(mtre);
    } 

    double montecarlo(double initPrice, double seed){
        double epsilon =  stdNormalGeneration(seed);
        double param_1 = this->rate - ((this->volatility * this->volatility) / 2);
        double param_2 = this->volatility * sqrt(this->timeperiod) * epsilon;
        return initPrice * exp(param_1*this->timeperiod + param_2);
    }

    double payoffPrice(double terminalPrice, double strikPrice){
        switch(this->ptype){
            case CALL: return std::max(terminalPrice - strikPrice, 0.0); break;
            case PUT: return std::max(strikPrice - terminalPrice, 0.0); break;
            default: return 0.0; break;
        }
    }


    double getOptionPrice(){
        for(int i = 0; i < n_samples; i++){
            for(int j = 1; j < timeperiod; j++){
                this->paths[i][j] = montecarlo(this->paths[i][j-1], this->seeds[i]);
            }
        }
        vector<double> finalPrices(this->n_samples);
        for(auto x: paths){
            finalPrices.push_back(payoffPrice(x.back(), this->strike));
        }
        return std::accumulate(finalPrices.begin(), finalPrices.end(), 0.0) / (double)this->n_samples; 
    }
};


















int main()
{
    int timeperiod = 30;                    //30 days
    double volatility = 0.02;               //2% volatility
    double initPrice = 600.0;               // initial price of derivative (spot price)
    double rate = 0.06;                     //6% expected return rate
    int n_samples = 1;
    double seed = time(nullptr);
    double strike = 650.0;                  // strike price of derivative
    Paytype pt = CALL;                      //'Payoff type call or put'

    MonteCarloPricing mcp = MonteCarloPricing(timeperiod,volatility,initPrice,rate,strike,pt,n_samples);
    // cout<<mcp.stdNormalGeneration(time(nullptr))<<endl;
    // cout<<mcp.montecarlo(1000.0,time(nullptr))<<endl;
    cout<<mcp.getOptionPrice()<<endl;

    for(auto x: mcp.seeds){
        cout<<x<<" ";
    }

    return 0;
}
